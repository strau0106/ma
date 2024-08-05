`define ADDR_BUS_WIDTH 9

package control;
    typedef enum {
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
    typedef enum {
        NONE,
        ZERO,
        CARRY,
        REMAINDER
    } alu_flag_e /*verilator public*/;
    typedef enum {
        NOP,
        READ,
        WRITE,
        ABSOLUTE,
        REL_SUB,
        REL_ADD
    } memory_op_e /*verilator public*/;
    typedef enum {
        ABSOLUTE,
        RELATIVE
    } memory_addr_mode_e /*verilator public*/;

endpackage
