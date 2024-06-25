// Test file for component of Section 1.2: Arithmetic Logic Unit

#include <alu.h>
#include <verilated.h>
#include <gtest/gtest.h>

class ALUTest: public ::testing::Test {
    protected: 
    alu * alu_dut; 

    void SetUp() {
        alu_dut = new alu; 
        alu_dut->eval();
    }
    
    void TearDown() {
        alu_dut->final();
        delete alu_dut;
    }
};


TEST_F(ALUTest, TuringRequirement1211) {
    alu_dut->register1 = 3;
    alu_dut->register2 = 2;
    alu_dut->clock = 1;
    alu_dut->out = 1; 
    alu_dut->op_add = 1;

    ASSERT_EQ(alu_dut->result, 5);

}

int main(int argc, char **argv) {
  Verilated::commandArgs(argc, argv);
  testing::InitGoogleTest(&argc, argv);
  auto res = RUN_ALL_TESTS();
  Verilated::mkdir("logs");
  VerilatedCov::write("logs/alu.dat");
  return res;
}
