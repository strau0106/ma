#ifndef LIB_MICRO_INSTRUCTION_WORD_HPP
#define LIB_MICRO_INSTRUCTION_WORD_HPP

#include <control_word.hpp>

class MicroInstructionWord {
   private:
    unsigned int flag : 2;
    unsigned int state : 4;
    unsigned int opcode : 8;

   public:
    MicroInstructionWord() {
        this->flag = 0;
        this->state = 0;
        this->opcode = 0;
    }
    MicroInstructionWord* set_flag(unsigned int flag) {
        this->flag = flag;
        return this;
    }
    MicroInstructionWord* set_state(unsigned int state) {
        this->state = state;
        return this;
    }
    MicroInstructionWord* set_opcode(unsigned int opcode) {
        this->opcode = opcode;
        return this;
    }
    unsigned int bin() const {
        const unsigned val = (state << (MICRO_INSTRUCTION_WORD_WIDTH - 4)) +
                             (opcode << (MICRO_INSTRUCTION_WORD_WIDTH - 12)) +
                             (flag);
        return val;
    }
};

#endif  // LIB_MICRO_INSTRUCTION_WORD_HPP