#ifndef _STACK_FUNCTIONS_
#define _STACK_FUNCTIONS_

#include "Stack.h"
#include "Stack_Errors.h"


#define DUMP_INFO()\
    fprintf(stderr, "STACK_DUMP: FILE: %s, LINE: %d, FUNCTION: %s\n", \
            __FILE__, __LINE__, __func__); \
                                    


#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

StackErr_t StackDump(Stack_t* param);
StackErr_t StackVerify(Stack_t* param);
StackErr_t StackResize(Stack_t* param);
StackErr_t StackPush(Stack_t* param, stack_data_type input_value);
stack_data_type StackPop(Stack_t* param);
StackErr_t StackDestruct(Stack_t* stack_clean);
StackErr_t StackConstruct(Stack_t* param);
StackErr_t StackAdd(Stack_t* param);
StackErr_t StackOut(Stack_t* param);
StackErr_t StackMul(Stack_t* param);
StackErr_t StackHlt(Stack_t* param);
StackErr_t StackPUSHR(Stack_t* param, Register* regs_param);
StackErr_t StackPOPR(Stack_t* param, Register* regs_param);

#endif //_STACK_FUNCTIONS_