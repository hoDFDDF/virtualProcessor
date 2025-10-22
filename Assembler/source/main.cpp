#include "AsmFileParametrs.h"
#include "Assembler.h"

int main(){
    AsmFileParams asm_file_param = {};
    ProcessorInstructions instruction = {};
    ReadTextFromAsmFile(&instruction, &asm_file_param);
    FillCodeArray(&instruction, &asm_file_param);
    WriteTranstaledComandToFile(&instruction);
    
    return 0;
}