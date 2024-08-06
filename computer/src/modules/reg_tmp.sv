// Section 1.3.3: Register
import control::*;

module reg_tmp (
    input bit clock,
    input bit reset,
    input bit[7:0] in,
    output bit[7:0] out,
    input reg_op_e op
);

    bit[7:0] reg_tmp;

    bit[7:0] tmp;

    assign out = (op == ENABLE) ? tmp : 'z;

    always_ff @(posedge clock) begin
        if (reset) begin
            reg_tmp <= 8'h00;
        end else begin
            case (op)
                default:
                    ; // no operation
                ENABLE:
                    tmp <= reg_tmp;
                LOAD:
                    reg_tmp <= in;
            endcase
        end
    end
endmodule
