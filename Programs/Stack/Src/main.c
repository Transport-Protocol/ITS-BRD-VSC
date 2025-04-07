/**
 ******************************************************************************
 * @file    main.c
 * @author  Martin Becke
 * @brief   Kleines Testprogramm fuer lwip
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/


#include "LCD_GUI.h"
#include "lcd.h"
#include <stdint.h>
#include "lcd.h"
#include "led.h"
#include "lwip_interface.h"
#include "mqtt_client.h"

extern void initITSboard(void);

/* Definitionen */
#define TASK_COUNT 3
/* Enumeration für den Zustand der Statemaschine */
typedef enum { STATE_ETHERNET_FRAME_PULL, STATE_MQTT_SUBSCRIBE_SESSION, STATE_MQTT_PUBLISH_SESSION, STATE_IDLE } State_t;

/* Struktur für eine Task */
typedef struct {
  void (*taskFunction)(void); // Funktionspointer zur Task
  uint32_t nextExecutionTime; // Zeitpunkt für die nächste Ausführung
  uint32_t offset;            // Offset für die nächste Ausführung
  bool isEnabled;             // Aktivierungsflag
} Task_t;

/* Funktionsdeklarationen */
void TASK_ETHERNET_FRAME_PULL(void);
void TASK_MQTT_SUBSCRIBE_SESSION(void);
void TASK_MQTT_PUBLISH_SESSION(void);
void Scheduler(void);
void StateMachine(void);

/* Globale Variablen */
State_t currentState = STATE_IDLE;
uint32_t currentTime = 0; // Simulierte Zeitvariable
Task_t taskList[TASK_COUNT] = {
    {TASK_ETHERNET_FRAME_PULL, 0, 10, true}, 
    {TASK_MQTT_SUBSCRIBE_SESSION, 0, 100, true}, 
    {TASK_MQTT_PUBLISH_SESSION, 0, 200, true}

};
/* Indipendent Watchdog initialisierung - Restartet den Controler*/
void IWDG_Initialisieren(uint8_t prescaler, uint16_t intervall) {
  // Aktiviere den LSI-Takt
  RCC->CSR |= RCC_CSR_LSION;

  // Warte, bis der LSI-Takt stabil ist
  while(!(RCC->CSR & RCC_CSR_LSIRDY));

  // Entsperre den Zugriff auf die IWDG-Register
  IWDG->KR = 0x5555;

  // Stelle den prescaler ein
  IWDG->PR = prescaler;

  // Stelle den Neuladewert ein
  IWDG->RLR = intervall;

  // Starte den IWDG
  IWDG->KR = 0xCCCC;
}

int main(void) {
  initITSboard(); // Initialisierung des ITS Boards

  GUI_init(DEFAULT_BRIGHTNESS); // Initialisierung des LCD Boards mit Touch

  // Begruessungstext
  lcdPrintlnS("MQTT-project");

  // initialisiere den Stack 
  init_lwip_stack();

  // Setup Interface
  netif_config();

  // Watchdog IWDG initialisieren
  IWDG_Initialisieren(3, 2000); // Timeout von ca. 1 Sekunde
  MQTT_ConnectTimer_Init();
  
  // Test in Endlosschleife
  while (1) {
    Scheduler();    // Aufruf des Schedulers in der Endlosschleife
    StateMachine(); // Aufruf der Statemaschine

    // IWDG auffrischen und Bedingungen stellen
    IWDG->KR = 0xAAAA;
  }
}

/* StateMachine-Funktion */
void StateMachine(void) {
  switch (currentState) {
  case STATE_ETHERNET_FRAME_PULL:
    currentState = STATE_IDLE;
    break;
  case STATE_MQTT_SUBSCRIBE_SESSION:
    currentState = STATE_IDLE;
    break;
  case STATE_MQTT_PUBLISH_SESSION:
    currentState = STATE_IDLE;
    break;
  case STATE_IDLE:
    // Im IDLE-Zustand keine spezifische Aktion
    break;
  default:
    // Fehlerbehandlung für unbekannte Zustände
    currentState = STATE_IDLE;
    break;
  }
}

/* Scheduler-Funktion */
void Scheduler(void) {
  for (uint8_t i = 0; i < TASK_COUNT; i++) {
    currentTime = HAL_GetTick(); // Simulierte Zeit fortschreiben
    if (taskList[i].isEnabled && currentTime >= taskList[i].nextExecutionTime) {
      taskList[i].taskFunction();
      taskList[i].nextExecutionTime = currentTime + taskList[i].offset;
    }
  }
}

/* Task ETHERNET_FRAME_PULL - Beispielhafte Implementierung */
void TASK_ETHERNET_FRAME_PULL(void) {
  // Task 0 Funktionalität
  // Beispiel: LED toggeln
  // Kommentar: Diese Task toggelt die LED0
  toggleGPIO(&led_pins[0]);
  check_input();
  currentState = STATE_ETHERNET_FRAME_PULL;
}

/* Task 1 - Beispielhafte Implementierung */
void TASK_MQTT_SUBSCRIBE_SESSION(void) {
  // Task 1 Funktionalität
  // Beispiel: LED toggeln
  // Kommentar: Diese Task toggelt die LED1
  toggleGPIO(&led_pins[1]);
  init_mqtt_subscriber();
  currentState = STATE_MQTT_SUBSCRIBE_SESSION;
}

/* Task 2 - Beispielhafte Implementierung */
void TASK_MQTT_PUBLISH_SESSION(void) {
  // Task 2 Funktionalität
  // Beispiel: LED toggeln
  // Kommentar: Diese Task toggelt die LED2
  toggleGPIO(&led_pins[2]);
  mqtt_pin_publish();
  currentState = STATE_MQTT_PUBLISH_SESSION;
}

/* Erweiterungshinweis:
 * Um die Statemaschine zu erweitern, können neue Tasks
 * in die taskList hinzugefügt und entsprechende
 * Funktionen definiert werden.
 */

// EOF
