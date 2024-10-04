// Section 1.3

#include <assembler.h>
#include <cpu.h>
#include <cpu___024root.h>
#include <cpu_control.h>
#include <gtest/gtest.h>
#include <microcode.h>
#include <verilated.h>
#include <verilated_fst_c.h>
#include <string>

class CPU : public ::testing::Test {
   protected:
    cpu* cpu_dut;
    std::unique_ptr<VerilatedContext> contextp{new VerilatedContext};

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

    void RunAndDumpUntilHalt(const char* dumpfile) {

        //Verilated::traceEverOn(true);
        VerilatedFstC* tfp = new VerilatedFstC;
        cpu_dut->trace(tfp, 99);
        tfp->open(dumpfile);
        while (!cpu_dut->rootp->cpu__DOT__halt) {
            contextp->timeInc(1);
            cpu_dut->eval();
            tfp->dump(contextp->time());
        }
        tfp->close();
    }
    /*
    void RunAndDumpUntilCondition(const char* dumpfile, bool& condition) {

        contextp->traceEverOn(true);
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
        Verilated::time(0);
    }

    void TearDown() {
        cpu_dut->final();
        std::string log_file = "logs/cpu_";
        log_file += std::to_string(contextp->time());
        log_file += ".log";
        VerilatedCov::write(log_file.c_str());
        delete cpu_dut;
        contextp.release();
    }
};

TEST_F(CPU, Req) {
    // init memory with two arbitrary values
    // and let run through to see if we get those values read into control_unit.macro_intsruction
    cpu_dut->rootp->cpu__DOT__memory__DOT__cells[0] = 0b10101010;
    cpu_dut->rootp->cpu__DOT__memory__DOT__cells[2] = 0b010101011;

    Microcode* TestMicrocode;
    TestMicrocode = new Microcode;
    TestMicrocode->StoreMicrocodeIntoModel(
        cpu_dut->rootp->cpu__DOT__control_unit__DOT__microcode.m_storage);

    std::cout
        << cpu_dut->rootp->cpu__DOT__control_unit__DOT__microcode.m_storage[0];

    cpu_dut->eval();

    Verilated::traceEverOn(true);
    VerilatedFstC* tfp = new VerilatedFstC;
    cpu_dut->trace(tfp, 99);
    tfp->open("dumpfile.fst");
    cpu_dut->eval();
    contextp->timeInc(1);
    while (contextp->time() < 10000) {
        contextp->timeInc(1);
        cpu_dut->eval();
        tfp->dump(contextp->time());
    }
    tfp->close();
}

TEST_F(CPU, FunctionalTestCorrectStorageOfInstructionInMicrocode) {
    Microcode* TestMicrocode = new Microcode();
    TestMicrocode->AddMacroInstruction(
        (new MacroInstruction("TST"))
            ->set_next_state(new TimingState(
                (new ControlWord())
                    ->set_data_word_selector(1)
                    ->set_memory_op(cpu_control::memory_op_e::READ)
                    ->set_rax_op(cpu_control::reg_op_e::LOAD))));

    TestMicrocode->StoreMicrocodeIntoModel(
        cpu_dut->rootp->cpu__DOT__control_unit__DOT__microcode.m_storage);

    cpu_dut->eval();
}

TEST_F(CPU, REQ2) {
    contextp->time(0);
    Verilated::time(0);
    contextp->traceEverOn(true);
    Verilated::traceEverOn(true);

    auto FibMicrocode = (new Microcode());

    FibMicrocode->AddMacroInstruction(
        (new MacroInstruction("LDA"))
            ->set_next_state((new TimingState(
                (new ControlWord())
                    ->set_data_word_selector(1)
                    ->set_memory_bus_selector(cpu_control::memory_bus_selector_e::PC)
                    ->set_memory_op(cpu_control::memory_op_e::READ)
                    ->set_rax_op(cpu_control::reg_op_e::LOAD)))));

    FibMicrocode->AddMacroInstruction(
        (new MacroInstruction("LDB"))
            ->set_next_state(new TimingState(
                (new ControlWord())
                    ->set_data_word_selector(1)
                    ->set_memory_bus_selector(cpu_control::memory_bus_selector_e::PC)
                    ->set_memory_op(cpu_control::memory_op_e::READ)
                    ->set_rbx_op(cpu_control::reg_op_e::LOAD))));

    FibMicrocode->AddMacroInstruction(
        (new MacroInstruction("ADD"))
            ->set_next_state(new TimingState(
                (new ControlWord())
                    ->set_alu_op(cpu_control::alu_op_e::ADD)
                    ->set_alu_enable(1)
                    ->set_rcx_op(cpu_control::reg_op_e::LOAD))));

    FibMicrocode->AddMacroInstruction(
        (new MacroInstruction("MBA"))
            ->set_next_state(new TimingState(
                (new ControlWord())
                    ->set_rbx_op(cpu_control::reg_op_e::ENABLE)
                    ->set_rax_op(cpu_control::reg_op_e::LOAD))));

    FibMicrocode->AddMacroInstruction(
        (new MacroInstruction("MCB"))
            ->set_next_state(new TimingState(
                (new ControlWord())
                    ->set_rbx_op(cpu_control::reg_op_e::LOAD)
                    ->set_rcx_op(cpu_control::reg_op_e::ENABLE))));

    FibMicrocode->AddMacroInstruction(
        (new MacroInstruction("HLT"))
            ->set_next_state(
                new TimingState((new ControlWord())->set_halt(1))));

    FibMicrocode->ComputeMicrocodeFromMacroInstructions();
    FibMicrocode->StoreMicrocodeIntoModel(
        cpu_dut->rootp->cpu__DOT__control_unit__DOT__microcode.m_storage);

    auto FibAssembler = new Assembler(FibMicrocode);

    FibAssembler->next("LDA", 0)->next("LDB", 1);
    for (int i = 0; i < 10; i++) {
        FibAssembler->next("ADD")->next("MBA")->next("MCB");
    }
    FibAssembler->next("HLT");

    FibAssembler->StoreIntoModel(
        cpu_dut->rootp->cpu__DOT__memory__DOT__cells.m_storage);

    cpu_dut->eval();

    RunAndDumpUntilHalt("dumpfile3.fst");
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    testing::InitGoogleTest(&argc, argv);
    auto res = RUN_ALL_TESTS();

    //std::this_thread::sleep_for(std::chrono::seconds(1));std::this_thread::sleep_for(std::chrono::seconds(5));
    Verilated::mkdir("logs");
    //VerilatedCov::write("logs/cpu.dat");
    //std::this_thread::sleep_for(std::chrono::seconds(1));std::this_thread::sleep_for(std::chrono::seconds(5));
    return res;
}
