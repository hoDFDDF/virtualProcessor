#include "AsmFileParametrs.h"
#include "Assembler.h"

int main(){
    AsmFileParams asm_file_param = {};
    ProcessorInstructions instruction = {};
    Command cmd = {};
    ReadTextFromAsmFile(&instruction, &asm_file_param);
    FillCodeArray(&instruction, &asm_file_param, &cmd);
    WriteTranstaledComandToFile(&instruction);
    
    return 0;
}