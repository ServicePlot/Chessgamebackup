// Chess.cpp : This file contains the functions for our space & board class
// Authors: Luke P, Jaylameyada T, and Caleb K
// Date last updated: 5/16/2022
/* Description: This file contains the functions for our space & board class */
#include "ChessClasses.h"



//default constructor for space
Space::Space()
{
	piece = EMPTY;
	color = NONE;
}

//function that sets the space's color and peice
void Space::setSpace(Space* space)
{
	color = space->getColor();
	piece = space->getPiece();
}

//function that set an empty space
void Space::setEmpty()
{
	color = NONE;
	piece = EMPTY;
}

//this gets the piece that is on the board
Piece Space::getPiece()
{
	return piece;
}

//this gets the color of the peice on the space
Color Space::getColor()
{
	return color;
}

//this will set the peice and color to whatever is passed in
void Space::setPieceAndColor(Piece p, Color c)
{
	piece = p;
	color = c;
}

//this function prints the board
void Board::printBoard() {
	using namespace std;
	//first we print the y axis guide
	cout << "   y: 0  1  2  3  4  5  6  7 " << endl << "x:" << endl;

	//then we run this for loop
	for (int i = 0; i < 8; i++)
	{
		//this sets the spaces
		cout << " " << i << "   ";
		//and then this for loop will print the peices 
		for (int j = 0; j < 8; j++)
		{
			//we will need to access the peices stored in our 2D array
			Piece p = spaces[i][j].getPiece();
			Color c = spaces[i][j].getColor();

			//and then this switch will set them based on the enums assinged to them
			switch (p)
			{
			case KING: (c == WHITE) ? cout << "|K|" : cout << "|k|";
				break;
			case QUEEN: (c == WHITE) ? cout << "|Q|" : cout << "|q|";
				break;
			case BISHOP:(c == WHITE) ? cout << "|B|" : cout << "|b|";
				break;
			case KNIGHT:(c == WHITE) ? cout << "|H|" : cout << "|h|";
				break;
			case ROOK: (c == WHITE) ? cout << "|R|" : cout << "|r|";
				break;
			case PAWN: (c == WHITE) ? cout << "|P|" : cout << "|p|";
				break;
			case EMPTY: cout << "| |";
				break;
				//if there is an error it will print this
			default: cout << "XXX";
				break;
			}

		}
		cout << endl;
	}

}

//next we need to move the pieces
bool Board::Movepiece()
{
	using namespace std;
	string move;
	int x1, x2, y1, y2;
	bool stop = false;
	while (!stop)
	{
		(turn == WHITE) ? cout << "It is White's turn" << endl : cout << "It is Black's turn" << endl;
		cout << "To move a peice type its xy code and the xy code you would like to move it EXAMPLE:0102 to move white pawn 01 " << endl;
		cin >> move;
		x1 = move[0] - 48;
		y1 = move[1] - 48;
		x2 = move[2] - 48;
		y2 = move[3] - 48;
		if (getSpace(x1, y1)->getColor() == turn)
		{


			if (makeMove(x1, y1, x2, y2) == false)
			{
				cout << "Move is Invalid, try again." << endl;
			}
			else
				stop = true;
		}
		else
			cout << "That is not your peice." << endl;
	}
	if (getSpace(x2, y2)->getPiece() == KING)
		if (getSpace(x1, y1)->getColor() == WHITE)
		{
			cout << "WHITE WINS" << endl;
			return false;
		}
		else

		{
			cout << "BLACK WINS" << endl;
			return false;
		}


	if (turn == BLACK)
		turn = WHITE;
	else
		turn = BLACK;

	return true;

}

