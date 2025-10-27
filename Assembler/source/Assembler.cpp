#include "Assembler.h"

//FIXME check all arrray counters
void ReadTextFromAsmFile(ProcessorInstructions* instruction, AsmFileParams* asm_file_param) {
    FILE* asm_file_ptr = fopen("ProcessorCommand.asm", "r"); // FIXME - const
    if (asm_file_ptr == NULL) {
        perror("Error opening file");
        return;
    }
    
    GetAsmFileNumStrings(asm_file_param);
    fprintf(stdout,"%s", "AAA\n");
    instruction->instr_buffer = (char**)calloc(asm_file_param->asm_nStrings, sizeof(char*));
    
    char temp_buffer[size_of_tempBuffer];
    for (size_t index_of_arrPtr = 0; index_of_arrPtr < asm_file_param->asm_nStrings; 
                                                                index_of_arrPtr++) {
        fgets(temp_buffer, size_of_tempBuffer, asm_file_ptr);
        temp_buffer[strlen(temp_buffer) - 1] = '\0';
                                                 
        instruction->instr_buffer[index_of_arrPtr] = strdup(temp_buffer);
        fprintf(stdout, "%s ", instruction->instr_buffer[index_of_arrPtr]);
    }

    fclose(asm_file_ptr);    
}
void WriteTranstaledComandToFile(ProcessorInstructions* instruction){
    FILE* byte_code_file_ptr = fopen("C:\\Users\\uranory32\\Documents\\GitHub\\virtualProcessor\\Processor\\ByteCode.txt", "w");
    if (byte_code_file_ptr == NULL) {
        perror("Error opening byte_code_file");
    }

    for (size_t index_code_array = 0; index_code_array < instruction->code_array_size; index_code_array++) {
        if (instruction->code_array[index_code_array] == PUSH) { 
            fprintf(byte_code_file_ptr, "%d %d\n", instruction->code_array[index_code_array], 
                                            instruction->code_array[index_code_array + 1]);
            index_code_array++;                               
        } else if (instruction->code_array[index_code_array] == PUSHR || instruction->code_array[index_code_array] == POPR) {
            fprintf(byte_code_file_ptr, "%d %d\n", instruction->code_array[index_code_array], 
                                            instruction->code_array[index_code_array + 1]);
            index_code_array++;   
        }
        else {
            fprintf(byte_code_file_ptr, "%d\n", instruction->code_array[index_code_array]);                            
        }
    }
    fclose(byte_code_file_ptr);
}

void cleanStrings(char* string){
    char* pos;
    if ((pos = strchr(string, '\r')) != NULL ) *pos = '\0';
    if ((pos = strchr(string, '\n')) != NULL ) *pos = '\0';
}

size_t ParseArgs(char* str_command_name, char* command_param, ProcessorInstructions* instruction){

    int nArguments = sscanf(instruction->instr_buffer[instruction->index_instr_buffer], "%s %s",
                                                               str_command_name, command_param);
    if (nArguments == 2) {
        instruction->str_arg = 2;
        // TODO: ParseArgument()
    } else if (nArguments == 1) { 
        instruction->str_arg = 1;
    } else {
        instruction->str_arg = 0;
    }
    instruction->index_instr_buffer++;
    return nArguments;//залупа, нахую тогда записывать в структуру.
}

Instractions CommandParser(ProcessorInstructions* instruction, Command* cmd){

    char str_command_name[40] = {0};
    char command_param[32] = {0};
    size_t nArguments = ParseArgs(str_command_name, command_param, instruction);
    // TODO: ParseInstruction(str_command_name, command_param) {
    // TODO: for const Command* const commands[12] = {{PUSH, "PUSH"}}     
    Instractions enum_command_name = NO_INSTRUCTION;
    instruction->reg_val = NO_REGS;
    instruction->val = -1;
    // TODO: const Registers* const regs[4] = {{RAX, "RAX"}} instruction->reg_val = regs[i].enum_name
    // cделать цикл.
    for (size_t index = 0; index < command_arr_size; index++) { 
        int command_check = strcmp(commands[index].cmnd_name, str_command_name);
        if (command_check == 0) {
            enum_command_name = commands[index].enum_cmnd_name;
            break;
        }   
    }

    if (nArguments == 2) {
        for (size_t regs_index = 0; regs_index < register_array_size; regs_index++) {
            int reg_arg_check = strcmp(registers[regs_index].reg_name, command_param);
            if (reg_arg_check == 0) { 
                instruction->reg_val = registers[regs_index].enum_reg_name;
                break;
            }
        }
    }

    if (nArguments == 2 && instruction->reg_val == NO_REGS) {
        instruction->val = atoi(command_param);
    }

    fprintf(stdout, "INDEX_INSTR_BUFFER = [%d]\n",  instruction->index_instr_buffer);
    fprintf(stdout, "THIS COMMAND = {%s}\n", instruction->instr_buffer[instruction->index_instr_buffer]);
    
    fprintf(stderr, "commamd_code = %d\n", enum_command_name);
    
    fprintf(stderr, "comand_name = %s\n", str_command_name);
    fprintf(stderr, "comand_value = %d\n", instruction->val);
    fprintf(stdout, "HOW MANY ARGS = [%d]\n", nArguments);
    fprintf(stdout,  "VALUE OF REG ARG = [%d]", instruction->reg_val);

    return enum_command_name;
}

void FillCodeArray(ProcessorInstructions* instruction, AsmFileParams* asm_file_param, Command* cmd){
    instruction->code_array = (int*)calloc(256, sizeof(int));

    instruction->index_instr_buffer = 0;
    size_t file_string_count = asm_file_param->asm_nStrings;
    instruction->code_array_size = 0;
    for (size_t nArgs =  0; nArgs < file_string_count; nArgs++) {

        // TODO: массив структур для меток. Из имени метки и ее ip

        Instractions instruction_name = CommandParser(instruction, cmd);
        fprintf(stdout, "Got the instruction with name = {%d}\n\n", instruction_name);
        /// переделай выглядит уебищно
        if (instruction->str_arg == 2) {
            instruction->code_array[instruction->code_array_size] = (int)instruction_name;

            instruction->code_array[instruction->code_array_size + 1] = (instruction->reg_val != NO_REGS) ?
            (int)instruction->reg_val : instruction->val;

            instruction->code_array_size += 2;
        } else {
            instruction->code_array[instruction->code_array_size] = (int)instruction_name;
            instruction->code_array_size++;
        }

        fprintf(stdout, "What code of instruction was put in array_code = %d\n", instruction->code_array[nArgs]);   
    }
    fprintf(stdout, "Number of command in array_command = {%d}", instruction->code_array_size);
    for (size_t index_code_array = 0; index_code_array < instruction->code_array_size; index_code_array++) {
        fprintf(stdout, "%d ", instruction->code_array[index_code_array]);
    }
}

