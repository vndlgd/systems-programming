# Disassembler Project

First, we read the object file into a vector of vectors, so we can use each vector to find if
the first initial is a 'H', 'T', or 'E' record, and pass that record to its corresponding functions.

In opcode.cpp, we included a struct that contained the opcode mnemonic name, value in hex, and its format
number. Along with a function to obtain the mnemonic and format given an int value. Along with some conversion
methods that we're not all used afterall. We also created a function to obtain a single bit in order to check
the nixbpe flags. 

Main calls our readFile(take the first parameter ".obj") and readSymbol functions (take the 
second parameter ".sym") and finally call our diss function that takes care of all the disassembling. 

Inside of our disassembler file (Dasm.cpp), 
    headerRecord(): takes the first header record and analyze it and print accordingly to the file (out.lst)
    its name and address 
    textRecord(): takes any record that starts with the letter 'T' and begins at position 9, to analyze
    the object codes/literals/symbols.
    However, we did not get to finish this section. We ran out of time and struggled with implementing
    the targetAddress, baseAddress, literals (RETADR), LTORG, currentAddress (gave us a hard time as well).
    
To run this program in the terminal:
cd into the directory and run the following commands:
    make
    dissem test.obj test.sym
