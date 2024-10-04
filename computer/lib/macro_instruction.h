#ifndef LIB_MACRO_INSTRUCTION_H
#define LIB_MACRO_INSTRUCTION_H

#include <control_word.hpp>
#include <string>
#include <timing_state.hpp>

#define NUMBER_OF_FLAGS 4
#define NUMBER_OF_DEFINABLE_STATES 12

class MacroInstruction {
   private:
    std::string name;
    unsigned int opcode = 0;
    std::array<TimingState*, NUMBER_OF_DEFINABLE_STATES> timing_states;
    unsigned int current_state = 0;

   public:
    MacroInstruction(const char _name[4]);

    MacroInstruction* add_timing_state(char state_number,
                                       TimingState* timing_state);

    MacroInstruction* set_next_state(TimingState* next_state);

    MacroInstruction* set_remaining_states(TimingState* state);

    MacroInstruction* set_opcode(unsigned int opcode);

    std::string get_name() { return this->name; }

    unsigned int get_opcode() const { return this->opcode; }

    std::map<unsigned int, ControlWord*> bin_map();
};

#endif  // LIB_MACRO_INSTRUCTION_H