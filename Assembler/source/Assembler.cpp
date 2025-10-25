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

Instractions CommandParser(ProcessorInstructions* instruction, AsmFileParams* asm_file_param){
    char str_command_name[40];
    char command_param[32];
    char  register_name[10];

    //memset(str_command_name, 0, sizeof(str_command_name));
    //memset(command_param, 0, sizeof(command_param));
    //char* current_line = instruction->instr_buffer[instruction->index_instr_buffer];
   // cleanStrings(current_line);
    int nArguments = sscanf(instruction->instr_buffer[instruction->index_instr_buffer], "%s %s",
                                                   str_command_name, command_param);
    
    // TODO: ParseInstruction(str_command_name, command_param) {
                // TODO: for const Command* const commands[12] = {{PUSH, "PUSH"}}   
// }
    Instractions enum_command_name = NO_INSTRUCTION;
    instruction->reg_val = NO_REGS;
    instruction->val = -1;
    if (nArguments == 2) {
        instruction->val = atoi(command_param);
        instruction->str_arg = 2;
        // TODO: ParseArgument()
    } else if (nArguments == 1) { 
        instruction->str_arg = 1;
    } else {
        instruction->str_arg = 0;
    }

    // TODO: const Registers* const regs[4] = {{RAX, "RAX"}} instruction->reg_val = regs[i].enum_name
    
    if (strcmp("PUSH", str_command_name) == 0 && nArguments == 2) {
        enum_command_name = PUSH;
        fprintf(stderr, "%s", "AAA\n");
    } else if (strcmp("POP", str_command_name) == 0 && nArguments == 1) {
        enum_command_name = POP;
    } else if (strcmp("POPR", str_command_name) == 0 && nArguments ==  2 && strcmp("RAX", command_param) == 0){
        enum_command_name = POPR;
        instruction->reg_val = RAX;
    } else if (strcmp("PUSHR", str_command_name) == 0 && nArguments ==  2 && strcmp("RBX", command_param) == 0){
        enum_command_name = PUSHR;
        instruction->reg_val = RBX;
        fprintf(stdout, COLOR_RED"%s = ");
    } else if (strcmp("ADD", str_command_name) == 0 && nArguments == 1) {
        enum_command_name = ADD;
    } else if (strcmp("HLT", str_command_name) == 0 && nArguments == 1) {
        enum_command_name = HLT;
    } else if (strcmp("OUT", str_command_name) == 0 && nArguments == 1) {
        enum_command_name = OUT;
    } else {
        fprintf(stdin, "Invalid instruction");

    }

    fprintf(stdout, "INDEX_INSTR_BUFFER = [%d]\n",  instruction->index_instr_buffer);
    fprintf(stdout, "THIS COMMAND = {%s}\n", instruction->instr_buffer[instruction->index_instr_buffer]);
    
    fprintf(stderr, "commamd_code = %d\n", enum_command_name);
    
    fprintf(stderr, "comand_name = %s\n", str_command_name);
    fprintf(stderr, "comand_value = %d\n", instruction->val);
    fprintf(stdout, "HOW MANY ARGS = [%d]\n", nArguments);
    fprintf(stdout,  "VALUE OF REG ARG = [%d]", instruction->reg_val);
    instruction->index_instr_buffer++;
    return enum_command_name;
}


void FillCodeArray(ProcessorInstructions* instruction, AsmFileParams* asm_file_param){
    instruction->code_array = (int*)calloc(1000, sizeof(int));
    instruction->index_instr_buffer = 0;
    size_t file_string_count = asm_file_param->asm_nStrings;
    instruction->code_array_size = 0;
    for (size_t nArgs =  0; nArgs < file_string_count; nArgs++) {

        // TODO: массив структур для меток. Из имени метки и ее ip
        
        Instractions instruction_name = CommandParser(instruction,asm_file_param);
        fprintf(stdout, "Got the instruction with name = {%d}\n\n", instruction_name);
        
        if (instruction->str_arg == 2 && instruction->reg_val == NO_REGS) {
            instruction->code_array[instruction->code_array_size] = (int)instruction_name;
            
            instruction->code_array[instruction->code_array_size + 1] = instruction->val;
            instruction->code_array_size += 2;

        } else if (instruction->str_arg == 2 && instruction->reg_val != NO_REGS) {
            instruction->code_array[instruction->code_array_size] = (int)instruction_name;
            instruction->code_array[instruction->code_array_size + 1] = (int)instruction->reg_val;
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

