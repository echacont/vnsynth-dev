#include "defines.h"

extern "C" void uart_init(void);
extern "C" void uart_putc(unsigned char);
extern "C" unsigned char uart_getc(void);

void uart_puts(char* str) {
  while (*str) uart_putc(*str++);
  uart_putc('\n');
}

int main() {

  WRITE_REG(SegEn_ADDR, 0xFC);

  uart_init();
  //uart_putc(13);
  //uart_puts("Hello from bare-metal RISC-V!");
  //uart_putc(13);
  //uart_puts("Type something and it'll show up!");
  //uart_putc(13);

  for (;;) {
    // ideally, this should be handled by an interrupt.
    // this library configures the UART so that it emits
    // one when it's ready to read from.
    char c = uart_getc();
    //if (c == 10 || c == 13) uart_putc('\n');
    //else {
    //uart_putc(c);
    if (c != 0)
      WRITE_REG(SegDig_ADDR, c);
    
  }
}
