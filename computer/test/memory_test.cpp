// Section 1.3.2: Memory

#include <gtest/gtest.h>
#include <memory.h>
#include <memory___024root.h>
#include <memory_control.h>
#include <verilated.h>

class Memory : public ::testing::Test {
   public:
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
        memory_dut->bus_selector = 0;
    }

    void TearDown() {
        memory_dut->final();
        std::string log_file = "logs/memory";
        log_file +=
            ::testing::UnitTest::GetInstance()->current_test_info()->name();
        log_file += ".log";
        VerilatedCov::write(log_file.c_str());
        delete memory_dut;
    }
};

TEST_F(Memory, TuringRequirement2121) {

#define ARBITRARY_WRITE_LOCATION 0b111110001
#define ARBITRARY_DATA 0b11101111
    memory_dut->rootp->memory__DOT__memory_address_register =
        ARBITRARY_WRITE_LOCATION;
    memory_dut->data_word_selector = 0;
    memory_dut->in = 0b11101111;  // arbitrary data
    memory_dut->op = memory_control::memory_op_e::WRITE;

    AdvanceClock();

    ASSERT_EQ(memory_dut->rootp->memory__DOT__cells
                  .m_storage[ARBITRARY_WRITE_LOCATION << 1],
              ARBITRARY_DATA);  // << 1 because of data_word_selector

#define ARBITRARY_READ_LOCATION 0b111010001

    // data_word_selector is still 0

    memory_dut->rootp->memory__DOT__cells
        .m_storage[ARBITRARY_READ_LOCATION << 1] = ARBITRARY_DATA;
    memory_dut->rootp->memory__DOT__memory_address_register =
        ARBITRARY_READ_LOCATION;

    memory_dut->op = memory_control::memory_op_e::READ;

    AdvanceClock();

    ASSERT_EQ(memory_dut->out, ARBITRARY_DATA);
}

TEST_F(Memory, FeatureRequirement2121) {

#define ARBITRARY_WRITE_LOCATION 0b111110001
#define ARBITRARY_DATA 0b11101111
    memory_dut->rootp->memory__DOT__memory_address_register =
        ARBITRARY_WRITE_LOCATION;
    memory_dut->data_word_selector = 1;
    memory_dut->in = 0b11101111;  // arbitrary data
    memory_dut->op = memory_control::memory_op_e::WRITE;

    AdvanceClock();

    ASSERT_EQ(memory_dut->rootp->memory__DOT__cells
                  .m_storage[(ARBITRARY_WRITE_LOCATION << 1) + 1],
              ARBITRARY_DATA);  // << 1 because of data_word_selector

#define ARBITRARY_READ_LOCATION 0b111010001

    // data_word_selector is still 1

    memory_dut->rootp->memory__DOT__cells
        .m_storage[(ARBITRARY_READ_LOCATION << 1) + 1] = ARBITRARY_DATA;
    memory_dut->rootp->memory__DOT__memory_address_register =
        ARBITRARY_READ_LOCATION;

    memory_dut->op = memory_control::memory_op_e::READ;

    AdvanceClock();

    ASSERT_EQ(memory_dut->out, ARBITRARY_DATA);
}

