# Custom Soft Processor Unit (SPU) & Assembler Toolchain

This is a full-cycle virtual execution environment built from scratch in C++. It is designed to understand how hardware natively executes instructions, manages memory, and handles stack operations. The project consists of a custom Assembly compiler and a software-emulated CPU.

## System Architecture

The repository is strictly divided into functional modules that mimic a real hardware toolchain:

### 1. The Assembler (`/Assembler`)
A custom compiler that translates human-readable `.asm` files into raw binary bytecode.
* **Lexical Analysis & Parsing:** Parses custom assembly syntax, handling labels, registers, and memory addresses.
* **Bytecode Generation:** Outputs strict binary files ready for processor execution, ensuring proper instruction encoding.
* **Example Code:** See `ProcessorCommand.asm` for an example of the supported instruction set architecture (ISA).

### 2. The Virtual CPU (`/Processor/PROCESSOR`)
The heart of the virtual machine. It reads the binary executable, decodes instructions, and simulates a hardware execution cycle.
* **CPU Core:** Simulates instruction pointers, registers, and addressable RAM memory.
* **Calculator Unit (ALU):** Handles mathematical and logical operations triggered by the bytecode.

### 3. Secure Stack Implementation (`/Processor/STACK`)
Since the SPU is a stack-based machine, the reliability of the execution relies entirely on the stack. I implemented a highly secure custom stack structure:
* **Memory Protection:** Built with robust error handling and verification mechanisms to prevent buffer overflows, underflows, and memory corruption during bytecode execution.

## Build and Run

The project is managed via a root `makefile` that orchestrates the compilation of both the Assembler and the Processor.

### Compilation
```bash
git clone [https://github.com/your-username/virtualprocessor.git](https://github.com/your-username/virtualprocessor.git)
cd virtualprocessor
make