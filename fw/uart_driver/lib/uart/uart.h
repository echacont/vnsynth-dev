// Eleonora Chacon Taylor 2024
// uart.h header for uart library
// Based on https://github.com/safinsingh/ns16550a

extern  void uart_init(void);
extern  void uart_putc(unsigned char);
extern  unsigned char uart_getc(void);

void uart_puts(char* str) {
  while (*str) uart_putc(*str++);
  uart_putc('\n');
}
