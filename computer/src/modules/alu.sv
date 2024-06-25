// Section 1.2 Arithmetic Logic Unit


module alu(
    input bit clock,
    output bit[8:0] result,
    input bit[8:0] register1,
    input bit[8:0] register2,
    input bit out,
    input bit op_add

);
    always_ff @(posedge clock) begin

    end

endmodule
