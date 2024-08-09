// connect everything up. bus to everything. reg_direct from rax and rbx to alu. everything else to control_unit    
module cpu ();

    logic clock;
    logic reset;
    logic halt;

    wire [7:0] bus;

    memory_op_e memory_op;
    bit data_word_selector;
    bit bus_selector;

    alu_op_e alu_op;
    bit alu_enable;
    alu_flag_e alu_flag;

    reg_op_e rax_op;
    reg_op_e rbx_op;
    reg_op_e rcx_op;
    reg_op_e rdx_op;

    wire [7:0] rax_direct;
    wire [7:0] rbx_direct;

    reg_acc rax (
        .clock(clock),
        .reset(reset),
        .in(bus),
        .out(bus),
        .op(rax_op),
        .reg_direct(rax_direct)
    );

    reg_acc rbx (
        .clock(clock),
        .reset(reset),
        .in(bus),
        .out(bus),
        .op(rbx_op),
        .reg_direct(rbx_direct)
    );

    reg_tmp rcx (
        .clock(clock),
        .reset(reset),
        .in(bus),
        .out(bus),
        .op(rcx_op)
    );

    reg_tmp rdx (
        .clock(clock),
        .reset(reset),
        .in(bus),
        .out(bus),
        .op(rdx_op)
    );

    alu alu (
        .clock(clock),
        .result(bus),
        .flag(alu_flag),
        .register1(rax_direct),
        .register2(rbx_direct),
        .enable(alu_enable),
        .op(alu_op)
    );

    control_unit control_unit (
        .clock(clock),
        .reset(reset),
        .halt(halt),
        .memory_op(memory_op),
        .data_word_selector(data_word_selector),
        .bus_selector(bus_selector),
        .alu_op(alu_op),
        .alu_enable(alu_enable),
        .alu_flag(alu_flag),
        .rax_op(rax_op),
        .rbx_op(rbx_op),
        .rcx_op(rcx_op),
        .rdx_op(rdx_op),
        .bus(bus)
        );

    memory memory (
        .clock(clock),
        .reset(reset),
        .in(bus),
        .out(bus),
        .op(memory_op),
        .data_word_selector(data_word_selector),
        .bus_selector(bus_selector)
    );

endmodule
