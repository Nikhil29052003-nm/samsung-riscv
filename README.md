# samsung-riscv

This is a RISC-V Talent Development Program, powered by Samsung Semiconductor India Research (SSIR) along with VLSI System Design (VSD).

Basic Details About Me

Name: NIKHIL.N.M

College: Vidyavardhaka college of engineering

Email ID: nikhilnm.2905@gmail.com

LinkedIN Profile: Nikhil N M

Task 1:
Install the RISC-V toolchain using the VDI link, then compile the C code using both the normal GCC compiler and the RISC-V GCC compiler to compare the results. Refer to the provided C-based and RISC-V lab videos for guidance on completing the task.

Task 2:
Using SPIKE simulation tool to verify output of the code with respect to gcc-compiler output and understanding of assmebly code calculations on register using the SPIKE.
</details>
<details>
<summary><b>Task 3:</b> Understand the RISC-V Instruction set. </summary>   
<br>

**Below I have left two links to understand the the instruction type of RISC-V and their register length**

* [RISC-V card](https://www.cs.sfu.ca/~ashriram/Courses/CS295/assets/notebooks/RISCV/RISCV_CARD.pdf)
* [RISC-V instruction set summary](https://pages.hmc.edu/harris/ddca/ddcarv/DDCArv_AppB_Harris.pdf)

* Now doing our task first obtain the object dump file of the c-program which you have written by compiling it with risc-v compiler. And then see the instruction set summary and risc-v card and start to decode each of the instruction what it does.
* The RISC-V instructions are categorized into types based on their field organization. Each type has specific fields like opcode, func3, func7, immediate values, and register numbers. The types include:
  **R-type**: Register type
  
  **I-type**: Immediate type
 
  **S-type**: Store type
 
  **B-type**: Branch type
 
  **U-type**: Upper immediate type
 
  **J-type**: Jump type
  
* Below is 15 instruction taken from my object dumpfile and explained in detail.
![isa](https://github.com/user-attachments/assets/1f0997c3-ac19-4c39-97ec-b469f37d4474)

This is the instruction table divided with respect to registers bit columns:

| **Instruction** | **Instruction Format** | **Immediate (12 bits)** | **rs1 (5 bits)** | **funct3 (3 bits)** | **rd (5 bits)** | **Opcode (7 bits)** |
|------------------|-------------------------|--------------------------|-------------------|---------------------|------------------|---------------------|
| `lui a0, 0x2b`  | U                      | N/A                      | N/A               | N/A                 | 01010           | 0110111            |
| `addi sp, sp, -48` | I                    | 111111111101             | 00010             | 000                 | 00010            | 0010011            |
| `sd ra, 40(sp)`  | S                      | 010100                   | 00010             | 011                 | 00001 (rs2)      | 0100011            |
| `jal ra, <__divdi3>`| J                      | `<imm[20|10:1|11|19:12]>`| N/A               | N/A                 | 00001            | 1101111            |
| `lw s0, 12(sp)`  | I                      | 000000000110             | 00010             | 010                 | 10000            | 0000011            |
| `beqz s0, <main + 0x60>`| B                    | `<imm[11|4:1|10:5|12]>`  | 10000             | 000                 | 00000 (rs2)      | 1100011            |
| `li a1, 10`      | I                      | 000000001010             | 00000             | 000                 | 01011            | 0010011            |
| `mv a0, s0`      | I                      | 000000000000             | 10000             | 000                 | 01010            | 0010011            |
| `addw s1, a0, s1`| R                      | N/A                      | 01010 (rs1)       | 000                 | 10001            | 0111011            |
| `sext.w a0, a0`  | I                      | 000000000000             | 01010             | 000                 | 01010            | 0011011            |
| `bnez s0, <main + 0x38>`| B                    | `<imm[11|4:1|10:5|12]>`  | 10000             | 001                 | 00000 (rs2)      | 1100011            |
| `sw zero, 12(sp)`| S                      | 00000                    | 00010             | 010                 | 00000 (rs2)      | 0100011            |
| `ld ra, 40(sp)`  | I                      | 010100                   | 00010             | 011                 | 00001            | 0000011            |
| `ret`            | I                      | 000000000000             | 00001             | 000                 | 00000            | 1100111            |
| `add a0, s1, a1` | R                      | N/A                      | 10001 (rs1)       | 000                 | 01010            | 0110011            |

# RISC-V Instruction Breakdown

1. ### `lui a0, 0x2b`
**lui (Load Upper Immediate):** Loads a 20-bit immediate value into the upper 20 bits of a register.
#### Instruction: `lui a0, 0x2b`
- **Opcode:** `0110111` (7 bits)
- **Immediate:** `0x2b` (`0000000000001011`, 20 bits)
- **Destination Register (rd):** `a0` (`x10`, 5 bits)
#### Breakdown:
- **Immediate (0x2b):** `0000000000001011`
- **rd (a0 = x10):** `01010`
- **Opcode:** `0110111`
#### Binary Representation:
- Immediate (20 bits): `0000000000001011`
- rd (5 bits): `01010`
- Opcode (7 bits): `0110111`

---

2. ### `addi sp, sp, -48`
**addi (Add Immediate):** Adds an immediate value to a register.
#### Instruction: `addi sp, sp, -48`
- **Opcode:** `0010011` (7 bits)
- **Immediate:** `-48` (`111111100000`, 12 bits, in 2's complement)
- **Source Register (rs1):** `sp` (`x2`, 5 bits)
- **Destination Register (rd):** `sp` (`x2`, 5 bits)
- **Function (funct3):** `000` (3 bits)
#### Breakdown:
- **Immediate (12 bits):** `111111100000`
- **rs1 (sp = x2):** `00010`
- **funct3:** `000`
- **rd (sp = x2):** `00010`
- **Opcode:** `0010011`
#### Binary Representation:
- Immediate (12 bits): `111111100000`
- rs1 (5 bits): `00010`
- funct3 (3 bits): `000`
- rd (5 bits): `00010`
- Opcode (7 bits): `0010011`

---

3. ### `sd ra, 40(sp)`
**sd (Store Doubleword):** Stores a 64-bit value from a source register into memory.
#### Instruction: `sd ra, 40(sp)`
- **Opcode:** `0100011` (7 bits)
- **Immediate:** `40` (`0000101000`, 12 bits, split into `imm[11:5]` and `imm[4:0]`)
- **Source Register (rs2):** `ra` (`x1`, 5 bits)
- **Base Register (rs1):** `sp` (`x2`, 5 bits)
- **Function (funct3):** `011` (3 bits)
#### Breakdown:
- **Immediate (40):** `0000101000` (split into `imm[11:5] = 0000101` and `imm[4:0] = 01000`)
- **rs2 (ra = x1):** `00001`
- **rs1 (sp = x2):** `00010`
- **funct3:** `011`
- **Opcode:** `0100011`
#### Binary Representation:
- imm[11:5] (7 bits): `0000101`
- rs2 (5 bits): `00001`
- rs1 (5 bits): `00010`
- funct3 (3 bits): `011`
- imm[4:0] (5 bits): `01000`
- Opcode (7 bits): `0100011`

---

4. ### `sd s0, 32(sp)`
**sd (Store Doubleword):** Stores a 64-bit value from a source register into memory.
#### Instruction: `sd s0, 32(sp)`
- **Opcode:** `0100011` (7 bits)
- **Immediate:** `32` (`000010000`, 12 bits, split into `imm[11:5]` and `imm[4:0]`)
- **Source Register (rs2):** `s0` (`x8`, 5 bits)
- **Base Register (rs1):** `sp` (`x2`, 5 bits)
- **Function (funct3):** `011` (3 bits)
#### Breakdown:
- **Immediate (32):** `000010000` (split into `imm[11:5] = 0000100` and `imm[4:0] = 00000`)
- **rs2 (s0 = x8):** `01000`
- **rs1 (sp = x2):** `00010`
- **funct3:** `011`
- **Opcode:** `0100011`
#### Binary Representation:
- imm[11:5] (7 bits): `0000100`
- rs2 (5 bits): `01000`
- rs1 (5 bits): `00010`
- funct3 (3 bits): `011`
- imm[4:0] (5 bits): `00000`
- Opcode (7 bits): `0100011`

---

5. ### `sd s1, 24(sp)`
**sd (Store Doubleword):** Stores a 64-bit value from a source register into memory.
#### Instruction: `sd s1, 24(sp)`
- **Opcode:** `0100011` (7 bits)
- **Immediate:** `24` (`000011000`, 12 bits, split into `imm[11:5]` and `imm[4:0]`)
- **Source Register (rs2):** `s1` (`x9`, 5 bits)
- **Base Register (rs1):** `sp` (`x2`, 5 bits)
- **Function (funct3):** `011` (3 bits)
#### Breakdown:
- **Immediate (24):** `000011000` (split into `imm[11:5] = 0000011` and `imm[4:0] = 00000`)
- **rs2 (s1 = x9):** `01001`
- **rs1 (sp = x2):** `00010`
- **funct3:** `011`
- **Opcode:** `0100011`
#### Binary Representation:
- imm[11:5] (7 bits): `0000011`
- rs2 (5 bits): `01001`
- rs1 (5 bits): `00010`
- funct3 (3 bits): `011`
- imm[4:0] (5 bits): `00000`
- Opcode (7 bits): `0100011`

---

6. ### `jal ra, <printf>`
**jal (Jump and Link):** Jumps to a target address and stores the return address in the destination register.
#### Instruction: `jal ra, <printf>`
- **Opcode:** `1101111` (7 bits)
- **Immediate:** `<offset>` (20 bits, split into imm[20|10:1|11|19:12])
- **Destination Register (rd):** `ra` (`x1`, 5 bits)
#### Breakdown:
- **Immediate (offset):** Split into imm[20] = `1`, imm[10:1] = `<10 bits>`, imm[11] = `1`, imm[19:12] = `<8 bits>`
- **rd (ra = x1):** `00001`
- **Opcode:** `1101111`
#### Binary Representation:
- imm[20|10:1|11|19:12]: `<binary>`
- rd (5 bits): `00001`
- Opcode (7 bits): `1101111`

---

7. ### `lw s0, 12(sp)`
**lw (Load Word):** Loads a 32-bit value from memory into a register.
#### Instruction: `lw s0, 12(sp)`
- **Opcode:** `0000011` (7 bits)
- **Immediate:** `12` (`0000000000001100`, 12 bits)
- **Destination Register (rd):** `s0` (`x8`, 5 bits)
- **Base Register (rs1):** `sp` (`x2`, 5 bits)
#### Breakdown:
- **Immediate (12):** `0000000000001100`
- **rd (s0 = x8):** `01000`
- **rs1 (sp = x2):** `00010`
- **funct3:** `010`
- **Opcode:** `0000011`
#### Binary Representation:
- Immediate (12 bits): `0000000000001100`
- rd (5 bits): `01000`
- rs1 (5 bits): `00010`
- funct3 (3 bits): `010`
- Opcode (7 bits): `0000011`

---

8. ### `mv a0, s1`
**mv (Move):** This pseudo-instruction moves the value from one register to another, implemented as `addi`.
#### Instruction: `mv a0, s1`
- **Opcode:** `0010011` (7 bits)
- **Immediate:** `0` (`000000000000`, 12 bits)
- **Source Register (rs1):** `s1` (`x9`, 5 bits)
- **Destination Register (rd):** `a0` (`x10`, 5 bits)
- **Function (funct3):** `000` (3 bits)
#### Breakdown:
- **Immediate (0):** `000000000000`
- **rs1 (s1 = x9):** `01001`
- **funct3:** `000`
- **rd (a0 = x10):** `01010`
- **Opcode:** `0010011`
#### Binary Representation:
- Immediate (12 bits): `000000000000`
- rs1 (5 bits): `01001`
- funct3 (3 bits): `000`
- rd (5 bits): `01010`
- Opcode (7 bits): `0010011`

---

9. ### `addw s1, a0, s1`
**addw (Add Word):** Adds two 32-bit values and stores the result in a register.
#### Instruction: `addw s1, a0, s1`
- **Opcode:** `0111011` (7 bits)
- **Source Register (rs1):** `a0` (`x10`, 5 bits)
- **Source Register (rs2):** `s1` (`x9`, 5 bits)
- **Destination Register (rd):** `s1` (`x9`, 5 bits)
- **Function (funct3):** `000` (3 bits)
- **Function (funct7):** `0000000` (7 bits)
#### Breakdown:
- **funct7:** `0000000`
- **rs2 (s1 = x9):** `01001`
- **rs1 (a0 = x10):** `01010`
- **funct3:** `000`
- **rd (s1 = x9):** `01001`
- **Opcode:** `0111011`
#### Binary Representation:
- funct7 (7 bits): `0000000`
- rs2 (5 bits): `01001`
- rs1 (5 bits): `01010`
- funct3 (3 bits): `000`
- rd (5 bits): `01001`
- Opcode (7 bits): `0111011`

---

10. ### `sext.w s0, a0`
**sext.w (Sign-Extend Word):** Extends a 32-bit word to a 64-bit value with sign extension.
#### Instruction: `sext.w s0, a0`
- **Opcode:** `0011011` (7 bits)
- **Immediate:** `0` (`000000000000`, 12 bits)
- **Source Register (rs1):** `a0` (`x10`, 5 bits)
- **Destination Register (rd):** `s0` (`x8`, 5 bits)
- **Function (funct3):** `000` (3 bits)
#### Breakdown:
- **Immediate (0):** `000000000000`
- **rs1 (a0 = x10):** `01010`
- **funct3:** `000`
- **rd (s0 = x8):** `01000`
- **Opcode:** `0011011`
#### Binary Representation:
- Immediate (12 bits): `000000000000`
- rs1 (5 bits): `01010`
- funct3 (3 bits): `000`
- rd (5 bits): `01000`
- Opcode (7 bits): `0011011`

---

11. ### `ret`
**ret (Return):** Returns from a function, equivalent to `jalr x0, ra, 0`.
#### Instruction: `ret`
- **Opcode:** `1100111` (7 bits)
- **Immediate:** `0` (`000000000000`, 12 bits)
- **Source Register (rs1):** `ra` (`x1`, 5 bits)
- **Destination Register (rd):** `x0` (zero register, 5 bits)
- **Function (funct3):** `000` (3 bits)
#### Breakdown:
- **Immediate (0):** `000000000000`
- **rs1 (ra = x1):** `00001`
- **funct3:** `000`
- **rd (x0):** `00000`
- **Opcode:** `1100111`
#### Binary Representation:
- Immediate (12 bits): `000000000000`
- rs1 (5 bits): `00001`
- funct3 (3 bits): `000`
- rd (5 bits): `00000`
- Opcode (7 bits): `1100111`

---

12. ### `bnez s0, <label>`
**bnez (Branch if Not Equal to Zero):** Branches if the register value is non-zero.
#### Instruction: `bnez s0, <label>`
- **Opcode:** `1100011` (7 bits)
- **Immediate:** `<label>` (12 bits, split into `imm[11]`, `imm[4:1]`, `imm[10:5]`, and `imm[12]`)
- **Source Register (rs1):** `s0` (`x8`, 5 bits)
- **Source Register (rs2):** `x0` (`x0`, 5 bits)
- **Function (funct3):** `001` (3 bits)
#### Breakdown:
- **Immediate:** `<label>` (split into imm[11], imm[4:1], imm[10:5], imm[12])
- **rs1 (s0 = x8):** `01000`
- **rs2 (x0):** `00000`
- **funct3:** `001`
- **Opcode:** `1100011`
#### Binary Representation:
- imm[11|4:1|10:5|12]: `<binary>`
- rs1 (5 bits): `01000`
- rs2 (5 bits): `00000`
- funct3 (3 bits): `001`
- Opcode (7 bits): `1100011`

---

13. ### `sw zero, 12(sp)`
**sw (Store Word):** Stores a 32-bit value from a register into memory.
#### Instruction: `sw zero, 12(sp)`
- **Opcode:** `0100011` (7 bits)
- **Immediate:** `12` (`000000000110`, 12 bits)
- **Source Register (rs2):** `zero` (`x0`, 5 bits)
- **Base Register (rs1):** `sp` (`x2`, 5 bits)
- **Function (funct3):** `010` (3 bits)
#### Breakdown:
- **Immediate (12):** `000000000110`
- **rs2 (zero = x0):** `00000`
- **rs1 (sp = x2):** `00010`
- **funct3:** `010`
- **Opcode:** `0100011`
#### Binary Representation:
- Immediate (12 bits): `000000000110`
- rs2 (5 bits): `00000`
- rs1 (5 bits): `00010`
- funct3 (3 bits): `010`
- Opcode (7 bits): `0100011`

---

14. ### `ld ra, 120(sp)`
**ld (Load Doubleword):** Loads a 64-bit value from memory into a register.
#### Instruction: `ld ra, 120(sp)`
- **Opcode:** `0000011` (7 bits)
- **Immediate:** `120` (`000000111100`, 12 bits)
- **Base Register (rs1):** `sp` (`x2`, 5 bits)
- **Destination Register (rd):** `ra` (`x1`, 5 bits)
- **Function (funct3):** `011` (3 bits)
#### Breakdown:
- **Immediate (120):** `000000111100`
- **rs1 (sp = x2):** `00010`
- **funct3:** `011`
- **rd (ra = x1):** `00001`
- **Opcode:** `0000011`
#### Binary Representation:
- Immediate (12 bits): `000000111100`
- rs1 (5 bits): `00010`
- funct3 (3 bits): `011`
- rd (5 bits): `00001`
- Opcode (7 bits): `0000011`

---

15. ### `lw s0, 12(sp)`
**lw (Load Word):** Loads a 32-bit value from memory into a register.
#### Instruction: `lw s0, 12(sp)`
- **Opcode:** `0000011` (7 bits)
- **Immediate:** `12` (`0000000000001100`, 12 bits)
- **Destination Register (rd):** `s0` (`x8`, 5 bits)
- **Base Register (rs1):** `sp` (`x2`, 5 bits)
- **Function (funct3):** `010` (3 bits)
#### Breakdown:
- **Immediate (12):** `0000000000001100`
- **rd (s0 = x8):** `01000`
- **rs1 (sp = x2):** `00010`
- **funct3:** `010`
- **Opcode:** `0000011`
#### Binary Representation:
- Immediate (12 bits): `0000000000001100`
- rd (5 bits): `01000`
- rs1 (5 bits): `00010`
- funct3 (3 bits): `010`
- Opcode (7 bits): `0000011`

---

* This completes the breakdown for all 15 instructions!
</details>

<details>
<summary><b>Task 4:</b> By making use of RISCV Core: Verilog Netlist and Testbench, perform an experiment of Functional Simulation and observe the waveforms</summary>  
<br>

>***NOTE:** Since the designing of RISCV Architecture and writing it's testbench is not the part of this Research Internship, so we will use the Verilog Code and Testbench of RISCV that has already been designed. The reference GitHub repository is : [iiitb_rv32i](https://github.com/vinayrayapati/rv32i/)*    
  
### Steps to perform functional simulation of RISCV  
1. Create a new directory with your name ```mkdir <your_name>```
2. Create two files by using ```gvim``` command as ```iiitb_rv32i.v``` and ```iiitb_rv32i_tb.v```  
3. Copy the code from the reference github repo and paste it in your verilog and testbench files  
  
  
4. To run and simulate the verilog code, enter the following command:  
	```
	$ iverilog -o dsn iiitb_rv32i.v iiitb_rv32i_tb.v
	$ vvp dsn
	```
![Screenshot 2025-01-23 222201](https://github.com/user-attachments/assets/c3a89dd2-c782-4597-861e-a6c93fcf9756)
 
5. To see the simulation waveform in GTKWave, enter the following command:
	```
	$ gtkwave iiitb_rv32i.vcd
	```
6. The GTKWave will be opened and following window will be appeared 

![image](https://github.com/user-attachments/assets/7bf25565-654f-4592-8f20-cbcf1a689038)
    
#### As shown in the figure below, all the instructions in the given verilog file is hard-coded. Hard-coded means that instead of following the RISCV specifications bit pattern, the designer has hard-coded each instructions based on their own pattern. Hence the 32-bits instruction that we generated in Task-3 will not match with the given instruction.  
  
<img width="500" alt="Instructions" src="https://github.com/maazm007/vsdsquadron-mini-internship/assets/83294849/24cc896a-7817-4941-be7f-95d44c35d4d8">
  
#### Following are the differences between standard RISCV ISA and the Instruction Set given in the reference repository:  
  
|  **Operation**  |  **Standard RISCV ISA**  |  **Hardcoded ISA**  |  
|  :----:  |  :----:  |  :----:  |  
|  ADD R6, R2, R1  |  32'h00110333  |  32'h02208300  |  
|  SUB R7, R1, R2  |  32'h402083b3  |  32'h02209380  |  
|  AND R8, R1, R3  |  32'h0030f433  |  32'h0230a400  |  
|  OR R9, R2, R5  |  32'h005164b3  |  32'h02513480  |  
|  XOR R10, R1, R4  |  32'h0040c533  |  32'h0240c500  |  
|  SLT R1, R2, R4  |  32'h0045a0b3  |  32'h02415580  |  
|  ADDI R12, R4, 5  |  32'h004120b3  |  32'h00520600  |  
|  BEQ R0, R0, 15  |  32'h00000f63  |  32'h00f00002  |  
|  SW R3, R1, 2  |  32'h0030a123  |  32'h00209181  |  
|  LW R13, R1, 2  |  32'h0020a683  |  32'h00208681  |  
|  SRL R16, R14, R2  |  32'h0030a123  |  32'h00271803  |
|  SLL R15, R1, R2  |  32'h002097b3  |  32'h00208783  |   
  

#### *Analysing the Output Waveform of various instructions*  
**```Instruction 1: ADD R6, R2, R1```**  
  
![ADD](https://github.com/maazm007/vsdsquadron-mini-internship/assets/83294849/fff34786-9f52-488b-827d-9516ba655ed1)

**```Instruction 2: SUB R7, R1, R2```**  
  
![SUB](https://github.com/maazm007/vsdsquadron-mini-internship/assets/83294849/a4ce7d65-1e61-4a35-9e9f-9941de9d6e19)

**```Instruction 3: AND R8, R1, R3```**  

![AND](https://github.com/maazm007/vsdsquadron-mini-internship/assets/83294849/28706b39-2cfa-4b29-b0ac-6c1bbc1cbbe9)

**```Instruction 4: OR R9, R2, R5```**  

![OR](https://github.com/maazm007/vsdsquadron-mini-internship/assets/83294849/617b18d4-35f8-42e4-8294-b8259042f1d6)

**```Instruction 5: XOR R10, R1, R4```**  

![XOR](https://github.com/maazm007/vsdsquadron-mini-internship/assets/83294849/724f6c43-6f5c-4be2-899a-061b202cbf34)

**```Instruction 6: SLT R1, R2, R4```**  

![SLT](https://github.com/maazm007/vsdsquadron-mini-internship/assets/83294849/6d0a3063-9a8c-49e2-84ab-eb8f99875d0a)

**```Instruction 7: ADDI R12, R4, 5```**  

![ADDI](https://github.com/maazm007/vsdsquadron-mini-internship/assets/83294849/d8287e99-05d4-4140-b4bc-844da65fe1c8)

**```Instruction 8: BEQ R0, R0, 15```**  
  
![BEQ](https://github.com/maazm007/vsdsquadron-mini-internship/assets/83294849/583e69e5-88ef-4853-8a3b-a282bb8cc90f)
 
**```Instruction 9: BNE R0, R1, 20```**

![BNE](https://github.com/maazm007/vsdsquadron-mini-internship/assets/83294849/d09128b6-172a-4b3a-bfa6-2364142bb9f8)
  
**```Instruction 10: SLL R15, R1, R2```**  

![SLL](https://github.com/maazm007/vsdsquadron-mini-internship/assets/83294849/885a63bc-485e-4594-8d15-52f2ec8da800)

</details>  
<details>
<summary><b>Task 5:</b>  🚗 Smart Collision Avoidance & Lane Departure Warning System </summary>  

## 📌 Overview  
This project is designed to enhance vehicle safety by using an **ultrasonic sensor** for **collision detection** and an **IR sensor** for **lane departure warnings**. The system runs on the **VSDSquadron Mini RISC-V board** and provides real-time feedback via an **LCD display and a buzzer**.  

### ✨ Features  
- **Collision Detection:** Ultrasonic sensor detects nearby objects and triggers an alert.  
- **Lane Departure Warning:** IR sensor detects lane markings and alerts the driver if the vehicle moves off track.  
- **LCD Display:** Shows warnings such as "Collision Warning!" and "Lane Departure!"  
- **Buzzer Alert:** Provides an audible warning for hazards.  

---

## 📦 List of Components  

| **Component**             | **Quantity** | **Specification/Notes**            |
|---------------------------|-------------|------------------------------------|
| **VSDSquadron Mini Board** | 1           | CH32V003, CH32V00x Series        |
| **Ultrasonic Sensor (HC-SR04)** | 1  | Detects nearby obstacles          |
| **IR Sensor Module (TCRT5000 or similar)** | 1 | Detects lane departure            |
| **LCD Display (I2C 16x2)** | 1           | Displays warning messages         |
| **Buzzer**                | 1           | Active Buzzer (3.3V/5V)          |
| **Resistors**             | 2           | 10kΩ Pull-ups (if required)       |
| **Jumper Wires**          | As needed   | For connections                   |
| **Power Supply**          | 1           | 3.3V / 5V source                  |

---

## 🔌 Pin Connections  

| **Component**         | **MCU Pin** | **Port & Pin**  | **Direction** | **Description** |
|----------------------|------------|-----------------|--------------|---------------|
| **Ultrasonic Trigger** | PD4        | GPIOD, Pin 4    | Output       | Sends trigger pulse |
| **Ultrasonic Echo**    | PD3        | GPIOD, Pin 3    | Input        | Receives reflected pulse |
| **IR Sensor**         | PD5        | GPIOD, Pin 5    | Input        | Detects lane markings |
| **LCD SDA**          | PC1        | GPIOC, Pin 1    | Output       | I2C Data Line |
| **LCD SCL**          | PC2        | GPIOC, Pin 2    | Output       | I2C Clock Line |
| **Buzzer**           | PD2        | GPIOD, Pin 2    | Output       | Alerts driver |
| **Power**            | VCC        | 3.3V / 5V       | -           | Power Supply |
| **Ground**           | GND        | GND             | -           | Common Ground |

---

## 🚀 How It Works  

1. **System Initialization:**  
   - GPIO pins are configured.  
   - LCD and sensors are initialized.  

2. **Collision Detection:**  
   - The ultrasonic sensor measures distance.  
   - If an object is closer than **10 cm**, a **buzzer sounds** and the **LCD displays "Collision Warning!"**  

3. **Lane Departure Detection:**  
   - The IR sensor monitors lane markings.  
   - If the vehicle **departs from the lane**, a warning message is displayed and the buzzer activates.  

4. **Continuous Monitoring:**  
   - The system **checks sensor data in real-time** and updates alerts accordingly.  
---
![pin connection](https://github.com/user-attachments/assets/fa0eb595-2343-474f-8d2d-b448e8f6d4b2)

</details> 
