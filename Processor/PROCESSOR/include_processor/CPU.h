#ifndef _CPU_H_ 
#define _CPU_H_ 

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h> 

const int size_of_tempBuffer = 100;
struct ByteCodeFile{
    char** byteCode_buffer_ptr;
    size_t nStrings;
    size_t str_index;
};

struct Register{
    int* regs_array;
    int* instruction_pointer;
};

enum Registers{
    RAX = 23,
    RBX,
    RCX,
    RDX,
    ROX, // register for errors
};  

void ReadByteCode(ByteCodeFile* byte_code); 
void GetByteCodeFileNumStrings(ByteCodeFile* byte_code);
#endif //_CPU_H_