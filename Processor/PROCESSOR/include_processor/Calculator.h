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

union currentFunc{ //получше разобраться как рабоатет union
        StackErr_t(*calc_and_controlFuncs)(Stack_t* param);
        stack_data_type(*pop_func)(Stack_t* param);
        StackErr_t(*push_func)(Stack_t* param, stack_data_type input_value);
};

struct ExecutableInstructions{ // for all fuction ecxept StackPuch, StackPop.
    val command_value;
    ExecutableCommand enum_processor_command;
    currentFunc execute_func;
    val arg_value;
};

const size_t instruction_array_size = 5;
const ExecutableInstructions instruction[] = { {4, ADD,  {instruction.execute_func.calc_and_controlFuncs = StackAdd}},
                                               {2, POP,  {instruction.execute_func.pop_func = StackPop}},
                                               {1, PUSH, {instruction.execute_func.push_func = StackPush}},
                                               {6, OUT, {instruction.execute_func.calc_and_controlFuncs = StackOut}},
                                               {3, HLT, {instruction.execute_func.calc_and_controlFuncs = StackHlt}}
};
 

void ParseByteCodeCommands(Stack_t* stack_func_execute, ByteCodeFile* byte_code, ExecutableInstructions* command_param);
void ExecuteCommandsInStack(Stack_t* stack_func_execute, ByteCodeFile* byte_code, ExecutableInstructions* command_param);
void cleanStrings(char* string);
#endif //_CALCULATOR_H_