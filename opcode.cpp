//
// Created by Ivan Delgado on 10/20/2021
//

#include "opcode.h"
#define OP_TABLE_SIZE 59

struct OpTabVals {
    std::string name;
    int OpCode;
    int format;
};

const struct OpTabVals opCodeTable[] = {
    {"ADD", 0x18, 3},  {"ADDF", 0x58, 3},   {"ADDR", 0x90, 2},   {"AND", 0x40, 3},  {"CLEAR", 0xB4, 2},
    {"COMP", 0x28, 3}, {"COMPF", 0x88, 3},  {"COMPR", 0xA0, 2},  {"DIV", 0x24, 3},  {"DIVF", 0x64, 3},
    {"DIVR", 0x9C, 2}, {"FIX", 0xC4, 1},    {"FLOAT", 0xC0, 1},  {"HIO", 0xF4, 1},  {"J", 0x3C, 3},
    {"JEQ", 0x30, 3},  {"JGT", 0x34, 3},    {"JLT", 0x38, 3},    {"JSUB", 0x48, 3}, {"LDA", 0x00, 3},
    {"LDB", 0x68, 3},  {"LDCH", 0x50, 3},   {"LDF", 0x70, 3},    {"LDL", 0x08, 3},  {"LDS", 0x6C, 3},
    {"LDT", 0x74, 3},  {"LDX", 0x04, 3},    {"LPS", 0xD0, 3},    {"MUL", 0x20, 3},  {"MULF", 0x60, 3},
    {"MULR", 0x98, 2}, {"NORM", 0xC8, 1},   {"OR", 0x44, 3},     {"RD", 0xD8, 3},   {"RMO", 0xAC, 2},
    {"RSUB", 0x4C, 3}, {"SHIFTL", 0xA4, 2}, {"SHIFTR", 0xA8, 2}, {"SIO", 0xF0, 1},  {"SSK", 0xEC, 3},
    {"STA", 0x0C, 3},  {"STB", 0x78, 3},    {"STCH", 0x54, 3},   {"STF", 0x80, 3},  {"STI", 0xD4, 3},
    {"STL", 0x14, 3},  {"STS", 0x7C, 3},    {"STSW", 0xE8, 3},   {"STT", 0x84, 3},  {"STX", 0x10, 3},
    {"SUB", 0x1C, 3},  {"SUBF", 0x5C, 3},   {"SUBR", 0x94, 2},   {"SVC", 0xB0, 2},  {"TD", 0xE0, 3},
    {"TIO", 0xF8, 1},  {"TIX", 0x2C, 3},    {"TIXR", 0xB8, 2},   {"WD", 0xDC, 3}
};

// takes in opcode and retrieves its corresponding mnemonic
std::string OpTab::getMnemonic(int opCode) { 
    for (int i = 0; i < OP_TABLE_SIZE; i++)
            if (opCodeTable[i].OpCode == opCode) 
            {
                return opCodeTable[i].name;
            }
        int newOpCode = opCode & 0xFC;  //bit mask to get the first 6 bits
        return getMnemonic(newOpCode); // using recursion 
}

// takes in opcode and gets corresponding format. Same process as getMnemonic
int OpTab::getFormat(int opCode) { 
    for (int i = 0; i < OP_TABLE_SIZE; i++)
        if (opCodeTable[i].OpCode == opCode)
        {
            return opCodeTable[i].format;
        }
    int newOpCode = opCode & 0xFC;
    return getFormat(newOpCode);
}

// retrieve a single bit of any input at any position N
// https://stackoverflow.com/questions/9531214/access-individual-bits-in-a-char-c
bool OpTab::getBitN(int input, int n) {
    return ((input >> n) & 1);
}

// Conversion functions

// char array to int 
int OpTab::charArrayToInt(char num[]) {
   int len = strlen(num);
   int base = 1;
   int temp = 0;
   for (int i=len-1; i>=0; i--) {
      if (num[i]>='0' && num[i]<='9') {
         temp += (num[i] - 48)*base;
         base = base * 16;
      }
      else if (num[i]>='A' && num[i]<='F') {
         temp += (num[i] - 55)*base;
         base = base*16;
      }
   }
   return temp;
}

// hex char to int
int OpTab::hexCharToDecimal(char a)
{
    int b = (int)a;
    b = b - 55; // handles hex conversion of A, B, C, D, E, F
    return b;
}

// int to hex char
char OpTab::decimalToHexChar(int a) 
{
    if (a > 9)
    {
        char hexValues[] = {'A', 'B', 'C', 'D', 'E', 'F'};
        for (int i = 1; i < 7; i++) 
        {
            if (a - 9 == i)
            return hexValues[i - 1];
        }
    }
    else 
    {
        int b = a + '0';
        return b;
    }
    return 'X';
}

// gets mnemonic based off register number (Hard coded)
std::string OpTab::getRegister(int a)
{
    std::string mnemonic[] = {"A", "X", "L", "B", "S", "T", "F", "PC", "SW"};

    if (a <= 6) {
        return mnemonic[a];
    } else if (a == 8) {
        return mnemonic[7];
    } else if (a == 9) {
        return mnemonic[8];
    } 
}