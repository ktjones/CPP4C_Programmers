//***************************************************************************************************
//
//  C++ Program 
//	- Homework #4 - Hex Game (Phase 1)
//
//***************************************************************************************************
//*******************************
//
//  Standard Header
//
//*******************************

#include <iostream>
#include <time.h>
#include <random>
#include "header - Hex.h"
#include "header - Graph.h"

using namespace std;

//********************************
//
//  Pre-Program Declarations
//
//********************************



//***************************************************************************************************
//
//  Main Program Section
//
//***************************************************************************************************

int main(int nNumberofArgs, char* pszArgs[])
{
	//*  Variable Declaration
	int Board_Size = 5;
	int winner = 0;
	
	/*
	unsigned seed = time(0);
	default_random_engine generator(seed);
	uniform_int_distribution<int> distribution(1,Board_Size*Board_Size);
	*/
	

	//* Main Code
	//Create Game
	Hex Game_of_Hex = Hex(Board_Size);
	
	//Start Game
	Game_of_Hex.Hex_PlayerSelection();
		
	cout << endl << endl;
 	system("PAUSE");
	
	Game_of_Hex.Hex_PrintBoard();
	
	//Enter Main Game Loop
	while(winner == 0)
	{

		winner = Game_of_Hex.Hex_GamePlay();
		Game_of_Hex.Hex_PrintBoard();
		
	}
	
	//Evaluate Game Winning Flag
	if(winner == 1)
	{
		cout << endl;
		cout << "Player 1 Wins";
		cout << endl;
	}
	else if(winner == 2)
	{
		cout << endl;
		cout << "Player 2 Wins";
		cout << endl;
	}
	else
	{
		cout << endl;
		cout << "Someone must have Quit.  Too Bad!";
		cout << endl;
	}

	//*  Program End
	//   - wait until user is ready before terminating program
	//   - to allow the user to see the program results

	cout << endl << endl;
	system("PAUSE");
	return 0;
}

