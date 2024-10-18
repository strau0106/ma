#ifndef LIB_ASSEMBLER_H
#define LIB_ASSEMBLER_H

#include "microcode.h"

class Assembler {
   private:
    Microcode* microcode;
    unsigned int memory[16383];
    unsigned int ptr;

   public:
    Assembler(Microcode* _microcode) {
        this->microcode = _microcode;
        this->ptr = 0;
        std::fill(memory, memory + 16383 - 1, 0);
    };
    Assembler* next(const char _name[4]) {
        memory[ptr] = this->microcode->GetMacroInstructionOpcode(_name);
        ptr++;
        ptr++;
        return this;
    }

    Assembler* next(const char _name[4], char8_t arg) {
        memory[ptr] = this->microcode->GetMacroInstructionOpcode(_name);
        ptr++;
        memory[ptr] = arg;
        ptr++;
        return this;
    }

    void StoreIntoModel(CData* m_storage) {
        std::copy(memory, memory + (1 << 9) - 1, m_storage);
    }

    const unsigned int GetCurrentInstructionAddress() {
        return ptr/2;
    }
};

#endif  // LIB_ASSEMBLER_H