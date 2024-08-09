// Section 1.3

#include <cpu.h>
#include <cpu___024root.h>
#include <cpu_control.h>
#include <gtest/gtest.h>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include <microcode.h>

class CPU : public ::testing::Test {
   protected:
    cpu* cpu_dut;
    const std::unique_ptr<VerilatedContext> contextp{new VerilatedContext};

    void RunAndDumpUntilHalt(const char* dumpfile) {

        Verilated::traceEverOn(true);
        VerilatedVcdC* tfp = new VerilatedVcdC;
        cpu_dut->trace(tfp, 99);
        tfp->open(dumpfile);
        while (contextp->time() && !cpu_dut->rootp->cpu__DOT__halt) {
            contextp->timeInc(1);
            cpu_dut->eval();
            tfp->dump(contextp->time());
        }
        tfp->close();
    }

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

    void InitMicrocode() {
       
    }

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
    
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    testing::InitGoogleTest(&argc, argv);
    auto res = RUN_ALL_TESTS();
    Verilated::mkdir("logs");
    VerilatedCov::write("logs/cpu.dat");
    return res;
}
