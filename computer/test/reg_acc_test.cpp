// Section 1.3.3: Register

#include <gtest/gtest.h>
#include <reg_acc.h>
#include <reg_acc___024root.h>
#include <reg_acc_control.h>
#include <verilated.h>

class RegAcc : public ::testing::Test {
   protected:
    reg_acc* reg_acc_dut;

    void AdvanceClock() {
        reg_acc_dut->clock = 1;
        reg_acc_dut->eval();
        reg_acc_dut->clock = 0;
        reg_acc_dut->eval();
    }

    void SetUp() {
        reg_acc_dut = new reg_acc;
        reg_acc_dut->eval();
    }

    void TearDown() {
        reg_acc_dut->final();
        delete reg_acc_dut;
    }
};

TEST_F(RegAcc, TuringRequirement2131) {
    reg_acc_dut->op = reg_acc_control::reg_op_e::LOAD;
    reg_acc_dut->in = 0b11101111;

    AdvanceClock();

    ASSERT_EQ(reg_acc_dut->reg_direct, 0b11101111);
}

TEST_F(RegAcc, TuringRequirement2132) {
    reg_acc_dut->op = reg_acc_control::reg_op_e::ENABLE;
    reg_acc_dut->reg_direct = 0b11101111;

    AdvanceClock();

    ASSERT_EQ(reg_acc_dut->out, 0b11101111);
}
/*
TEST_F(RegAcc, REQTBD) {
    reg_acc_dut->op = reg_acc_control::reg_op_e::LOAD;
    reg_acc_dut->in = 0b11101111;

    AdvanceClock();

    ASSERT_EQ(reg_acc_dut->reg_direct, 0b11101111);

    reg_acc_dut->op = reg_acc_control::reg_op_e::ENABLE;
    reg_acc_dut->rootp->reg_direct = 0b1010101;

    AdvanceClock();

    ASSERT_EQ(reg_acc_dut->out, 0b1010101);
}

TEST_F(RegAcc, REQTBD2) {
    reg_acc_dut->op = reg_acc_control::reg_op_e::LOAD;
    reg_acc_dut->in = 0b11101111;

    AdvanceClock();

    ASSERT_EQ(reg_acc_dut->reg_direct, 0b11101111);

    reg_acc_dut->op = 4;  // invalid op
    reg_acc_dut->in = 0b1010101;

    AdvanceClock();

    ASSERT_EQ(reg_acc_dut->reg_direct, 0b11101111);

    reg_acc_dut->op = reg_acc_control::reg_op_e::ENABLE;

    AdvanceClock();

    ASSERT_EQ(reg_acc_dut->out, 0b11101111);
}

TEST_F(RegAcc, REQTBD3) {
    reg_acc_dut->op = reg_acc_control::reg_op_e::LOAD;
    reg_acc_dut->in = 0b11101111;

    AdvanceClock();

    ASSERT_EQ(reg_acc_dut->reg_direct, 0b11101111);

    reg_acc_dut->reset = 1;

    AdvanceClock();

    reg_acc_dut->op = reg_acc_control::reg_op_e::ENABLE;

    AdvanceClock();

    ASSERT_EQ(reg_acc_dut->out, 0);
}
*/
int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    testing::InitGoogleTest(&argc, argv);
    auto res = RUN_ALL_TESTS();
    Verilated::mkdir("logs");
    VerilatedCov::write("logs/reg_acc.dat");
    return res;
}
