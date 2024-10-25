#pragma once
#include "microcode.h"

class Assembler {
   private:
    Microcode* microcode;
    unsigned int memory[16383];
    unsigned int ptr;

   public:
    explicit Assembler(Microcode* _microcode);

    Assembler* next(const char _name[4]);

    Assembler* next(const char _name[4], char8_t arg);

    void StoreIntoModel(CData* m_storage);

    unsigned int GetCurrentInstructionAddress() const;
};
