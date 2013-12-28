//**************************************************************
//
//  C++ Template - HEX Header File
//
//**************************************************************

//**************************************************************
//
//  Definition Statements - Begin
//
//**************************************************************

#ifndef HEADER_HEX_H_
#define HEADER_HEX_H_

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <random>
#include "header - Graph.h"
#include "header - MST.h"
#include "header - Players.h"

using namespace std;

//**************************************************************
//
//  Code Body - Begin
//
//**************************************************************

//*******************************
//
//  Hex Class
//
//*******************************

class Hex
{
	private:
		
		//Standard Variables
		int Hex_Board_Size;
		int Hex_Graph_Size;
		int Hex_Number_of_Moves;
		int Hex_Current_Turn; //BLANK = 0, BLUE = 1, RED = 2

			
		//Objects
		Graph Hex_Board_Graph;
		Graph Hex_Board_Graph_MC;
		MST Hex_Board_MST;
		Players Hex_Player1;
		Players Hex_Player2;
		random_device rd;

	public:
		
		//Ctors & Dtors
		Hex(int n = 4);
		~Hex();

		//Hex Board Working Methods
		void Hex_CreateBoard();
		int Hex_GetBoardSize();
		void Hex_PrintBoard();
		int Hex_CheckForWinner();
		int Hex_CheckForWinnerMC();

		//Hex Player Working Methods
		void Hex_PlayerSelection();
		int Hex_GamePlay();
		int Hex_PlayerMove();
		int Hex_ComputerMoveAI();
		int Hex_ComputerMoveRandom();
		int Hex_ComputerMoveRandomMC(int startnode, int currentturn, vector<int> vq);

		//Hex Overloaded Operators
		int operator()(const pair<int,double> & p1, const pair<int,double> & p2);
		
		//Hex Player Un-Tested Methods
		
		
};

//**************************************************************
//
//  Code Body - End
//
//**************************************************************

//**************************************************************
//
//  Definition Statements - End
//
//**************************************************************

#endif