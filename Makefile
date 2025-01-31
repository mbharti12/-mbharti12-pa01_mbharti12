# Makefile
#also have to compile the game itself
CXX_FLAG = --std=c++11 -g

all: game

game: main.o cards.o utility.o
	g++ $(CXX_FLAG) -o game main.o cards.o utility.o

tests: tests.o cards.o utility.o
	g++ $(CXX_FLAG) -o tests tests.o cards.o utility.o

main.o: main.cpp
	g++ -c $(CXX_FLAG) main.cpp

tests.o: tests.cpp
	g++ -c $(CXX_FLAG) tests.cpp

cards.o: cards.cpp
	g++ -c $(CXX_FLAG) cards.cpp

utility.o: utility.cpp
	g++ -c $(CXX_FLAG) utility.cpp

clean:
	rm -f tests game *.o