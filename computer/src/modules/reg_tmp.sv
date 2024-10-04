// Section 1.3.3: Register
import control::*;

module reg_tmp (
    input bit clock,
    input bit[7:0] in,
    output bit[7:0] out,
    input reg_op_e op
);

    bit[7:0] reg_tmp;

    bit[7:0] tmp;

    assign out = (op == ENABLE) ? tmp : 'z;

    always_ff @(posedge clock) begin
        case (op)
            default:
                ; // no operation
            ENABLE:
                tmp = reg_tmp;
        endcase
    end
    always_ff @(negedge clock) begin
        case (op)
            default:
                ; // no operation
            LOAD:
                reg_tmp = in;
        endcase
    end
endmodule
