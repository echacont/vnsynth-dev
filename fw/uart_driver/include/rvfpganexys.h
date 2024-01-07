// Eleonora Chacón Taylor 2024
// rvfpganexys.h: main header file for RVfpgaNexys platform

// swervolf PSP/BSP libraries
#include "psp_api.h"
#include "bsp_timer.h"
#include "bsp_printf.h"

// swervolf-nexys Wishbone bus 
// seven segment display driver
#define SegEn_ADDR    0x80001038
#define SegDig_ADDR   0x8000103C

// Wishbone bus 32-bit register access macros
#define READ_REG(dir) (*(volatile unsigned *)dir)
#define WRITE_REG(dir, value) { (*(volatile unsigned *)dir) = (value); }

