#ifndef LIB_CONTROL_WORD_H
#define LIB_CONTROL_WORD_H

#include <verilated.h>
#define CONTROL_WORD_WIDTH 22
#define MICRO_INSTRUCTION_WORD_WIDTH 14
#define NUMBER_OF_FLAGS 4

class ControlWord {
   private:
    unsigned int alu_op : 4;
    unsigned int alu_enable : 1;
    unsigned int memory_op : 3;
    unsigned int data_word_selector : 1;
    unsigned int memory_bus_selector : 1;
    unsigned int rax_op : 2;
    unsigned int rbx_op : 2;
    unsigned int rcx_op : 2;
    unsigned int rdx_op : 2;
    unsigned int reset : 1;
    unsigned int halt : 1;
    unsigned int control_unit_load : 1;
    unsigned int next_instr : 1;

   public:
    ControlWord() {
        this->alu_op = 0;
        this->alu_enable = 0;
        this->memory_op = 0;
        this->data_word_selector = 0;
        this->memory_bus_selector = 0;
        this->rax_op = 0;
        this->rbx_op = 0;
        this->rcx_op = 0;
        this->rdx_op = 0;
        this->reset = 0;
        this->halt = 0;
        this->control_unit_load = 0;
        this->next_instr = 0;
    }

    ControlWord* set_alu_op(unsigned int alu_op) {
        this->alu_op = alu_op;
        return this;
    }

    ControlWord* set_alu_enable(unsigned int alu_enable) {
        this->alu_enable = alu_enable;
        return this;
    }

    ControlWord* set_memory_op(unsigned int memory_op) {
        this->memory_op = memory_op;
        return this;
    }

    ControlWord* set_data_word_selector(unsigned int data_word_selector) {
        this->data_word_selector = data_word_selector;
        return this;
    }

    ControlWord* set_memory_bus_selector(unsigned int memory_bus_selector) {
        this->memory_bus_selector = memory_bus_selector;
        return this;
    }

    ControlWord* set_rax_op(unsigned int rax_op) {
        this->rax_op = rax_op;
        return this;
    }

    ControlWord* set_rbx_op(unsigned int rbx_op) {
        this->rbx_op = rbx_op;
        return this;
    }

    ControlWord* set_rcx_op(unsigned int rcx_op) {
        this->rcx_op = rcx_op;
        return this;
    }

    ControlWord* set_rdx_op(unsigned int rdx_op) {
        this->rdx_op = rdx_op;
        return this;
    }

    ControlWord* set_reset(unsigned int reset) {
        this->reset = reset;
        return this;
    }

    ControlWord* set_halt(unsigned int halt) {
        this->halt = halt;
        return this;
    }

    ControlWord* set_control_unit_load(unsigned int control_unit_load) {
        this->control_unit_load = control_unit_load;
        return this;
    }

    ControlWord* set_next_instr(unsigned int next_instr) {
        this->next_instr = next_instr;
        return this;
    }

    IData bin() {
        std::cout << "nextisntr" << next_instr << std::endl;
        return ((alu_op) << (CONTROL_WORD_WIDTH - 4)) +
               ((alu_enable) << (CONTROL_WORD_WIDTH - 5)) +
               ((memory_op) << (CONTROL_WORD_WIDTH - 8)) +
               ((data_word_selector) << (CONTROL_WORD_WIDTH - 9)) +
               ((memory_bus_selector) << (CONTROL_WORD_WIDTH - 10)) +
               ((rax_op) << (CONTROL_WORD_WIDTH - 12)) +
               ((rbx_op) << (CONTROL_WORD_WIDTH - 14)) +
               ((rcx_op) << (CONTROL_WORD_WIDTH - 16)) +
               ((rdx_op) << (CONTROL_WORD_WIDTH - 18)) +
               ((reset) << (CONTROL_WORD_WIDTH - 19)) +
               ((halt) << (CONTROL_WORD_WIDTH - 20)) +
               ((control_unit_load) << (CONTROL_WORD_WIDTH - 21)) +
               ((next_instr) << (CONTROL_WORD_WIDTH - 22));
    }
};

#endif  // LIB_CONTROL_WORD_H
