#include "StackFuncs.h"
#include "CPU.h"
StackErr_t StackConstruct(Stack_t* param){
    if (param == nullptr) {
        fprintf(stderr, "Pointer to Stack_Struct is null");
    }

    param->stack_size = 0;
    param->capacity = 5;

    param->stack_data = (stack_data_type*)calloc(param->capacity, 
                                        sizeof(stack_data_type));

    StackVerify(param);
    return STACK_VERIFIDE;                               
}

StackErr_t StackDestruct(Stack_t* stack_clean){//TODO fill shit
    StackVerify(stack_clean);
    free(stack_clean->stack_data);
    stack_clean->capacity = -12394831;
    stack_clean->stack_data = nullptr;
    stack_clean->stack_size = -999212;
    return STACK_VERIFIDE;
}

stack_data_type StackPop(Stack_t* param){//TODO return  elem
    StackVerify(param);
    stack_data_type ret_elem = param->stack_data[param->stack_size - 1];
    if (param->stack_size > 0) {
        param->stack_size--;
    } else { 
        fprintf(stderr, "STACK_ERROR_SIZE");
    }
    
    StackVerify(param);
    return ret_elem;
}

StackErr_t StackAdd(Stack_t* param){ // TODO hui
    StackVerify(param);
    if (param->stack_size < 2) {
        fprintf(stderr, "%s", "EROOR OF ADD COMMNND, thereless than 2  elements in stack");
        return STACK_ERROR_SIZE;
    }

    param->stack_data[param->stack_size - 1] +=  param->stack_data[param->stack_size - 2];
    param->stack_size--;
    fprintf(stdout, "param->stack_data[param->stack_size] = %g\n", param->stack_data[param->stack_size]);
    fprintf(stdout, "param->stack_data[param->stack_size - 1] = %g\n", param->stack_data[param->stack_size - 1]);
    
    StackVerify(param);
    //StackPush(param, param->stack_data[param->stack_size]);

    return STACK_VERIFIDE;
}

StackErr_t StackOut(Stack_t* param){ //TODO
    StackVerify(param);
    fprintf(stderr,"STACK OUT IN_1\n");
    FILE* processor_out_result = fopen("PROCESSOR_OUT", "w");
    if (processor_out_result == NULL) {
        perror("PROCESSOR_OUT_FILE");
    }
    fprintf(stderr,"STACK OUT IN__2\n");
    fprintf(stderr,"processor_out_result = %d",  param->stack_size - 1);
    StackVerify(param);
    fprintf(stderr,"processor_out_result = %g",  param->stack_data[param->stack_size - 1]);
    StackVerify(param); // TODO HUI
    fprintf(processor_out_result, "%g", param->stack_data[param->stack_size - 1]);

    StackVerify(param);
    fclose(processor_out_result);
    return STACK_VERIFIDE;
}
StackErr_t StackPush(Stack_t* param, stack_data_type input_value){
    StackVerify(param);
    
    if ((param->stack_size) == param->capacity) {
        fprintf(stderr, "stack_size = %d\n ", param->stack_size);
        StackResize(param);   
    }

    fprintf(stderr, "intput value in stack push = %g\n", input_value);
    fprintf(stderr, "[%p] !!! [%p]\n", param, param->stack_data);
    fprintf(stderr, "%d: %g -> %g", param->stack_size, param->stack_data[param->stack_size],
                                    input_value);
    param->stack_data[param->stack_size++] = input_value;
    fprintf(stderr, "CHECK2\n");
    fprintf(stderr, "stack_size = %d\n ", param->stack_size);
    fprintf(stderr, "input_val = %d\n ", input_value);
    StackVerify(param);
    fprintf(stderr, COLOR_RED "STACK SIZE = %d" COLOR_RESET, param->stack_size);

    return STACK_VERIFIDE;
}

StackErr_t StackHlt(Stack_t* param){
    StackVerify(param);
    fprintf(stdout, "Command HLT pushed into stack\n");
    exit(EXIT_SUCCESS);
    return STACK_VERIFIDE;
}

StackErr_t StackResize(Stack_t* param){
    StackVerify(param);
    fprintf(stderr,"PENIS_STACK_RESIZE\n");
    stack_data_type* stack_data_buffer;
    stack_data_buffer = param->stack_data; 
    param->capacity *= 2;
    stack_data_buffer = (stack_data_type*)realloc(stack_data_buffer, 
                                                     param->capacity * sizeof(stack_data_type));
    

    if (stack_data_buffer != nullptr) {
        fprintf(stderr, "STACK_RESIZE_NOT_WORK\n");
        param->stack_data =  stack_data_buffer;
        fprintf(stderr, "STACK_RESIZE_NOT_WORK\n");

    } else {
        fprintf(stderr,"STACK_MEMORY_REALLOCATION_ERROR");   
    }
    StackVerify(param); 
    return STACK_VERIFIDE;
}


StackErr_t StackVerify(Stack_t* param){//TODO битовые сдвиги
    param->stack_status =  STACK_SUCCESS;

    fprintf(stderr, "PENIS_Verify\n");
    if (param == nullptr) {
        param->stack_status |= STACK_PTR_NULL;
        StackDump(param);
    }

    StackErr_t default_value = STACK_SUCCESS;

    if (param->stack_size > param->capacity) {
        param-> stack_status |= STACK_ERROR_OVERFLOW;
        default_value = STACK_ERROR_OVERFLOW;
    }
    if (param->stack_data == nullptr) {
        param-> stack_status |= STACK_DATA_NULL;
        default_value = STACK_DATA_NULL;
    }

    if (param->capacity == 0) {
        param-> stack_status |= STACK_ERROR_UNDERFLOW;
        default_value = STACK_ERROR_UNDERFLOW;
    }
   
    if (param->capacity < 0 || param->stack_size < 0) {
        param-> stack_status |= STACK_ERROR_SIZE;
        default_value = STACK_ERROR_SIZE;
    } 
    
    if (default_value != STACK_SUCCESS) {
        StackDump(param);  
    }
    
    return STACK_SUCCESS; 
}

StackErr_t StackDump(Stack_t* param){//macros for _FILE_ and etc.
    
    DUMP_INFO();
    fprintf(stderr, "StackPtr[%p]\n", param);
    size_t error_number = 5;
    
    fprintf(stderr, "stack_code_error = ");
    for (int nbits = 7; nbits >= 0; nbits--) {
        fprintf(stderr, "%c", (param->stack_status >> nbits & 1) ? '1' : '0');
    }
    fprintf(stderr, "\n");
    fprintf(stderr, "stack_size = %d\n", param->stack_size);
    fprintf(stderr, "capacipy = %d\n", param->capacity);
    fprintf(stderr, "DataPtr[%p]\n", param->stack_data);


    if (param->stack_size <= 0) {
        
        fprintf(stderr,"\nOperation Pop was presumably called, size of stack is empty it was empty.ERROR_STACK_SIZE");
        return DUMP_EXIT;
    }
    for (size_t data_index = 0; data_index < param->stack_size; data_index++) {
        fprintf(stderr, "[%u] = %lg\n", data_index, param->stack_data[data_index]);
    }

    return DUMP_EXIT;
}