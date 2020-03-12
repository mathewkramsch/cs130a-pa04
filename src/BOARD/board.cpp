// board.cpp

#include "board.h"
using namespace std;

string board::getPath() {
	int current = 1;
	string path = 1 + " ";
	vector<int> snakeHeadsInWay;

	vector<pair<int,int>> laddersToTake = getLaddersToTake();

	// also try to go to biggest ladder
	for (int i=0; i<laddersToTake.size(); i++) {
		for (int j=0; j<snakes.size(); i++)
			if (snakes[j].first < laddersToTake[i].first) snakeHeadsInWay.push_back(snakes[j].first);
		path += getPathToLadder(current, laddersToTake[i], snakeHeadsInWay);
		snakeHeadsInWay.clear();
	}
	path += getPathToEnd(current);
	return path;
}

vector<pair<int,int>> board::getLaddersToTake() {
// POSTCONDITION: returns vector of ladders to take in order to take them
	// each \element .first= start of ladder, .second= end of ladder
	// if ladders vector is empty, returns NULL
	if (ladders.empty()) return NULL;
	vector<pair<int,int>> laddersToTake;
	pair<int,int> nextLadder = ladders[0];
	int nextLadderSize = ladders[0].second - ladders[0].first;
	int prevLadderEnd = 1;
	bool takeLadder = false;

	/* CRITERIA FOR NEXTLADDER
	 CASE 1: small ladder (if ladder end - start < 6) 
	 	- only take if ladderEnd > previous roll +6
	CASE 2: ladder inside another ladder
		- dont take that ladder
	CASE 3: ladder's end is in another ladder's start (if nextLadder.second > other ladder's.first)
		- take the ladder whose path to get to end of other ladder is less
	*/

	for (int i=0; i<ladders.size(); i++) {
		if (ladders[i].first < nextLadder.first) {
			if (ladders[i].second > nextLadder.second) 
				takeLadder = true;
		}
		if (takeLadder) laddersToTake.push_back(ladders[i]);
	}
	return laddersToTake;
}

string board::getPathToLadder(int &current, pair<int,int> ladder, vector<int> snakeHeadsInWay) {
// PRECONDITION: current = current space on board
	// ladder = (start of ladder, end of ladder) and is the ladder to take
// POSTCONDITION: returns the path to ladder avoiding snake heads in the way
	// ladder traversals are given by '+', there is a space at the end of path
	// updates current. if no path to ladder (blocked by snakeHeads) returns empty path
	string path = "";
	if (ladder.first - current <= 6) {
		current = ladder.second;
		return to_string(ladder.first) +"+"+ to_string(ladder.second);
	}  // else ladder is not reachable in this roll
	int roll = 6;
	bool collision = false;  // if current space == snakeHead space
	do {
		if (collision) roll--;
		for (int i=0; i<snakeHeadsInWay.size(); i++) {
			if (current+roll == snakeHeadsInWay[i]) collision = true;
		}
	} while (collsion);

	if (roll>0) {
		current += roll;
		path += to_string(current) +" "+ getPathToLadder(current+roll, ladder, snakeHeadsInWay);
	}
	return path;
}

string board::getPathToEnd(int &current) {
// PRECONDITION: current is the current space on the board
// POSTCONDITION: returns the path to the end of the board (without ladders)
	string path = "";
	bool collision = false;
	int roll = 6;
	do {
		if (collision) roll--;
		for (int i=0; i<snakes.size(); i++) {

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
