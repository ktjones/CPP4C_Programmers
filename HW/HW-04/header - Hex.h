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
#include "header - Graph.h"
#include "header - MST.h"

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
		int Hex_Number_of_Players;
		int Hex_Number_of_Moves;
		enum Hex_Player_Colors{BLANK = 0, BLUE = 1, RED = 2};
		enum Hex_Player_Types{NONE = 0, HUMAN = 1, COMPUTER = 2};
		Hex_Player_Colors Hex_Current_Turn;
		Hex_Player_Types Hex_Player1;
		Hex_Player_Types Hex_Player2;

		//Objects
		Graph Hex_Board_Graph;
		MST Hex_Board_MST;
		
	public:
		
		//Constructors
		Hex(int n = 0);
		~Hex();

		//Hex Board Working Methods
		int Hex_GetBoardSize();
		void Hex_CreateBoard();
		void Hex_PrintBoard();

		//Hex Player Working Methods
		void Hex_PlayerSelection();
		int Hex_PlayerMove();
		void Hex_ComputerMove();
		int Hex_CheckForWinner();

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