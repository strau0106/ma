#include <control_word.h>
#include <cpu_control.h>
#include <microcode.h>

void Microcode::PrimeMicrocode() {
    // state_0 for all 00000000000000 00001111111111
    // state_1 for all 00010000000000 00011111111111
    ControlWord* INC = new ControlWord();
    unsigned int INC_CONTROL_WORD =
        INC->set_memory_op(cpu_control::memory_op_e::INC)
            ->set_memory_bus_selector(cpu_control::memory_bus_selector_e::PC)
            ->bin();
    delete INC;

    ControlWord* FETCH = new ControlWord();
    unsigned int FETCH_CONTROL_WORD =
        FETCH->set_memory_op(cpu_control::memory_op_e::READ)
            ->set_memory_bus_selector(cpu_control::memory_bus_selector_e::PC)
            ->set_control_unit_load(1)
            ->bin();
    delete FETCH;

    ControlWord* NOP = new ControlWord();
    unsigned int NOP_CONTROL_WORD = NOP->bin();
    delete NOP;

    for (int i = 0; i < (1 << MICRO_INSTRUCTION_WORD_WIDTH); i++) {
        this->microcode[i] = NOP_CONTROL_WORD;
    }

    for (int i = 0; i < (1 << MICRO_INSTRUCTION_WORD_WIDTH - 4); i++) {
        this->microcode[i] = INC_CONTROL_WORD;
        this->microcode[i + (1 << MICRO_INSTRUCTION_WORD_WIDTH - 4)] =
            FETCH_CONTROL_WORD;
    }
}

void Microcode::StoreMicrocodeIntoModel(IData* m_storage) {
    std::copy(microcode, microcode + (1 << MICRO_INSTRUCTION_WORD_WIDTH) - 1,
              m_storage);
}