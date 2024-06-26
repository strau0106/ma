// Test file for component of Section 1.2.1: Arithmetic Logic Unit

#include <alu.h>
#include <verilated.h>
#include <gtest/gtest.h>

class ALU: public ::testing::Test {
    protected: 
    alu * alu_dut; 

    void AdvanceClock()
    {
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


TEST_F(ALU, TuringRequirement1211) {
    alu_dut->register1 = 3;
    alu_dut->register2 = 2;
    alu_dut->out = 1; 
    alu_dut->op_add = 1;

    AdvanceClock();

    EXPECT_EQ(alu_dut->result, 5);

}

TEST_F(ALU, FeatureRequirement1211) {
    alu_dut->register1 = 5;
    alu_dut->register2 = 3; 
    
    alu_dut->out = 1;
    alu_dut->op_sub =1; 
    
    AdvanceClock();

    EXPECT_EQ(alu_dut->result, 2);

}

TEST_F(ALU, FeatureRequirement1212) {
    alu_dut->register1 = 4;
    alu_dut->register2 = 2; 

    alu_dut->out=1;
    alu_dut->op_mul=1;

    AdvanceClock();

    EXPECT_EQ(alu_dut->result, 8);
}

TEST_F(ALU, FreatureRequirement1213) {
    alu_dut->register1 = 4;
    alu_dut->register2 = 2; 

    alu_dut->out=1;
    alu_dut->op_div=1;

    AdvanceClock();

    EXPECT_EQ(alu_dut->result, 2);

    alu_dut->register1 = 7;
    alu_dut->register2 = 2; 

    AdvanceClock();

    EXPECT_EQ(alu_dut->result, 3);
}


TEST_F(ALU, FreatureRequirement1214) {
    alu_dut->register1 = 0b10110101; // 181

    alu_dut->out=1;
    alu_dut->op_dir=0;
    alu_dut->op_shift=1;

    AdvanceClock();

    EXPECT_EQ(alu_dut->result, 0b01101010); // 106

    alu_dut->register1 = 0b10110101; // 181

    alu_dut->out=1;
    alu_dut->op_dir=1;
    alu_dut->op_shift=1;

    AdvanceClock();

    EXPECT_EQ(alu_dut->result, 0b01011010); // 90
}

TEST_F(ALU, FreatureRequirement1215) {
    alu_dut->register1 = 0b10110101; // 181 

    alu_dut->out=1;
    alu_dut->op_dir=0;
    alu_dut->op_rot=1;

    AdvanceClock();

    EXPECT_EQ(alu_dut->result, 0b01101011); // 107

    alu_dut->register1 = 0b10110101;  // 181
    alu_dut->out=1;
    alu_dut->op_dir=1;
    alu_dut->op_rot=1;

    AdvanceClock();

    EXPECT_EQ(alu_dut->result, 0b11011010); // 218
}

TEST_F(ALU, FreatureRequirement1216) {
    alu_dut->register1 = 12; 
    alu_dut->register2 = 2;

    alu_dut->out=1;
    alu_dut->op_dir=0;
    alu_dut->op_shift=1;
    alu_dut->op_add=1;

    AdvanceClock();

    EXPECT_EQ(alu_dut->result, 0);
}

TEST_F(ALU, FreatureRequirement1217) {
    alu_dut->register1 = 12; 
    alu_dut->register2 = 2;

    alu_dut->out=0;

    alu_dut->op_dir=0;
    alu_dut->op_shift=1;
    alu_dut->op_add=1;

    AdvanceClock();

    EXPECT_EQ(alu_dut->result, 0);
}



int main(int argc, char **argv) {
  Verilated::commandArgs(argc, argv);
  testing::InitGoogleTest(&argc, argv);
  auto res = RUN_ALL_TESTS();
  Verilated::mkdir("logs");
  VerilatedCov::write("logs/alu.dat");
  return res;
}
