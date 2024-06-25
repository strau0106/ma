// Section 1.2.1: Arithmetic Logic Unit


module alu(
    input bit clock,
    output bit[8:0] result,
    input bit[8:0] register1,
    input bit[8:0] register2,
    input bit out,
    input bit op_add,
    input bit op_sub,
    input bit op_mul,
    input bit op_div,
    input bit op_shift,
    input bit op_rot,
    input bit op_dir


);
    always_ff @(posedge clock) begin
        if (out) begin
            if (op_add) begin
                result <= register1 + register2;
            end
            else if (op_sub) begin
                result <= register1 - register2;
            end
        end
    end

endmodule
