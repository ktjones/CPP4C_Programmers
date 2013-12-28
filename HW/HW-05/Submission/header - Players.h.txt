//**************************************************************
//
//  C++ Template - Player Header File
//
//**************************************************************

//**************************************************************
//
//  Definition Statements - Begin
//
//**************************************************************

#ifndef HEADER_PLAYERS_H_
#define HEADER_PLAYERS_H_

#include <iostream>

using namespace std;

//**************************************************************
//
//  Code Body - Begin
//
//**************************************************************


//*******************************
//
//  Compound Types
//
//*******************************

//*******************************
//
//  Players Class
//
//*******************************

class Players
{
	
	private:

		//Standard Variables
		int Player_Type;	//NONE = 0, COMPUTER = 1, HUMAN = 2
		int Player_Color;	//BLANK = 0, BLUE = 1, RED = 2

	public:

		//Ctors & Dtors
		Players();
		~Players();

		//Players Working Methods
		void Players_SetPlayerColor(int pc);
		void Players_SetPlayerType(int pt);
		int Players_GetPlayerColor();
		int Players_GetPlayerType();

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