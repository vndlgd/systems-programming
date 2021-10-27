//
// Created by Jose Moreno Reyes on 10/14/21.
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
 * This function will take the 1st line of the header record
 * that is stored in a vector of vectors, and then it will
 * analyze the line and add the 1st line to the out.lst file.
 */
void Dasm::headerRecord(std::string line1)
{
    //1  2-7    8-13  14-19
    //H Assign 000000 0005A2
    //Add the starting address 0000
    std::string strAddress = line1.substr(7, 4);
    //Need address of the
    std::string address = "  0";
    std::string pName = line1.substr(1, 6);

    outFile << std::setw(5) << std::left << strAddress << " " <<pName
    << "  START" << address << std::endl;
}
/*
 * This function will be the main driver to disassemble txt records
 * from the test.obj. It will be also responsible for writing to the outfile.
 */
void Dasm::textRecord(std::string textRecord)
{
    /*
     * Need to keep track of PC. (where i am where the next line is going to be
     * start at 0.
     * go to the first leading 2, 69
     * 69 -> dec 011010(Add 2 0'') 01
     * convert 01101000 to hex == 68, then 68 is LDB in the
     * OPCode table
     * Go to symbol table and check if address is there 0000
     * If so, add corresponding values. We've FIRST
     *
     * Take the next 3, 691, 011010 010001 is extended.
     * NEED, to also check operand type. # @
     * In SYmbol table we've 002C6 which is RETADR
     *
     * 1 = T
     * 2-7 = Start Address of record(hex)
     * 8-9 = Lenght of object code record; bytes (hexa)
     * 10-69 = Object Code (69/10+1) = 10 inst
     * 1 234567 89 10-20
     * T 000000 0A 691002C61722BF0222BC
     */

}
/*
 * This function will take the first line as a parameter to get the name of the program.
 * and the last line as a parameter as well.
 */
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
            std::cout << "Header Record: " << header << std::endl;
            headerRecord(header);
        }
        //text record
        else if (fileData[i][i][0] == 'T')
        {
            std::string text = fileData[i][i];
            std::cout << "Text Record: " << text << std::endl;
        }
            //Modification Record
        else if (fileData[i][i][0] == 'M')
        {
            std::string modification = fileData[i][i];
            std::cout << "Modification Record: " << modification << std::endl;
        }
            //End Record
        else if (fileData[i][i][0] == 'E')
        {
            std::string end = fileData[i][i];
            endRecord(end, header);
            std::cout << "End Record: " << end << std::endl;
        }
    }
    std::cout << "Write to file completed." << std::endl;
}

void Dasm::format2(OpCode opcode, std::string line, int instruction, int position) {
    std::string opCodeName = opcode.getMnemonic(instruction);

    int r1; // 3rd char, convert from char to int and getRegister(r1)
    int r2; // 4th char convert from char to int and getRegister(r2)

}

int Dasm::format3(OpCode opcode, std::string line, int instruction, int position) {
    std::string opCodeName = opcode.getMnemonic(instruction);
    bool nixbpe[6];

}

