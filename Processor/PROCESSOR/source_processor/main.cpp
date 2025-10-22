#include <stdio.h>
#include "CPU.h"
#include "Calculator.h"

int main(){
    ByteCodeFile byte_code = {};
    Stack_t stack_func_execute = {};
    Command_parametrs command_param = {};
    StackConstruct(&stack_func_execute);
    ReadByteCode(&byte_code);
    ExecuteCommandsInStack(&stack_func_execute, &byte_code, &command_param);
    StackDump(&stack_func_execute);
    StackDestruct(&stack_func_execute);
    return 0;
}