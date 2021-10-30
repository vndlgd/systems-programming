//
// Created by Ivan Delgado and Jose Moreno Reyes 
//

#include "Dasm.h"

std::ifstream objFile, symFile;
std::ofstream outFile ("out.lst");
std::vector<std::vector<std::string > > fileData;
std::vector<std::string> symName;
std::vector<std::string> symValue;
std::vector<std::string> symFlag;
std::vector<std::string> litNames;
std::vector<std::string> litLength;
std::vector<std::string> litAddr;
std::vector<std::string> litConst;

//Read file data into a vector
//https://www.tutorialspoint.com/how-to-read-a-text-file-with-cplusplus
void Dasm::readFile(char *fileName)
{
    //Open File
    //std::ifstream objFile(fileName);
    objFile.open(fileName);
    if (!objFile.is_open())
    {
        std::cout << ".obj File Not Found" << std::endl;
        exit(EXIT_FAILURE);
    }
    //Read Data line by line into vector of vectors
    std::string str;
    std::vector<std::string> temp;
    while (std::getline(objFile, str))
    {
        temp.push_back(str);
        fileData.push_back(temp);
    }
    objFile.close();
}
void Dasm::readSymbol(char *fileName)
{
    symFile.open(fileName);
    if (!symFile.is_open())
    {
        std::cout << ".sym File Not Found" << std::endl;
        exit(EXIT_FAILURE);
    }
    //Read Data line by line into vector of vectors
    std::vector<std::string> tempVector;
    std::string line;
    while(symFile.good())
    {
        getline(symFile, line);
        tempVector.push_back(line);

    }
    std::string tempLine;
    //iterate through the 2 vector
    for (int i = 2; i < tempVector[i].size(); i++)
    {
        symName.push_back(tempVector[i].substr(0,6));
        symValue.push_back(tempVector[i].substr(8,6));
        symFlag.push_back(tempVector[i].substr(16, 1));
    }
    for (int i = 10; i < tempVector[i].size(); i++)
    {
        litNames.push_back(tempVector[i].substr(0, 4));
        litConst.push_back(tempVector[i].substr(8,10));
        litLength.push_back(tempVector[i].substr(20, 1));
        litAddr.push_back(tempVector[i].substr(24,6));
    }
}

/*
 * This function will be the main driver to disassemble txt records
 * from the test.obj. It will be also responsible for writing to the outfile.
 */
int Dasm::instructionAnalyzer(int row, int current)
{
    OpTab code = *new OpTab;
    int opcode = (int)strtol(fileData[row][row].substr(current, 2).c_str(), NULL, 16);
    int opFormat = code.getFormat(opcode);
    outFile << std::uppercase << std::setfill('0') << std::setw(4) << std::right << std::hex << currentAddress << "  ";

    if (opFormat == 2) 
    {
        format2(code, opcode, row, current);
    }
    else if (opFormat == 3)
    {
        opFormat = format3(code, opcode, row, current);
    }
    if (opFormat != 1)
        std::cout << "";
        return (opFormat * 2);
}

/*
 * This function will take the 1st line of the header record
 * that is stored in a vector of vectors, and then it will
 * analyze the line and add the 1st line to the out.lst file.
 */
void Dasm::headerRecord(int row)
{
    //1  2-7    8-13  14-19
    //H Assign 000000 0005A2
    //Add the starting address 0000
    std::string strAddress = fileData[row][row].substr(7, 4);
    //Need address of the
    std::string address = "  0";
    std::string pName = fileData[row][row].substr(1, 6);
    currentAddress = 0;
    targetAddress = 0;

    outFile << std::setw(5) << std::left << strAddress << " " <<pName
    << "  START" << address << std::endl;
}

void Dasm::textRecordAnalyzer(int row) { 
    OpTab code = *new OpTab;
    int current = 9; 
    int textLength = 2 * (int)strtol(fileData[row][row].substr(7, 2).c_str(), NULL, 16); // how many chars
    // unsigned int currentAddress = ((unsigned int)strtol(fileData[0][0].substr(7, 6).c_str(), NULL, 16));
    // std::cout << currentAddress << std::endl;

    while (current < (textLength + 9)) {
        int objSize = instructionAnalyzer(row, current);
        currentAddress += (objSize/2);
        current += objSize;
    }
    // check for assembler directives
    // check symbol table before opcodes
}

void Dasm::endRecord(std::string lastLine, std::string fline)
{
    //E000000
    std::string pName = fline.substr(1, 6);
    outFile << "              " << "END" << "    " << pName << std::endl;
}


void Dasm::diss()
{
    std::string header;
    for (int i = 0; i < fileData.size(); i++)
    {
        //headerRecord
        if (fileData[i][i][0] == 'H')
        {
            header = fileData[i][i];
            // std::cout << "Header Record: " << header << std::endl;
            headerRecord(i);
        }
        //text record
        else if (fileData[i][i][0] == 'T')
        {
            std::string text = fileData[i][i];
            textRecordAnalyzer(i);
        }
            //End Record
        else if (fileData[i][i][0] == 'E')
        {
            std::string end = fileData[i][i];
            endRecord(end, header);
        }
    }
}

