#ifndef _ASSEMBLER_TRAMSLATOR_
#define _ASSEMBLER_TRAMSLATOR_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#include <math.h>
#include <unistd.h>
#include "AsmFileParametrs.h"

#define RESET_ALL       "\x1b[0m"
#define COLOR_BLACK     "\x1b[30m"
#define COLOR_RED       "\x1b[31m"
#define COLOR_GREEN     "\x1b[32m"
#define COLOR_YELLOW    "\x1b[33m"
#define COLOR_BLUE      "\x1b[34m"
#define COLOR_MAGENTA   "\x1b[35m"
#define COLOR_CYAN      "\x1b[36m"
#define COLOR_WHITE     "\x1b[37m"

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
    PUSHR,
    POPR,
    DIV,
    NO_INSTRUCTION
};
enum Regs{
    RAX = 42,
    RBX,
    RCX,
    NO_REGS
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
    char* temp_buffer_command_name;
    size_t str_arg;
    Regs reg_val;
};
struct Registers{
    Regs enum_reg_name;
    const char* reg_name;
};
struct Command{
    Instractions enum_cmnd_name;
    const char* cmnd_name;
};
struct JMPS{
    char* jump_name;
    int IP;
};
struct BuffersStorage{
    char* command_buffer;
    char* args_buffer;
};
const size_t command_arr_size = 7;
const Command commands[command_arr_size] = {{PUSH,"PUSH"},
                                            {POP,  "POP"},
                                            {OUT,  "OUT"},
                                            {HLT,  "HLT"},
                                            {ADD,  "ADD"},
                                            {PUSHR, "PUSHR"},
                                            {POPR, "POPR"},
                                            
                                                    
};

const size_t register_array_size = 3;
const Registers registers[register_array_size] = {{RAX, "RAX"},
                                                {RBX, "RBX"},
                                                {RCX, "RCX"}
}; 

//const size_t jmp_arr_size = 3;
//const JMPS jmp_arr[jmp_arr_size] = { {":5", 0},
//                                     {"", 0}
//};

size_t ParseArgs(char* str_command_name, char* command_param, ProcessorInstructions* instruction);                                        
void ReadTextFromAsmFile(ProcessorInstructions* instruction, AsmFileParams* asm_file_param);
Instractions CommandParser(ProcessorInstructions* instruction, Command* cmd);
void FillCodeArray(ProcessorInstructions* instruction, AsmFileParams* asm_file_param, Command* cmd);
void WriteTranstaledComandToFile(ProcessorInstructions* instruction);

#endif //_ASSEMBLER_TRAMSLATOR_