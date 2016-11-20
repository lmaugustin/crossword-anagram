# Makefile for the Game of Life

GFLAGS=-g -c -std=c++11

crossword: crossword.o word.o puzzle.o
	g++ crossword.o word.o puzzle.o -o crossword

word.o: word.cpp word.h
	g++ ${GFLAGS} word.cpp -o word.o

puzzle.o: puzzle.cpp puzzle.h
	g++ ${GFLAGS} puzzle.cpp -o puzzle.o

crossword.o: crossword.cpp
	g++ ${GFLAGS} crossword.cpp -o crossword.o

clean:
	rm -f *.o *~ crossword