//this function is used at the start to set the positions of the pieces
void Board::setBoard()
{
	spaces[0][0].setPieceAndColor(ROOK, WHITE);
	spaces[1][0].setPieceAndColor(KNIGHT, WHITE);
	spaces[2][0].setPieceAndColor(BISHOP, WHITE);
	spaces[3][0].setPieceAndColor(QUEEN, WHITE);
	spaces[4][0].setPieceAndColor(KING, WHITE);
	spaces[5][0].setPieceAndColor(BISHOP, WHITE);
	spaces[6][0].setPieceAndColor(KNIGHT, WHITE);
	spaces[7][0].setPieceAndColor(ROOK, WHITE);

	spaces[0][7].setPieceAndColor(ROOK, BLACK);
	spaces[1][7].setPieceAndColor(KNIGHT, BLACK);
	spaces[2][7].setPieceAndColor(BISHOP, BLACK);
	spaces[3][7].setPieceAndColor(QUEEN, BLACK);
	spaces[4][7].setPieceAndColor(KING, BLACK);
	spaces[5][7].setPieceAndColor(BISHOP, BLACK);
	spaces[6][7].setPieceAndColor(KNIGHT, BLACK);
	spaces[7][7].setPieceAndColor(ROOK, BLACK);

	//these for loops set up the pawns for each side
	for (int i = 0; i < 8; i++)
	{
		spaces[i][1].setPieceAndColor(PAWN, WHITE);
		spaces[i][6].setPieceAndColor(PAWN, BLACK);

	}
	//then theis sets the empty spaces
	for (int i = 2; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
			spaces[j][i].setPieceAndColor(EMPTY, NONE);

	}
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			spaces[i][j].setX(i);
			spaces[i][j].setY(j);
		}

}

//this simply prints the board and retruns the moved peice for our while loop in main
bool Board::playGame()
{
	system("cls");
	printBoard();
	return Movepiece();

}

//rules for moving the king peice
bool Board::moveKing(Space* thisKing, Space* thatSpace) {
	if (abs(thatSpace->getX() - thisKing->getX()) == 1)
		if (abs(thatSpace->getY() - thisKing->getY()) == 1)
		{
			thatSpace->setSpace(thisKing);
			thisKing->setEmpty();
			return true;
		}
		else return false;
	else return false;
}
//rules for moving the queen peice
bool Board::moveQueen(Space* thisQueen, Space* thatSpace) 
{ 
	int queenX = thisQueen->getX();
	int queenY = thisQueen->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();
	std::cout << "this";
	int yIncrement;
	int xIncrement;

	bool invalid = false;
	if (queenX != thatX || queenY != thatY)
	{

		if (queenX == thatX)
		{
			yIncrement = (thatY - queenY) / (abs(thatY - queenY));
			for (int i = queenY + yIncrement; i != thatY; i += yIncrement)
			{

				if (spaces[thatX][i].getColor() != NONE)
					return false;

			}
		}
		else
			if (queenY == thatY)
			{

				xIncrement = (thatX - queenX) / (abs(thatX - queenX));
				for (int i = queenX + xIncrement; i != thatX; i += xIncrement)
				{
					if (spaces[i][thatY].getColor() != NONE)
						return false;
				}
			}
			else
				if (abs(queenX - thatX) == abs(queenY - thatY))
				{
					xIncrement = (thatX - queenX) / (abs(thatX - queenX));
					yIncrement = (thatY - queenY) / (abs(thatY - queenY));

					for (int i = 1; i < abs(queenX - thatX); i++)
					{
						std::cout << "It got here somehow";
						if (spaces[queenX + xIncrement * i][queenY + yIncrement * i].getColor() != NONE)
							return false;

					}
				}
				else
					return false;
	}
	if (invalid == false)
	{
		thatSpace->setSpace(thisQueen);
		thisQueen->setEmpty();
		return true;
	}
	else
	{
		return false;
	}
}

//rules for moving the Bishop peice
bool Board::moveBishop(Space* thisBishop, Space* thatSpace) 
{
	int bishopX = thisBishop->getX();
	int bishopY = thisBishop->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();
	bool invalid = false;
	Space* s;
	if (abs(bishopX - thatX) == abs(bishopY - thatY))
	{
		int xIncrement = (thatX - bishopX) / (abs(thatX - bishopX));
		int yIncrement = (thatY - bishopY) / (abs(thatY - bishopY));

		for (int i = 1; i < abs(bishopX - thatX); i++)
		{
			std::cout << "It got here somehow";
			if (spaces[bishopX + xIncrement * i][bishopY + yIncrement * i].getColor() != NONE)
				return false;

		}
	}
	else
		return false;

	if (invalid == false)
	{
		thatSpace->setSpace(thisBishop);
		thisBishop->setEmpty();
		return true;
	}
	else
	{
		return false;
	}
}

//rules for moving the Knight peice
bool Board::moveKnight(Space* thisKnight, Space* thatSpace)
{
	int knightX = thisKnight->getX();
	int knightY = thisKnight->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();

	if ((abs(knightX - thatX) == 2 && abs(knightY - thatY) == 1) || (abs(knightX - thatX) == 1 && abs(knightY - thatY) == 2))
	{
		thatSpace->setSpace(thisKnight);
		thisKnight->setEmpty();
		return true;
	}
	else
	{
		return false;
	}
}

