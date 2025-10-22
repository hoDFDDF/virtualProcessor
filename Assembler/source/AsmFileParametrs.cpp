#include "AsmFileParametrs.h"

void GetAsmFileSize(AsmFileParams* asm_param){ 
    assert(asm_param != nullptr);
    stat("ProcessorCommand.asm", &(asm_param->stat_ptr));
    asm_param->asm_file_size = asm_param->stat_ptr.st_size;
}

void GetAsmFileNumStrings(AsmFileParams* asm_param){

    assert(asm_param != nullptr);
    FILE* file_ptr = fopen("ProcessorCommand.asm", "r");
    if (file_ptr == NULL) {
        perror("Error opening file");
    }
    asm_param->asm_nStrings = 0;
    char file_symbol= 0;
    while ((file_symbol = fgetc(file_ptr)) != EOF) {
        if (file_symbol == '\n') {
            fprintf(stdout, "%s\n", "1");
            asm_param->asm_nStrings++;
        }
        fprintf(stdout, "%d\n", asm_param->asm_nStrings);
    }
    fclose(file_ptr);

}

