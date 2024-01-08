// Eleonora Chacón Taylor 2024
// rvfpganexys.h: main header file for RVfpgaNexys platform
#ifndef RVFPGANEXYS_H
#define RVFPGANEXYS_H
// swervolf PSP/BSP libraries
#include "psp_api.h"
#include "bsp_timer.h"
#include "bsp_printf.h"

// swervolf-nexys Wishbone bus 
// seven segment display driver
#define SegEn_ADDR    0x80001038
#define SegDig_ADDR   0x8000103C
#define GPIO_SWs        0x80001400
#define GPIO_LEDs       0x80001404
#define GPIO_INOUT      0x80001408
#define GPIO2_IN        0x80001800
#define GPIO2_INOUT     0x80001808
#define RGPIO_INTE      0x8000140C
#define RGPIO_PTRIG     0x80001410
#define RGPIO_CTRL      0x80001418
#define RGPIO_INTS      0x8000141C
#define RGPIO2_INTE     0x8000180C
#define RGPIO2_PTRIG    0x80001810
#define RGPIO2_CTRL     0x80001818
#define RGPIO2_INTS     0x8000181C
#define RPTC_CNTR       0x80001200
#define RPTC_HRC        0x80001204
#define RPTC_LRC        0x80001208
#define RPTC_CTRL       0x8000120c
#define Select_INT      0x80001018

// Wishbone bus 32-bit register access macros
#define READ_REG(dir) (*(volatile unsigned *)dir)
#define WRITE_REG(dir, value) { (*(volatile unsigned *)dir) = (value); }

#endif // RVFPGANEXYS_H
