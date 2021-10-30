# CC = g++
# CFLAGS = -c
# TARGET = dsm
#
# all: $(TARGET)
#
# $(TARGET): main.o Dasm.o opcode.o
# 	$(CC) main.o Dasm.o opcode.o -o $(TARGET)
#
# main.o: main.cpp
# 	$(CC) $(CFLAGS) main.cpp
#
# Dasm.o: Dasm.cpp
# 	$(CC) $(CFLAGS) Dasm.cpp
#
# OpCode.o: OpCode.cpp
# 	$(CC) $(CFLAGS) opcode.cpp
#
# clean:
# 	rm -f core *.o $(TARGET)

CC=g++

CFLAGS= -std=c++11

all: dissem

dissem: main.cpp Dasm.cpp opcode.cpp
	$(CC) $(CFLAGS) main.cpp -o dissem

clean:
	$(RM) *.o out.lst dissem