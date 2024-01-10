// Eleonora Chacón Taylor 2024
// waveram.c  wavetable ram test program

#include "rvfpganexys.h"

int main (void)
{

    int lenght = 128;
    for (int i = 0; i < lenght; i++)
    {
      WRITE_REG(SYNTH_ADDR, i);
      WRITE_REG(SYNTH_DATA, (i<<4)+1)
      WRITE_REG(SYNTH_RAM_RW, 1);
    }
    
    // enable audio
    WRITE_REG(SYNTH_CTRL, 1);
    
    volatile int t = 0;
    for (int i = 0; i < 80; i++)
      t++;

    // disable audio
    WRITE_REG(SYNTH_CTRL, 2);

    for (int i = 0; i < 80; i++)
      t++;

    // enable audio
    WRITE_REG(SYNTH_CTRL, 1);
    
    for (int i = 0; i < 80; i++)
      t++;

    // disable audio
    WRITE_REG(SYNTH_CTRL, 2);
}
