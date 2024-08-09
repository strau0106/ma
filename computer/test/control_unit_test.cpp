// Test file for component of Section 1.3.1: Arithmetic Logic Unit

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
};

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    testing::InitGoogleTest(&argc, argv);
    auto res = RUN_ALL_TESTS();
    Verilated::mkdir("logs");
    VerilatedCov::write("logs/control_unit.dat");
    return res;
}
