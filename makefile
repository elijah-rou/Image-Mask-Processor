CC = g++
CC_FLAGS = -c -Wall -o 
LD_FLAGS = -o
SRC_FILES = $(wildcard src/*.cpp)
TEST_FILES = $(wildcard test/*.cpp) src/Image*
OBJ_FILES = $(addprefix obj/,$(notdir $(SRC_FILES:.cpp=.o)))
OUT = imageops

default: $(OBJ_FILES)
# create main
	$(CC) $(SRC_FILES) $(LD_FLAGS) bin/$(OUT) --std=c++11

obj/%.o :src/%.cpp
	$(CC) $(CC_FLAGS) $@ $^ --std=c++11

clean:
	-rm obj/*.o
	-rm bin/$(OUT)
	-rm bin/test
	-rm bin/output/*

run:
	@make
	bin/$(OUT) $(args)

quick:
	@make
	bin/$(OUT) -a Lenna_standard.pgm Lenna_hat_mask.pgm outAdd
	bin/$(OUT) -s Lenna_standard.pgm Lenna_hat_mask.pgm outSub
	bin/$(OUT) -i Lenna_standard.pgm outInv
	bin/$(OUT) -l Lenna_standard.pgm Lenna_hat_mask.pgm outMas
	bin/$(OUT) -t Lenna_standard.pgm 100 outThr
	bin/$(OUT) -f Lenna_standard.pgm blur.fir outFil

test: $(OBJ_FILES)
	$(CC) $(TEST_FILES) -o bin/test --std=c++11
	bin/test

