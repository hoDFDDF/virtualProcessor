#include "CPU.h"
#include "Calculator.h"
#include "StackFuncs.h"

void ExecuteFunctions(Stack_t* stack_param, ExecutableInstructions* instr){
    fprintf(stderr,"input_val in calculator func = %g\n ::8string", instr->arg_value); 
    //fprintf(stderr, COLOR_GREEN "command_cheker = %d\n" COLOR_RESET, command_checker);
    switch (instr->enum_processor_command) {
    case ADD: 
        StackAdd(stack_param);
        break;
    case POP:
        StackPop(stack_param);
        break;
    case PUSH:
        fprintf(stderr, "%g", stack_param->stack_data[0]);
        printf(COLOR_RED " input_val in calculator func = %g\n" COLOR_RESET, instr->arg_value);
        StackPush(stack_param, instr->arg_value);
        break;
    case OUT: 
        StackOut(stack_param);
        break;
    default:
        fprintf(stderr, "There are no such command or function");
    }
}

void ParseByteCodeCommands(Stack_t* stack_func_execute, ByteCodeFile* byte_code, 
                   ExecutableInstructions* instr_command, Register* regs_param){
    int str_command = 0;
    int command_arg = 0;

    int nArguments = sscanf(byte_code->byteCode_buffer_ptr[byte_code->str_index], "%d %d",
                                                               &str_command, &command_arg);
    fprintf(stdout, "str_command = %d,  command_arg = %d\n", str_command, command_arg);
    fprintf(stdout, "nArguments = %d\n", nArguments);
    fprintf(stdout, "String in byte code file = %s\n [%zu]", byte_code->byteCode_buffer_ptr[byte_code->str_index],
                                                                                            byte_code->str_index);
   
    instr_command->enum_processor_command = NO_COMMAND;
    instr_command->arg_value = 0;
    regs_param->reg_enum = NO_REGS;

    for (size_t index_command = 0; index_command < instruction_array_size; index_command++) {
        if (instruction[index_command].command_value == str_command) { 
            fprintf(stdout, "FOUND COMMAND: %d -> %d\n", 
            instruction[index_command].command_value, str_command);
            instr_command->enum_processor_command = instruction[index_command].enum_processor_command;
            break;
        }
    }
    
    if (nArguments == 2 && regs_param->reg_enum != NO_REGS) {
        printf("HELLO it' nArguments == 2 && regs_param->reg_enum != NO_REGS\n");
        for (size_t regs_index = 0; regs_index < regs_size; regs_index++) {
            if (regs_param[regs_index].reg_val == command_arg) { 
                regs_param->reg_val = regs[regs_index].reg_enum;
                break;
            }
        }
    }

    if (nArguments == 2 && regs_param->reg_enum == NO_REGS) {
        printf("HELLO it' nArguments == 2 && regs_param->reg_enum == NO_REGS\n");

        instr_command->arg_value = command_arg;

        printf("BY it' nArguments == 2 && regs_param->reg_enum == NO_REGS\n");
        
    }
    if (instr_command->enum_processor_command != NO_COMMAND) {
        printf("EXECUTING: command=%d, arg_value=%g\n", 
               instr_command->enum_processor_command, instr_command->arg_value);
        ExecuteFunctions(stack_func_execute, instr_command);
    } else {
        fprintf(stderr, "ERROR: Unknown command %d\n", str_command);
    }
    printf("BY it' nArguments == 2 && regs_param->reg_enum == NO_REGS\n");
        
    fprintf(stdout, "command_arg = %d\n", command_arg);
    printf(" it' nArguments == 2 && regs_param->reg_enum == NO_REGS\n");    
}

void ExecuteCommandsInStack(Stack_t* stack_func_execute, ByteCodeFile* byte_code, 
                    ExecutableInstructions* instr_command, Register* regs_param){
    
    assert(stack_func_execute != NULL);
    assert(byte_code != NULL);
    assert(instr_command != NULL);
    fprintf(stdout, "%s\n", "Check ExecuteCommandsInStack_!!!");
    byte_code->str_index = 0;

    for (size_t str_index = 0; str_index < byte_code->nStrings; str_index++) {
        //fprintf(stdout, "%s\n", "Check ExecuteCommandsInStack_!!!");
        ParseByteCodeCommands(stack_func_execute, byte_code, instr_command, regs_param);
        byte_code->str_index++;
        
        fprintf(stdout, "str_index  = %zu\n",  byte_code->str_index);
    } 
}