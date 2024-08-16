#ifndef LIB_MICROCODE_H
#define LIB_MICROCODE_H

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

#define INC_CONTROL_WORD_MACRO                                                \
    COMPUTE_CONCATENATED_CONTROL_WORD(                                  \
        cpu_control::alu_op_e::ALU_NOP,         /*alu_op*/              \
        0,                                      /*alu_enable*/          \
        cpu_control::memory_op_e::INC,          /*memory_op*/           \
        0,                                      /*data_word_selector*/  \
        cpu_control::memory_bus_selector_e::PC, /*memory_bus_selector*/ \
        cpu_control::reg_op_e::REG_NOP,         /*rax_op*/              \
        cpu_control::reg_op_e::REG_NOP,         /*rbx_op*/              \
        cpu_control::reg_op_e::REG_NOP,         /*rcx_op*/              \
        cpu_control::reg_op_e::REG_NOP,         /*rdx_op*/              \
        0,                                      /*reset*/               \
        0,                                      /*halt*/                \
        0,                                      /*control_unit_load*/   \
        0                                       /*next_instr*/          \
    )

#define FETCH_CONTROL_WORD_MACRO                                              \
    COMPUTE_CONCATENATED_CONTROL_WORD(                                  \
        cpu_control::alu_op_e::ALU_NOP,         /*alu_op*/              \
        0,                                      /*alu_enable*/          \
        cpu_control::memory_op_e::READ,         /*memory_op*/           \
        0,                                      /*data_word_selector*/  \
        cpu_control::memory_bus_selector_e::PC, /*memory_bus_selector*/ \
        cpu_control::reg_op_e::REG_NOP,         /*rax_op*/              \
        cpu_control::reg_op_e::REG_NOP,         /*rbx_op*/              \
        cpu_control::reg_op_e::REG_NOP,         /*rcx_op*/              \
        cpu_control::reg_op_e::REG_NOP,         /*rdx_op*/              \
        0,                                      /*reset*/               \
        0,                                      /*halt*/                \
        1,                                      /*control_unit_load*/   \
        0                                       /*next_instr*/          \
    )

#define NOP_CONTROL_WORD_MACRO                                                \
    COMPUTE_CONCATENATED_CONTROL_WORD(                                  \
        cpu_control::alu_op_e::ALU_NOP,         /*alu_op*/              \
        0,                                      /*alu_enable*/          \
        cpu_control::memory_op_e::NOP,          /*memory_op*/           \
        0,                                      /*data_word_selector*/  \
        cpu_control::memory_bus_selector_e::PC, /*memory_bus_selector*/ \
        cpu_control::reg_op_e::REG_NOP,         /*rax_op*/              \
        cpu_control::reg_op_e::REG_NOP,         /*rbx_op*/              \
        cpu_control::reg_op_e::REG_NOP,         /*rcx_op*/              \
        cpu_control::reg_op_e::REG_NOP,         /*rdx_op   */           \
        0,                                      /*reset*/               \
        0,                                      /*halt*/                \
        0,                                      /*control_unit_load*/   \
        0                                       /*next_instr*/          \
    )

class Microcode {
   public:
    struct micro_instruction_state_t {
        int resulting_control_word : CONTROL_WORD_WIDTH;
        cpu_control::alu_flag_e flags[4];
    };

    struct macro_instruction_t {
        const char* name;
        micro_instruction_state_t states[4];
    };

    struct microcode_t {
        micro_instruction_state_t* microcode[1 << MICRO_INSTRUCTION_WORD_WIDTH];
    };
    typedef IData microcode_bin_t[(1 << MICRO_INSTRUCTION_WORD_WIDTH) - 1];
    IData microcode_bin_instruction_state_t;
    static const int INC_CONTROL_WORD = INC_CONTROL_WORD_MACRO;
    static const int FETCH_CONTROL_WORD = FETCH_CONTROL_WORD_MACRO;
    static const int NOP_CONTROL_WORD = NOP_CONTROL_WORD_MACRO;
    static void PrimeMicrocode(microcode_bin_t& microcode);  // insert fetch decode

    static void ComputeMicrocode(const microcode_t& microcode,
                                 microcode_bin_t& microcode_bin);
};

#endif  // LIB_MICROCODE_H
