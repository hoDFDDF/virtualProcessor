#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_

#include "Stack.h"
#include "StackFuncs.h"
#include <stdlib.h>

typedef long val;

enum ExecutableCommand{
    PUSH = 1,
    POP,
    HLT,
    ADD,
    MUL,
    OUT, 
    NO_COMMAND
}; 

struct ExecutableInstructions{ // for all fuction ecxept StackPuch, StackPop.
    int command_value;
    ExecutableCommand enum_processor_command;
    stack_data_type arg_value;//change 
};

const size_t instruction_array_size = 5;
const ExecutableInstructions instruction[instruction_array_size] = { {4,  ADD,   0},
                                               {2,  POP,   0},
                                               {1,  PUSH,  0},
                                               {6,  OUT,   0},
                                               {3,  HLT,   0}
};
 
void ExecuteFunctions(Stack_t* stack_param, ExecutableInstructions* instr);
void ParseByteCodeCommands(Stack_t* stack_func_execute, ByteCodeFile* byte_code, ExecutableInstructions* instr_command, Register* regs_param);
void ExecuteCommandsInStack(Stack_t* stack_func_execute, ByteCodeFile* byte_code, ExecutableInstructions* instr_command, Register* regs_param);

#endif //_CALCULATOR_H_