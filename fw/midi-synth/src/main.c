#include "rvfpganexys.h"
#include <interrupts.h>
#include <midi.h>
#include <wavesynth.h>



int main() {

  initialize_midi();
  interrupt_init();
  wavesynth_init();
  
  for (;;) {
    MidiEvent_t midi;
    midi = pop_midi();
    if (midi.valid)
    {
      M_PSP_WRITE_REGISTER_32(SegDig_ADDR, midi.status << 16 | midi.channel << 12 | midi.data1 << 8 | midi.data2);
    }
    if (midi.status == NoteOn) {
      wavesynth_noteOn(midi.data1, midi.data2);
    }
    if (midi.status == NoteOff) {
      wavesynth_noteOff(midi.data1);
    }
  }
}




