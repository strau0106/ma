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

    void SetUp() {
        reg_tmp_dut = new reg_tmp;
        reg_tmp_dut->eval();
    }

    void TearDown() {
        reg_tmp_dut->final();
        delete reg_tmp_dut;
    }
};

TEST_F(RegTmp, TuringRequirement1332) {
    reg_tmp_dut->op = reg_tmp_control::reg_op_e::ENABLE;
    reg_tmp_dut->rootp->reg_tmp__DOT__reg_tmp = 0b1010101;

    AdvanceClock();

    ASSERT_EQ(reg_tmp_dut->out, 0b1010101);
}

TEST_F(RegTmp, TuringRequirement1333) {
    reg_tmp_dut->op = reg_tmp_control::reg_op_e::LOAD;
    reg_tmp_dut->in = 0b11101111;

    AdvanceClock();

    ASSERT_EQ(reg_tmp_dut->rootp->reg_tmp__DOT__reg_tmp, 0b11101111);
}

TEST_F(RegTmp, REQTBD) {
    reg_tmp_dut->op = reg_tmp_control::reg_op_e::LOAD;
    reg_tmp_dut->in = 0b11101111;

    AdvanceClock();

    ASSERT_EQ(reg_tmp_dut->rootp->reg_tmp__DOT__reg_tmp, 0b11101111);

    reg_tmp_dut->op = reg_tmp_control::reg_op_e::ENABLE;
    reg_tmp_dut->rootp->reg_tmp__DOT__reg_tmp = 0b1010101;

    AdvanceClock();

    ASSERT_EQ(reg_tmp_dut->out, 0b1010101);
}

TEST_F(RegTmp, REQTBD2) {
    reg_tmp_dut->op = reg_tmp_control::reg_op_e::LOAD;
    reg_tmp_dut->in = 0b11101111;

    AdvanceClock();

    ASSERT_EQ(reg_tmp_dut->rootp->reg_tmp__DOT__reg_tmp, 0b11101111);

    reg_tmp_dut->op = 99;  // invalid op
    reg_tmp_dut->in = 0b1010101;

    AdvanceClock();

    ASSERT_EQ(reg_tmp_dut->rootp->reg_tmp__DOT__reg_tmp, 0b11101111);

    reg_tmp_dut->op = reg_tmp_control::reg_op_e::ENABLE;

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
