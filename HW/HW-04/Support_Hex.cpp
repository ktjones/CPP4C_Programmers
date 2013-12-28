//*******************************
//
//  C++ Support File 
//	- Hex Class
//
//*******************************

//*******************************
//
//  Standard Header
//
//*******************************

#include <iostream>
#include <vector>
#include <cctype>
#include "header - Graph.h"
#include "header - Hex.h"
#include "header - MST.h"

using namespace std;

//***************************************************************************************************
//
//  Support Program Section - Hex Class
//
//***************************************************************************************************

//********************************
//
//  Hex Constructors
//
//********************************

Hex::Hex(int n) : Hex_Board_Size(n), Hex_Graph_Size(n*n+4), Hex_Number_of_Players(-1), Hex_Number_of_Moves(0), Hex_Current_Turn(BLANK), Hex_Player1(NONE), Hex_Player2(NONE), Hex_Board_Graph(n*n+4), Hex_Board_MST()
{
	
	//Initialize Variables
	

	//Create Board Using Graph Structure with all nodes set to 0
	Hex_CreateBoard();
	
	//Chatty Ctor
	cout << "Board Constructed using Default Ctor" << endl;

	//cout << endl;
	//Hex_Board_Graph.Graph_ShowEdge();

	return;
}

Hex::~Hex()
{

}

//********************************
//
//  Hex Board Working Methods
//
//********************************

