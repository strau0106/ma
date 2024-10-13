#ifndef LIB_MICROCODE_H
#define LIB_MICROCODE_H

#include <cpu_control.h>
#include <macro_instruction.h>
#include <control_word.hpp>
#define ADDR_BUS_WIDTH 9
#define MICRO_INSTRUCTION_WORD_WIDTH 14
#define CONTROL_WORD_WIDTH 25

#define ALL_FLAGS                                                              \
    {                                                                          \
        cpu_control::alu_flag_e::NONE, cpu_control::alu_flag_e::ZERO,          \
            cpu_control::alu_flag_e::CARRY, cpu_control::alu_flag_e::REMAINDER \
    }

class Microcode {
   private:
    //typedef IData microcode_bin_t[(1 << MICRO_INSTRUCTION_WORD_WIDTH) - 1];
    typedef std::array<IData, (1 << MICRO_INSTRUCTION_WORD_WIDTH) - 1>
        microcode_bin_t;
    IData microcode_bin_instruction_state_t;

    //microcode_bin_t microcode_bin;
    std::array<ControlWord*, (1 << MICRO_INSTRUCTION_WORD_WIDTH) - 1> microcode = * new std::array<ControlWord *, (1 << MICRO_INSTRUCTION_WORD_WIDTH) - 1>();

    std::array<MacroInstruction*, 100> macro_instructions = * new std::array<MacroInstruction*, 100>();
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

#endif  // LIB_MICROCODE_H
