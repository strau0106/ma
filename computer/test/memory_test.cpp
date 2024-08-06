// Section 1.3.2: Memory

#include <gtest/gtest.h>
#include <memory.h>
#include <memory___024root.h>
#include <memory_control.h>
#include <verilated.h>

class Memory : public ::testing::Test {
 protected:
  memory* memory_dut;

  void AdvanceClock() {
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

TEST_F(Memory, TuringRequirement1321) {

#define ARBITRARY_WRITE_LOCATION 0b111110001
#define ARBITRARY_DATA 0b11101111
  memory_dut->rootp->memory__DOT__addr_reg = ARBITRARY_WRITE_LOCATION;
  memory_dut->data_word_selector = 0;
  memory_dut->in = 0b11101111;  // arbitrary data
  memory_dut->op = memory_control::memory_op_e::WRITE;

  AdvanceClock();

  ASSERT_EQ(memory_dut->rootp->memory__DOT__cells
                .m_storage[ARBITRARY_WRITE_LOCATION << 1],
            ARBITRARY_DATA);  // << 1 because of data_word_selector

#define ARBIRARY_READ_LOCATION 0b111010001

  // data_word_selector is still 0

  memory_dut->rootp->memory__DOT__cells.m_storage[ARBIRARY_READ_LOCATION << 1] =
      ARBITRARY_DATA;
  memory_dut->rootp->memory__DOT__addr_reg = ARBIRARY_READ_LOCATION;

  memory_dut->op = memory_control::memory_op_e::READ;

  AdvanceClock();

  ASSERT_EQ(memory_dut->out, ARBITRARY_DATA);
}

TEST_F(Memory, TuringRequirementt1323) {
  memory_dut->data_word_selector = 0;
  memory_dut->rootp->memory__DOT__cells.m_storage[127 << 1] = 0b11111111;

  memory_dut->in = 127;
  memory_dut->op = memory_control::memory_op_e::ABSOLUTE;

  AdvanceClock();

  ASSERT_EQ(memory_dut->rootp->memory__DOT__addr_reg, 127);

  memory_dut->op = memory_control::memory_op_e::READ;

  AdvanceClock();

  ASSERT_EQ(memory_dut->out, 0b11111111);
}

TEST_F(Memory, TuringRequirementt1324) {
  memory_dut->data_word_selector = 0;
  memory_dut->rootp->memory__DOT__cells.m_storage[300 << 1] = 0b11111111;
  memory_dut->rootp->memory__DOT__cells.m_storage[290 << 1] = 0b11111110;

  memory_dut->in = 127;
  memory_dut->op = memory_control::memory_op_e::ABSOLUTE;

  AdvanceClock();

  ASSERT_EQ(memory_dut->rootp->memory__DOT__addr_reg, 127);

  memory_dut->in = 173;
  memory_dut->op = memory_control::memory_op_e::REL_ADD;

  AdvanceClock();

  ASSERT_EQ(memory_dut->rootp->memory__DOT__addr_reg, 300);

  memory_dut->op = memory_control::memory_op_e::READ;

  AdvanceClock();

  ASSERT_EQ(memory_dut->out, 0b11111111);

  memory_dut->in = 10;
  memory_dut->op = memory_control::memory_op_e::REL_SUB;

  AdvanceClock();

  ASSERT_EQ(memory_dut->rootp->memory__DOT__addr_reg, 290);

  memory_dut->op = memory_control::memory_op_e::READ;

  AdvanceClock();

  ASSERT_EQ(memory_dut->out, 0b11111110);
}

int main(int argc, char** argv) {
  Verilated::commandArgs(argc, argv);
  testing::InitGoogleTest(&argc, argv);
  auto res = RUN_ALL_TESTS();
  Verilated::mkdir("logs");
  VerilatedCov::write("logs/memory.dat");
  return res;
}