//rules for moving the Rook peice
bool Board::moveRook(Space* thisRook, Space* thatSpace)
{
	int rookX = thisRook->getX();
	int rookY = thisRook->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();
	bool invalid = false;
	if (rookX != thatX || rookY != thatY)
	{

		if (rookX == thatX)
		{
			int yIncrement = (thatY - rookY) / (abs(thatY - rookY));
			for (int i = rookY + yIncrement; i != thatY; i += yIncrement)
			{

				if (spaces[thatX][i].getColor() != NONE)
					return false;

			}
		}
		else
			if (rookY == thatY)
			{

				int xIncrement = (thatX - rookX) / (abs(thatX - rookX));
				for (int i = rookX + xIncrement; i != thatX; i += xIncrement)
				{
					if (spaces[i][thatY].getColor() != NONE)
						return false;
				}
			}
			else
				return false;
	}
	if (invalid == false)
	{
		thatSpace->setSpace(thisRook);
		thisRook->setEmpty();
		return true;
	}
	else
	{
		std::cout << "That is an invalid move for rook";
		return false;
	}
}

//rules for moving the Pawn peice
bool Board::movePawn(Space* thisPawn, Space* thatSpace) {

	using namespace std;
	bool invalid = false;
	int pawnX = thisPawn->getX();
	int pawnY = thisPawn->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();


	if (thisPawn->getColor() == WHITE)
	{

		if (pawnX == thatX && thatY == pawnY + 1 && thatSpace->getColor() == NONE)
		{
			thatSpace->setSpace(thisPawn);
			thisPawn->setEmpty();
			return true;
		}
		else
			if ((pawnX + 1 == thatX || pawnX - 1 == thatX) && pawnY + 1 == thatY && thatSpace->getColor() == BLACK)
			{
				thatSpace->setSpace(thisPawn);
				thisPawn->setEmpty();
				return true;
			}
			else
				return false;
	}
	else
		if (thisPawn->getColor() == BLACK)
		{
			if (pawnX == thatX && thatY == pawnY - 1 && thatSpace->getColor() == NONE)
			{
				thatSpace->setSpace(thisPawn);
				thisPawn->setEmpty();
				return true;
			}
			else
				if ((pawnX + 1 == thatX || pawnX - 1 == thatX) && pawnY - 1 == thatY && thatSpace->getColor() == WHITE)
				{
					thatSpace->setSpace(thisPawn);
					thisPawn->setEmpty();
					return true;
				}
				else
					return false;
		}
		else
			return false;
}
//next this function handles the inputs. it passes in the xy cords
bool Board::makeMove(int x1, int y1, int x2, int y2) {
	using namespace std;
	//checks if the input is within the bounds of the board
	if (x1 < 0 || x1>7 || y1 < 0 || y1>7 || x2 < 0 || x2>7 || y2 < 0 || y2>8)
	{
		std::cout << "One of your inputs was our of bounds" << std::endl;
		return false;
	}
	//gets the source
	Space* src = getSpace(x1, y1);

	//then gets the destination
	Space* dest = getSpace(x2, y2);

	//handles trying to take your own piece
	if (src->getColor() == dest->getColor() && dest->getColor() != NONE)
	{
		std::cout << "Invalid move: cannot land on your own piece" << std::endl;
		return false;
	}

	//next is a switch statment that will get the piece that is stored in our source
	//then depending on its enum will run the coresponding function
	switch (src->getPiece())
	{
	case KING: return moveKing(src, dest);
		break;
	case QUEEN: return moveQueen(src, dest);
		break;
	case BISHOP: return moveBishop(src, dest);
		break;
	case KNIGHT: return moveKnight(src, dest);
		break;
	case ROOK: return moveRook(src, dest);
		break;
	case PAWN: return movePawn(src, dest);
		break;
	//this will run if the player selects an empty space
	case EMPTY: std::cout << "You do not have a piece there" << std::endl;  return false;
		break;
	//then if none of these are selected and somehow the user gets past everything it will print this
	default: std::cerr << "Something went wrong in the switch statement in makeMove()" << std::endl;
		break;
	}
	return false;
}