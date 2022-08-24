#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <stdio.h>
#include "DisassemblerConstants.h"


// TODO: fix printf of hex codes
int Disassemble(unsigned char *codebuffer, int addr)
{
    unsigned char *code = &codebuffer[addr];
    int opbytes = 1;
    printf("%04x\t%s", addr, DisassemblerConst::instr[*code].mnemonic.c_str());
    if (DisassemblerConst::instr[*code].size > opbytes) {
        if (DisassemblerConst::instr[*code].size == 3) {
            printf("%02x", &codebuffer[addr + 2]);
        }
        printf("%02xh", &codebuffer[addr + 1]);
        opbytes = DisassemblerConst::instr[*code].size;
    }

    printf("\n");
    return opbytes;
}

int main(int argc, char *argv[])
{
    if(argc != 2){
        std::cerr<<"usage: d80 file.com";
    }
    FILE *f = fopen(argv[1], "rb");
    if (f == NULL){
        std::cerr<<"error: could not open: "<<argv[1];
    }

    fseek(f, 0L, SEEK_END);
    int fsize = ftell(f);
    fseek(f, 0L, SEEK_SET);

    unsigned char *buffer = (unsigned char *) malloc(fsize);

    fread(buffer, fsize, 1, f);
    fclose(f);

    int addr = 0;

    while (addr<fsize) {
        addr+=Disassemble(buffer, addr);
    }
    return 0;
}

