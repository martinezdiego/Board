# La ruta de tu instalación de clang o g++
CXX = clang++ -std=c++14

FLAGS = -g -O2 -Wall

INCLUDE = -I.

default: main

main: board.o
	$(CXX) $(FLAGS) $(INCLUDE) $@.cpp -o $@  board.o

board.o: board.cpp
	$(CXX) $(FLAGS) $(INCLUDE) -c board.cpp

clean:
	$(RM) *~ *.o main 
