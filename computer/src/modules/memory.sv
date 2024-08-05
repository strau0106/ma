// Section 1.3.1: Memory
import control::*;

module memory (
    input bit clock,
    input bit[7:0] in,
    output bit[7:0] out,
    input bit data_word_selector,
    input memory_op_e op
);

    bit[(`ADDR_BUS_WIDTH-1):0] addr_reg;
    bit[7:0] cells [(1<<`ADDR_BUS_WIDTH+1)-1];

    bit[7:0] out_tmp;
    assign out = (op == READ) ? out_tmp : 'z;

    always_ff @(posedge clock) begin
        case (op)
            default:
                ; // no operation
            READ:
                out_tmp <= cells[{addr_reg, data_word_selector}];
            WRITE:
                cells[{addr_reg, data_word_selector}] <= in;
            ABSOLUTE:
                addr_reg <= {1'b0, in};
            REL_SUB:
                addr_reg <= addr_reg - {1'b0, in};
            REL_ADD:
                addr_reg <= addr_reg + {1'b0, in};
        endcase
    end
endmodule
