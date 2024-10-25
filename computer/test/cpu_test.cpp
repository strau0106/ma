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
   public:
    cpu* cpu_dut;
    std::unique_ptr<VerilatedContext> contextp{new VerilatedContext};

    void RunAndDumpUntilHalt(const char* dumpfile) const {
        auto* tfp = new VerilatedFstC;
        cpu_dut->trace(tfp, 99);
        tfp->open(dumpfile);
        while (!cpu_dut->rootp->cpu__DOT__halt) {
            if (contextp->time() > 100000)
                FAIL();
            contextp->timeInc(1);
            cpu_dut->eval();
            tfp->dump(contextp->time());
        }
        tfp->close();
    }

    void SetUp() override {
        cpu_dut = new cpu;
        cpu_dut->eval();
        Verilated::time(0);
    }

    void TearDown() override {
        cpu_dut->final();
        std::string log_file = "logs/cpu_";
        log_file += std::to_string(contextp->time());
        log_file += ".log";
        VerilatedCov::write(log_file.c_str());
        delete cpu_dut;
        contextp.release();
    }
};

TEST_F(CPU, DemoSection41) {
    contextp->time(0);
    Verilated::time(0);
    contextp->traceEverOn(true);
    Verilated::traceEverOn(true);

    auto* FibMicrocode = (new Microcode());

    FibMicrocode->AddMacroInstruction(
        (new MacroInstruction("LDA"))
            ->set_next_state((new TimingState(
                (new ControlWord())
                    ->set_data_word_selector(1)
                    ->set_memory_bus_selector(
                        cpu_control::memory_bus_selector_e::PC)
                    ->set_memory_op(cpu_control::memory_op_e::READ)
                    ->set_rax_op(cpu_control::reg_op_e::LOAD)))));

    FibMicrocode->AddMacroInstruction(
        (new MacroInstruction("LDB"))
            ->set_next_state(new TimingState(
                (new ControlWord())
                    ->set_data_word_selector(1)
                    ->set_memory_bus_selector(
                        cpu_control::memory_bus_selector_e::PC)
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

    auto* FibAssembler = new Assembler(FibMicrocode);

    FibAssembler->next("LDA", 0)->next("LDB", 1);
    for (int i = 0; i < 10; i++) {
        FibAssembler->next("ADD")->next("MBA")->next("MCB");
    }
    FibAssembler->next("HLT");

    FibAssembler->StoreIntoModel(
        cpu_dut->rootp->cpu__DOT__memory__DOT__cells.m_storage);

    cpu_dut->eval();

    RunAndDumpUntilHalt("fib.fst");
    EXPECT_EQ(cpu_dut->rootp->cpu__DOT__rcx__DOT__reg_tmp, 89);
}

TEST_F(CPU, DemoSection42) {
    contextp->time(0);
    Verilated::time(0);
    contextp->traceEverOn(true);
    Verilated::traceEverOn(true);

    auto NSumMicrocode = (new Microcode());

    NSumMicrocode->AddMacroInstruction(
        (new MacroInstruction("LDA"))
            ->set_next_state((new TimingState(
                (new ControlWord())
                    ->set_data_word_selector(1)
                    ->set_memory_bus_selector(
                        cpu_control::memory_bus_selector_e::PC)
                    ->set_memory_op(cpu_control::memory_op_e::READ)
                    ->set_rax_op(cpu_control::reg_op_e::LOAD)))));

    NSumMicrocode->AddMacroInstruction(
        (new MacroInstruction("LDB"))
            ->set_next_state(new TimingState(
                (new ControlWord())
                    ->set_data_word_selector(1)
                    ->set_memory_bus_selector(
                        cpu_control::memory_bus_selector_e::PC)
                    ->set_memory_op(cpu_control::memory_op_e::READ)
                    ->set_rbx_op(cpu_control::reg_op_e::LOAD))));

    NSumMicrocode->AddMacroInstruction(
        (new MacroInstruction("LDC"))
            ->set_next_state(new TimingState(
                (new ControlWord())
                    ->set_data_word_selector(1)
                    ->set_memory_bus_selector(
                        cpu_control::memory_bus_selector_e::PC)
                    ->set_memory_op(cpu_control::memory_op_e::READ)
                    ->set_rcx_op(cpu_control::reg_op_e::LOAD))));
    NSumMicrocode->AddMacroInstruction(
        (new MacroInstruction("ADB"))
            ->set_next_state(new TimingState(
                (new ControlWord())
                    ->set_alu_op(cpu_control::alu_op_e::ADD)
                    ->set_alu_enable(1)
                    ->set_rbx_op(cpu_control::reg_op_e::LOAD))));

    NSumMicrocode->AddMacroInstruction(
        (new MacroInstruction("ADC"))
            ->set_next_state(new TimingState(
                (new ControlWord())
                    ->set_alu_op(cpu_control::alu_op_e::ADD)
                    ->set_alu_enable(1)
                    ->set_rcx_op(cpu_control::reg_op_e::LOAD))));

    NSumMicrocode->AddMacroInstruction(
        (new MacroInstruction("MCA"))
            ->set_next_state(new TimingState(
                (new ControlWord())
                    ->set_rcx_op(cpu_control::reg_op_e::ENABLE)
                    ->set_rax_op(cpu_control::reg_op_e::LOAD))));

    NSumMicrocode->AddMacroInstruction(
        (new MacroInstruction("JNC"))
            ->set_next_state(
                (new TimingState(
                     (new ControlWord())
                         ->set_memory_bus_selector(
                             cpu_control::memory_bus_selector_e::PC)
                         ->set_address_reg_op(
                             cpu_control::address_reg_op_e::REL_SUB)
                         ->set_data_word_selector(1)

                         ->set_memory_op(cpu_control::memory_op_e::READ)))
                    ->override_control_word_for_flag(
                        cpu_control::alu_flag_e::CARRY,
                        ((new ControlWord())
                             ->set_next_instr(1)
                             ->set_alu_op(9)))));

    NSumMicrocode->AddMacroInstruction(
        (new MacroInstruction("HLT"))
            ->set_next_state(
                new TimingState((new ControlWord())->set_halt(1))));

    NSumMicrocode->ComputeMicrocodeFromMacroInstructions();
    NSumMicrocode->StoreMicrocodeIntoModel(
        cpu_dut->rootp->cpu__DOT__control_unit__DOT__microcode.m_storage);
    NSumMicrocode->ComputeOpCodes();

    auto NSumAssembler = new Assembler(NSumMicrocode);

    NSumAssembler->next("LDB", 0)
        ->next("LDC", 0)
        ->next("LDA", 1)
        ->next("ADB")
        ->next("MCA")
        ->next("ADC")
        ->next("JNC", 5)
        ->next("HLT");

    NSumAssembler->StoreIntoModel(
        cpu_dut->rootp->cpu__DOT__memory__DOT__cells.m_storage);

    cpu_dut->eval();

    VerilatedFstC* tfp = new VerilatedFstC;
    cpu_dut->trace(tfp, 99);
    tfp->open("nsum.fst");
    while (!cpu_dut->rootp->cpu__DOT__halt && contextp->time() != 10000) {
        contextp->timeInc(1);
        cpu_dut->eval();
        tfp->dump(contextp->time());
    }
    tfp->close();
    EXPECT_EQ(cpu_dut->rootp->cpu__DOT__rax_direct, 253);
    EXPECT_EQ(cpu_dut->rootp->cpu__DOT__rbx_direct, 23);
}

TEST_F(CPU, DemoSection43) {
    contextp->time(0);
    Verilated::time(0);
    contextp->traceEverOn(true);
    Verilated::traceEverOn(true);

    auto* BrainfuckMicrocode = (new Microcode());

    BrainfuckMicrocode->AddMacroInstruction(
        (new MacroInstruction("LDA"))
            ->set_next_state((new TimingState(
                (new ControlWord())
                    ->set_data_word_selector(1)
                    ->set_memory_bus_selector(
                        cpu_control::memory_bus_selector_e::MAR)
                    ->set_memory_op(cpu_control::memory_op_e::READ)
                    ->set_rax_op(cpu_control::reg_op_e::LOAD)))));

    BrainfuckMicrocode->AddMacroInstruction(
        (new MacroInstruction("LDB"))
            ->set_next_state(new TimingState(
                (new ControlWord())
                    ->set_data_word_selector(1)
                    ->set_memory_bus_selector(
                        cpu_control::memory_bus_selector_e::PC)
                    ->set_memory_op(cpu_control::memory_op_e::READ)
                    ->set_rbx_op(cpu_control::reg_op_e::LOAD))));

    BrainfuckMicrocode->AddMacroInstruction(
        (new MacroInstruction("ADS"))
            ->set_next_state(new TimingState(
                (new ControlWord())
                    ->set_alu_op(cpu_control::alu_op_e::ADD)
                    ->set_alu_enable(1)
                    ->set_memory_op(cpu_control::memory_op_e::WRITE)
                    ->set_data_word_selector(1)
                    ->set_memory_bus_selector(
                        cpu_control::memory_bus_selector_e::MAR))));

    BrainfuckMicrocode->AddMacroInstruction(
        (new MacroInstruction("SUS"))
            ->set_next_state(new TimingState(
                (new ControlWord())
                    ->set_alu_enable(1)
                    ->set_alu_op(cpu_control::alu_op_e::SUB)
                    ->set_memory_op(cpu_control::memory_op_e::WRITE)
                    ->set_data_word_selector(1)
                    ->set_memory_bus_selector(
                        cpu_control::memory_bus_selector_e::MAR))));

    BrainfuckMicrocode->AddMacroInstruction(
        (new MacroInstruction("SUB"))
            ->set_next_state(new TimingState(
                (new ControlWord())->set_alu_op(cpu_control::alu_op_e::SUB))));

    BrainfuckMicrocode->AddMacroInstruction(
        (new MacroInstruction("REA"))
            ->set_next_state(new TimingState(
                (new ControlWord())
                    ->set_rbx_op(cpu_control::reg_op_e::ENABLE)
                    ->set_address_reg_op(cpu_control::address_reg_op_e::REL_ADD)
                    ->set_data_word_selector(1)
                    ->set_memory_bus_selector(
                        cpu_control::memory_bus_selector_e::MAR))));

    BrainfuckMicrocode->AddMacroInstruction(
        (new MacroInstruction("RES"))
            ->set_next_state(new TimingState(
                (new ControlWord())
                    ->set_rbx_op(cpu_control::reg_op_e::ENABLE)
                    ->set_address_reg_op(cpu_control::address_reg_op_e::REL_SUB)
                    ->set_data_word_selector(1)
                    ->set_memory_bus_selector(
                        cpu_control::memory_bus_selector_e::MAR))));

    BrainfuckMicrocode->AddMacroInstruction(
        (new MacroInstruction("JNE"))
            ->set_next_state(
                (new TimingState(
                     (new ControlWord())
                         ->set_rbx_op(cpu_control::reg_op_e::ENABLE)
                         ->set_address_reg_op(
                             cpu_control::address_reg_op_e::REL_SUB)
                         ->set_memory_bus_selector(
                             cpu_control::memory_bus_selector_e::PC)))
                    ->override_control_word_for_flag(
                        cpu_control::alu_flag_e::ZERO, ((new ControlWord())
                                                            ->set_next_instr(1)
                                                            ->set_alu_op(9)))));

    BrainfuckMicrocode->AddMacroInstruction(
        (new MacroInstruction("HLT"))
            ->set_next_state(
                new TimingState((new ControlWord())->set_halt(1))));
    BrainfuckMicrocode->ComputeMicrocodeFromMacroInstructions();
    BrainfuckMicrocode->StoreMicrocodeIntoModel(
        cpu_dut->rootp->cpu__DOT__control_unit__DOT__microcode.m_storage);
    BrainfuckMicrocode->ComputeOpCodes();

    auto* BrainfuckAssembler = (new Assembler(BrainfuckMicrocode));
    BrainfuckAssembler->next("LDB", 150)
        ->next("REA")
        ->next("REA")
        ->next("REA");  // Move MAR away from 0 so that it does not interfere.

    std::string brainfuck_program = "++>>+++++[-[-]]>>+++";
    // set address 0 to 2
    // move ptr two to the right
    // set to 5
    // repeatedly subtract 1 until 0
    // move ptr two to the right
    // set address to 3

    unsigned int opening_brackets[10] = {0};
    unsigned int ptr = 0;
    for (char& instr : brainfuck_program) {
        switch (instr) {
            case '+':
                BrainfuckAssembler->next("LDA")->next("LDB", 1)->next("ADS");
                break;
            case '-':
                BrainfuckAssembler->next("LDA")->next("LDB", 1)->next("SUS");
                break;
            case '>':
                BrainfuckAssembler->next("LDB", 1)->next("REA");
                break;
            case '<':
                BrainfuckAssembler->next("LDB", 1)->next("RES");
                break;
            case '[':
                opening_brackets[++ptr] =
                    BrainfuckAssembler->GetCurrentInstructionAddress();
                break;
            case ']':
                BrainfuckAssembler->next("LDA")
                    ->next("LDB", 0)
                    ->next("SUB")
                    ->next("LDB",
                           (BrainfuckAssembler->GetCurrentInstructionAddress() -
                            opening_brackets[ptr--]) +
                               2)
                    ->next("JNE");
                break;
            default:
                throw std::runtime_error("Invalid Instruction");
                break;
        }
    }

    BrainfuckAssembler->next("HLT");
    BrainfuckAssembler->StoreIntoModel(
        cpu_dut->rootp->cpu__DOT__memory__DOT__cells.m_storage);

    cpu_dut->eval();

    RunAndDumpUntilHalt("brainfuck.fst");

    const auto memory_address_register =
        cpu_dut->rootp->cpu__DOT__memory__DOT__memory_address_register;
    const auto& memory = cpu_dut->rootp->cpu__DOT__memory__DOT__cells;

    EXPECT_EQ(memory[(memory_address_register << 1) + 1], 3);
    EXPECT_EQ(memory[((memory_address_register - 2) << 1) + 1], 0);
    EXPECT_EQ(memory[((memory_address_register - 4) << 1) + 1], 2);
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    testing::InitGoogleTest(&argc, argv);
    Verilated::mkdir("logs");

    auto res = RUN_ALL_TESTS();

    return res;
}
