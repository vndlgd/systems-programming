//
// Created by Jose Moreno Reyes on 10/16/21.
//
#pragma once
#ifndef PG01_DASM_H
#define PG01_DASM_H
#include <stdio.h>
#include <string>
#include <iomanip>
#include <iterator>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include "opcode.cpp"


class Dasm {

public:
    void diss();
    void readFile(char *fileName);
    void readSymbol(char *fileName);
    void textRecordAnalyzer(int row);

private:
    void headerRecord(int row);
    int instructionAnalyzer(int row, int current);
    void endRecord(std::string lastLine, std::string fline);
    void format2(OpTab opcode, int instruction, int row, int position);
    int format3(OpTab opcode, int instruction, int row, int position);
    int format4(OpTab opcode, int instruction, int row, int position);

    unsigned int currentAddress;
    unsigned int baseAddress;
    unsigned int targetAddress;
};
#endif //PG01_DASM_H