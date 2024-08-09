// generate microcode given a list of makro_instruction_t
// first n states always fetch decode exe etc
#include<microcode.h>
#include<cpu_control.h>

#define ALL_FLAGS {cpu_control::alu_flag_e::NONE, cpu_control::alu_flag_e::ZERO, cpu_control::alu_flag_e::CARRY, cpu_control::alu_flag_e::REMAINDER}

// state 0 inc => bus_selector = pc, memory_op = INC
// state 1 load instr in control unit => data_word_selector = 0, bus_selector = pc, memory_op = READ, control_unit.load = enable
// for state 0 and 1 all flags are valid.


 Microcode::micro_instruction_state_t state_0 = {
    {
     cpu_control::alu_op_e::ALU_NOP,
     0, // alu_enable, 
    cpu_control::memory_op_e::INC,
    0, // data_word_selector
    cpu_control::memory_bus_selector_e::PC,
    cpu_control::reg_op_e::REG_NOP,
    cpu_control::reg_op_e::REG_NOP,
    cpu_control::reg_op_e::REG_NOP,
    cpu_control::reg_op_e::REG_NOP,
    0, // reset
    0, // halt
    0, // control_unit_load
    0, // next_instr
    },
    ALL_FLAGS
};

 Microcode::micro_instruction_state_t state_1 = {
    {
     cpu_control::alu_op_e::ALU_NOP,
     0, // alu_enable, 
    cpu_control::memory_op_e::READ,
    0, // data_word_selector
    cpu_control::memory_bus_selector_e::PC,
    cpu_control::reg_op_e::REG_NOP,
    cpu_control::reg_op_e::REG_NOP,
    cpu_control::reg_op_e::REG_NOP,
    cpu_control::reg_op_e::REG_NOP,
    0, // reset
    0, // halt
    1, // control_unit_load
    0, // next_instr
    },
    ALL_FLAGS
};


void Microcode::PrimeMicrocode(microcode_t &microcode) {
    // must insert state_0 at 00000000000000 00001111111111
    // and state_1 at 00010000000000 00011111111111
    int numStates = 1 << (MICRO_INSTRUCTION_WORD_WIDTH - 4);
    std::fill(microcode.microcode, microcode.microcode + numStates, &state_0);
    std::fill(microcode.microcode + numStates, microcode.microcode + (numStates << 1), &state_1);
    
}
