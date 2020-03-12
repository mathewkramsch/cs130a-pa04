// board.h

#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <utility>
#include "string"

class board {
	public:
		board(int size, std::vector<std::pair<int,int>> l, std::vector<std::pair<int,int>> s):
			boardSize(size), ladders(l), snakes(s) {}
		std::string getPath();
		std::string printVectors();  // for debugging

	private:
		int boardSize;
		std::vector<std::pair<int,int>> ladders;
		std::vector<std::pair<int,int>> snakes;

		std::vector<std::pair<int,int>> getLaddersToTake();  // helper functions
		std::string getPathToLadder(int &current, std::pair<int,int> ladder, std::vector<int> snakeHeadsInWay);
		std::string getPathToEnd(int &current);
};

#endif
