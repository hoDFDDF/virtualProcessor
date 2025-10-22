#ifndef _ASM_FILE_PARAMS_
#define _ASM_FILE_PARAMS_

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct AsmFileParams{
    size_t asm_nStrings;
    size_t asm_file_size;
    char* asm_file_buffer;   
    struct stat stat_ptr;
    FILE* file_ptr;

};
void GetAsmFileNumStrings(AsmFileParams* asm_param);
void GetAsmFileSize(AsmFileParams* asm_param);

#endif //_ASM_FILE_PARAMS_