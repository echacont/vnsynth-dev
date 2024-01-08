// Eleonora Chacon Taylor 2024
// uart.h header for uart library
// Based on https://github.com/safinsingh/ns16550a
#ifndef UART_H
#define UART_H

extern void uart_init(void);
extern void uart_putc(unsigned char);
extern unsigned char uart_getc(void);
extern unsigned int  uart_geti(void);
extern void uart_clear(void);
extern unsigned int uart_status(); 
extern unsigned int uart_msr();
extern unsigned int uart_iir();
extern void uart_int_enable();
extern void uart_int_disable();

#endif // UART_H
