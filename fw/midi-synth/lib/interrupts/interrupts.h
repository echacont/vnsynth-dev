// Eleonora Chacón Taylor 2024
// interrupts.h header file for interrupts in the swervolf-nexys platform

#ifndef INTERRUPTS_H
#define INTERRUPTS_H

// include swervolf PSP/BSP libraries
#include "psp_api.h"
#include "bsp_external_interrupts.h"
#include "psp_ext_interrupts_eh1.h"
// include UART library
#include <uart.h>

extern D_PSP_DATA_SECTION D_PSP_ALIGNED(1024) pspInterruptHandler_t G_Ext_Interrupt_Handlers[8];

// prototypes

// Initializes the interrupt subsystem
void DefaultInitialization(void);

// Interrupt source initialization
void ExternalIntLine_Initialization(u32_t uiSourceId, u32_t priority, pspInterruptHandler_t pTestIsr);

// interrupts
// main wrapper
void interrupt_init(void);
void GPIO_ISR(void);
void PTC_ISR(void);

void GPIO_Initialization(void);
void PTC_Initialization(void);
void SevenSegments_Initialization(void);

#endif // INTERRUPTS_H
