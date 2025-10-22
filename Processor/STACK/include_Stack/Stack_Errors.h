#ifndef _STACK_ERRORS_
#define _STACK_ERRORS_

const size_t error_num = 4;

enum StackErr_t{
    STACK_SUCCESS              = 0,
    STACK_PTR_NULL        = 1 << 0,
    STACK_ERROR_OVERFLOW  = 1 << 1,
    STACK_ERROR_UNDERFLOW = 1 << 2,
    STACK_ERROR_MEMORY    = 1 << 3,
    STACK_ERROR_DATA      = 1 << 4,
    STACK_ERROR_SIZE      = 1 << 5,
    STACK_DATA_NULL       = 1 << 6,
    DUMP_EXIT,
    STACK_VERIFIDE
};

struct ErrorInfo{
    StackErr_t  code_error;
    bool is_error;
    const char* error_message;
};

#endif //_STACK_ERRORS_