// Eleonora Chacon Taylor 2024
// midi.byte  midi library

#include <midi.h>

static MidiEvent_t midievnt;
uint8_t expected_bytes; 

void initialize_midi(void)
{
    expected_bytes = 0;
}

MidiEvent_t pop_midi()
{
    MidiEvent_t copy = midievnt;
    midievnt.valid = 0;
    return copy;
}

void parse_midi(char byte)
{
    midievnt.valid = 0;
    if ((byte >= 0xF0) & (expected_bytes == 0))  // SYSTEM MESSAGE
    {
        midievnt.valid = 1;
        midievnt.status = byte;
        midievnt.data1 = 0;
        midievnt.data2 = 0;
    }
    else if ((byte >= 0x80) & (expected_bytes == 0)) // CHANNEL MESSAGE
    {
        midievnt.status  = byte & 0xF0;
        midievnt.channel = byte & 0x0F;
        expected_bytes = 2;
        midievnt.valid = 0;
    }
    else {
        if (expected_bytes == 2) // first DATA byte
        {
            expected_bytes = 1;
            midievnt.data1 = byte;
            midievnt.valid = 0;
        }
        else if (expected_bytes == 1) // second DATA byte
        {
            expected_bytes = 0;
            midievnt.data2 = byte;   
            midievnt.valid = 1;
        }
    }
    return midievnt;
}