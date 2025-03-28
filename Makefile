CCOMP=g++
CFLAGS=-std=c++11 -lm

VFLAGS=--leak-check=full --show-leak-kinds=all

SRC_DIR=srcmake

SRC_TestDom=TestDominancia.cpp Individuo.cpp Dominancia.cpp SegmentTree.cpp

TestDominancia: $(addprefix $(SRC_DIR)/, $(SRC_TestDom) Individuo.hpp )
	$(CCOMP) -O2 -o $@ $(addprefix $(SRC_DIR)/, $(SRC_TestDom) ) $(CFLAGS) 

valgrind1:
	$(CCOMP) -o Main $(addprefix $(SRC_DIR)/, $(SRC_TestDom) ) -g $(CFLAGS) 
	valgrind  --leak-check=full ./Main 100 3
	rm -f ./Main

test1_2D: TestDominancia
	./TestDominancia 1000 2

test1_3D: TestDominancia
	./TestDominancia 10 3