void Hex::Hex_CreateBoard()
{
	
	//Creation of a Board of Size Hex_Board_Size
	//Board assumes edges have a color of 0 (neither Red or Blue)
	for (int i=0; i<Hex_Board_Size*Hex_Board_Size; i++)
	{

		//First Row
		// First Node
		if(i==0)
		{
		
			Hex_Board_Graph.Graph_AddEdge(i,i+1,1);
			Hex_Board_Graph.Graph_AddEdge(i,i+Hex_Board_Size,1);
			
		}
		// Second Node through the N-2 Node
		if(i>0 && i<(Hex_Board_Size-2))
		{

			Hex_Board_Graph.Graph_AddEdge(i,i+1,1);
			Hex_Board_Graph.Graph_AddEdge(i,i-1,1);
			Hex_Board_Graph.Graph_AddEdge(i,i+Hex_Board_Size,1);
			Hex_Board_Graph.Graph_AddEdge(i,i+Hex_Board_Size-1,1);

		}
		// Last Node in the first Row
		if(i==(Hex_Board_Size-1))
		{
		
			Hex_Board_Graph.Graph_AddEdge(i,i-1,1);
			Hex_Board_Graph.Graph_AddEdge(i,i+Hex_Board_Size,1);
			Hex_Board_Graph.Graph_AddEdge(i,i+Hex_Board_Size-1,1);
			
		}
		
		//Second through The Next-to-Last Row
		if(i>(Hex_Board_Size-1) && i<(((Hex_Board_Size*Hex_Board_Size)-1)-(Hex_Board_Size-1)))
		{
			// Look for a left edge node 
			if(i%Hex_Board_Size == 0)
			{
				
				Hex_Board_Graph.Graph_AddEdge(i,i-Hex_Board_Size,1);
				Hex_Board_Graph.Graph_AddEdge(i,i-Hex_Board_Size+1,1);
				Hex_Board_Graph.Graph_AddEdge(i,i+1,1);
				Hex_Board_Graph.Graph_AddEdge(i,i+Hex_Board_Size,1);
				
			}
			// Look for a node that is between the left edge and the right edge
			else if(i%Hex_Board_Size>0 && i%Hex_Board_Size<(Hex_Board_Size-1))
			{

				Hex_Board_Graph.Graph_AddEdge(i,i-1,1);
				Hex_Board_Graph.Graph_AddEdge(i,i-Hex_Board_Size,1);
				Hex_Board_Graph.Graph_AddEdge(i,i-Hex_Board_Size+1,1);
				Hex_Board_Graph.Graph_AddEdge(i,i+1,1);
				Hex_Board_Graph.Graph_AddEdge(i,i+Hex_Board_Size,1);
				Hex_Board_Graph.Graph_AddEdge(i,i+Hex_Board_Size-1,1);

			}
			// Look for the right Edge
			else if(i%Hex_Board_Size==(Hex_Board_Size-1))
			{

				Hex_Board_Graph.Graph_AddEdge(i,i-1,1);
				Hex_Board_Graph.Graph_AddEdge(i,i-Hex_Board_Size,1);
				Hex_Board_Graph.Graph_AddEdge(i,i+Hex_Board_Size,1);
				Hex_Board_Graph.Graph_AddEdge(i,i+Hex_Board_Size-1,1);

			}

		}
		//Last Row
		if(i>(((Hex_Board_Size*Hex_Board_Size)-1)-(Hex_Board_Size)))
		{

			// Look for a left edge node 
			if(i%Hex_Board_Size == 0)
			{
				
				Hex_Board_Graph.Graph_AddEdge(i,i-Hex_Board_Size,1);
				Hex_Board_Graph.Graph_AddEdge(i,i-Hex_Board_Size+1,1);
				Hex_Board_Graph.Graph_AddEdge(i,i+1,1);

			}
			// Look for a node that is between the left edge and the right edge
			else if(i%Hex_Board_Size>0 && i%Hex_Board_Size<(Hex_Board_Size-1))
			{

				Hex_Board_Graph.Graph_AddEdge(i,i-1,1);
				Hex_Board_Graph.Graph_AddEdge(i,i-Hex_Board_Size,1);
				Hex_Board_Graph.Graph_AddEdge(i,i-Hex_Board_Size+1,1);
				Hex_Board_Graph.Graph_AddEdge(i,i+1,1);

			}
			// Look for the right Edge
			else if(i%Hex_Board_Size==(Hex_Board_Size-1))
			{

				Hex_Board_Graph.Graph_AddEdge(i,i-1,1);
				Hex_Board_Graph.Graph_AddEdge(i,i-Hex_Board_Size,1);
				
			}

		}

	}

	//Assignment of Virtual Nodes representing North/South/East/West
	// North Virtual Edge (Associated with Row 0)
	for (int i=0; i<Hex_Board_Size; i++)
	{
		Hex_Board_Graph.Graph_AddEdge(Hex_Board_Size*Hex_Board_Size,i,1);
		Hex_Board_Graph.Graph_AddEdge(i,Hex_Board_Size*Hex_Board_Size,1);

		Hex_Board_Graph.Graph_SetEdgeColor(Hex_Board_Size*Hex_Board_Size,i,RED);
		Hex_Board_Graph.Graph_SetEdgeColor(i,Hex_Board_Size*Hex_Board_Size,RED);
	}

	//South Virtual Edge (Associated with the last Row)
	for (int i=((Hex_Board_Size*Hex_Board_Size)-(Hex_Board_Size)); i<(Hex_Board_Size*Hex_Board_Size); i++)
	{
		Hex_Board_Graph.Graph_AddEdge(Hex_Board_Size*Hex_Board_Size+1,i,1);
		Hex_Board_Graph.Graph_AddEdge(i,Hex_Board_Size*Hex_Board_Size+1,1);

		Hex_Board_Graph.Graph_SetEdgeColor(Hex_Board_Size*Hex_Board_Size+1,i,RED);
		Hex_Board_Graph.Graph_SetEdgeColor(i,Hex_Board_Size*Hex_Board_Size+1,RED);
	}
	
	// East Virtual Edge (Associated with Column 0)
	for (int i=0; i<((Hex_Board_Size*Hex_Board_Size)-(Hex_Board_Size)+1); i+=Hex_Board_Size)
	{
		Hex_Board_Graph.Graph_AddEdge(Hex_Board_Size*Hex_Board_Size+2,i,1);
		Hex_Board_Graph.Graph_AddEdge(i,Hex_Board_Size*Hex_Board_Size+2,1);

		Hex_Board_Graph.Graph_SetEdgeColor(Hex_Board_Size*Hex_Board_Size+2,i,BLUE);
		Hex_Board_Graph.Graph_SetEdgeColor(i,Hex_Board_Size*Hex_Board_Size+2,BLUE);
	}

	// West Virtual Edge (Associate with Column ((Hex_Board_Size*row)-1)
	for (int i=Hex_Board_Size-1; i<(Hex_Board_Size*Hex_Board_Size); i+=Hex_Board_Size)
	{
		Hex_Board_Graph.Graph_AddEdge(Hex_Board_Size*Hex_Board_Size+3,i,1);
		Hex_Board_Graph.Graph_AddEdge(i,Hex_Board_Size*Hex_Board_Size+3,1);

		Hex_Board_Graph.Graph_SetEdgeColor(Hex_Board_Size*Hex_Board_Size+3,i,BLUE);
		Hex_Board_Graph.Graph_SetEdgeColor(i,Hex_Board_Size*Hex_Board_Size+3,BLUE);
	}
	

}

