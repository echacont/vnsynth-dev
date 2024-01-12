// Eleonora Chacon Taylor 2024
// wavesynth.h header for wavesynth driver

#ifndef WAVESYNTH_H
#define WAVESYNTH_H

#include "../../include/rvfpganexys.h"

// Wavetable 
#define SYNTH_RAM_RW    0x80001600
#define SYNTH_ADDR      0x80001604
#define SYNTH_DATA      0x80001608
#define SYNTH_CTRL      0x8000160C
#define SYNTH_CYCLE     0x80001610
#define SYNTH_TIMER     0x80001614
#define SYNTH_WAVEPOS   0x80001618

#define SYNTH_WAVE_SAMPLES 512

// Wishbone bus 32-bit register access macros
#define READ_REG(dir) (*(volatile unsigned *)dir)
#define WRITE_REG(dir, value) { (*(volatile unsigned *)dir) = (value); }

// prototypes
void  wavesynth_init(void);
void  wavesynth_noteOn(u08_t note_num, u08_t velocity);
void  wavesynth_noteOff(u08_t note_num);
u08_t midi_note2cycles(u08_t note_num, u08_t num_wave_samples);




#endif // WAVESYNTH_H