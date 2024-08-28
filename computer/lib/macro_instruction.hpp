#ifndef LIB_MACRO_INSTRUCTION_H
#define LIB_MACRO_INSTRUCTION_H

#include <cpu_control.h>
#include <control_word.hpp>
#include <micro_instruction_word.hpp>
#include <string>
#include <timing_state.hpp>

#define NUMBER_OF_FLAGS 4
#define NUMBER_OF_DEFINABLE_STATES 14

class MacroInstruction {
   private:
    std::string name;
    unsigned int opcode;
    TimingState* timing_states[NUMBER_OF_DEFINABLE_STATES];
    char current_state = 0;

   public:
    MacroInstruction(const char _name[4], TimingState* first_state) {

        this->name = std::string(_name);
        this->timing_states[0] = first_state;

        for (int i = 1; i < NUMBER_OF_DEFINABLE_STATES; i++) {
            this->timing_states[i] = (new TimingState(
                ControlWord().set_next_instr(1)));  // NOP / next_instr
        }
    }

    MacroInstruction* add_timing_state(char state_number,
                                       TimingState* timing_state) {
        this->timing_states[state_number] = timing_state;
        return this;
    }

    MacroInstruction* set_next_state(TimingState* next_state) {
        this->timing_states[++this->current_state] = next_state;
        return this;
    }

    MacroInstruction* set_remaing_states(TimingState* next_state) {
        for (int i = this->current_state; i < NUMBER_OF_DEFINABLE_STATES; i++) {
            this->timing_states[i] = next_state;
        }
        return this;
    }

    MacroInstruction* set_opcode(unsigned int opcode) {
        this->opcode = opcode;
        return this;
    }

    std::string get_name() { return this->name; }

    unsigned int get_opcode() { return this->opcode; }

    std::map<unsigned int, unsigned int> bin_map() {
        std::map<unsigned int, unsigned int> bin_map;
        for (int i = 0; i < NUMBER_OF_DEFINABLE_STATES; i++) {
            const unsigned int* bin_timing_state =
                this->timing_states[i]->bin();
            for (int j = 0; j < NUMBER_OF_FLAGS; j++) {
                unsigned int micro_instruction_word =
                    MicroInstructionWord()
                        .set_flag(j)
                        ->set_state(i + 2)
                        ->set_opcode(this->get_opcode())
                        ->bin();
                bin_map[micro_instruction_word] = bin_timing_state[j];
            }
        }
        return bin_map;
    }
};

#endif  // LIB_MACRO_INSTRUCTION_H