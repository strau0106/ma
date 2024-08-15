`define ADDR_BUS_WIDTH 9
`define MICRO_INSTRUCTION_WORD_WIDTH 14
`define CONTROL_WORD_WIDTH 22


package control;
    typedef enum logic[3:0] {
        ALU_NOP,
        ADD,
        SUB,
        MUL,
        DIV,
        SHL,
        ROL,
        SHR,
        ROR,
        AND,
        OR,
        XOR,
        NOT
    } alu_op_e /*verilator public*/;
    typedef enum logic [1:0] {
        NONE,
        ZERO,
        CARRY,
        REMAINDER
    } alu_flag_e /*verilator public*/;
    typedef enum logic [2:0] {
        NOP,
        READ,
        WRITE,
        ABSOLUTE,
        REL_SUB,
        REL_ADD,
        INC
    } memory_op_e /*verilator public*/;
    typedef enum bit {
        MAR,
        PC
    } memory_bus_selector_e /*verilator public*/;
    typedef enum logic[1:0]{
        REG_NOP,
        LOAD,
        ENABLE
    } reg_op_e /*verilator public*/;

    typedef struct {
        alu_op_e alu_op;
        bit alu_enable;
        memory_op_e memory_op;
        bit data_word_selector;
        bit bus_selector;
        reg_op_e rax_op;
        reg_op_e rbx_op;
        reg_op_e rcx_op;
        reg_op_e rdx_op;
        bit reset;
        bit halt;
        bit control_unit_load;
        bit next_instr;
        } control_word_t;



endpackage