TEST_F(Memory, TuringRequirementt2122) {
    memory_dut->data_word_selector = 0;
    memory_dut->bus_selector = 0;
    memory_dut->rootp->memory__DOT__cells.m_storage[300 << 1] = 0b11111111;
    memory_dut->rootp->memory__DOT__cells.m_storage[290 << 1] = 0b11111110;

    memory_dut->in = 127;
    memory_dut->address_reg_op = memory_control::address_reg_op_e::ABSOLUTE;

    AdvanceClock();

    ASSERT_EQ(memory_dut->rootp->memory__DOT__memory_address_register, 127);

    memory_dut->in = 173;
    memory_dut->address_reg_op = memory_control::address_reg_op_e::REL_ADD;

    AdvanceClock();

    ASSERT_EQ(memory_dut->rootp->memory__DOT__memory_address_register, 300);
    memory_dut->address_reg_op = memory_control::address_reg_op_e::IR_NOP;

    memory_dut->op = memory_control::memory_op_e::READ;

    AdvanceClock();

    ASSERT_EQ(memory_dut->out, 0b11111111);

    memory_dut->in = 10;
    memory_dut->address_reg_op = memory_control::address_reg_op_e::REL_SUB;

    AdvanceClock();

    ASSERT_EQ(memory_dut->rootp->memory__DOT__memory_address_register, 290);

    memory_dut->op = memory_control::memory_op_e::READ;

    AdvanceClock();

    ASSERT_EQ(memory_dut->out, 0b11111110);

    memory_dut->bus_selector = 1;

    memory_dut->in = 127;
    memory_dut->address_reg_op = memory_control::address_reg_op_e::ABSOLUTE;

    AdvanceClock();

    ASSERT_EQ(memory_dut->rootp->memory__DOT__programm_counter, 127);

    memory_dut->in = 173;
    memory_dut->address_reg_op = memory_control::address_reg_op_e::REL_ADD;

    AdvanceClock();

    ASSERT_EQ(memory_dut->rootp->memory__DOT__programm_counter, 300);
    memory_dut->address_reg_op = memory_control::address_reg_op_e::IR_NOP;

    memory_dut->op = memory_control::memory_op_e::READ;

    AdvanceClock();

    ASSERT_EQ(memory_dut->out, 0b11111111);

    memory_dut->in = 10;
    memory_dut->address_reg_op = memory_control::address_reg_op_e::REL_SUB;

    AdvanceClock();

    ASSERT_EQ(memory_dut->rootp->memory__DOT__programm_counter, 290);

    memory_dut->op = memory_control::memory_op_e::READ;

    AdvanceClock();

    ASSERT_EQ(memory_dut->out, 0b11111110);
}

TEST_F(Memory, TuringRequirement2123) {
    memory_dut->in = 123;
    memory_dut->bus_selector = 0;

    memory_dut->address_reg_op = memory_control::address_reg_op_e::ABSOLUTE;

    AdvanceClock();

    memory_dut->bus_selector = 1;

    AdvanceClock();

    ASSERT_EQ(memory_dut->rootp->memory__DOT__memory_address_register, 123);
    ASSERT_EQ(memory_dut->rootp->memory__DOT__programm_counter, 123);
}

TEST_F(Memory, TuringRequirementt2124) {
    memory_dut->data_word_selector = 0;
    memory_dut->rootp->memory__DOT__cells.m_storage[127 << 1] = 0b11111111;

    memory_dut->in = 127;
    memory_dut->address_reg_op = memory_control::address_reg_op_e::ABSOLUTE;

    AdvanceClock();

    ASSERT_EQ(memory_dut->rootp->memory__DOT__memory_address_register, 127);

    memory_dut->op = memory_control::memory_op_e::READ;

    AdvanceClock();

    ASSERT_EQ(memory_dut->out, 0b11111111);
}

TEST_F(Memory, FeatureRequirement2125) {
    memory_dut->address_reg_op = memory_control::address_reg_op_e::INC;
    memory_dut->bus_selector = 1;

    AdvanceClock();

    ASSERT_EQ(memory_dut->rootp->memory__DOT__programm_counter, 1);
    memory_dut->bus_selector = 0;

    AdvanceClock();

    ASSERT_EQ(memory_dut->rootp->memory__DOT__programm_counter, 1);
    //ASSERT_EQ(memory_dut->rootp->memory__DOT__memory_address_register, 1);
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    testing::InitGoogleTest(&argc, argv);
    auto res = RUN_ALL_TESTS();
    Verilated::mkdir("logs");
    VerilatedCov::write("logs/memory.dat");
    return res;
}
