// generate microcode given a list of makro_instruction_t
// first n states always fetch decode exe etc
#include <cpu_control.h>
#include <microcode.h>


void Microcode::PrimeMicrocode(microcode_bin_t& microcode) {
    // state_0 for all 00000000000000 00001111111111
    // state_1 for all 00010000000000 00011111111111

    for (int i = 0; i < (1 << MICRO_INSTRUCTION_WORD_WIDTH); i++) {
        microcode[i] = NOP_CONTROL_WORD;
    }

    for (int i = 0; i < (1 << MICRO_INSTRUCTION_WORD_WIDTH - 4); i++) {
        microcode[i] = INC_CONTROL_WORD;
        microcode[i + (1 << MICRO_INSTRUCTION_WORD_WIDTH - 4)] =
            FETCH_CONTROL_WORD;
    }
}