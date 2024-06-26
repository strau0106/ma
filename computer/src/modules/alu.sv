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
    input op_dir_e op_dir
  

);
    always_ff @(posedge clock) begin
        if (out & op_add+op_sub+op_mul+op_div+op_shift+op_rot==1) begin
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
            end
        end
    end

endmodule