void Dasm::format2(OpTab opcode, int instruction, int row, int position) {
    OpTab code = *new OpTab;
    std::string name = code.getMnemonic(instruction);

    for (int i = 0; i < symValue.size() - 1; i++) {
        if (currentAddress == symValue[i][i]) {
            break;
        } 
    }

    for (int i = 0; i < litNames.size() - 1; i++) {
        if (currentAddress == litNames[i][i]) {
            return;
        }
    }

    int register1 = (int)strtol(fileData[row][row].substr(position+2, 1).c_str(), NULL, 16); 
    int register2 = (int)strtol(fileData[row][row].substr(position+3, 1).c_str(), NULL, 16); 
    std::string objectCode = fileData[row][row].substr(position, 4);
    outFile << name << "  ";
    if (register1 == 0 || register2 == 0)
    {
        outFile << "A,";
    }
    else if (register1 == 1 || register2 == 1)
    {
        outFile << "X,";
    }
    else if (register1 == 2 || register2 == 2)
    {
        outFile << "L,";
    }
    else if (register1 == 3 || register2 == 3)
    {
        outFile << "B,";
    }
    else if (register1 == 4 || register2 == 4)
    {
        outFile << "S,";
    }
    else if (register1 == 5 || register2 == 5)
    {
        outFile << "T,";
    }
    else
    {
        outFile << "F,";
    }
    
    outFile << "  " << objectCode << std::endl;
}

int Dasm::format3(OpTab opcode, int instruction, int row, int position) {
    OpTab code = *new OpTab;
    std::string name = code.getMnemonic(instruction);
    int format = code.getFormat(instruction);
    bool nixbpe[6];
    int flags = (int)strtol(fileData[row][row].substr(position+1, 2).c_str(), NULL, 16);
    flags = flags & 0x3F; // remove 2 left most bits for nixbpe 
    outFile << name << "  ";

    for (int i = 0; i <= 5; i++)
    {
        nixbpe[i] = code.getBitN(flags, 5-i); // nixbpe stored as [n, i, x, b, p, e], n being position 5
    }

    for (int i = 0; i < symValue.size() - 1; i++) { // check for symbol table
        int sym = strtol(symValue[i].c_str(), NULL, 16);
        if (currentAddress == sym) {
            outFile << symName[i]; 
            break;
        } 
    }

    for (int i = 0; i < litNames.size() - 1; i++) { // check for literal table
        int literal = strtol(litAddr[i].c_str(), NULL, 16);
        if (currentAddress == literal) {
        }
    }

    if (nixbpe[5] == 1) // if e = 1 (insert format 4 code here)
    {
        format = format4(opcode, instruction, row, position);
    }
    else 
    {
        std::string objectCode = fileData[row][row].substr(position, 6);

        targetAddress = (unsigned int)strtol(fileData[row][row].substr(position, 6).c_str(), NULL, 16);
        targetAddress = targetAddress & 0x000FFF; 

        if (nixbpe[3] == 0 && nixbpe[4] == 1) { // b = 0 p = 1 PC relative
            targetAddress = targetAddress + currentAddress + 3;
        }

        if (nixbpe[3] == 1 && nixbpe[4] == 0) { // b = 1 p = 0 base relative
            targetAddress = targetAddress + baseAddress;
        }

        if (nixbpe[0] == 0 && nixbpe[1] == 1) // immediate addressing
        {
            for (int i = 0; i < symValue.size() - 1; i++) {
                int sym = (unsigned int)strtol(symValue[i].c_str(), NULL, 16);
                if (targetAddress == sym || currentAddress == sym) {
                    //outFile << "    #" << symName[i];
                }
            }
        } else if (nixbpe[0] == 1 && nixbpe[1] == 0) // indirect addressing
        {
            outFile << "    @";
        } else if (nixbpe[0] == 1 && nixbpe[1] == 1) // simple addressing
        {
            outFile << "    ";
        }

        outFile << objectCode << std::endl;
    }
    return format;
}

int Dasm::format4(OpTab opcode, int instruction, int row, int position) 
{
    OpTab code = *new OpTab;
    std::string name = code.getMnemonic(instruction);
    int format = code.getFormat(instruction);
    bool nixbpe[6];
    int flags = (int)strtol(fileData[row][row].substr(position+1, 2).c_str(), NULL, 16);
    flags = flags & 0x3F; // remove 2 left most bits for nixbpe 

    for (int i = 0; i <= 5; i++)
    {
        nixbpe[i] = code.getBitN(flags, 5-i); // nixbpe stored as [n, i, x, b, p, e], n being position 5
    }

    targetAddress = (unsigned int)strtol(fileData[row][row].substr(position, 8).c_str(), NULL, 16);
    targetAddress = targetAddress & 0x000FFFFF; 

    if (nixbpe[3] == 0 && nixbpe[4] == 0) {
        outFile << "+" << name << "  ";
        for (int i = 0; i < symValue.size() - 1; i++) {
            int sym = (unsigned int)strtol(symValue[i].c_str(), NULL, 16);
            if (targetAddress == sym) {
                outFile << "    #" << symName[i];
                break;
            }
        }
    }
        std::string objectCode = fileData[row][row].substr(position, 8);
        outFile << "    " << objectCode << std::endl;
        return (3+nixbpe[5]);
}
