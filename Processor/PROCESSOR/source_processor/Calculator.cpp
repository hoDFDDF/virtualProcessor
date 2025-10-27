#include "CPU.h"
#include "Calculator.h"
#include "StackFuncs.h"


void ParseByteCodeCommands(Stack_t* stack_func_execute, ByteCodeFile* byte_code, ExecutableInstructions* instr_command, Register* regs_param){
    FILE* file_ptr = fopen("ByteCode.txt", "w");
    int str_command[40];
    int command_arg[40];

    int nArguments = sscanf(byte_code->byteCode_buffer_ptr[byte_code->str_index], "%d %d",
                                                               str_command, command_arg);
    
    fprintf(stdout, "nArguments = %d\n", nArguments);
    fprintf(stdout, "String in byte code file = %s\n [%zu]", byte_code->byteCode_buffer_ptr[byte_code->str_index],
                                                                                            byte_code->str_index);
   
    char* cmd_endptr;
    char* arg_endptr;
    instr_command->enum_processor_command = NO_COMMAND;
    regs_param->reg_val = NO_REGS;
//
//
    //    for (size_t index = 0; index < command_arr_size; index++) { 
    //    int command_check = strcmp(commands[index].cmnd_name, str_command_name);
    //    if (command_check == 0) {
    //        enum_command_name = commands[index].enum_cmnd_name;
    //        break;
    //    }   
    //}
//
    //if (nArguments == 2) {
    //    for (size_t regs_index = 0; regs_index < register_array_size; regs_index++) {
    //        int reg_arg_check = strcmp(registers[regs_index].reg_name, command_param);
    //        if (reg_arg_check == 0) { 
    //            instruction->reg_val = registers[regs_index].enum_reg_name;
    //            break;
    //        }
    //    }
    //}
//
    //if (nArguments == 2 && instruction->reg_val == NO_REGS) {
    //    instruction->val = atoi(command_param);
    //}
//

    for (size_t index_command = 0; index_command < instruction_array_size; index_command++) {
        
        //int arg = strtol(command_arg, &arg_endptr, 10);
        if (instruction[index_command].command_value == str_command) { 
            
            instr_command->enum_processor_command = instruction[index_command].enum_processor_command;
            instr_command->execute_func = instruction[index_command].execute_func;
            //instr_command->arg_value = arg;
        }
    }
    

      if (nArguments == 2)
            for (size_t regs_index = 0; regs_index < regs_size; regs_index++) {
            if (*command_arg == regs_param[regs_index].reg_val) { 
                instruction->reg_val = regs[regs_index].reg_enum;
                break;
            }
        }
    
    if (nArguments == 2 && instruction->reg_enum == NO_REGS) {
        instr_command
    }
        fprintf(stdout, "command_arg = '%s'\n", command_arg);
    fclose(file_ptr);
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