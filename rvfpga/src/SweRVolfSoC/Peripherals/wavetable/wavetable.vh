// ELeonora Chacón Taylor 2024
// wavetable.vh wavetable hardware description header file

`define WAVE_BRAM_DATA_WIDTH    16
`define WAVE_BRAM_DATA_SIZE     2048
`define WAVE_BRAM_ADDR_WIDTH    11

`define WAVE_PDM_DATA_WIDTH     16

// synth FSM
`define SYNTH_FSM_IDLE           2'b00
`define SYNTH_FSM_RESET          2'b10
`define SYNTH_FSM_SETUP          2'b01
`define SYNTH_FSM_AUDIO          2'b11

// pdmaudio FSM
`define PDM_FSM_IDLE             2'b00
`define PDM_FSM_WRITE_RELOAD     2'b01
`define PDM_FSM_READ_SAMPLE      2'b10
`define PDM_FSM_WRITE_SAMPLE     2'b11
