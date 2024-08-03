#include <memory.h>
#include <memory_control.h>
#include <verilated.h>
#include <gtest/gtest.h>


class Memory: public ::testing::Test {
    protected: 
    memory * memory_dut; 

    void AdvanceClock()
    {
        memory_dut->clock = 1;
        memory_dut->eval();
        memory_dut->clock = 0;
        memory_dut->eval();
    }

    void SetUp() {
        memory_dut = new memory; 
        memory_dut->eval();
    }
    
    void TearDown() {
        memory_dut->final();
        delete memory_dut;
    }
};

TEST_F(Memory, TuringRequirement1411) {
    FAIL();
}

int main(int argc, char **argv) {
  Verilated::commandArgs(argc, argv);
  testing::InitGoogleTest(&argc, argv);
  auto res = RUN_ALL_TESTS();
  Verilated::mkdir("logs");
  VerilatedCov::write("logs/memory.dat");
  return res;
}
