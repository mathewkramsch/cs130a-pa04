// main.cpp

#include "BOARD/board.h"
#include <sstream>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {

	if (argc!=2) { cerr << "no input\n"; return 1; }

	int totalNumberOfBoards;
	int currentBoardNum=1;  // to keep track of which board is current
	int leastNumMoves;  // least number of moves required to solve current board
	string pathTaken;  // path taken to solve board, ladders= '+', snakes= '-'

	int boardSize, numLadders, numSnakes;
	int ladderStart, ladderEnd;  // location of start/end of ladder
	int snakeHead, snakeTail;
	vector<pair<int,int>> ladders;  // each element = ladderStart,ladderEnd pair
	vector<pair<int,int>> snakes;
	pair<int,int> p (0,0);  // to hold pairs

	stringstream ss(argv[1]);
	ss >> totalNumberOfBoards;

	while (currentBoardNum <= totalNumberOfBoards) {
		string boardMssg="Board Game #:";
		ladders.clear();
		snakes.clear();

		ss >> boardSize >> numLadders >> numSnakes;  // 1st line of input

		for (int i=0; i<numLadders; i++) {  // 2nd line
			ss >> ladderStart >> ladderEnd;
			p = make_pair(ladderStart,ladderEnd);
			ladders.push_back(p);
		}
		for (int i=0; i<numSnakes; i++) {  // 3rd line 
			ss >> snakeHead >> snakeTail;
			p = make_pair(snakeHead,snakeTail);
			snakes.push_back(p);
		}

		board b(boardSize,ladders,snakes);
		leastNumMoves = b.getNumMoves();
		pathTaken = b.getPath();

		cout << boardMssg << currentBoardNum++ << endl;
		cout << leastNumMoves << endl;
		cout << pathTaken << endl;
	}
	
	return 0;
}
