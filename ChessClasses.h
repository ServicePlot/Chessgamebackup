// Chess.h : This file contains the our classes and emums
// Authors: Luke P, Jaylameyada T, and Caleb K
// Date last updated: 5/16/2022
/* Description: This file contains the our classes and emums, also declares the functions that will be written in another cpp file*/
#pragma once

#include <iostream>
#include <cmath>
#include <string>


//enums that are used just to keep track and rename our values for the peices
enum Piece { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN, EMPTY };

//state of colors the player can be in 0=white, 1=black, then we need one for empty spaces or none 
enum Color { WHITE, BLACK, NONE };

//for every section of the board that is made is an object known a space
class Space
{
	//we will need our enums declarded in the class and some local variabels
	Piece piece;
	Color color;
	int x, y;
public:
	//next we set up our functions to be declared in a cpp file later
	void setSpace(Space*);
	void setEmpty();
	void setPieceAndColor(Piece, Color);
	Piece getPiece();
	Color getColor();
	void setX(int ex) { x = ex; }
	void setY(int why) { y = why; }
	int getX() { return x; }
	int getY() { return y; }
	Space();
};

class Board
{
	//this 2D array holds everything
	Space spaces[8][8];
	//and starts the turn off at white as its default
	Color turn = WHITE;

	//these are the move functions that will be defined in a later cpp file
	bool moveKing(Space* thisKing, Space* thatSpace);
	bool moveQueen(Space* thisQueen, Space* thatSpace);
	bool moveBishop(Space* thisBishop, Space* thatSpace);
	bool moveKnight(Space* thisKnight, Space* thatSpace);
	bool moveRook(Space* thisRook, Space* thatSpace);
	bool movePawn(Space* thisPawn, Space* thatSpace);
	bool makeMove(int x1, int y1, int x2, int y2);
	void printBoard();
public:
	//our getter for our space
	Space* getSpace(int x, int y)
	{
		return &spaces[x][y];
	}
	//setter for our space
	void setSpace(Space* s, int x, int y)
	{
		spaces[x][y] = *s;
	}

	//then our last few funcitons
	bool Movepiece();
	void setBoard();
	bool playGame();
};
