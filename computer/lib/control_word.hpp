#ifndef LIB_CONTROL_WORD_H
#define LIB_CONTROL_WORD_H

#include <verilated.h>
#define CONTROL_WORD_WIDTH 25
#define MICRO_INSTRUCTION_WORD_WIDTH 14
#define NUMBER_OF_FLAGS 4

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

    ControlWord* set_address_reg_op(unsigned int address_reg_op) {
        this->address_reg_op = address_reg_op;
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

    unsigned int bin() {
        //
        //std::cout << "nextisntr" << next_instr << std::endl;
        /*
        std::cout << "alu_op: " << this->alu_op << std::endl;
        std::cout << "alu_enable: " << this->alu_enable << std::endl;
        std::cout << "memory_op: " << this->memory_op << std::endl;
        std::cout << "data_word_selector: " << this->data_word_selector << std::endl;
        std::cout << "memory_bus_selector: " << this->memory_bus_selector << std::endl;
        std::cout << "rax_op: " << this->rax_op << std::endl;
        std::cout << "rbx_op: " << this->rbx_op << std::endl;
        std::cout << "rcx_op: " << this->rcx_op << std::endl;
        std::cout << "rdx_op: " << this->rdx_op << std::endl;
        std::cout << "reset: " << this->reset << std::endl;
        std::cout << "halt: " << this->halt << std::endl;
        std::cout << "control_unit_load: " << this->control_unit_load << std::endl;
        std::cout << "next_instr: " << this->next_instr << std::endl;
        */
        if (this->alu_op > 10) {
            throw std::runtime_error("asd");
        }

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

#endif  // LIB_CONTROL_WORD_H
