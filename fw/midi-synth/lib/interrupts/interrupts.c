// Eleonora Chacón Taylor 2024
// interrupts.c source code for the interrupts in the swervolf-nexys platform
#include "../include/rvfpganexys.h"
#include <interrupts.h>
#include <midi.h>

// global variables
int SegDisplCount=1;
int TimerCount = 0x17D784;
MidiEvent_t midi;

void UART_ISR(void)
{
  uart_int_disable();
  //static unsigned int i = 0;
  //i++;
  //M_PSP_WRITE_REGISTER_32(SegDig_ADDR, i);
  char c = 0;
  unsigned int interrupt_id = uart_iir();
  switch(interrupt_id)
  {
      case 0xC1: // modem status
          uart_msr();
          c = uart_getc();
          break;

      case 0xCC: // timeout indication
          c = uart_getc();
          break;
      default:
          M_PSP_WRITE_REGISTER_32(GPIO_LEDs, 0xE000| interrupt_id);
          break;
  }

  parse_midi(c);

  bspClearExtInterrupt(1);
  uart_int_enable();
}

void GPIO_ISR(void)
{
  unsigned int sw, buttons;

  // Read the two GPIO to see what happened.
  sw = M_PSP_READ_REGISTER_32(RGPIO_INTS) >> 16;
  buttons = M_PSP_READ_REGISTER_32(RGPIO2_INTS);

  if ((sw & 0x01) == 0x1) {
    /* reinitiate the count */
    SegDisplCount=1;
    /* Clear the interrupt*/
    M_PSP_WRITE_REGISTER_32(RGPIO_INTS, 0x0);           /* RGPIO_INTS */
  }
  if ((buttons & 0x1) == 0x1) {
    /* Cycle count velocity */
    TimerCount = TimerCount - 0x100;
    if (TimerCount < 0) TimerCount = 0x2FFF;
    /* Clear the interrupt*/
    M_PSP_WRITE_REGISTER_32(RGPIO2_INTS, 0x0);           /* RGPIO_INTS */
  }

  /* Clear external interrupts from GPIO (IRQ4) */
  bspClearExtInterrupt(4);
}


void PTC_ISR(void)
{
  //static unsigned int i = 0;
  //M_PSP_WRITE_REGISTER_32(SegDig_ADDR, i);
  //i++;

  //unsigned int lsr = uart_status();
  //M_PSP_WRITE_REGISTER_32(GPIO_LEDs, lsr);
  /* Modify IRQ3 priority if SegDisplCount>10 */
  //if (SegDisplCount>10) pspExtInterruptSetPriority(3,5);

  /* Clear PTC interrupt */
  M_PSP_WRITE_REGISTER_32(RPTC_CNTR, 0x0);
  M_PSP_WRITE_REGISTER_32(RPTC_CTRL, 0x40);
  M_PSP_WRITE_REGISTER_32(RPTC_CTRL, 0x31);

  /* Stop the generation of the specific external interrupt */
  bspClearExtInterrupt(3);
}

// main wrapper
void interrupt_init(void)
{
  // Misc initialization
  SevenSegments_Initialization();
  // Initialize interrupt sources
  GPIO_Initialization();
  PTC_Initialization();
  uart_init();
  // Initialize the interrupt system 
  DefaultInitialization();
  pspExtInterruptsSetThreshold(5);
  ExternalIntLine_Initialization(4, 6, GPIO_ISR);
  ExternalIntLine_Initialization(3, 6, PTC_ISR);
  // elecha: UART interrupt initialization
  ExternalIntLine_Initialization(1, 6, UART_ISR);
  // Enable interrupts
  M_PSP_WRITE_REGISTER_32(Select_INT, 0x3);
  pspInterruptsEnable();
  M_PSP_SET_CSR(D_PSP_MIE_NUM, D_PSP_MIE_MEIE_MASK);
  // enable UART interrupts
  uart_int_enable();
}

