#include "CPU.h"

void ReadByteCode(ByteCodeFile* byte_code){
    assert(byte_code != NULL);
    FILE* byte_code_file_ptr = fopen("ByteCode.txt", "r");
    
    if (byte_code_file_ptr == NULL) {
        perror("Error opening file");
        return;
    }
    
    GetByteCodeFileNumStrings(byte_code);
    fprintf(stdout,"%zu\n", byte_code->nStrings);
    fprintf(stdout,"%s", "AAA\n");
    byte_code->byteCode_buffer_ptr = (char**)calloc(byte_code->nStrings, sizeof(char*));
    fprintf(stdout,"%s", "HELLO_Caaloc\n");
    char temp_buffer[size_of_tempBuffer];

    for (size_t byte_code_file_count = 0; byte_code_file_count < byte_code->nStrings; 
                                                            byte_code_file_count++) {                             
        fgets(temp_buffer, size_of_tempBuffer, byte_code_file_ptr);
        temp_buffer[strlen(temp_buffer) - 1] = '\0';
        byte_code->byteCode_buffer_ptr[byte_code_file_count] = strdup(temp_buffer);
                                
    }

    for (size_t index = 0; index < byte_code->nStrings; index++) {
        fprintf(stdout, "%s ", byte_code->byteCode_buffer_ptr[index]);
    }
    fclose(byte_code_file_ptr);
}

void GetByteCodeFileNumStrings(ByteCodeFile* byte_code){

    assert(byte_code != nullptr);
    FILE* byte_code_file_ptr = fopen("ByteCode.txt", "r");
    if (byte_code_file_ptr == NULL) {
        perror("Error opening file");
    }
    byte_code->nStrings = 0;
    char file_symbol = 0;
    while ((file_symbol = fgetc(byte_code_file_ptr)) != EOF) {
        if (file_symbol == '\n') {
            byte_code->nStrings++;
        }
    }
    fclose(byte_code_file_ptr);
}



//////////////////////REGISTERS/////////////////

