#ifndef _ASSEMBLER_TRAMSLATOR_
#define _ASSEMBLER_TRAMSLATOR_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#include <math.h>
#include <unistd.h>
#include "AsmFileParametrs.h"


typedef int instraction_type;

const int size_of_tempBuffer = 50;
enum Instractions{
    PUSH = 1,
    POP,
    ADD,
    SUB,
    MUL,
    OUT,
    HLT,
    NO_INSTRUCTION
};

enum AssemblerErrors_t{
    INVALID_INSTRUCTION,
    ERROR_ARGUMENT_REQUIRED,
};
struct ProcessorInstructions{ 
    int* code_array;
    instraction_type val;
    Instractions name;
    char** instr_buffer;
    size_t code_array_size;
    size_t index_instr_buffer;
    char* temp_buffer_command_name ;
    size_t str_arg;
};

void ReadTextFromAsmFile(ProcessorInstructions* instruction, AsmFileParams* asm_file_param);
Instractions CommandParser(ProcessorInstructions* instruction, AsmFileParams* asm_file_param);
void FillCodeArray(ProcessorInstructions* instruction, AsmFileParams* asm_file_param);
void WriteTranstaledComandToFile(ProcessorInstructions* instruction);

#endif //_ASSEMBLER_TRAMSLATOR_