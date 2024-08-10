#ifndef MICROCODE_H
#define MICROCODE_H

#include <cpu_control.h>

#define ADDR_BUS_WIDTH 9
#define MICRO_INSTRUCTION_WORD_WIDTH 14
#define CONTROL_WORD_WIDTH 22

class Microcode {
   public:
    typedef cpu_control_word_t__struct__0 control_word;
    typedef struct micro_instruction_state_t {
        control_word resulting_control_word;
        cpu_control::alu_flag_e flags[4];
    };

    typedef struct macro_instruction_t {
        const char* name;
        micro_instruction_state_t states[4];
    };

    typedef struct microcode_t {
        micro_instruction_state_t* microcode[1 << MICRO_INSTRUCTION_WORD_WIDTH];
    };
    typedef IData microcode_bin_t[(1 << MICRO_INSTRUCTION_WORD_WIDTH) - 1];
    typedef IData microcode_bin_instruction_state_t;
    static void PrimeMicrocode(microcode_t& microcode);  // insert fetch decode

    static void ConvertMicrocodeToBin(const microcode_t& microcode,
                                      microcode_bin_t& microcode_bin);

   private:
    static void ConvertInstructionStateToBin(
        micro_instruction_state_t state,
        microcode_bin_instruction_state_t& bin_state);
};

#endif  // MICROCODE_H
