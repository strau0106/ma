#ifndef LIB_MACRO_INSTRUCTION_H
#define LIB_MACRO_INSTRUCTION_H

#include <cpu_control.h>
#include <control_word.hpp>
#include <micro_instruction_word.hpp>
#include <string>
#include <timing_state.hpp>

#define NUMBER_OF_FLAGS 4
#define NUMBER_OF_DEFINABLE_STATES 13

class MacroInstruction {
   private:
    std::string name;
    unsigned int opcode=0;
    std::array<std::array<ControlWord *, NUMBER_OF_FLAGS>, NUMBER_OF_DEFINABLE_STATES> timing_states;
    unsigned int current_state = 0;

   public:
    MacroInstruction(const char _name[4], TimingState* first_state) {
        this->name = std::string(_name);

        this->timing_states[0] = first_state->bin();

        for (int i = 0; i < NUMBER_OF_DEFINABLE_STATES; i++) {
            this->timing_states[i] = (new TimingState(
                (new ControlWord())->set_next_instr(1)))->bin();  // NOP / next_instr
        }
    }

    MacroInstruction* add_timing_state(char state_number,
                                       TimingState* timing_state) {
        this->timing_states[state_number] = timing_state->bin();
        return this;
    }

    MacroInstruction* set_next_state(TimingState* next_state) {
        this->timing_states[++this->current_state] = next_state->bin();
        return this;
    }

    MacroInstruction* set_remaing_states(TimingState* state) {
        this->current_state++;
        for (unsigned int i = ++this->current_state; i < NUMBER_OF_DEFINABLE_STATES; i++) {
            this->timing_states[i] = state->bin();
        }
        return this;
    }

    MacroInstruction* set_opcode(unsigned int opcode) {
        this->opcode = opcode;
        return this;
    }

    std::string get_name() { return this->name; }

    unsigned int get_opcode() { return this->opcode; }

    std::map<unsigned int, ControlWord *> bin_map() {
        /*set_remaing_states(new TimingState(
                ControlWord().set_next_instr(1)));*/

        std::map<unsigned int, ControlWord *> bin_map;

        for (int i = 0; i < NUMBER_OF_DEFINABLE_STATES; i++) {

            std::array<ControlWord *, NUMBER_OF_FLAGS> bin_timing_state =
                this->timing_states[i];

            for (int j = 0; j < NUMBER_OF_FLAGS; j++) {
                unsigned int micro_instruction_word =
                    MicroInstructionWord()
                        .set_flag(j)
                        ->set_state(i + 3)
                        ->set_opcode(this->get_opcode())
                        ->bin();
                auto control_word = bin_timing_state[j];
                bin_map[micro_instruction_word] = control_word;
            }
        }
        return bin_map;
    }
};

#endif  // LIB_MACRO_INSTRUCTION_H