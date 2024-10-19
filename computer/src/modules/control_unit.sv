// Section 1.3.4: Control Unit

import control::*;

module control_unit (
    output reg clock,
    output bit halt,

    output memory_op_e memory_op,
    output address_reg_op_e address_reg_op,
    output bit data_word_selector,
    output bit bus_selector,

    output alu_op_e alu_op,
    output bit alu_enable,
    input alu_flag_e alu_flag,

    output reg_op_e rax_op,
    output reg_op_e rbx_op,
    output reg_op_e rcx_op,
    output reg_op_e rdx_op,

    input bit[7:0] bus
);

    bit reset;
    bit clock_tmp;
    always
        #5 clock_tmp = ~clock_tmp;

    assign clock = ~halt ? clock_tmp : 0;

    bit[3:0] state;

    bit[7:0] macro_instruction;

    bit next_instr;
    bit load;


    bit[(`CONTROL_WORD_WIDTH-1):0] microcode[(1<<`MICRO_INSTRUCTION_WORD_WIDTH)-1];

    bit[(`MICRO_INSTRUCTION_WORD_WIDTH-1):0] micro_instruction_word;
    assign micro_instruction_word = {state, macro_instruction, alu_flag};

    bit[(`CONTROL_WORD_WIDTH-1):0] control_word;
    assign control_word = microcode[micro_instruction_word];

    // control_word decoding
    always_ff @(negedge clock) begin
        if (load) begin
           macro_instruction <= bus;
        end
        {alu_op, alu_enable, memory_op, address_reg_op, data_word_selector, bus_selector,
         rax_op, rbx_op, rcx_op, rdx_op, reset, halt, load, next_instr} <= control_word;
    end
    bit state_tmp;

    // state generation
    always_ff @(posedge clock) begin
        if (next_instr) begin
            state <= 4'h0;
        end else begin
            state_tmp <= ~state_tmp;
            state <= state + 1;
        end




    end
endmodule
