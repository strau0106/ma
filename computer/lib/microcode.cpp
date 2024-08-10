// generate microcode given a list of makro_instruction_t
// first n states always fetch decode exe etc
#include <cpu_control.h>
#include <microcode.h>

#define ALL_FLAGS                                                              \
    {                                                                          \
        cpu_control::alu_flag_e::NONE, cpu_control::alu_flag_e::ZERO,          \
            cpu_control::alu_flag_e::CARRY, cpu_control::alu_flag_e::REMAINDER \
    }

// state 0 inc => bus_selector = pc, memory_op = INC
// state 1 load instr in control unit => data_word_selector = 0, bus_selector = pc, memory_op = READ, control_unit.load = enable
// for state 0 and 1 all flags are valid.

Microcode::micro_instruction_state_t state_0 = {
    {
        cpu_control::alu_op_e::ALU_NOP,
        0,  // alu_enable,
        cpu_control::memory_op_e::INC,
        0,  // data_word_selector
        cpu_control::memory_bus_selector_e::PC, cpu_control::reg_op_e::REG_NOP,
        cpu_control::reg_op_e::REG_NOP, cpu_control::reg_op_e::REG_NOP,
        cpu_control::reg_op_e::REG_NOP,
        0,  // reset
        0,  // halt
        0,  // control_unit_load
        0,  // next_instr
    },
    ALL_FLAGS};

Microcode::micro_instruction_state_t state_1 = {
    {
        cpu_control::alu_op_e::ALU_NOP,
        0,  // alu_enable,
        cpu_control::memory_op_e::READ,
        0,  // data_word_selector
        cpu_control::memory_bus_selector_e::PC, cpu_control::reg_op_e::REG_NOP,
        cpu_control::reg_op_e::REG_NOP, cpu_control::reg_op_e::REG_NOP,
        cpu_control::reg_op_e::REG_NOP,
        0,  // reset
        0,  // halt
        1,  // control_unit_load
        0,  // next_instr
    },
    ALL_FLAGS};

Microcode::micro_instruction_state_t state_empty = {
    {
        cpu_control::alu_op_e::ALU_NOP,
        0,  // alu_enable,
        cpu_control::memory_op_e::NOP,
        0,  // data_word_selector
        cpu_control::memory_bus_selector_e::MAR, cpu_control::reg_op_e::REG_NOP,
        cpu_control::reg_op_e::REG_NOP, cpu_control::reg_op_e::REG_NOP,
        cpu_control::reg_op_e::REG_NOP,
        0,  // reset
        0,  // halt
        0,  // control_unit_load
        0,  // next_instr
    },
    ALL_FLAGS};

void Microcode::ConvertInstructionStateToBin(
    micro_instruction_state_t state,
    microcode_bin_instruction_state_t& bin_state) {
    // bin concat one member after the other
    // if state is nullptr, set all bits to 0
    bin_state =
        (state.resulting_control_word.__PVT__alu_op
         << CONTROL_WORD_WIDTH - 4) +
        (state.resulting_control_word.__PVT__alu_enable
         << CONTROL_WORD_WIDTH - 5) +
        (state.resulting_control_word.__PVT__memory_op
         << CONTROL_WORD_WIDTH - 8) +
        (state.resulting_control_word.__PVT__data_word_selector
         << CONTROL_WORD_WIDTH - 9) +
        (state.resulting_control_word.__PVT__bus_selector
         << CONTROL_WORD_WIDTH - 10) +
        (state.resulting_control_word.__PVT__rax_op
         << CONTROL_WORD_WIDTH - 12) +
        (state.resulting_control_word.__PVT__rbx_op
         << CONTROL_WORD_WIDTH - 14) +
        (state.resulting_control_word.__PVT__rcx_op
         << CONTROL_WORD_WIDTH - 16) +
        (state.resulting_control_word.__PVT__rdx_op
         << CONTROL_WORD_WIDTH - 18) +
        (state.resulting_control_word.__PVT__reset
         << CONTROL_WORD_WIDTH - 19) +
        (state.resulting_control_word.__PVT__halt << CONTROL_WORD_WIDTH - 20) +
        (state.resulting_control_word.__PVT__control_unit_load
         << CONTROL_WORD_WIDTH - 21) +
        (state.resulting_control_word.__PVT__next_instr
         << CONTROL_WORD_WIDTH - 22);
}

void Microcode::ConvertMicrocodeToBin(const microcode_t& microcode,
                                      microcode_bin_t& microcode_bin) {
    for (int i = 0; i < (1 << MICRO_INSTRUCTION_WORD_WIDTH); i++) {
        if (microcode.microcode[i]) {
            ConvertInstructionStateToBin(*(microcode.microcode[i]),
                                         microcode_bin[i]);
        }
    }
}

void Microcode::PrimeMicrocode(microcode_t& microcode) {
    // state_0 for all 00000000000000 00001111111111
    // state_1 for all 00010000000000 00011111111111

    for (int i = 0; i < (1 << MICRO_INSTRUCTION_WORD_WIDTH); i++) {
        microcode.microcode[i] = &state_empty;
    }

    for (int i = 0; i < (1 << MICRO_INSTRUCTION_WORD_WIDTH - 4); i++) {
        microcode.microcode[i] = &state_0;
        microcode.microcode[i + (1 << MICRO_INSTRUCTION_WORD_WIDTH - 4)] =
            &state_1;

    }

   
}