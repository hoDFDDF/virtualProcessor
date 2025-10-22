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

struct Command_parametrs{ 
    val command_value;
    ExecutableCommand processor_command;
    bool isCommand;  
};
void ParseByteCodeCommands(Stack_t* stack_func_execute, ByteCodeFile* byte_code, Command_parametrs* command_param);
void ExecuteCommandsInStack(Stack_t* stack_func_execute, ByteCodeFile* byte_code, Command_parametrs* command_param);
void cleanStrings(char* string);
#endif //_CALCULATOR_H_