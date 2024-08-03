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
        READ,
        WRITE
    } memory_op_e /*verilator public*/;
    typedef enum {
        ABSOLUTE,
        RELATIVE
    } memory_addr_mode_e /*verilator public*/;

endpackage
