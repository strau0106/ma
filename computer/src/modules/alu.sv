// Section 1.2.1: Arithmetic Logic Unit
import control ::*;

module alu(
    input bit clock,
    output bit[7:0] result,
    input bit[7:0] register1,
    input bit[7:0] register2,
    input bit out,
    input bit op_add,
    input bit op_sub,
    input bit op_mul,
    input bit op_div,
    input bit op_shift,
    input bit op_rot,
    input op_dir_e op_dir,
    input bit op_and, 
    input bit op_or, 
    input bit op_xor,
    input bit op_not
);
    always_ff @(posedge clock) begin
        bit[9:0] op_sum = {op_add,op_sub,op_mul,op_div,op_shift,op_rot,op_and,op_or,op_xor,op_not}; 
        if (out && ^op_sum==1'b1) begin
            if (op_add) begin
                result <= register1 + register2;
            end else if (op_sub) begin
                result <= register1 - register2;
            end else if (op_mul) begin
                result <= register1 * register2;
            end else if (op_div) begin
                result <= register1 / register2;
            end else if (op_shift) begin
                if (op_dir == LEFT) result <= register1 << 1;
                else result <= register1 >> 1;
            end else if (op_rot) begin
                if (op_dir == LEFT) result <= {register1[6:0], register1[7:7]};
                else result <= {register1[0:0], register1[7:1]};
            end else if (op_and) begin
              result <= register1 & register2;
            end else if (op_or) begin
              result <= register1 | register2;
            end else if (op_xor) begin
              result <= register1 ^ register2;
            end else if (op_not) begin
              result <= ~register1;
            end



        end
    end

endmodule
