#ifndef _CPU_H_ 
#define _CPU_H_ 

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h> 


#define RESET_ALL       "\x1b[0m"
#define COLOR_BLACK     "\x1b[30m"
#define COLOR_RED       "\x1b[31m"
#define COLOR_GREEN     "\x1b[32m"
#define COLOR_YELLOW    "\x1b[33m"
#define COLOR_BLUE      "\x1b[34m"
#define COLOR_MAGENTA   "\x1b[35m"
#define COLOR_CYAN      "\x1b[36m"
#define COLOR_WHITE     "\x1b[37m"

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