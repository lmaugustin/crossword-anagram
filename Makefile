# Makefile for the Game of Life

GFLAGS=-g -c -std=c++11

life: lifeboard.o life.o
	g++ lifeboard.o life.o -o life

lifeboard.o: lifeboard.cpp lifeboard.h
	g++ ${GFLAGS} lifeboard.cpp -o lifeboard.o

life.o: life.cpp
	g++ ${GFLAGS} life.cpp -o life.o

clean:
	rm *.o *~ life
