#ifndef SYS_ARCH_H_
#define SYS_ARCH_H_
#include <stdbool.h>
#include "lwip/init.h"
#include "stm32f4xx_hal.h"

typedef struct {
    volatile bool taken;  // Flag to indicate if the semaphore is taken
} sys_sem_t;

typedef struct {
    void *msg;            // Pointer to the message
    volatile bool available;  // Flag to indicate if a message is available
} sys_mbox_t;

// Overwrite u32_t sys_now(void);

#endif