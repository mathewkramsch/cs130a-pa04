# Makefile

CXX=g++
FLAGS=-std=c++11 -Wall -Wextra -Werror
DEPENDENCIES= src/main.o src/utility.o src/BOARD/board.o

all: make_obj_dir snl cleanup

snl: ${DEPENDENCIES}
	${CXX} $^ ${FLAGS} -o $@

make_obj_dir:
	mkdir -p obj
cleanup:
	mv src/*o src/BOARD/*.o -t obj
clean:
	/bin/rm -f -r obj src/*.o src/BOARD/*.o snl vgcore*
