// Section 1.3.1: Memory
import control ::*;

module memory(
    input bit clock,
    input bit data_word,
    input bit[7:0] addr,
    input memory_op_e op,
    input memory_addr_mode_e addr_mode,
    output bit[7:0] data
);

endmodule
