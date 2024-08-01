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
endpackage
