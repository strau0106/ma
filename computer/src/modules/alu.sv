// Section 1.3.1: Arithmetic Logic Unit
import control ::*;

module alu(
    input bit clock,
    output bit[7:0] result,
    input bit[7:0] register1,
    input bit[7:0] register2,
    input bit out,
    input alu_op_e alu_op,
);
    reg tmp[8:0]
    assign result = tmp[7:0] & {8{out}};
    
    always_ff @(posedge clock) begin
    
    case (alu_op)
    ADD:
      tmp <= register1 + register2;
    SUB: 
      tmp <= register1 - register2; // 
            if (alu_control.op_add) begin
                result <= register1 + register2;
            end else if (alu_control.op_sub) begin
                result <= register1 - register2;
            end else if (alu_control.op_mul) begin
                result <= register1 * register2;
            end else if (alu_control.op_div) begin
                result <= register1 / register2;
            end else if (alu_control.op_shift) begin
                if (alu_control.op_dir == LEFT) result <= register1 << 1;
                else result <= register1 >> 1;
            end else if (alu_control.op_rot) begin
                if (alu_control.op_dir == LEFT) result <= {register1[6:0], register1[7:7]};
                else result <= {register1[0:0], register1[7:1]};
            end else if (alu_control.op_and) begin
              result <= register1 & register2;
            end else if (alu_control.op_or) begin
              result <= register1 | register2;
            end else if (alu_control.op_xor) begin
              result <= register1 ^ register2;
            end else if (alu_control.op_not) begin
              result <= ~register1;
            end



        end
    end

endmodule
