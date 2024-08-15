// Section 1.3

#include <cpu.h>
#include <cpu___024root.h>
#include <cpu_control.h>
#include <gtest/gtest.h>
#include <microcode.h>
#include <verilated.h>
#include <verilated_fst_c.h>

class CPU : public ::testing::Test {
   protected:
    cpu* cpu_dut;
    const std::unique_ptr<VerilatedContext> contextp{new VerilatedContext};

    void RunUntilHalt() {
        while (!cpu_dut->rootp->cpu__DOT__halt) {
            contextp->timeInc(1);
            cpu_dut->eval();
        }
    }

    void RunUntilCondition(bool& condition) {
        while (condition) {
            contextp->timeInc(1);
            cpu_dut->eval();
        }
    }

  /*   void RunAndDumpUntilHalt(const char* dumpfile) {

        Verilated::traceEverOn(true);
        VerilatedVcdC* tfp = new VerilatedVcdC;
        cpu_dut->trace(tfp, 99);
        tfp->open(dumpfile);
        while (Verilated::time() && !cpu_dut->rootp->cpu__DOT__halt) {
            Verilated::timeInc(1);
            cpu_dut->eval();
            tfp->dump(contextp->time());
        }
        tfp->close();
    }

    void RunAndDumpUntilCondition(const char* dumpfile, bool& condition) {

        Verilated::traceEverOn(true);
        VerilatedVcdC* tfp = new VerilatedVcdC;
        cpu_dut->trace(tfp, 99);
        tfp->open(dumpfile);
        while (contextp->time() && condition) {
            contextp->timeInc(1);
            cpu_dut->eval();
            tfp->dump(contextp->time());
        }
        tfp->close();
    } */

    void SetUp() {
        cpu_dut = new cpu;
        cpu_dut->eval();
    }

    void TearDown() {
        cpu_dut->final();
        delete cpu_dut;
    }
};

TEST_F(CPU, Req) {
    // init memory with two arbitrary values
    // and let run through to see if we get those values read into control_unit.makro_intsruction
    cpu_dut->rootp->cpu__DOT__memory__DOT__cells[0] = 0b10101010;
    cpu_dut->rootp->cpu__DOT__memory__DOT__cells[2] = 0b010101011;

    Microcode::microcode_bin_t microcode;
    Microcode::PrimeMicrocode(microcode);
    
    // copy microcode to m_storage
    // cpu_dut->rootp->cpu__DOT__control_unit__DOT__microcode.m_storage
    std::copy(microcode, microcode+16383, cpu_dut->rootp->cpu__DOT__control_unit__DOT__microcode.m_storage);

    std::cout<<cpu_dut->rootp->cpu__DOT__control_unit__DOT__microcode.m_storage[0];

    contextp->traceEverOn(true);
    VerilatedFstC* tfp = new VerilatedFstC;
    cpu_dut->trace(tfp, 99);
    tfp->open("dumpfile.fst");

    contextp->timeInc(1);
    while (cpu_dut->rootp->cpu__DOT__control_unit__DOT__state != 7) {
        contextp->timeInc(1);
        cpu_dut->eval();
        tfp->dump(contextp->time());
    }
    while (cpu_dut->rootp->cpu__DOT__control_unit__DOT__state != 5) {
        contextp->timeInc(1);
        cpu_dut->eval();
        tfp->dump(contextp->time());
    }
        while (cpu_dut->rootp->cpu__DOT__control_unit__DOT__state != 4) {
        contextp->timeInc(1);
        cpu_dut->eval();
        tfp->dump(contextp->time());
    }
    tfp->close();
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    testing::InitGoogleTest(&argc, argv);
    auto res = RUN_ALL_TESTS();
    Verilated::mkdir("logs");
    VerilatedCov::write("logs/cpu.dat");
    return res;
}
