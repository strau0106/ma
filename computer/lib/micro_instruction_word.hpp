#pragma once

#include <control_word.hpp>

class MicroInstructionWord {
    unsigned int flag : 2;
    unsigned int state : 4;
    unsigned int opcode : 8;

   public:
    MicroInstructionWord() {
        this->flag = 0;
        this->state = 0;
        this->opcode = 0;
    }
    MicroInstructionWord* set_flag(unsigned int _flag) {
        this->flag = _flag;
        return this;
    }
    MicroInstructionWord* set_state(unsigned int _state) {
        this->state = _state;
        return this;
    }
    MicroInstructionWord* set_opcode(unsigned int _opcode) {
        this->opcode = _opcode;
        return this;
    }
    unsigned int bin() const {
        const unsigned val = (state << (MICRO_INSTRUCTION_WORD_WIDTH - 4)) +
                             (opcode << (MICRO_INSTRUCTION_WORD_WIDTH - 12)) +
                             (flag);
        return val;
    }
};