int Hex::Hex_GetBoardSize()
{
	
	return Hex_Board_Size;

}

void Hex::Hex_PrintBoard()
{
	//Clear the screen
	system("CLS");

	//Print the first row
	for(int i=0; i<Hex_Board_Size;i++)
	{
		
		if(i==0)
		{
			
			cout << "  ";

			for (int x=0;x<Hex_Board_Size;x++)
			{
				cout << char(x+65) << "   ";
			}
		
			cout << endl;
		}

		//Print the current line
		// Pad each line to make the slant
		for (int x=0; x<i; x++)
		{
			cout << " ";
		}
		
		// Print the line #
		cout << i+1 << " ";

		for(int j=0; j<Hex_Board_Size;j++)
		{
			// Print the player in each board location
			if(Hex_Board_Graph.Graph_GetNodeColor((Hex_Board_Size*i)+j) == BLANK)
			{
				cout << ".";
			}
			else if (Hex_Board_Graph.Graph_GetNodeColor((Hex_Board_Size*i)+j) == RED)
			{
				cout << "X";
			}
			else if(Hex_Board_Graph.Graph_GetNodeColor((Hex_Board_Size*i)+j) == BLUE)
			{
				cout << "O";
			}
			else
			{
				cout << "That color isn't recognized by the game!  Error!";
				return;
			}

			// Print the connecting "-" from node to node
			if(j != Hex_Board_Size-1)
			{
				cout << " - ";
			}
		}

		cout << endl;

		//Printing the line after the current
		// If the current line is the last line of the board
		//  then skip it.
		if (i == Hex_Board_Size-1)
		{
			continue;
		}
		else
		{
			// shift the line over to make the hex board
			for (int x=0; x<i; x++)
			{
				cout << " ";
			}
			
			// Pad the line to shift it over
			cout << "   ";

			// Print the connection lines
			for(int j=0; j<Hex_Board_Size;j++)
			{
				
				if(j != Hex_Board_Size-1)
				{
					cout << "\\ / ";
				}
				else
				{
					cout << "\\";
				}
			}
		}
		cout << endl;
				
	}
	
	return;
}

//********************************
//
//  Hex Player Working Methods
//
//********************************

void Hex::Hex_PlayerSelection()
{
	
	//Initailize Variables
	
	//Run Code
	while(Hex_Number_of_Players < 0 || Hex_Number_of_Players > 2)
	{
		cout << "Please enter the number of players (0,1,2): ";
		cin >> Hex_Number_of_Players;

		cout << endl;
		cout << "Okie Dokie!  You want it like that huh? Fine..." << endl;
		cout << endl;

		if(Hex_Number_of_Players == 0)
		{
			Hex_Player1 = COMPUTER;
			Hex_Player2 = COMPUTER;
			cout << "Both Players are Computers (Good Luck with That!)" << endl;
		}
		else if(Hex_Number_of_Players == 1)
		{
			Hex_Player1 = COMPUTER;
			Hex_Player2 = HUMAN;
			cout << "Player #1 is a Computer." << endl;
			cout << "Player #2 is a Human. " << endl;
		}
		else if(Hex_Number_of_Players == 2)
		{
			Hex_Player1 = HUMAN;
			Hex_Player2 = HUMAN;
			cout << "Player #1 is a Human." << endl;
			cout << "Player #2 is a Human. " << endl;

		}
		else
		{
			cout << endl << endl;
			cout << "You entered an illegal # of players.  Try again!";
			cout << endl << endl;
		}
	}

	cout << endl;
	cout << "Have Fun Playing the Game!";

}