void DefaultInitialization(void)
{
  u32_t uiSourceId;

  /* Register interrupt vector */
  pspInterruptsSetVectorTableAddress(&M_PSP_VECT_TABLE);

  /* Set external-interrupts vector-table address in MEIVT CSR */
  pspExternalInterruptSetVectorTableAddress(G_Ext_Interrupt_Handlers);

  /* Put the Generation-Register in its initial state (no external interrupts are generated) */
  bspInitializeGenerationRegister(D_PSP_EXT_INT_ACTIVE_HIGH);

  for (uiSourceId = D_BSP_FIRST_IRQ_NUM; uiSourceId <= D_BSP_LAST_IRQ_NUM; uiSourceId++)
  {
    /* Make sure the external-interrupt triggers are cleared */
    bspClearExtInterrupt(uiSourceId);
  }

  /* Set Standard priority order */
  pspExtInterruptSetPriorityOrder(D_PSP_EXT_INT_STANDARD_PRIORITY);

  /* Set interrupts threshold to minimal (== all interrupts should be served) */
  pspExtInterruptsSetThreshold(M_PSP_EXT_INT_THRESHOLD_UNMASK_ALL_VALUE);

  /* Set the nesting priority threshold to minimal (== all interrupts should be served) */
  pspExtInterruptsSetNestingPriorityThreshold(M_PSP_EXT_INT_THRESHOLD_UNMASK_ALL_VALUE);
}

void ExternalIntLine_Initialization(u32_t uiSourceId, u32_t priority, pspInterruptHandler_t pTestIsr)
{
  /* Set Gateway Interrupt type (Level) */
  pspExtInterruptSetType(uiSourceId, D_PSP_EXT_INT_LEVEL_TRIG_TYPE);

  /* Set gateway Polarity (Active high) */
  pspExtInterruptSetPolarity(uiSourceId, D_PSP_EXT_INT_ACTIVE_HIGH);

  /* Clear the gateway */
  pspExtInterruptClearPendingInt(uiSourceId);

  /* Set IRQ4 priority */
  pspExtInterruptSetPriority(uiSourceId, priority);
    
  /* Enable IRQ4 interrupts in the PIC */
  pspExternalInterruptEnableNumber(uiSourceId);

  /* Register ISR */
  G_Ext_Interrupt_Handlers[uiSourceId] = pTestIsr;
}


void GPIO_Initialization(void)
{
  /* Configure LEDs and Switches */
  M_PSP_WRITE_REGISTER_32(GPIO_INOUT, 0xFFFF);        /* GPIO_INOUT */
  M_PSP_WRITE_REGISTER_32(GPIO_LEDs, 0x0);            /* GPIO_LEDs */

  /* Configure Buttons (GPIO2)*/
  M_PSP_WRITE_REGISTER_32(GPIO2_INOUT, 0x0);

  /* Configure GPIO interrupts */
  M_PSP_WRITE_REGISTER_32(RGPIO_INTE, 0x10000);       /* RGPIO_INTE */
  M_PSP_WRITE_REGISTER_32(RGPIO_PTRIG, 0x10000);      /* RGPIO_PTRIG */
  M_PSP_WRITE_REGISTER_32(RGPIO_INTS, 0x0);           /* RGPIO_INTS */
  M_PSP_WRITE_REGISTER_32(RGPIO_CTRL, 0x1);           /* RGPIO_CTRL */

  /* Configure GPIO2 interrupts */
  M_PSP_WRITE_REGISTER_32(RGPIO2_INTE, 0x1F);           /* BTNC generates interrupt */
  M_PSP_WRITE_REGISTER_32(RGPIO2_PTRIG, 0x1);           /* BTNC is active high */
  M_PSP_WRITE_REGISTER_32(RGPIO2_INTS, 0x0);            /* Clears interrupts */
  M_PSP_WRITE_REGISTER_32(RGPIO2_CTRL, 0x1);            /* Enables interrupts from this IP */


}


void PTC_Initialization(void)
{
  /* Configure PTC with interrupts */
  M_PSP_WRITE_REGISTER_32(RPTC_LRC, TimerCount);
  M_PSP_WRITE_REGISTER_32(RPTC_CNTR, 0x0);
  M_PSP_WRITE_REGISTER_32(RPTC_CTRL, 0x40);
  M_PSP_WRITE_REGISTER_32(RPTC_CTRL, 0x31);
}

void SevenSegments_Initialization(void)
{
  M_PSP_WRITE_REGISTER_32(SegEn_ADDR, 0);
  M_PSP_WRITE_REGISTER_32(SegDig_ADDR, 0);
}