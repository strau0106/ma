#include "assembler.h"

Assembler* Assembler::next(const char _name[4]) {
    memory[ptr] = this->microcode->GetMacroInstructionOpcode(_name);
    ptr++;
    ptr++;
    return this;
}

Assembler* Assembler::next(const char _name[4], char8_t arg) {
    memory[ptr] = this->microcode->GetMacroInstructionOpcode(_name);
    ptr++;
    memory[ptr] = arg;
    ptr++;
    return this;
}
void Assembler::StoreIntoModel(CData* m_storage) {
    std::copy(memory, memory + (1 << 9) - 1, m_storage);
}

unsigned int Assembler::GetCurrentInstructionAddress() const {
    return ptr / 2;
}

Assembler::Assembler(Microcode* _microcode) {
    this->microcode = _microcode;
    this->ptr = 0;
    std::fill(memory, memory + 16383 - 1, 0);
};
