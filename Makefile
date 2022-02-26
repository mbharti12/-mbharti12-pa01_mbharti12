# Makefile
#also have to compile the game itself
CXX_FLAG = --std=c++11 -g

all: clean tests ./tests

game: main.o cards.o
	g++ $(CXX_FLAG) -o game main.o cards.o

tests: tests.o cards.o
	g++ $(CXX_FLAG) -o tests tests.o cards.o

main.o: main.cpp
	g++ -c $(CXX_FLAG) main.cpp

tests.o: tests.cpp
	g++ -c $(CXX_FLAG) tests.cpp

cards.o: cards.cpp
	g++ -c $(CXX_FLAG) cards.cpp

clean:
	rm -f tests game *.o