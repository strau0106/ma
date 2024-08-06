// Section 1.3.3: Register
import control::*;

module reg_acc (
    input bit clock,
    input bit[7:0] in,
    output bit[7:0] out,
    input reg_op_e op,
    output bit[7:0] reg_direct
);
    bit[7:0] tmp;

    assign out = (op == ENABLE) ? tmp : 'z; // New data only at posedge clock

    always_ff @(posedge clock) begin
        case (op)
            default:
                ; // no operation
            ENABLE:
                tmp <= reg_direct;
            LOAD:
                reg_direct <= in;
        endcase
    end
endmodule
