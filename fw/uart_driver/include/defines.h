// Eleonora Chacón Taylor 2024
// swervolf-nexys defines

#define SegEn_ADDR    0x80001038
#define SegDig_ADDR   0x8000103C

#define READ_REG(dir) (*(volatile unsigned *)dir)
#define WRITE_REG(dir, value) { (*(volatile unsigned *)dir) = (value); }
