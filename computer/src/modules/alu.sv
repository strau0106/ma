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
    bit is_remainder;

    assign is_zero = (tmp == 0);
    assign is_remainder = (op == DIV) && (enable*register2 != register1);

    assign flag = (is_zero | !enable) ? ZERO :
                  ((is_carry & (op==ADD | op==MUL)) ? CARRY :
                  (is_remainder ? REMAINDER : NONE));

    assign result = enable ? tmp : 0;

    always_ff @(posedge clock) begin
    case (op)
      default:
        tmp <= 0;
      ADD:
        {is_carry, tmp} <= register1 + register2;
      SUB:
        tmp <= register1 - register2;
      MUL:
        {is_carry, tmp} <= register1 * register2;
      DIV:
        tmp <= register1 / register2;
      SHL:
        tmp <= register1 << 1;
      ROL:
        tmp <= {register1[6:0], register1[7:7]};
      SHR:
        tmp <= register1 >> 1;
      ROR:
        tmp <= {register1[0:0], register1[7:1]};
      AND:
        tmp <= register1 & register2;
      OR:
        tmp <= register1 | register2;
      XOR:
        tmp <= register1 ^ register2;
      NOT:
        tmp <= ~register1;
    endcase
  end
endmodule
