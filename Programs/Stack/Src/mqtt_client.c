/**
******************************************************************************
* @file    main_mqtt.c
* @author  TI Team
*          HAW-Hamburg
*          Labor f�r technische Informatik
*          Berliner Tor  7
*          D-20099 Hamburg
* @version 1.0
*
* @date    17. Juli 2020
* @brief   Rahmen fuer C Programme, die auf dem ITSboard ausgefuehrt werden.
******************************************************************************
*/
/**
 * LED Descriptions:
 *
 * - LED 4 (GPIOD_PIN_4) - MQTT Session Task:
 *   This LED toggles whenever the `mqttSessionTask()` function is called.
 *   It indicates that the MQTT client is being initialized or updated when the
 * network is active.

 *
 * - LED 7 (GPIOD_PIN_7) - MQTT Publish Task:
 *   This LED toggles whenever the `mqttPublishTask()` function is called.
 *   It indicates that all pending MQTT messages are being published to the
 * broker.
 *
 * - LED 2 (GPIOD_PIN_2) - TIM2 IRQ Handler:
 *   This LED toggles whenever the `TIM2 IRQ Handler()` function is called and
 * we believe the main loop is running.
 */

#include <stdbool.h>
#include <string.h>
#include "netif/etharp.h"
#include "lwip/apps/mqtt.h"
#include "mqtt_client.h"
#include "led.h"


#define PUBLISH_ERROR_THRESHOLD 10

#define MQTT_RECONNECT_INTERVAL 100 // ms
#define MQTT_BROKER_IP "192.168.33.1"
#define MQTT_BROKER_PORT 1883
#define MQTT_CLIENT_ID "its-board-client"
#define MQTT_PUBLISH_TOPIC "/its-board/status/gioP"
#define MQTT_SUBSCRIBE_TOPIC "/its-board/status/gioS"
#define MQTT_QUEUE_SIZE 3

#define TIM2_INTERVAL 1000


// Simple Queue mgmnt
static volatile uint32_t publish_inflight = 0;
static mqtt_message_t mqtt_queue[MQTT_QUEUE_SIZE];
static int queue_head = 0;
static int queue_tail = 0;
static int queue_size = 0;

// Client info und setup
static char received_topic[64];
static struct mqtt_connect_client_info_t client_info;
static ip_addr_t broker_ipaddr;

typedef enum {
  MQTT_EVENT_NONE,
  MQTT_EVENT_CONNECTED,
  MQTT_EVENT_ACCEPTED,
  MQTT_EVENT_DISCONNECTED,
  MQTT_EVENT_PUBLISHED,
  MQTT_EVENT_DATA_RECEIVED,
  MQTT_EVENT_ERROR
} mqtt_event_t;
// Global variables for MQTT client state
static volatile mqtt_event_t mqtt_event = MQTT_EVENT_NONE;

typedef enum {
  Internal_error_no,
  Internal_error_connection_missed,
  Internal_error_GPIO_status_publish_failed,
  Internal_error_mqtt_sub_request_failed,
  Internal_error_mqtt_publish_request_failed,
  Internal_error_mqtt_connection_timeout
} internal_mqqtt_error_t;
static volatile internal_mqqtt_error_t internal_error = Internal_error_no;

typedef enum { LED_ACTION_NONE, LED_ACTION_SET, LED_ACTION_RESET } led_action_t;

//extern ETH_HandleTypeDef EthHandle;
// Global variables
struct netif gnetif;

// The Client
static mqtt_client_t *mqtt_client = NULL;

// @todo Perhaps I will use es session struct sometday
volatile bool client_running = true;
volatile bool initial = true;

// Function prototypes
static void check_network(void);
static void mqttSessionTask(void);
static void mqttPublishTask(void);
static void dhcpTask(void);
static void ethernetTask(void);
static void timeoutTask(void);

void mqtt_client_reinit(mqtt_client_t *mqtt_client);
void mqtt_client_update(mqtt_client_t *mqtt_client);

// Function prototypes for internal use
static void enqueue_message_isr(const char *topic, const char *data);
static mqtt_message_t *dequeue_message_main(void);

