// Test file for component of Section 1.3.1: Arithmetic Logic Unit

#include <alu.h>
#include <alu_control.h>
#include <gtest/gtest.h>
#include <verilated.h>

class ALU : public ::testing::Test {
   protected:
    alu* alu_dut;

    void AdvanceClock() {
        alu_dut->clock = 1;
        alu_dut->eval();
        alu_dut->clock = 0;
        alu_dut->eval();
    }

    void SetUp() {
        alu_dut = new alu;
        alu_dut->eval();
    }

    void TearDown() {
        alu_dut->final();
        delete alu_dut;
    }
};

TEST_F(ALU, TuringRequirement2111) {
    alu_dut->register1 = 3;
    alu_dut->register2 = 2;
    alu_dut->enable = 1;
    alu_dut->op = alu_control::alu_op_e::ADD;

    AdvanceClock();

    EXPECT_EQ(alu_dut->result, 5);

    alu_dut->register1 = 0b11111111;  // 255
    alu_dut->register2 = 0b00000001;  // 1

    AdvanceClock();

    EXPECT_EQ(alu_dut->result, 0);

    alu_dut->register1 = 0b11111111;  // 255
    alu_dut->register2 = 0b00000010;  // 2

    AdvanceClock();

    EXPECT_EQ(alu_dut->result, 1);
}

TEST_F(ALU, FeatureRequirement2111) {
    alu_dut->register1 = 5;
    alu_dut->register2 = 3;

    alu_dut->enable = 1;
    alu_dut->op = alu_control::alu_op_e::SUB;

    AdvanceClock();

    EXPECT_EQ(alu_dut->result, 2);
}

TEST_F(ALU, FreatureRequirement2112) {
    alu_dut->register1 = 0b10110101;  // 181

    alu_dut->enable = 1;
    alu_dut->op = alu_control::alu_op_e::SHL;

    AdvanceClock();

    EXPECT_EQ(alu_dut->result, 0b01101010);  // 106

    alu_dut->register1 = 0b10110101;  // 181

    alu_dut->enable = 1;
    alu_dut->op = alu_control::alu_op_e::SHR;

    AdvanceClock();

    EXPECT_EQ(alu_dut->result, 0b01011010);  // 90
}

TEST_F(ALU, FreatureRequirement2113) {
    alu_dut->register1 = 0b10110101;  // 181

    alu_dut->enable = 1;
    alu_dut->op = alu_control::alu_op_e::ROL;

    AdvanceClock();

    EXPECT_EQ(alu_dut->result, 0b01101011);  // 107

    alu_dut->register1 = 0b10110101;  // 181
    alu_dut->enable = 1;
    alu_dut->op = alu_control::alu_op_e::ROR;
    AdvanceClock();

    EXPECT_EQ(alu_dut->result, 0b11011010);  // 218
}

TEST_F(ALU, FreatureRequirement2114) {
    alu_dut->register1 = 0b01010111;
    alu_dut->register2 = 0b00110010;

    alu_dut->enable = 1;
    alu_dut->op = alu_control::alu_op_e::AND;

    AdvanceClock();

    EXPECT_EQ(alu_dut->result, 0b00010010);

    alu_dut->op = alu_control::alu_op_e::OR;

    AdvanceClock();

    EXPECT_EQ(alu_dut->result, 0b01110111);

    alu_dut->op = alu_control::alu_op_e::XOR;

    AdvanceClock();

    EXPECT_EQ(alu_dut->result, 0b01100101);
}

TEST_F(ALU, FreatureRequirement2115) {
    alu_dut->register1 = 0b10101010;

    alu_dut->enable = 1;

    alu_dut->op = alu_control::alu_op_e::NOT;

    AdvanceClock();

    EXPECT_EQ(alu_dut->result, 0b01010101);
}

TEST_F(ALU, TuringRequirement2112) {
    alu_dut->register1 = 1;
    alu_dut->register2 = 1;
    alu_dut->enable = 1;
    alu_dut->op = alu_control::alu_op_e::ADD;

    AdvanceClock();

    EXPECT_EQ(alu_dut->result, 2);
    EXPECT_EQ(alu_dut->flag, alu_control::alu_flag_e::NONE);

    alu_dut->register2 = 255;
    alu_dut->register1 = 255;

    AdvanceClock();

    EXPECT_EQ(alu_dut->result, 254);
    EXPECT_EQ(alu_dut->flag, alu_control::alu_flag_e::CARRY);

}

TEST_F(ALU, FeatureRequirement2116) {
    alu_dut->register1 = 1;
    alu_dut->register2 = 1;
    alu_dut->enable = 1;
    alu_dut->op = alu_control::alu_op_e::SUB;

    AdvanceClock();

    EXPECT_EQ(alu_dut->result, 0);
    EXPECT_EQ(alu_dut->flag, alu_control::alu_flag_e::ZERO);
}

TEST_F(ALU, FreatureRequirement2117) {
    alu_dut->register1 = 12;
    alu_dut->register2 = 2;

    alu_dut->enable = 1;
    alu_dut->op = 16;

    AdvanceClock();

    EXPECT_EQ(alu_dut->result, 0);
}

TEST_F(ALU, FreatureRequirement2118) {
    alu_dut->register1 = 12;
    alu_dut->register2 = 2;

    alu_dut->enable = 0;

    alu_dut->op = alu_control::alu_op_e::ADD;

    AdvanceClock();

    EXPECT_EQ(alu_dut->result, 0);

    alu_dut->enable = 1;

    AdvanceClock();

    alu_dut->enable = 0;

    AdvanceClock();

    EXPECT_EQ(alu_dut->result, 0);
}


int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    testing::InitGoogleTest(&argc, argv);
    auto res = RUN_ALL_TESTS();
    Verilated::mkdir("logs");
    VerilatedCov::write("logs/alu.dat");
    return res;
}
