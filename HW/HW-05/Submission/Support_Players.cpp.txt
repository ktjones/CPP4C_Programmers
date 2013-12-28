//*******************************
//
//  C++ Support Files 
//	- Player Class
//	
//*******************************

//*******************************
//
//  Standard Header
//
//*******************************

#include <iostream>
#include "header - Players.h"

using namespace std;

//***************************************************************************************************
//
//  Support Program Section - Players Class
//
//***************************************************************************************************

//********************************
//
//  Players Constructors
//
//********************************

Players::Players() : Player_Type(0), Player_Color(0)
{
		
}

Players::~Players()
{
		
}

//********************************
//
//   MST Working Methods
//
//********************************

void Players::Players_SetPlayerColor(int pc)
{

	//Initialize Variables


	//Run Code
	Player_Color = pc;

	return;

}

void Players::Players_SetPlayerType(int pt)
{

	//Initialize Variables


	//Run Code
	Player_Type = pt;

	return;
	
}

int Players::Players_GetPlayerColor()
{
	
	//Initialize Variables


	//Run Code

	return Player_Color;

}

int Players::Players_GetPlayerType()
{

	//Initialize Variables


	//Run Code

	return Player_Type;

}