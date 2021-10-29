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
    void instructionAnalyzer(); // change to int 
    void textRecordAnalyzer(int row);

private:
    void headerRecord(std::string line1);
    void textRecord(std::string textRecord);
    void endRecord(std::string lastLine, std::string fline);
    void format2(OpTab opcode, int instruction, int row, int position);
    int format3(OpTab opcode, int instruction, int row, int position);
    int format4(OpTab opcode, int instruction, int row, int position);
};
#endif //PG01_DASM_H
