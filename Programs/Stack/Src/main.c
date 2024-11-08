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
#include "lcd.h"

#include "led.h"
#include "lwip_interface.h"

#include "lwip/apps/lwiperf.h"

#define IPERF_EXCLUSIVE 0 // 1: exclusive iperf mode, 0: non-exclusive iperf mode

extern void initITSboard(void);

/* Definitionen */
/* Enumeration für den Zustand der Statemaschine */
typedef enum { STATE_ETHERNET_FRAME_PULL, STATE_TASK1, STATE_TASK2, STATE_IPERF, STATE_IDLE } State_t;
#define TASK_COUNT STATE_IDLE
/* Struktur für eine Task */
typedef struct {
  void (*taskFunction)(void); // Funktionspointer zur Task
  uint32_t nextExecutionTime; // Zeitpunkt für die nächste Ausführung
  uint32_t offset;            // Offset für die nächste Ausführung
  bool isEnabled;             // Aktivierungsflag
} Task_t;

/* Funktionsdeklarationen */
void TASK_ETHERNET_FRAME_PULL(void);
void Task1(void);
void Task2(void);
void IPERF(void);
void Scheduler(void);
void StateMachine(void);

/* Globale Variablen */
State_t currentState = STATE_IDLE;
uint32_t currentTime = 0; // Simulierte Zeitvariable
Task_t taskList[TASK_COUNT] = {
    [STATE_ETHERNET_FRAME_PULL]={TASK_ETHERNET_FRAME_PULL, 0, 1, true}, 
    [STATE_TASK1]              ={Task1, 0, 100, false}, 
    [STATE_TASK2]              ={Task2, 0, 200, false},
    [STATE_IPERF]              ={IPERF, 0, 1000, true}   
};

int main(void) {
  initITSboard(); // Initialisierung des ITS Boards

  GUI_init(DEFAULT_BRIGHTNESS); // Initialisierung des LCD Boards mit Touch

  // Begruessungstext
  lcdPrintlnS("LWIP IPerf Server");

  // *********************** Setup ************************
  // Initialisiere den Stack 
  init_lwip_stack();
  // Setup Interface
  netif_config();
  
  // ********************* INIT APPS **********************
  if(taskList[STATE_IPERF].isEnabled){
    lwiperf_start_tcp_server_default(NULL, NULL);
    // If we run iperf exclusively, we need to run only the iperf task in the main loop
    while (IPERF_EXCLUSIVE) {
      taskList[STATE_ETHERNET_FRAME_PULL].taskFunction();
    }
  }

  // Alle Task in Endlosschleife
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
  case STATE_IPERF:
    currentState = STATE_IDLE;
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
/* Task IPERF - Measurement*/
void IPERF(void){
  toggleGPIO(&led_pins[3]);
  currentState = STATE_IPERF; 
}

/* Erweiterungshinweis:
 * Um die Statemaschine zu erweitern, können neue Tasks
 * in die taskList hinzugefügt und entsprechende
 * Funktionen definiert werden.
 */

// EOF
