#ifndef LIB_MICROCODE_H
#define LIB_MICROCODE_H

#include <control_word.h>
#include <cpu_control.h>

#define ADDR_BUS_WIDTH 9
#define MICRO_INSTRUCTION_WORD_WIDTH 14
#define CONTROL_WORD_WIDTH 22

#define ALL_FLAGS                                                              \
    {                                                                          \
        cpu_control::alu_flag_e::NONE, cpu_control::alu_flag_e::ZERO,          \
            cpu_control::alu_flag_e::CARRY, cpu_control::alu_flag_e::REMAINDER \
    }

#define COMPUTE_CONCATENATED_CONTROL_WORD(                                   \
    alu_op, alu_enable, memory_op, data_word_selector, bus_selector, rax_op, \
    rbx_op, rcx_op, rdx_op, reset, halt, control_unit_load, next_instr)      \
    ((alu_op) << (CONTROL_WORD_WIDTH - 4)) +                                 \
        ((alu_enable) << (CONTROL_WORD_WIDTH - 5)) +                         \
        ((memory_op) << (CONTROL_WORD_WIDTH - 8)) +                          \
        ((data_word_selector) << (CONTROL_WORD_WIDTH - 9)) +                 \
        ((bus_selector) << (CONTROL_WORD_WIDTH - 10)) +                      \
        ((rax_op) << (CONTROL_WORD_WIDTH - 12)) +                            \
        ((rbx_op) << (CONTROL_WORD_WIDTH - 14)) +                            \
        ((rcx_op) << (CONTROL_WORD_WIDTH - 16)) +                            \
        ((rdx_op) << (CONTROL_WORD_WIDTH - 18)) +                            \
        ((reset) << (CONTROL_WORD_WIDTH - 19)) +                             \
        ((halt) << (CONTROL_WORD_WIDTH - 20)) +                              \
        ((control_unit_load) << (CONTROL_WORD_WIDTH - 21)) +                 \
        ((next_instr) << (CONTROL_WORD_WIDTH - 22))

class Microcode {
   private:
    struct micro_instruction_state_t {
        int resulting_control_word : CONTROL_WORD_WIDTH;
        cpu_control::alu_flag_e flags[4];
    };

    struct microcode_t {
        micro_instruction_state_t* microcode[1 << MICRO_INSTRUCTION_WORD_WIDTH];
    };

    typedef IData microcode_bin_t[(1 << MICRO_INSTRUCTION_WORD_WIDTH) - 1];

    IData microcode_bin_instruction_state_t;

    microcode_bin_t microcode;

    void PrimeMicrocode();  // insert fetch decode

   public:
    struct macro_instruction_t {
        const char* name;
        micro_instruction_state_t states[4];
    };

    Microcode() { PrimeMicrocode(); }

    void AddMacroInstruction(const macro_instruction_t& macro_instruction);

    void StoreMicrocodeIntoModel(IData* m_storage);
};

#endif  // LIB_MICROCODE_H
