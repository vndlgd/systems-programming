//
// Created by Jose Moreno Reyes on 10/16/21.
//

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
#include "opcode.h"


class Dasm {

public:
    void diss();
    void readFile(char *fileName);
    void readSymbol(char *fileName);

private:
    void headerRecord(std::string line1);
    void textRecord(std::string textRecord);
    void endRecord(std::string lastLine, std::string fline);
    void format2(OpCode opcode, std::string line, int instruction, int position);
    int format3(OpCode opcode, std::string line, int instruction, int position);

};
#endif //PG01_DASM_H
