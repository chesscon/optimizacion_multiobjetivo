CCOMP=g++
CFLAGS=-std=c++11 -lm

VFLAGS=--leak-check=full --show-leak-kinds=all

SRC_DIR=src

SRC_TestDom=TestDominancia.cpp Individuo.cpp Dominancia.cpp

## TEST DOMINANCIA
TestDominancia: $(addprefix $(SRC_DIR)/, $(SRC_TestDom) Individuo.hpp )
	$(CCOMP) -O2 -o $@ $(addprefix $(SRC_DIR)/, $(SRC_TestDom) ) $(CFLAGS) 

valgrind1:
	$(CCOMP) -o Main $(addprefix $(SRC_DIR)/, $(SRC_TestDom) ) -g $(CFLAGS) 
	valgrind  --leak-check=full ./Main 100 3
	rm -f ./Main

test1_2D: TestDominancia
	./TestDominancia 100 2

test1_3D: TestDominancia
	./TestDominancia 10 3


## TEST Toolkit
# Toolkit
mainTk: $(addprefix $(SRC_DIR)/, mainTk.cpp Toolkit/*.cpp )
	$(CCOMP) -O2 -o $@ $^ $(CFLAGS) 	

WFG=1
TOTAL_POINTS=1000
Toolkit_WFG: mainTk
	./mainTk WFG$(WFG) $(TOTAL_POINTS) > output/front_WFG$(WFG).txt