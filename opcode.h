//
// Created by Ivan Delgado on 10/20/2021
//

#ifndef OPCODE_H
#define OPCODE_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <string.h>
#include <fstream>
#include <cmath>

class OpCode {

public:
    std::string getMnemonic(int opCode);
    int getFormat(int opCode);
    bool getBitN(int input, int n);
    int charArrayToInt(char num[]);
    int hexCharToDecimal(char a);
    char decimalToHexChar(int a);
    std::string getRegister(int a);
};
#endif

