#pragma once

#include <globals.h>
#include <verilated.h>

class ControlWord {
   private:
    unsigned int alu_op : 4 = 0;
    unsigned int alu_enable : 1 = 0;
    unsigned int memory_op : 3 = 0;
    unsigned int address_reg_op : 3 = 0;
    unsigned int data_word_selector : 1 = 0;
    unsigned int memory_bus_selector : 1 = 0;
    unsigned int rax_op : 2 = 0;
    unsigned int rbx_op : 2 = 0;
    unsigned int rcx_op : 2 = 0;
    unsigned int rdx_op : 2 = 0;
    unsigned int reset : 1 = 0;
    unsigned int halt : 1 = 0;
    unsigned int control_unit_load : 1 = 0;
    unsigned int next_instr : 1 = 0;

   public:
    ControlWord* set_alu_op(unsigned int _alu_op) {
        this->alu_op = _alu_op;
        return this;
    }

    ControlWord* set_alu_enable(unsigned int _alu_enable) {
        this->alu_enable = _alu_enable;
        return this;
    }

    ControlWord* set_memory_op(unsigned int _memory_op) {
        this->memory_op = _memory_op;
        return this;
    }

    ControlWord* set_address_reg_op(unsigned int _address_reg_op) {
        this->address_reg_op = _address_reg_op;
        return this;
    }

    ControlWord* set_data_word_selector(unsigned int _data_word_selector) {
        this->data_word_selector = _data_word_selector;
        return this;
    }

    ControlWord* set_memory_bus_selector(unsigned int _memory_bus_selector) {
        this->memory_bus_selector = _memory_bus_selector;
        return this;
    }

    ControlWord* set_rax_op(unsigned int _rax_op) {
        this->rax_op = _rax_op;
        return this;
    }

    ControlWord* set_rbx_op(unsigned int _rbx_op) {
        this->rbx_op = _rbx_op;
        return this;
    }

    ControlWord* set_rcx_op(unsigned int _rcx_op) {
        this->rcx_op = _rcx_op;
        return this;
    }

    ControlWord* set_rdx_op(unsigned int _rdx_op) {
        this->rdx_op = _rdx_op;
        return this;
    }

    ControlWord* set_reset(unsigned int _reset) {
        this->reset = _reset;
        return this;
    }

    ControlWord* set_halt(unsigned int _halt) {
        this->halt = _halt;
        return this;
    }

    ControlWord* set_control_unit_load(unsigned int _control_unit_load) {
        this->control_unit_load = _control_unit_load;
        return this;
    }

    ControlWord* set_next_instr(unsigned int _next_instr) {
        this->next_instr = _next_instr;
        return this;
    }

    unsigned int bin() const {
        return ((this->alu_op) << (CONTROL_WORD_WIDTH - 4)) +
               ((this->alu_enable) << (CONTROL_WORD_WIDTH - 5)) +
               ((this->memory_op) << (CONTROL_WORD_WIDTH - 8)) +
               ((this->address_reg_op) << (CONTROL_WORD_WIDTH - 11)) +
               ((this->data_word_selector) << (CONTROL_WORD_WIDTH - 12)) +
               ((this->memory_bus_selector) << (CONTROL_WORD_WIDTH - 13)) +
               ((this->rax_op) << (CONTROL_WORD_WIDTH - 15)) +
               ((this->rbx_op) << (CONTROL_WORD_WIDTH - 17)) +
               ((this->rcx_op) << (CONTROL_WORD_WIDTH - 19)) +
               ((this->rdx_op) << (CONTROL_WORD_WIDTH - 21)) +
               ((this->reset) << (CONTROL_WORD_WIDTH - 22)) +
               ((this->halt) << (CONTROL_WORD_WIDTH - 23)) +
               ((this->control_unit_load) << (CONTROL_WORD_WIDTH - 24)) +
               next_instr;
    }
};
