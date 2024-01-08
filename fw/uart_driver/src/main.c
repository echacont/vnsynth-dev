#include "rvfpganexys.h"
#include <uart.h>
#include <interrupts.h>

// interrupts
// main wrapper
void interrupt_init(void);
void GPIO_ISR(void);
void PTC_ISR(void);
void UART_ISR(void);
void GPIO_Initialization(void);
void PTC_Initialization(void);

// global variables
int SegDisplCount=1;
int TimerCount = 0x17D784;

int main() {

  GPIO_Initialization();
  PTC_Initialization();
  uart_init();
  
  M_PSP_WRITE_REGISTER_32(SegEn_ADDR, 0x00);
  M_PSP_WRITE_REGISTER_32(SegDig_ADDR, 0x0); 

  interrupt_init();
  uart_int_enable();

  for (;;) {
    //char c = uart_getc();
    //if (c == 10 || c == 13) uart_putc('\n');
    //else {
    //uart_putc(c);
    //if (c != 0)
    //  WRITE_REG(SegDig_ADDR, c);
  }
}

// main wrapper
void interrupt_init(void)
{
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
}

void UART_ISR(void)
{
  uart_int_disable();
  //static unsigned int i = 0;
  //i++;
  //M_PSP_WRITE_REGISTER_32(SegDig_ADDR, i);
  char c; // = uart_getc();
  unsigned int c0, c1, c2, c3;
  unsigned int interrupt_id = uart_iir();
  M_PSP_WRITE_REGISTER_32(GPIO_LEDs, interrupt_id);
  switch(interrupt_id)
  {
      case 0xC1: // modem status
          uart_msr();
          c = uart_getc();
          break;

      case 0xCC: // timeout indication
          c = uart_getc();
          //c1 = uart_geti();
          //c2 = uart_geti();
          //c3 = uart_geti();
  //M_PSP_WRITE_REGISTER_32(SegDig_ADDR, c0 | c1<<8 | c2<<16 | c3<<24);
          break;
      default:
          M_PSP_WRITE_REGISTER_32(GPIO_LEDs, interrupt_id);
          break;
  }

  // MIDI stuff
  static int byte = 0;
  static int ump = 0;
  ump = ump | c;
  if (byte < 3) 
    ump = ump<<8;
  byte++;
  if (byte == 4) // 4 bytes have been received.
  { 
    byte = 0;
    M_PSP_WRITE_REGISTER_32(SegDig_ADDR, ump);
    // call function to handle MIDI message
    
  }
  
  

  bspClearExtInterrupt(1);
  uart_int_enable();
}

void GPIO_ISR(void)
{
  unsigned int i;
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
