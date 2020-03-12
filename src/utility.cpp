// utility.cpp

#include "utility.h"

int getNumMoves(std::string pathTaken) {
// PRECONDITION: pathTaken is the path taken to get to end of board in least number of moves
// POSTCONDITION: returns number of moves taken in pathTaken (by counting number of spaces)
	int spaces=0;
	for (int i=0; i<pathTaken.size(); i++) {
		if (pathTaken[i] == ' ') spaces++;
	} return spaces;
}
