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
	int Board_Size = 11;
	int Game_Winning_Flag = 0;

	//Graph Game_Board_Graph = Graph(Board_Size);
	Hex Game_of_Hex = Hex(Board_Size);

	//* Main Code
	cout << endl;
	
	Game_of_Hex.Hex_PlayerSelection();

	/*
	while(Game_Winning_Flag==0)
	{
		Game_of_Hex.Hex_PrintBoard();
		Game_Winning_Flag = Game_of_Hex.Hex_PlayerMove();
	}
	
	if(Game_Winning_Flag == 1)
	{
		cout << "Blue Wins!" << endl;
	}
	else if(Game_Winning_Flag == 2)
	{
		cout << "Red Wins!" << endl;
	}
	*/

	//*  Program End
	//   - wait until user is ready before terminating program
	//   - to allow the user to see the program results

	cout << endl << endl;
	system("PAUSE");
	return 0;
}

