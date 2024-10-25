#pragma once
#include <cpu_control.h>
#include <macro_instruction.h>
#include <control_word.hpp>

#define MICRO_INSTRUCTION_WORD_WIDTH 14
#define CONTROL_WORD_WIDTH 25

class Microcode {
   private:
    std::array<ControlWord*, (1 << MICRO_INSTRUCTION_WORD_WIDTH) - 1>
        microcode = *new std::array<ControlWord*,
                                    (1 << MICRO_INSTRUCTION_WORD_WIDTH) - 1>();

    std::array<MacroInstruction*, 100> macro_instructions =
        *new std::array<MacroInstruction*, 100>();

    unsigned int n_macro_instructions = 0;

    void PrimeMicrocode();  // insert fetch decode
    void ComputeMicrocodeForMacroInstruction(unsigned int opcode,
                                             MacroInstruction* instruction);

   public:
    Microcode() { PrimeMicrocode(); }

    void AddMacroInstruction(MacroInstruction* macro_instruction);
    unsigned int GetMacroInstructionOpcode(const char name[4]);

    std::map<std::string, unsigned int> ComputeOpCodes();

    void StoreMicrocodeIntoModel(IData* m_storage);

    void ComputeMicrocodeFromMacroInstructions();
};
