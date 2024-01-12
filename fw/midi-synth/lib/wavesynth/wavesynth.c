// Eleonora Chacon Taylor 2024
// wavesynth.h header for wavesynth driver

#include <wavesynth.h>
#include <midi_notes.h>
#include <math.h>
#include "../../include/wave2.h"

void wavesynth_init(void)
{
    int lenght = SYNTH_WAVE_SAMPLES;
    for (int i = 0; i < lenght; i++)
    {
      WRITE_REG(SYNTH_ADDR, i);
      WRITE_REG(SYNTH_DATA, wave2[i]);
      WRITE_REG(SYNTH_RAM_RW, 1);
    }
    WRITE_REG(SYNTH_CYCLE, 512);
    WRITE_REG(SYNTH_TIMER, 500);
}

void wavesynth_noteOn(u08_t note_num, u08_t velocity)
{
    int n = SYNTH_WAVE_SAMPLES;
    // set pdmaudio timer to define pitch
    WRITE_REG(SYNTH_TIMER, midi_note2cycles(note_num, n));
    // enable synthesis
    WRITE_REG(SYNTH_CTRL, 1);
}

void wavesynth_noteOff(u08_t note_num)
{
    // disable synthesis
    WRITE_REG(SYNTH_CTRL, 2);
}

u08_t midi_note2cycles(u08_t note_num, u08_t num_wave_samples)
{
    u08_t cycles = 0;
    cycles = round(97656.25/midiNoteFrequencies[note_num-12]);
    return cycles;
}