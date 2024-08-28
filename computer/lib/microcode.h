#ifndef LIB_MICROCODE_H
#define LIB_MICROCODE_H

#include <cpu_control.h>
#include <control_word.hpp>
#include <macro_instruction.hpp>
#define ADDR_BUS_WIDTH 9
#define MICRO_INSTRUCTION_WORD_WIDTH 14
#define CONTROL_WORD_WIDTH 22

#define ALL_FLAGS                                                              \
    {                                                                          \
        cpu_control::alu_flag_e::NONE, cpu_control::alu_flag_e::ZERO,          \
            cpu_control::alu_flag_e::CARRY, cpu_control::alu_flag_e::REMAINDER \
    }

class Microcode {
   private:
    typedef IData microcode_bin_t[(1 << MICRO_INSTRUCTION_WORD_WIDTH) - 1];

    IData microcode_bin_instruction_state_t;

    microcode_bin_t microcode;

    std::vector<MacroInstruction*> macro_instructions;

    void PrimeMicrocode();  // insert fetch decode
    void ComputeMicrocodeForMacroInstruction(unsigned int opcode,
                                             MacroInstruction* instruction);

   public:
    Microcode() { PrimeMicrocode(); }

    void AddMacroInstruction(MacroInstruction* macro_instruction);
    unsigned int GetMacroInstructionOpcode(const char name[4]);

    std::map<std::string, unsigned int> ComputeOpCodes();

    void StoreMicrocodeIntoModel(IData* m_storage);
};

#endif  // LIB_MICROCODE_H
