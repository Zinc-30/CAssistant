# Project: CA
# Makefile created by Dev-C++ 5.4.2

CPP      = g++
CC       = gcc
OBJ      = char_oper.o del_comment.o file_io.o indent.o parentheses.o main.o identifier.o include.o define.o compare.o presolve.o
LINKOBJ  = char_oper.o del_comment.o file_io.o indent.o parentheses.o main.o identifier.o include.o define.o compare.o presolve.o
LIBS     = -lm -static-libstdc++ -static-libgcc -g3 #-L"F:/Dev-Cpp/MinGW32/lib"
INCS     = #-I"F:/Dev-Cpp/MinGW32/include"
CXXINCS  = #-I"F:/Dev-Cpp/MinGW32/include"
BIN      = ca 
CXXFLAGS = $(CXXINCS) -g3
CFLAGS   = $(INCS) -g3
RM       = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after


clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CC) $(LINKOBJ) -o $(BIN) $(LIBS)

char_oper.o: char_oper.c
	$(CC) -c char_oper.c -o char_oper.o $(CFLAGS)

del_comment.o: del_comment.c
	$(CC) -c del_comment.c -o del_comment.o $(CFLAGS)

file_io.o: file_io.c
	$(CC) -c file_io.c -o file_io.o $(CFLAGS)

indent.o: indent.c
	$(CC) -c indent.c -o indent.o $(CFLAGS)

parentheses.o: parentheses.c
	$(CC) -c parentheses.c -o parentheses.o $(CFLAGS)

main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS)

identifier.o: identifier.c
	$(CC) -c identifier.c -o identifier.o $(CFLAGS)

include.o: include.c
	$(CC) -c include.c -o include.o $(CFLAGS)

define.o: define.c
	$(CC) -c define.c -o define.o $(CFLAGS)

compare.o: compare.c
	$(CC) -c compare.c -o compare.o $(CFLAGS)

presolve.o: presolve.c
	$(CC) -c presolve.c -o presolve.o $(CFLAGS)