// callback functions for mqtt
static void mqtt_connection_cb(mqtt_client_t *mqtt_client, void *arg,
                               mqtt_connection_status_t status);
static void mqtt_sub_request_cb(void *arg, err_t result);
static void mqtt_publish_request_cb(void *arg, err_t result);
static void mqtt_incoming_publish_cb(void *arg, const char *topic,
                                     u32_t tot_len);
static void mqtt_incoming_data_cb(void *arg, const u8_t *data, u16_t len,
                                  u8_t flags);
static void handle_led_action(led_action_t led_action); 
static TIM_HandleTypeDef htim2;

/** 
* Interrupt handlers
*/ 
void TIM2_IRQHandler(void) {
  if (__HAL_TIM_GET_FLAG(&htim2, TIM_FLAG_UPDATE) != RESET &&
      __HAL_TIM_GET_IT_SOURCE(&htim2, TIM_IT_UPDATE) != RESET) {

    __HAL_TIM_CLEAR_IT(&htim2, TIM_IT_UPDATE);
    toggleGPIO(&led_pins[1]);
    check_mqtt_network();
   
  }
}

/**
 * @brief  Initialisiert den TIM2 als Verbindungstimer für MQTT.
 * @param  delay_ms: Verzögerung in Millisekunden.
 * @retval None
 */
void MQTT_ConnectTimer_Init() {
   uint32_t delay_ms = TIM2_INTERVAL; 
  // Konfiguration der NVIC-Priorität und Freigabe des IRQ
  HAL_NVIC_SetPriority(TIM2_IRQn, 5, 0);
  NVIC_EnableIRQ(TIM2_IRQn); // TIM2 Interrupt freischalten
  uint32_t timer_clock = HAL_RCC_GetPCLK1Freq();   

  // Wenn der APB1-Prescaler nicht 1 ist, wird der Timer-Takt verdoppelt
  if ((RCC->CFGR & RCC_CFGR_PPRE1) != RCC_CFGR_PPRE1_DIV1) {
    timer_clock *= 2;  // Timer-Takt ist doppelt so hoch wie PCLK1
  }
 // Aktivieren des TIM2 Clock
  __HAL_RCC_TIM2_CLK_ENABLE();
  // Berechne den Prescaler für 1 ms Takt (1 kHz)
  uint32_t prescaler = (timer_clock / 0.5) - 1;  // Why not double
  // Basis-Setup für TIM2
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = prescaler;   // TODO
  htim2.Init.Period = delay_ms - 1; // Verzögerung in ms
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  // Timer initialisieren
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK) {
    // Fehlerbehandlung falls Initialisierung fehlschlägt
  }
  HAL_TIM_Base_Start_IT(&htim2); // Timer starten und Interrupt aktivieren
}

bool check_mqtt_network(void) {
  if (client_running) {
    toggleGPIO(&led_pins[4]);
    return true;
  } else {
    if (!(netif_is_up(&gnetif) && netif_is_link_up(&gnetif))) {
      HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_1);
      return false;
    } else {
      HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_SET);

      initial = true;
      client_running = true;
    }
  }
  return true;
}

// Callback for MQTT connection status changes
static void mqtt_connection_cb(mqtt_client_t *mqtt_client, void *arg,
                               mqtt_connection_status_t status) {

  if (status == MQTT_CONNECT_TIMEOUT) {
    // Zeitüberschreitung beim Verbindungsaufbau
    internal_error = Internal_error_mqtt_connection_timeout;
    mqtt_event = MQTT_EVENT_ERROR;
    return;
  }

  mqtt_event = (status == MQTT_CONNECT_ACCEPTED) ? MQTT_EVENT_ACCEPTED
                                                 : MQTT_EVENT_DISCONNECTED;
}

// Callback for MQTT subscription requests
static void mqtt_sub_request_cb(void *arg, err_t result) {
  if (result != ERR_OK) {
    if (result == ERR_MEM) {
      toggleGPIO(&led_pins[5]); // Memmory error
    }
    internal_error = Internal_error_mqtt_sub_request_failed;
    mqtt_event = MQTT_EVENT_ERROR;
  }
}

