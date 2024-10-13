// Section 1.3.1: Arithmetic Logic Unit
import control ::*;

module alu(
    input bit clock,
    output wire[7:0] result,
    output alu_flag_e flag,
    input bit[7:0] register1,
    input bit[7:0] register2,
    input bit enable,
    input alu_op_e op
);
    bit[7:0] tmp;


    bit is_zero;
    bit is_carry;

    assign is_zero = (tmp == 0);

    assign result = enable ? tmp : 'z;

    always_ff @(posedge clock) begin
    case (op)
      default:
        ;
      ADD:
        {is_carry, tmp} = register1 + register2;
      SUB:
        tmp = register1 - register2;
      SHL:
        tmp = register1 << 1;
      ROL:
        tmp = {register1[6:0], register1[7:7]};
      SHR:
        tmp = register1 >> 1;
      ROR:
        tmp = {register1[0:0], register1[7:1]};
      AND:
        tmp = register1 & register2;
      OR:
        tmp = register1 | register2;
      XOR:
        tmp = register1 ^ register2;
      NOT:
        tmp = ~register1;
    endcase
    if (op != ALU_NOP) flag <= is_zero ? ZERO : ((is_carry & (op==ADD)) ? CARRY : NONE);
  end
endmodule
