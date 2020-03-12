// board.cpp

#include "board.h"
using namespace std;

int board::getNumMoves() {
	return -1;  // STUB
}

string board::getPath() {
	return "stub";
}

string board::printVectors() {
	string s="";
	s+= "LADDERS VECTOR:\n";
	for (int i=0; i<ladders.size(); i++)
		s+= "("+ to_string(ladders[i].first) +","+ to_string(ladders[i].second) +") ";
	s+= "\nSNAKES VECTOR:\n";
	for (int i=0; i<snakes.size(); i++)
		s+= "("+ to_string(snakes[i].first) +","+ to_string(snakes[i].second) +") ";
	return s + "\n";
}
