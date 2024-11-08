// Section 1.3.2: Memory

#include <gtest/gtest.h>
#include <reg_tmp.h>
#include <reg_tmp___024root.h>
#include <reg_tmp_control.h>
#include <verilated.h>

class RegTmp : public ::testing::Test {
   protected:
    reg_tmp* reg_tmp_dut;

    void AdvanceClock() {
        reg_tmp_dut->clock = 1;
        reg_tmp_dut->eval();
        reg_tmp_dut->clock = 0;
        reg_tmp_dut->eval();
    }

    void SetUp() override {
        reg_tmp_dut = new reg_tmp;
        reg_tmp_dut->eval();
    }

    void TearDown() override {
        reg_tmp_dut->final();
        delete reg_tmp_dut;
    }
};

TEST_F(RegTmp, TuringRequirement2131) {
    reg_tmp_dut->op = reg_tmp_control::reg_op_e::LOAD;
    reg_tmp_dut->in = 0b11101111;

    AdvanceClock();

    ASSERT_EQ(reg_tmp_dut->rootp->reg_tmp__DOT__reg_tmp, 0b11101111);
}

TEST_F(RegTmp, TuringRequirement2132) {
    reg_tmp_dut->op = reg_tmp_control::reg_op_e::ENABLE;
    reg_tmp_dut->rootp->reg_tmp__DOT__reg_tmp = 0b11101111;

    AdvanceClock();

    ASSERT_EQ(reg_tmp_dut->out, 0b11101111);
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    testing::InitGoogleTest(&argc, argv);
    auto res = RUN_ALL_TESTS();
    Verilated::mkdir("logs");
    VerilatedCov::write("logs/reg_tmp.dat");
    return res;
}
