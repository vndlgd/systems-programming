// Ivan Delgado
// Jose Moreno Reyes
// CS530 FAll 2021 Ben Shen

#include "opcode.h"
#include "Dasm.h"

using namespace std;

int main(int argc, char **argv)
{

    //New object
    Dasm newDisassembler;
    newDisassembler.readFile(argv[1]);
    newDisassembler.readSymbol(argv[2]);
    newDisassembler.diss();

    return 0;
}
