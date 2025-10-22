#ifndef _STACK_DATA_
#define _STACK_DATA_

#include <stdlib.h>
#include <stdint.h>

typedef double stack_data_type;

struct Stack_t{
    stack_data_type* stack_data;
    size_t stack_size;
    size_t capacity;
    uint8_t stack_status; 
};


#endif //_STACK_DATA_