// Callback for MQTT publish requests
static void mqtt_publish_request_cb(void *arg, err_t result) {
  struct pbuf *p = (struct pbuf *)arg;
  static uint16_t error_thresh = PUBLISH_ERROR_THRESHOLD;

  if (p != NULL) {
    (publish_inflight) ? publish_inflight-- : 0;
    //  pbuf_free(p);
  }
  if (result != ERR_OK) {
    if (result == ERR_MEM) {
      toggleGPIO(&led_pins[3]); // Memmory error
    }
    if (error_thresh--)
      return;

    internal_error = Internal_error_mqtt_publish_request_failed;
    mqtt_event = MQTT_EVENT_ERROR;
  }

  error_thresh = PUBLISH_ERROR_THRESHOLD;
}

// Publish the current GPIO status
static void publish_gpio_status() {
  static uint16_t error_thresh = PUBLISH_ERROR_THRESHOLD;

  // Read the current state of the LED GPIO
  GPIO_PinState gpio_status = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
  char status_msg[2];
  snprintf(status_msg, sizeof(status_msg), "%d", gpio_status);

  // Publish the GPIO status to the designated topic
  err_t err =
      mqtt_publish(mqtt_client, MQTT_PUBLISH_TOPIC, status_msg,
                   strlen(status_msg), 0, 0, mqtt_publish_request_cb, NULL);

  if (err != ERR_OK) {
    if (err == ERR_MEM) {
      toggleGPIO(&led_pins[3]); // Memmory error
    }

    if (error_thresh--)
      return;

    internal_error = Internal_error_GPIO_status_publish_failed;
    mqtt_event = MQTT_EVENT_ERROR;
  }
  error_thresh = PUBLISH_ERROR_THRESHOLD;
}

// Publish all relevant data (in this case, just the GPIO status)
void mqtt_pin_publish() {
  if (mqtt_client_is_connected(mqtt_client)) {
    publish_gpio_status();
  }
}

static void reinit(mqtt_client_t *mqtt_client) {
  if (mqtt_client_is_connected(mqtt_client)) {
    initial = false;
  }
  mqtt_disconnect(mqtt_client);
  while (!initial) { /* You can enter whenever you want, but you can never
                        leave, except the watchdog want to */
    HAL_Delay(10);
  }
  internal_error = Internal_error_no;
}

// Callback for incoming MQTT publish messages (topic)
static void mqtt_incoming_publish_cb(void *arg, const char *topic,
                                     u32_t tot_len) {
  // Store the received topic for later use
  strncpy(received_topic, topic, sizeof(received_topic) - 1);
  received_topic[sizeof(received_topic) - 1] = '\0';
}

// Callback for incoming MQTT publish messages (data)
static void mqtt_incoming_data_cb(void *arg, const u8_t *data, u16_t len,
                                  u8_t flags) {
  // Copy received data to a null-terminated buffer
  char received_data[128];
  strncpy(received_data, (const char *)data, len);
  received_data[len] = '\0';

  // Enqueue the received message
  enqueue_message_isr(
      received_topic,
      received_data); // It is called from an ISR, so it is safe to call the
                      // enqueue_message_isr function
  mqtt_event = MQTT_EVENT_DATA_RECEIVED;
}

void mqtt_client_init(mqtt_client_t *mqtt_client) {
  // Convert broker IP string to ip_addr_t
  ipaddr_aton(MQTT_BROKER_IP, &broker_ipaddr);

  // Set up client info
  memset(&client_info, 0, sizeof(client_info));
  client_info.client_id = MQTT_CLIENT_ID;
  client_info.keep_alive = 150;

  // Set callbacks for incoming publish and data
  mqtt_set_inpub_callback(mqtt_client, mqtt_incoming_publish_cb,
                          mqtt_incoming_data_cb, NULL);

  // Connect to the MQTT broker
  err_t err = mqtt_client_connect(mqtt_client, &broker_ipaddr, MQTT_BROKER_PORT,
                                  mqtt_connection_cb, NULL, &client_info);
  if (err != ERR_OK) {
    internal_error = Internal_error_connection_missed;
    mqtt_event = MQTT_EVENT_ERROR;
  }
}

