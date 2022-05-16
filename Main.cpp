// Main.cpp : This file contains the 'main' function.
// Authors: Luke P, Jaylameyada T, and Caleb K
// Date last updated: 5/16/2022
/* Description: Main program where the chess session is run. */

#include <iostream>
#include <string>
#include "ChessClasses.h"

using namespace std;

int main()
{
	Board b;
	string s;
	bool gamekeepgoing = true;

	//main gameloop using a bool to tell if the game is still going
	while (gamekeepgoing) 
	{
		//our board object b is used to set the board
		b.setBoard();
		//this while loop is then ran to ask the player if they want to play the game again
		while (b.playGame());
		cout << "Do you want to play again? (y for yes, any key for no) ";
		cin >> s;
		if (s != "y" || s != "Y")
		{
			gamekeepgoing = false;
		}
	}


	return 0;
}