int Hex::Hex_PlayerMove()
{

	//Initailize Variables
	int r = -1;
	int successfulmoveflag = 0;
	int winnerflag = 0;
	char c = 'A';
	bool entermoveflag = false;


	//Run Code
	cout << endl;
	
	while (successfulmoveflag == 0)
	{

		entermoveflag = false;

		if(Hex_Current_Turn == RED)
		{
			cout << "Red Player (X), its your turn!" << endl;
		}
		else if(Hex_Current_Turn == BLUE)
		{
			cout << "Blue Player (O), its your turn!" << endl;
		}
		else
		{
			cout << "Something is not right here!  Try again." << endl;
			cout << "Whose turn is it supposed to be (Blue=1 or Red=2)? ";
			int Temp_Hex_Current_Turn;
			cin >> Temp_Hex_Current_Turn;
			if(Temp_Hex_Current_Turn == 1)
			{
				Hex_Current_Turn = BLUE;
				continue;
			}
			else
			{
				Hex_Current_Turn = RED;
				continue;
			}
		}
	
		//Solicit Player Move
		cout << "Please enter your move (e.g. A1): ";
		cin >> c;
		c=toupper(c);
		if(c == 'Q')
		{
			cout << endl << endl;
			cout << "You have chosen to quit the game!  Bye Bye!" << endl;
			return -1;
		}
		
		cin >> r;
		cin.get();
		c=toupper(c);
		
		if((c >= 65 && c < 66+Hex_Board_Size) && (r>=0 && r<Hex_Board_Size+1))
		{
			entermoveflag = true;
		}
		else
		{
			entermoveflag = false;
			cin.clear();
			cout << endl << "You entered an invalid move!  Try Again" << endl << endl;
			continue;
		}
				
		//Check to see if player move is valid & set the move if valid
	
		if(Hex_Board_Graph.Graph_GetNodeColor((Hex_Board_Size*(r-1))+(c-65)) == 0)
		{
			Hex_Board_Graph.Graph_SetNodeColor((Hex_Board_Size*(r-1))+(c-65),Hex_Current_Turn);
			successfulmoveflag = 1;
		}
		else
		{
			cout << "Board Location is occuppied!  Try again!" << endl;
		}
	}

	//Set new Edge Colors (If Any)
	for(int i=0; i<Hex_Graph_Size;i++)
	{
		// Check the adjacency of each node with respect to the current player move
		// Set the edge color if the node is adjacent and the edge color isn't set yet, otherwise don't bother
		if(Hex_Board_Graph.Graph_Adjacent((Hex_Board_Size*(r-1))+(c-65),i,Hex_Current_Turn) && (Hex_Board_Graph.Graph_GetEdgeColor((Hex_Board_Size*(r-1))+(c-65),i) != Hex_Current_Turn))
		{
				Hex_Board_Graph.Graph_SetEdgeColor((Hex_Board_Size*(r-1))+(c-65),i,Hex_Current_Turn);
				Hex_Board_Graph.Graph_SetEdgeColor(i,(Hex_Board_Size*(r-1))+(c-65),Hex_Current_Turn);
		}
			
	}

	//Check for Winner
	winnerflag = Hex_CheckForWinner();

	if(winnerflag == 1)
	{
		return 1;
	}
	else if(winnerflag == 2)
	{
		return 2;
	}
	
	//Change the current player once a successful move is made & No winner is declared
	if(Hex_Current_Turn == RED)
	{
		Hex_Current_Turn = BLUE;
	}
	else
	{
		Hex_Current_Turn = RED;
	}
		
	return 0;

}

int Hex::Hex_CheckForWinner()
{
	//Initialize Variables

	//Run Code
	if(Hex_Current_Turn == BLUE)
	{
		Hex_Board_MST.MST_Path(Hex_Board_Graph, Hex_Board_Size*Hex_Board_Size, Hex_Current_Turn);
		
		if(Hex_Board_MST.MST_Check_Vertices(Hex_Board_Size*Hex_Board_Size+1))
		{
			return 1;
		}

	}

	else if(Hex_Current_Turn == RED)
	{
		Hex_Board_MST.MST_Path(Hex_Board_Graph, Hex_Board_Size*Hex_Board_Size+2, Hex_Current_Turn);
		
		if(Hex_Board_MST.MST_Check_Vertices(Hex_Board_Size*Hex_Board_Size+3))
		{
			return 2;
		}

	}

	return 0;
}

//********************************
//
//  Hex My Methods
//
//********************************

