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
		int getNumMoves();
		std::string getPath();

	private:
		int boardSize;
		std::vector<std::pair<int,int>> ladders;
		std::vector<std::pair<int,int>> snakes;
};

#endif
