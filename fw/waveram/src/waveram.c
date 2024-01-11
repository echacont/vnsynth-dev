// Eleonora Chacón Taylor 2024
// waveram.c  wavetable ram test program

#include "rvfpganexys.h"
#include "wave2.h"

int main (void)
{

    int lenght = N;
    for (int i = 0; i < lenght; i++)
    {
      WRITE_REG(SYNTH_ADDR, i);
      WRITE_REG(SYNTH_DATA, wave2[i])
      WRITE_REG(SYNTH_RAM_RW, 1);
    }

    WRITE_REG(SYNTH_CYCLE, 512);
    WRITE_REG(SYNTH_TIMER, 500);

    // enable audio
    WRITE_REG(SYNTH_CTRL, 1);
    
    volatile int t = 0;

    while (1) {
      
      for (int i = 0; i < 50000; i++)
        t++;

      WRITE_REG(SYNTH_TIMER, 1000);
      // WRITE_REG(SYNTH_WAVEPOS, 1);
      
      //WRITE_REG(SYNTH_WAVEPOS, 1);
   
      for (int i = 0; i < 50000; i++)
        t++;
      
      WRITE_REG(SYNTH_TIMER, 500);
      //WRITE_REG(SYNTH_WAVEPOS, 0);
    }

    // disable audio
    WRITE_REG(SYNTH_CTRL, 2);

    //for (int i = 0; i < 10; i++)
    //  t++;   
    //enable audio
    //WRITE_REG(SYNTH_CTRL, 1);*/

}
