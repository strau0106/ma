#pragma once

#include <cpu_control.h>
#include <globals.h>
#include <control_word.hpp>

class TimingState {
   private:
    std::array<ControlWord*, NUMBER_OF_FLAGS> control_words =
        std::array<ControlWord*, NUMBER_OF_FLAGS>();

   public:
    TimingState() {
        for (int i = 0; i < NUMBER_OF_FLAGS; i++) {
            this->control_words[i] = (new ControlWord())->set_next_instr(1);
        }
    }

    TimingState(ControlWord* default_control_word) {
        for (int i = 0; i < NUMBER_OF_FLAGS; i++) {
            this->control_words[i] = default_control_word;
        }
    }

    TimingState* override_control_word_for_flag(cpu_control::alu_flag_e flag,
                                                ControlWord* control_word) {
        this->control_words[flag] = control_word;
        return this;
    }

    std::array<ControlWord*, NUMBER_OF_FLAGS> bin() const {
        return this->control_words;
    }
};