///////////////////////////////////////////////////////////////////////////////
// Some baisc functions for the MQTT client

// Handle incoming MQTT messages and determine LED action
static led_action_t mqtt_handle_messages(void) {
  mqtt_message_t *message = dequeue_message_main();
  if (message != NULL) {
    if (strcmp(message->data, "Set") == 0) {
      return LED_ACTION_SET;
    } else if (strcmp(message->data, "Reset") == 0) {
      return LED_ACTION_RESET;
    }
  }
  return LED_ACTION_NONE;
}

// Main update function for the MQTT client
void mqtt_client_update(mqtt_client_t *mqtt_client) {
  led_action_t led_action = LED_ACTION_NONE;

  // Handle MQTT events
  if (mqtt_event != MQTT_EVENT_NONE) {
    switch (mqtt_event) {
    case MQTT_EVENT_ACCEPTED:
      // Subscribe to the designated topic when connection is accepted
      HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);
      mqtt_subscribe(mqtt_client, MQTT_SUBSCRIBE_TOPIC, 0, mqtt_sub_request_cb,
                     NULL);
      break;
    case MQTT_EVENT_DISCONNECTED:
      client_running = false;
      HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);
      // Reconnect to the MQTT broker if disconnected
      reinit(mqtt_client);

      break;
    case MQTT_EVENT_DATA_RECEIVED:
      // Process received messages and determine LED action
      led_action = mqtt_handle_messages();
      handle_led_action(led_action);
      break;
    case MQTT_EVENT_ERROR:
      // Handle error condition (implement error handling as needed)
      client_running = false;
      HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_SET);
      reinit(mqtt_client);

    default:
      break;
    }
    mqtt_event = MQTT_EVENT_NONE;
  }
}

void init_mqtt_subscriber(void) {
  if (check_mqtt_network()) {
    if (initial) {
      HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_RESET);
      initial = false;
      if (mqtt_client == NULL) {
        mqtt_client = mqtt_client_new();
      } else {
        if (mqtt_client_is_connected(mqtt_client)) {
          mqtt_disconnect(mqtt_client);
        }
      }
      mqtt_client_init(mqtt_client);
    }
    mqtt_client_update(mqtt_client);
  }
}
///////////////////////////////////////////////////////////////////////////////
// Helper function to handle received messages

// Add a message to the queue (interrupt-safe)
static void enqueue_message_isr(const char *topic, const char *data) {
  if (queue_size == MQTT_QUEUE_SIZE) {
    // If queue is full, overwrite the oldest message
    queue_head = (queue_head + 1) % MQTT_QUEUE_SIZE;
  } else {
    queue_size++;
  }

  // Copy topic and data to the queue, ensuring null-termination
  strncpy(mqtt_queue[queue_tail].topic, topic,
          sizeof(mqtt_queue[queue_tail].topic) - 1);
  strncpy(mqtt_queue[queue_tail].data, data,
          sizeof(mqtt_queue[queue_tail].data) - 1);
  mqtt_queue[queue_tail].topic[sizeof(mqtt_queue[queue_tail].topic) - 1] = '\0';
  mqtt_queue[queue_tail].data[sizeof(mqtt_queue[queue_tail].data) - 1] = '\0';

  queue_tail = (queue_tail + 1) % MQTT_QUEUE_SIZE;
}

// Remove and return a message from the queue
static mqtt_message_t *dequeue_message_main(void) {
  if (queue_size == 0) {
    return NULL;
  }

  mqtt_message_t *message = &mqtt_queue[queue_head];
  queue_head = (queue_head + 1) % MQTT_QUEUE_SIZE;
  queue_size--;

  return message;
}

// Perform the LED action (set or reset)
static void handle_led_action(led_action_t led_action) {
  if (led_action != LED_ACTION_NONE) {
    GPIO_PinState gpio_status =
        (led_action == LED_ACTION_SET) ? GPIO_PIN_SET : GPIO_PIN_RESET;
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, gpio_status);
  }
}