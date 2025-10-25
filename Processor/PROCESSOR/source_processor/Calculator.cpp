#include "CPU.h"
#include "Calculator.h"
#include "StackFuncs.h"

void cleanStrings(char* string){
    char* pos;
    if ((pos = strchr(string, '\r')) != NULL ) *pos = '\0';
    if ((pos = strchr(string, '\n')) != NULL ) *pos = '\0';
}

void ParseByteCodeCommands(Stack_t* stack_func_execute, ByteCodeFile* byte_code, Command_parametrs* command_param){

    char str_command[40];
    char command_arg[40];

    memset(str_command, 0, sizeof(str_command));
    memset(command_arg, 0, sizeof(command_arg));
    char* current_line = byte_code->byteCode_buffer_ptr[byte_code->str_index];
    cleanStrings(current_line);
    int nArguments = sscanf(byte_code->byteCode_buffer_ptr[byte_code->str_index], "%s %s",
                                                               str_command, command_arg);
 
    fprintf(stdout, "nArguments = %d\n", nArguments);
    fprintf(stdout, "String in byte code file = %s\n [%zu]", byte_code->byteCode_buffer_ptr[byte_code->str_index],
                                                                                            byte_code->str_index);
    command_param->processor_command = NO_COMMAND;
    
    char* endptr;
    if (nArguments == 2) {
        fprintf(stdout, "command_arg = '%s'\n", command_arg);
        command_param->command_value = strtol(command_arg, &endptr, 10);
        fprintf(stdout, "Value of arg(atoi) = %d\n", command_param->command_value);
    } else if (nArguments == 1) { 
        command_param->isCommand = 1;
    } else {
       command_param->isCommand = 0; 
    }
    
    if (strcmp("1", str_command) == 0 && nArguments == 2) {
        command_param->processor_command = PUSH;

        StackPush(stack_func_execute, command_param->command_value);
        fprintf(stderr, "%s", "AAA\n");
    } else if (strcmp("2", str_command) == 0 && nArguments == 1) {
        command_param->processor_command = POP;
        StackPop(stack_func_execute); 
    // заменить на сравнение значений
    } else if (strcmp("6", str_command) == 0 && nArguments == 1) {
        StackOut(stack_func_execute);
        command_param->command_value = OUT;
        
    } else if (strcmp("3", str_command) == 0 && nArguments == 1) {
        StackAdd(stack_func_execute);
        command_param->command_value = ADD;
        
    } else if (strcmp("7", str_command) == 0 && nArguments == 1) {
        fprintf(stdout, "%s", "Command HLT was pushed, end of program.....");
        exit(EXIT_SUCCESS); 
        command_param->command_value = HLT;
        
    } else {
        fprintf(stdin, "Invalid instruction");
    }
}

void ExecuteCommandsInStack(Stack_t* stack_func_execute, ByteCodeFile* byte_code, Command_parametrs* command_param){
    
    assert(stack_func_execute != NULL);
    assert(byte_code != NULL);
    assert(command_param != NULL);
    fprintf(stdout, "%s\n", "Check ExecuteCommandsInStack_!!!");
    byte_code->str_index = 0;
    command_param->isCommand = 0;
    command_param->command_value = 0;
    for (size_t str_index = 0; str_index < byte_code->nStrings; str_index++) {
        //fprintf(stdout, "%s\n", "Check ExecuteCommandsInStack_!!!");
        ParseByteCodeCommands(stack_func_execute,  byte_code, command_param);
        byte_code->str_index++;
        fprintf(stdout, "str_index  = %zu\n",  byte_code->str_index);
    } 
}