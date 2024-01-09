// Eleonora Chacón Taylor 2024
// waveram.c  wavetable ram test program

#include "rvfpganexys.h"

int main (void)
{
    int lenght = 2048;
    for (int i = 0; i < lenght; i++)
    {
      WRITE_REG(SYNTH_ADDR, i);
      WRITE_REG(SYNTH_DATA, (i<<4)+1)
      WRITE_REG(SYNTH_CTRL, 1);
    }
    for (int i = 0; i < lenght; i++)
    {
      WRITE_REG(SYNTH_ADDR, i);
      WRITE_REG(SYNTH_CTRL, 0);
      int data = READ_REG(SYNTH_DATA);
    }

}
