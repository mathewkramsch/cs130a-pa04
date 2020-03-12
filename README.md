# PA04 for CS130a
Mathew Kramsch

> Programming Assignment #4 for CS130a: Snakes and Ladders game

#### Sample Input:
./snl "5  
8 1 1  
8 11  
63 1  
10 3 7  
32 62 42 68 12 98  
95 13 97 25 93 37 79 27 75 19 49 47 67 17  
10 6 8  
32 62 44 66 22 58 34 60 2 70 71 87  
85 7 63 31 87 13 75 11 89 33 57 5 71 15 55 25  
20 10 11  
8 52 371 389 313 351 6 80 26 42 2 72 80 147 124 301 2 99 90 107  
51 19 39 11 37 29 81 3 59 5 79 23 53 7 43 33 77 21 207 3 378 78  
60 3 2  
2 131 119 3555 1563 2013  
140 117 3402 234"  

#### Input
- The first line is the number of board games which need to be solved. 
- The next 3 lines contain more information about the boards, 3 lines per board.
- The first of the 3 lines will have three numbers, N, L, S
	- N = the board size, NxN
	- L and S = the number of ladders and snakes on the boards respectively
- The second line will 2L numbers
	- each consecutive pair a, b represents the starting and ending points of a ladder respectively
- The third line will have 2S numbers
	- each consecutive pair c, d represents the head and tail of a snake respectively

#### Output
- Outputs 3 lines per board
- The first line is the number of the board game
- The second line is the least number of moves required for solving the current board
- The third line is the path taken to get to the end of the board
	- ladders are shown as +
	- snakes are shown as -
