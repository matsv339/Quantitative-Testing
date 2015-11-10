CC = g++
LIB = -larmadillo -lboost_system -lboost_iostreams
CFLAGS = -c

default: all
	@./test

all: test.o
	@$(CC) test.o -o test $(LIB)

test.o: test.cpp
	@$(CC) $(CFLAGS) test.cpp

clean:
	rm *o test