#include <cpu_control.h>
#include <microcode.h>
#include <control_word.hpp>

#include <bitset>
#include <macro_instruction.hpp>
#include <ranges>

void Microcode::PrimeMicrocode() {
    // state_0 for all 00000000000000 00001111111111
    // state_1 for all 00010000000000 00011111111111
    ControlWord* INC_CONTROL_WORD =
        ControlWord()
            .set_memory_op(6)
            ->set_memory_bus_selector(cpu_control::memory_bus_selector_e::PC);

    ControlWord* FETCH_CONTROL_WORD =
        ControlWord()
            .set_memory_op(1)
            ->set_memory_bus_selector(cpu_control::memory_bus_selector_e::PC);

    ControlWord* LOAD_CONTROL_WORD = ControlWord()
            .set_control_unit_load(1)
            ->set_memory_op(1)
            ->set_memory_bus_selector(cpu_control::memory_bus_selector_e::PC);

    ControlWord* NOP_CONTROL_WORD = new ControlWord();

    for (int i = 0; i < (1 << MICRO_INSTRUCTION_WORD_WIDTH); i++) {
        this->microcode[i] = NOP_CONTROL_WORD;
    }

    for (int i = 0; i < (1 << MICRO_INSTRUCTION_WORD_WIDTH - 4); i++) {
        this->microcode[i] = INC_CONTROL_WORD;
        this->microcode[i + (1 << MICRO_INSTRUCTION_WORD_WIDTH - 4)] =
            FETCH_CONTROL_WORD;
        this->microcode[i + (1 << MICRO_INSTRUCTION_WORD_WIDTH - 3)] = LOAD_CONTROL_WORD;
    }
}

std::map<std::string, unsigned int> Microcode::ComputeOpCodes() {
    std::map<std::string, unsigned int> opcodes;
    unsigned int opcode = 0;
    for (MacroInstruction* macro_instruction : this->macro_instructions) {
        opcodes[macro_instruction->get_name()] = opcode++;
    }
    return opcodes;
}

void Microcode::ComputeMicrocodeForMacroInstruction(
    unsigned int opcode, MacroInstruction* instruction) {
    instruction->set_opcode(opcode);
    auto map = instruction->bin_map();

    for (auto keys = std::views::keys(map); auto key : keys) {
        this->microcode[key] = map[key];
    }
}

void Microcode::ComputeMicrocodeFromMacroInstructions() {
    std::map<std::string, unsigned int> opcodes = this->ComputeOpCodes();
    for (MacroInstruction* macro_instruction : this->macro_instructions) {
        ComputeMicrocodeForMacroInstruction(
            opcodes[macro_instruction->get_name()], macro_instruction);
    }
}

void Microcode::StoreMicrocodeIntoModel(IData* m_storage) {

    for (unsigned int i = 0; i < (1 << MICRO_INSTRUCTION_WORD_WIDTH)-1; i++) {

        std::cout << microcode[i] << std::endl;
        m_storage[i] = microcode[i]->bin();
    }

}

void Microcode::AddMacroInstruction(MacroInstruction* macro_instruction) {
    this->macro_instructions[this->n_macro_instructions++] = macro_instruction;
}
unsigned int Microcode::GetMacroInstructionOpcode(const char name[4]) {
    for (auto macro_instruction : this->macro_instructions) {
        if (macro_instruction->get_name() == name) {
            return macro_instruction->get_opcode();
        }
    }
    throw std::runtime_error("Unknown microcode opcode");
}