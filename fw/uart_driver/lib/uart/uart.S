.text

.globl uart_init
.globl uart_putc
.globl uart_getc
.globl uart_clear
.globl uart_status
.globl uart_iir

#define UART_BASE 0x80002000
#define REG_BRDL (4*0x00) /* Baud rate divisor (LSB) */ 
#define REG_IER (4*0x01) /* Interrupt enable reg. */ 
#define REG_FCR (4*0x02) /* FIFO control reg. */ 
#define REG_LCR (4*0x03) /* Line control reg. */ 
#define REG_LSR (4*0x05) /* Line status reg. */ 
#define LCR_CS8 0x03 /* 8 bits data size */
#define LCR_1_STB 0x00 /* 1 stop bit */ 
#define LCR_PDIS 0x00 /* parity disable */
#define LSR_THRE 0x20
#define FCR_FIFO 0x01 /* enable XMIT and RCVR FIFO */ 
#define FCR_RCVRCLR 0x02 /* clear RCVR FIFO */
#define FCR_XMITCLR 0x04 /* clear XMIT FIFO */
#define FCR_MODE0 0x00 /* set receiver in mode 0 */ 
#define FCR_MODE1 0x08 /* set receiver in mode 1 */ 
#define FCR_FIFO_8 0x80 /* 8 bytes in RCVR FIFO */

#define DATA_READY    0x1

uart_init:
    
    li t0, UART_BASE
    /* Set DLAB bit in LCR to enable divisor latches*/ 
    li t1, 0x80
    sb t1, REG_LCR(t0)
    /* Set divisor regs */ 
    li t1, 27
    sb t1, REG_BRDL(t0)
    /* 8 data bits, 1 stop bit, no parity, clear DLAB */ 
    li t1, LCR_CS8 | LCR_1_STB | LCR_PDIS
    sb t1, REG_LCR(t0)
    /* At this point, transmission engine starts working */
    /* Set the FIFO trigger level */
    li t1, FCR_FIFO | FCR_MODE0 | FCR_FIFO_8 | FCR_RCVRCLR | FCR_XMITCLR 
    sb t1, REG_FCR(t0)
    /* enable received data interrupt */
    li t1, 1
    sb t1, REG_IER(t0)

    ret

uart_getc:
    li      t0, UART_BASE

    lbu     t1, REG_LSR(t0)
    andi    t1, t1, DATA_READY

    # jump to _uart_read if UART is ready to read from
    bnez    t1, _uart_read

    # otherwise, return 0
    mv      a0, zero
    j       _uart_get_end

_uart_read:
    # load character at UART address into a0
    lbu     a0, (t0)
    j       _uart_get_end

_uart_get_end:
    ret

uart_putc:
    li  t0, UART_BASE
_uartSendByte:
    /* Check for space in UART FIFO */ 
    lb t1, REG_LSR(t0)
    andi t1, t1, LSR_THRE
    beqz t1, _uartSendByte
    
    # store character at UART address in return register
    sb  a0, (t0)
    ret

uart_clear:
    li  t0, UART_BASE
    li  t1, FCR_RCVRCLR
    sb  t1, REG_FCR(t0)
    ret

uart_status:
    li  t0, UART_BASE
    lw  a0, REG_LSR(t0)
    ret

uart_iir:
    li  t0, UART_BASE
    lw  a0, REG_FCR(t0)
    ret
