# 8-bit Virtual CPU Register & ALU Simulator

A cycle-accurate architectural simulation of an 8-bit Arithmetic Logic Unit (ALU) and hardware registers implemented in C, designed to demonstrate low-level computer architecture principles, bitwise status flag handling, and arithmetic overflow detection.

---

## 1. Problem Statement
Understanding the interaction between hardware data paths and status flags (condition codes) is fundamental for IC design and digital architecture. This project models the low-level execution of basic arithmetic and logic operations in an 8-bit accumulator-based processing unit, with explicit handling of status registers.

## 2. Theory & Architecture
The simulated unit is based on an 8-bit accumulator architecture:
* **Accumulator (`regA` - 8-bit):** Primary working register holding operands and operation results.
* **Operand Register (`regB` - 8-bit):** Secondary register holding the secondary operand.
* **Status Register (`status` - 8-bit):** Condition flag register updated based on operation outputs:
  * **Bit 0 - Zero Flag (`Z`):** Asserted (`1`) when the result of an operation evaluates to zero; otherwise cleared (`0`).
  * **Bit 1 - Carry Flag (`C`):** Asserted (`1`) when an unsigned arithmetic addition results in an overflow exceeding 8 bits ($> 255$); otherwise cleared (`0`).

## 3. Implementation Details
The project utilizes pure ANSI C with explicit type widths (`stdint.h`):
* Bitwise masks (`FLAG_Z`, `FLAG_C`) are leveraged for bit manipulation without modifying adjacent flag bits.
* A 16-bit intermediate accumulator (`uint16_t`) is implemented in `alu_add()` to capture carry-out bits prior to truncating to the 8-bit destination register.

   ┌──────────┐    ┌──────────┐
   │   RegA   │    │   RegB   │
   └────┬─────┘    └────┬─────┘
        │               │
        ▼               ▼
   ┌──────────────────────────┐
   │           ALU            │
   │    (ADD / AND Logic)     │
   └────────────┬─────────────┘
                │
     ┌──────────┴──────────┐
     ▼                     ▼
┌───────────┐         ┌───────────┐
│ Result -> │         │  Status   │
│   RegA    │         │ (Z / C)   │
└───────────┘         └───────────┘

## 4. Verification & Testbench
A built-in test suite verifies boundary cases:
1. **Normal Addition:** $15 + 10 = 25$ (`RegA = 0x19`, `C=0`, `Z=0`).
2. **Carry / Overflow:** $200 + 100 = 300 \equiv 44 \pmod{256}$ (`RegA = 0x2C`, `C=1`, `Z=0`).
3. **Bitwise AND Zero Flag:** $10100000_2 \ \& \ 01010000_2 = 0$ (`RegA = 0x00`, `C=0`, `Z=1`).

### Build & Run
```bash
# Compilation
gcc main.c -o alu_sim

# Execution
./alu_sim

5. What I Learned & Key Takeaways
Hardware Thinking in C: Mapping abstract programming constructs directly to hardware concepts (registers, buses, flags).

Bitwise Manipulation: Precision masking using bitwise OR (|=), AND-NOT (&= ~), and bit shifts (<<).

Timing & Sequential Logic Preparation: Established baseline intuition for implementing full-adder datapath and register transfer logic in Verilog/SystemVerilog.

6. Possible Future Improvements
Implement signed arithmetic with Overflow Flag (V) using Two's Complement.

Add Subtract (SUB), Shift Left/Right (SHL/SHR), and Bitwise XOR (XOR) instructions.

Port the design logic to Verilog HDL and verify using an FPGA/ModelSim testbench.