// Section 1.3.1: Memory
import control::*;

module memory (
    input bit clock,
    input bit reset,
    input bit[7:0] in,
    output bit[7:0] out,
    input bit data_word_selector,
    input memory_bus_selector_e bus_selector, // 0: MAR, 1: PC
    input memory_op_e op
);

    bit[(`ADDR_BUS_WIDTH-1):0] memory_address_register;
    bit[(`ADDR_BUS_WIDTH-1):0] programm_counter;
    bit[(`ADDR_BUS_WIDTH-1):0] selected_bus;

    assign selected_bus = bus_selector ? programm_counter : memory_address_register;

    bit[7:0] cells [(1<<`ADDR_BUS_WIDTH+1)-1];

    bit[7:0] out_tmp;

    assign out = (op == READ) ? out_tmp : 'z;

    always_ff @(posedge clock) begin
        if (reset) begin
            memory_address_register = 0;
            programm_counter = 0;
        end else
        case (op)
            default:
                ; // no operation
            READ:
                out_tmp = cells[{selected_bus, data_word_selector}];
            ABSOLUTE:
                if (bus_selector) programm_counter = {1'b0, in};
                else memory_address_register = {1'b0, in};
            REL_SUB:
                if (bus_selector) programm_counter = programm_counter - {1'b0, in};
                else memory_address_register = memory_address_register - {1'b0, in};
            REL_ADD:
                if (bus_selector) programm_counter = programm_counter + {1'b0, in};
                else memory_address_register = memory_address_register + {1'b0, in};
            INC:
                if(bus_selector) programm_counter = programm_counter + 1;
                else memory_address_register = memory_address_register + 1;
        endcase
    end
    always_ff @(negedge clock) begin
      case(op)
        default:
            ; // no operation
        WRITE:
            cells[{selected_bus, data_word_selector}] = in;
      endcase
    end
      
endmodule
