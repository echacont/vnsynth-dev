// Eleonora Chacon Taylor 2024
// uart.h header for uart library
// Based on https://github.com/safinsingh/ns16550a
#ifndef UART_H
#define UART_H

extern  void uart_init(void);
extern  void uart_putc(unsigned char);
extern  unsigned char uart_getc(void);
extern  void uart_clear(void);
extern  unsigned int uart_status(); 
extern  unsigned int uart_iir();
    

void uart_puts(char* str) {
  while (*str) uart_putc(*str++);
  uart_putc('\n');
}

#endif // UART_H
