// Eleonora Chacón Taylor 2024
// waveram.c  wavetable ram test program

#include "rvfpganexys.h"
#include <math.h>

// wavetable stuff
#define N 128       // number of samples per wave
#define D 65535     // sample bit-depth (2^16-1)

int calc_wave(int n);

int main (void)
{

    int lenght = 128;
    for (int i = 0; i < lenght; i++)
    {
      WRITE_REG(SYNTH_ADDR, i);
      WRITE_REG(SYNTH_DATA, calc_wave(i))
      WRITE_REG(SYNTH_RAM_RW, 1);
    }
    
    // enable audio
    WRITE_REG(SYNTH_CTRL, 1);
    
    volatile int t = 0;
    for (int i = 0; i < 1000; i++)
      t++;

    // disable audio
    WRITE_REG(SYNTH_CTRL, 2);


}


int calc_wave(int n)
{
  return round(D*sin(2*M_PI*n/N));
}
