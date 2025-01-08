/**
 ******************************************************************************
 * @file    main.c
 * @author  Martin Becke
 * @brief   Kleines Testprogramm fuer lwip
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#define STM32F429xx
#include <arm_compat.h>

#include "LCD_GUI.h"
#include "stm32f4xx_hal.h"
#include <stdint.h>

#include "LCD_GUI.h"
#include "LCD_Touch.h"

#include "lcd.h"

#include "led.h"
#include "lwip_interface.h"



extern void initITSboard(void);

/* Definitionen */
#define TASK_COUNT 3
/* Enumeration für den Zustand der Statemaschine */
typedef enum { STATE_ETHERNET_FRAME_PULL, STATE_TASK1, STATE_TASK2, STATE_IDLE } State_t;

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

int main(void) {
  initITSboard(); // Initialisierung des ITS Boards

  GUI_init(DEFAULT_BRIGHTNESS); // Initialisierung des LCD Boards mit Touch
  TP_Init(false);               // Initialisierung des LCD Boards mit Touch

  // Begruessungstext
  lcdPrintlnS("LWIP-project");

  // initialisiere den Stack 
  init_lwip_stack();

  // Setup Interface
  netif_config();
  
  // Test in Endlosschleife
  while (1) {
    Scheduler();    // Aufruf des Schedulers in der Endlosschleife
    StateMachine(); // Aufruf der Statemaschine
  }
}

/* StateMachine-Funktion */
void StateMachine(void) {
  switch (currentState) {
  case STATE_ETHERNET_FRAME_PULL:
    currentState = STATE_IDLE;
    break;
  case STATE_TASK1:
    currentState = STATE_IDLE;
    break;
  case STATE_TASK2:
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
void Task1(void) {
  // Task 1 Funktionalität
  // Beispiel: LED toggeln
  // Kommentar: Diese Task toggelt die LED1
  toggleGPIO(&led_pins[1]);
  currentState = STATE_TASK1;
}

/* Task 2 - Beispielhafte Implementierung */
void Task2(void) {
  // Task 2 Funktionalität
  // Beispiel: LED toggeln
  // Kommentar: Diese Task toggelt die LED2
  toggleGPIO(&led_pins[2]);
  currentState = STATE_TASK2;
}

/* Erweiterungshinweis:
 * Um die Statemaschine zu erweitern, können neue Tasks
 * in die taskList hinzugefügt und entsprechende
 * Funktionen definiert werden.
 */

// EOF
