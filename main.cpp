// Ivan Delgado
// Jose Moreno Reyes
// CS530 FAll 2021 Ben Shen

#include "Dasm.cpp"

using namespace std;

int main(int argc, char **argv)
{

    //New object
    Dasm newDisassembler;
    // OpCode op;
    newDisassembler.readFile(argv[1]);
    newDisassembler.readSymbol(argv[2]);
    newDisassembler.diss();
    newDisassembler.instructionAnalyzer();

    return 0;
}
