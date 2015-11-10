CC = g++
LIB = -larmadillo -lboost_system -lboost_iostreams
CFLAGS = -c

default: all
	@./main

all: main.o
	@$(CC) main.o -o main $(LIB)

main.o: main.cpp
	@$(CC) $(CFLAGS) main.cpp

clean:
	rm *o main