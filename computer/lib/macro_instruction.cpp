#include <cpu_control.h>
#include <macro_instruction.h>
#include <micro_instruction_word.hpp>

MacroInstruction::MacroInstruction(const char _name[4]) {
    this->name = std::string(_name);
}

MacroInstruction* MacroInstruction::add_timing_state(
    char state_number, TimingState* timing_state) {
    this->timing_states[state_number] = timing_state;
    return this;
}

MacroInstruction* MacroInstruction::set_next_state(TimingState* next_state) {
    this->timing_states[this->current_state++] = next_state;
    return this;
}

MacroInstruction* MacroInstruction::set_remaining_states(TimingState* state) {
    for (unsigned int& i = this->current_state;
         i < NUMBER_OF_DEFINABLE_STATES; i++) {
        this->timing_states[i] = state;
    }
    return this;
}

MacroInstruction* MacroInstruction::set_opcode(unsigned int opcode) {
    this->opcode = opcode;
    return this;
}

std::map<unsigned int, ControlWord*> MacroInstruction::bin_map() {

    std::map<unsigned int, ControlWord*> bin_map;

    for (int i = 0; i < NUMBER_OF_DEFINABLE_STATES; i++) {

        std::array<ControlWord*, NUMBER_OF_FLAGS> bin_timing_state =
            this->timing_states[i]->bin();

        for (int j = 0; j < NUMBER_OF_FLAGS; j++) {
            unsigned int micro_instruction_word =
                (new MicroInstructionWord())
                    ->set_flag(j)
                    ->set_state(i + 4)
                    ->set_opcode(this->get_opcode())
                    ->bin();
            ControlWord* control_word = bin_timing_state[j];
            bin_map[micro_instruction_word] = control_word;
        }
    }
    return bin_map;
}