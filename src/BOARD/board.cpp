// board.cpp

#include "board.h"
#include <algorithm>  // for std::sort
#include <iostream>  // DELETE
using namespace std;

string board::getPath() {
	int current = 1;
	string path = "1 ";
	vector<pair<int,int>> laddersToTake = getLaddersToTake();

	for (int i=0; i<laddersToTake.size(); i++) path += getPathToLadder(current, laddersToTake[i]);
	if (current < boardSize*boardSize) path += getPathToEnd(current);
	else { path = path.substr(0,path.size()-1); }
	return path;
}

int board::getNumMoves(string pathTaken) {
// PRECONDITION: pathTaken is the path taken to get to the end of the board in least number of moves
// POSTCONDITION: returns number of moves taken in pathTaken (by counting number of spaces)
	int spaces=0;
	for (int i=0; i<pathTaken.size(); i++) {
		if (pathTaken[i]==' ') spaces++;
	} return spaces;
}

int board::getNumMoves(int start, int end) {
// PRECONDITION: start/end are both spaces on the board
// POSTCONDITION: gets the number of moves required to get from start to end and not hit a snake
	int current = start;
	int count = 0;
	while (current < end) { count++; current += getRoll(current,end); }
	return count;  // now current is >= end, so is at end
}

bool compareLadders(pair<int,int> a, pair<int,int> b) { return a.first < b.first; }
// POSTCONDITION: compares ladders based on which ladder starts first

vector<pair<int,int>> board::getLaddersToTake() {
// POSTCONDITION: returns vector of ladders to take in order to take them
	// each \element .first= start of ladder, .second= end of ladder
	// if ladders vector is empty, returns empty vector
	if (ladders.empty()) return ladders;
	sort(ladders.begin(), ladders.end(), compareLadders);  // sort ladders from smallest to largest

	// cout << "LADDERS: ";
	// for (int i=0; i<ladders.size(); i++) cout << "(" << ladders[i].first << "," << ladders[i].second << ") ";
	// cout << endl;

	vector<pair<int,int>> laddersToTake;
	bool takeLadder;
	int current = 1;  // current space
	bool aSnakeWasTaken = false;

	for (int i=0; i<ladders.size(); i++) {
		if (aSnakeWasTaken) continue;
		takeLadder = true;

		// CASE 1: small ladder
		if (ladders[i].first-ladders[i].second <= 6) {  // if ladder's size <=6
			if (getNumMoves(current,ladders[i].first) >= getNumMoves(current,ladders[i].second))
				takeLadder = false;  // dont take if can get to end of ladder w/o ladder faster/same
		}

		// CASE 2: ladder is completely inside previous ladder
		if (ladders[i].second < current) takeLadder = false;

		// CASE 3: if current ladder overlaps the next ladder
		if (i+1 < ladders.size() && ladders[i].second > ladders[i+1].first) {

			// find which ladder is faster
			bool currentLadderIsFaster = true;
			int numMovesCurrent;  // # moves to end of the next ladder using current ladder
			int numMovesNext;  // # moves to end of next ladder using next ladder
			numMovesCurrent = getNumMoves(current,ladders[i].first) + getNumMoves(ladders[i].second,ladders[i+1].second);
			numMovesNext = getNumMoves(current,ladders[i+1].first);
			if (numMovesCurrent > numMovesNext ) currentLadderIsFaster = false;
			if (!currentLadderIsFaster) takeLadder=false;

			// CASE 3A: if there exists a snake to take both ladders and that is faster than taking faster ladder
			bool takeSnake = false;  // if snake between two overlapping ladders to take both and its faster
			pair<int,int> snake;  // (head,tail) to hold snake with least amount of moves
			int numMovesBestSnake = -1;
			for (int j=0; j<snakes.size(); j++) {  // find snake whos head is after first ladder and tail is before second ladder
				if (snakes[j].first >= ladders[i].second && snakes[j].second <= ladders[i+1].first) {  // if in doubt take snake
					int numMovesSnake=0;  // # moves to end of next ladder using snake and taking both ladders
					// cout << "current: " << current << endl;
					// cout << "ladders[i].first: " << ladders[i].first << endl;
					numMovesSnake = getNumMoves(current, ladders[i].first) 
						+ getNumMoves(ladders[i].second, snakes[j].first)
						+ getNumMoves(snakes[j].second, ladders[i+1].first);
					// cout << "numMovesSnake: " << numMovesSnake << endl;
					if (numMovesSnake <= numMovesCurrent && numMovesSnake <= numMovesNext) {
						if (numMovesBestSnake==-1 || numMovesSnake < numMovesBestSnake) {
							numMovesBestSnake = numMovesSnake;
							snake = snakes[j];
						}
						takeSnake = true;
					}
				}				
			}
			if (takeSnake) {  // if taking a snake is the way to go, add both ladders
				// cout << "HERE" << endl;
				laddersToTake.push_back(ladders[i]);
				laddersToTake.push_back(snake);
				laddersToTake.push_back(ladders[i+1]);
				current = ladders[i+1].second;
			}
		}
		// CASE 4: If current ladder is overlapped by the previous ladder (since prev was added, it is faster)
		if (current > ladders[i].first) takeLadder=false; 

		// CASE 5: if ladder's start or end is on a snake head
		for (int j=0; j<snakes.size(); j++)
			if (ladders[i].first==snakes[j].first || ladders[i].second==snakes[j].first) takeLadder=false;
		if (takeLadder) {
			laddersToTake.push_back(ladders[i]);
			current = ladders[i].second;
		}
	}
	// cout << "LADDERSTOTAKE: ";
	// for (int i=0; i<laddersToTake.size(); i++) cout << "(" << laddersToTake[i].first << "," << laddersToTake[i].second << ") ";
	// cout << endl;
	return laddersToTake;
}

