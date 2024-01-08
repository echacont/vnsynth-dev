#include "rvfpganexys.h"
#include <interrupts.h>
#include <midi.h>



int main() {

  initialize_midi();
  interrupt_init();
  
  for (;;) {
    MidiEvent_t midi;
    midi = pop_midi();
    if (midi.valid)
    {
      M_PSP_WRITE_REGISTER_32(SegDig_ADDR, midi.status << 16 | midi.channel << 12 | midi.data1 << 8 | midi.data2);
    }
  }
}




