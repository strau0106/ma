// Test file for component of Section 1.3.4: Control Unit

#include <control_unit.h>
#include <control_unit___024root.h>
#include <control_unit_control.h>
#include <gtest/gtest.h>
#include <verilated.h>

class ControlUnit : public ::testing::Test {
   protected:
    control_unit* control_unit_dut;

    void SetUp() {
        control_unit_dut = new control_unit;

        control_unit_dut->eval();
    }

    void TearDown() {
        control_unit_dut->final();
        delete control_unit_dut;
    }

    void Cycle() {
        Verilated::timeInc(1);
        control_unit_dut->eval();
    }

    void MultipleCycles(int n) {
        for (int i = 0; i < n; i++) {
            Cycle();
        }
    }
};

TEST_F(ControlUnit, ArchRequirement1341) {
    control_unit_dut->eval();

    EXPECT_EQ(control_unit_dut->clock, 0);

    MultipleCycles(5);

    EXPECT_EQ(control_unit_dut->clock, 1);
}

TEST_F(ControlUnit, ArchRequirement1342) {
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
