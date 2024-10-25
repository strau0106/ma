// Test file for component of Section 1.3.4: Control Unit

#include <control_unit.h>
#include <control_unit___024root.h>
#include <control_unit_control.h>
#include <gtest/gtest.h>
#include <verilated.h>

#include <control_word.hpp>

class ControlUnit : public ::testing::Test {
   protected:
    control_unit* control_unit_dut;

    void SetUp() override {
        control_unit_dut = new control_unit;

        control_unit_dut->eval();
    }

    void TearDown() override {
        control_unit_dut->final();
        delete control_unit_dut;
    }

    void Cycle() const {
        Verilated::timeInc(1);
        control_unit_dut->eval();
    }

    void MultipleCyclesKeepingStateZero(int n) const {
        for (int i = 0; i < n; i++) {
            Cycle();
            control_unit_dut->rootp->control_unit__DOT__state = 0;
        }
    }

    void MultipleCycles(int n) const {
        for (int i = 0; i < n; i++) {
            Cycle();
        }
    }
};

TEST_F(ControlUnit, ArchRequirement21421) {
    control_unit_dut->eval();
    control_unit_dut->rootp->bus = 0b10101011;
    control_unit_dut->rootp->control_unit__DOT__load = 1;

    MultipleCycles(10);

    EXPECT_EQ(control_unit_dut->rootp->control_unit__DOT__macro_instruction,
              0b10101011);
}

TEST_F(ControlUnit, ArchRequirement21422) {
    control_unit_dut->eval();

    // Ensure all bits correctly of the control word are correctly translated and transferred into the model.
    for (int i = 0; i < 22; i++) {
        control_unit_dut->rootp->control_unit__DOT__microcode.m_storage[0] =
            (1 << i);
        std::cout << (1 << i) << std::endl;
        for (int j = 0; j < 10; j++) {
            control_unit_dut->rootp->control_unit__DOT__state = 0;
            control_unit_dut->rootp->control_unit__DOT____Vtogcov__state = 0;
            control_unit_dut->halt = 0;
            Cycle();
        }
        EXPECT_EQ(control_unit_dut->rootp->control_unit__DOT__control_word,
                  (1 << i));
    }

    // Ensure all components of the control word are correctly translated and transfered into the model.

    control_unit_dut->rootp->control_unit__DOT__microcode.m_storage[0] =
        ControlWord().set_alu_op(control_unit_control::alu_op_e::ROL)->bin();
    MultipleCyclesKeepingStateZero(10);
    EXPECT_EQ(control_unit_dut->alu_op, control_unit_control::alu_op_e::ROL);

    control_unit_dut->rootp->control_unit__DOT__microcode.m_storage[0] =
        ControlWord().set_alu_enable(1)->bin();
    MultipleCyclesKeepingStateZero(10);
    EXPECT_EQ(control_unit_dut->alu_enable, 1);

    control_unit_dut->rootp->control_unit__DOT__microcode.m_storage[0] =
        ControlWord().set_memory_op(0b11)->bin();
    MultipleCyclesKeepingStateZero(10);
    EXPECT_EQ(control_unit_dut->memory_op, 0b11);

    control_unit_dut->rootp->control_unit__DOT__microcode.m_storage[0] =
        ControlWord().set_data_word_selector(0b1)->bin();
    MultipleCyclesKeepingStateZero(10);
    EXPECT_EQ(control_unit_dut->data_word_selector, 0b1);

    control_unit_dut->rootp->control_unit__DOT__microcode.m_storage[0] =
        ControlWord().set_memory_bus_selector(0b1)->bin();
    MultipleCyclesKeepingStateZero(10);
    EXPECT_EQ(control_unit_dut->bus_selector, 0b1);

    control_unit_dut->rootp->control_unit__DOT__microcode.m_storage[0] =
        ControlWord().set_rax_op(0b11)->bin();
    MultipleCyclesKeepingStateZero(10);
    EXPECT_EQ(control_unit_dut->rax_op, 0b11);

    control_unit_dut->rootp->control_unit__DOT__microcode.m_storage[0] =
        ControlWord().set_rbx_op(0b11)->bin();
    MultipleCyclesKeepingStateZero(10);
    EXPECT_EQ(control_unit_dut->rbx_op, 0b11);

    control_unit_dut->rootp->control_unit__DOT__microcode.m_storage[0] =
        ControlWord().set_rcx_op(0b11)->bin();
    MultipleCyclesKeepingStateZero(10);
    EXPECT_EQ(control_unit_dut->rcx_op, 0b11);

    control_unit_dut->rootp->control_unit__DOT__microcode.m_storage[0] =
        ControlWord().set_rdx_op(0b11)->bin();
    MultipleCyclesKeepingStateZero(10);
    EXPECT_EQ(control_unit_dut->rdx_op, 0b11);

    control_unit_dut->rootp->control_unit__DOT__microcode.m_storage[0] =
        ControlWord().set_reset(0b1)->bin();
    MultipleCyclesKeepingStateZero(10);
    EXPECT_EQ(control_unit_dut->rootp->control_unit__DOT__reset, 0b1);

    // skip halt for now because it is annoying to handle

    control_unit_dut->rootp->control_unit__DOT__microcode.m_storage[0] =
        ControlWord().set_control_unit_load(0b1)->bin();
    MultipleCyclesKeepingStateZero(10);
    EXPECT_EQ(control_unit_dut->rootp->control_unit__DOT__load, 0b1);

    control_unit_dut->rootp->control_unit__DOT__microcode.m_storage[0] =
        ControlWord().set_next_instr(0b1)->bin();
    MultipleCyclesKeepingStateZero(10);
    EXPECT_EQ(control_unit_dut->rootp->control_unit__DOT__next_instr, 0b1);

    control_unit_dut->rootp->control_unit__DOT__microcode.m_storage[0] =
        ControlWord().set_halt(0b1)->bin();
    MultipleCyclesKeepingStateZero(10);
    EXPECT_EQ(control_unit_dut->rootp->halt, 0b1);
}

TEST_F(ControlUnit, ArchRequirement2143) {
    EXPECT_EQ(control_unit_dut->clock, 0);
    MultipleCycles(5);
    EXPECT_EQ(control_unit_dut->clock, 1);
}

TEST_F(ControlUnit, ArchRequirement2144) {
    // state increments by 1 every cycle and resets after 0xF

    control_unit_dut->eval();

    EXPECT_EQ(control_unit_dut->rootp->control_unit__DOT__state, 0);

    MultipleCycles(5);

    EXPECT_EQ(control_unit_dut->rootp->control_unit__DOT__state, 1);

    for (int i = 1; i < 15; i++) {
        MultipleCycles(10);
        EXPECT_EQ(control_unit_dut->rootp->control_unit__DOT__state, i + 1);
    }

    MultipleCycles(10);

    EXPECT_EQ(control_unit_dut->rootp->control_unit__DOT__state, 0);
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    testing::InitGoogleTest(&argc, argv);
    auto res = RUN_ALL_TESTS();
    Verilated::mkdir("logs");
    VerilatedCov::write("logs/control_unit.dat");
    return res;
}