string board::getPathToLadder(int &current, pair<int,int> ladder) {
// PRECONDITION: current = current space on board
	// ladder = (start of ladder, end of ladder) and is the ladder to take
	// NOTE: ladder can also be a snake in disguise
// POSTCONDITION: returns the path to ladder avoiding snake heads in the way
	// ladder traversals are given by '+', snake traversals are given by '-'
	// there is a space at the end of path
	// updates current. if no path to ladder (blocked by snakeHeads) returns empty path
	string path = "";
	bool isSnake = false;
	pair<int,int> snake(0,0);
	if (ladder.first-ladder.second > 0) isSnake = true;  // ladder is actually a snake, need path to it
	if (ladder.first-current <= 6) {
		current = ladder.second;
		if (isSnake) return to_string(ladder.first) +"-"+ to_string(ladder.second) +" ";
		else return to_string(ladder.first) +"+"+ to_string(ladder.second) +" ";
	}  // else ladder is not reachable in this roll
	current += getRoll(current,0);
	path += to_string(current) +" ";
	path += getPathToLadder(current,ladder);
	return path;
}

string board::getPathToEnd(int &current) {
// PRECONDITION: current is the current space on the board
// POSTCONDITION: returns the path to the end of the board (without ladders)
	string path = "";
	if (boardSize*boardSize-current <= 6) return to_string(boardSize*boardSize);
	current += getRoll(current,0);
	path += to_string(current) +" ";
	path += getPathToEnd(current);
	return path;
}

int board::getRoll(int current, int collideOkay) {
// PRECONDITION: current is the current space on the board, collideOkay is the space of ladder/snake okay to collide with
// POSTCONDITION: returns greatest dice roll that doesnt collide w/ snakeHead or ladderStart. if no roll w/o collision returns -1
	int roll = 6;
	bool collision = false;  // if current space == snakeHead space
	do {
		if (collision) { roll--; collision=false; }
		for (int i=0; i<snakes.size(); i++)
			if (collideOkay!=snakes[i].first && current+roll==snakes[i].first) collision=true;
		for (int i=0; i<ladders.size(); i++) 
			if (collideOkay!=ladders[i].first && current+roll==ladders[i].first) collision=true;
	} while (collision && roll > -1);
	if (roll>0) return roll;
	return -1;
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
