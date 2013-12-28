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
#include <queue>
#include <time.h>
#include <random>
#include <algorithm>
#include "header - Graph.h"
#include "header - Hex.h"
#include "header - MST.h"
#include "header - Players.h"

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

Hex::Hex(int n) : Hex_Board_Size(n), Hex_Graph_Size(n*n+4), Hex_Number_of_Moves(0), Hex_Current_Turn(0), Hex_Board_Graph(n*n+4), Hex_Board_Graph_MC(n*n+4), Hex_Board_MST(), Hex_Player1(), Hex_Player2()
{
	
	//Initialize Variables
	

	//Create Board Using Graph Structure with all nodes set to 0
	Hex_CreateBoard();
	
	//Chatty Ctor
	//cout << "Board Constructed using Default Ctor" << endl;

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
		if(i>0 && i<=(Hex_Board_Size-2))
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
	// North Virtual Edge (Associated with Row 0, and the color RED)
	for (int i=0; i<Hex_Board_Size; i++)
	{
		Hex_Board_Graph.Graph_AddEdge(Hex_Board_Size*Hex_Board_Size,i,1);
		Hex_Board_Graph.Graph_AddEdge(i,Hex_Board_Size*Hex_Board_Size,1);

		Hex_Board_Graph.Graph_SetEdgeColor(Hex_Board_Size*Hex_Board_Size,i,2);
		Hex_Board_Graph.Graph_SetEdgeColor(i,Hex_Board_Size*Hex_Board_Size,2);
	}

	//South Virtual Edge (Associated with the last Row, and the color RED)
	for (int i=((Hex_Board_Size*Hex_Board_Size)-(Hex_Board_Size)); i<(Hex_Board_Size*Hex_Board_Size); i++)
	{
		Hex_Board_Graph.Graph_AddEdge(Hex_Board_Size*Hex_Board_Size+1,i,1);
		Hex_Board_Graph.Graph_AddEdge(i,Hex_Board_Size*Hex_Board_Size+1,1);

		Hex_Board_Graph.Graph_SetEdgeColor(Hex_Board_Size*Hex_Board_Size+1,i,2);
		Hex_Board_Graph.Graph_SetEdgeColor(i,Hex_Board_Size*Hex_Board_Size+1,2);
	}
	
	// East Virtual Edge (Associated with Column 0, and the color BLUE)
	for (int i=0; i<((Hex_Board_Size*Hex_Board_Size)-(Hex_Board_Size)+1); i+=Hex_Board_Size)
	{
		Hex_Board_Graph.Graph_AddEdge(Hex_Board_Size*Hex_Board_Size+2,i,1);
		Hex_Board_Graph.Graph_AddEdge(i,Hex_Board_Size*Hex_Board_Size+2,1);

		Hex_Board_Graph.Graph_SetEdgeColor(Hex_Board_Size*Hex_Board_Size+2,i,1);
		Hex_Board_Graph.Graph_SetEdgeColor(i,Hex_Board_Size*Hex_Board_Size+2,1);
	}

	// West Virtual Edge (Associate with Column ((Hex_Board_Size*row)-1, and the color BLUE)
	for (int i=Hex_Board_Size-1; i<(Hex_Board_Size*Hex_Board_Size); i+=Hex_Board_Size)
	{
		Hex_Board_Graph.Graph_AddEdge(Hex_Board_Size*Hex_Board_Size+3,i,1);
		Hex_Board_Graph.Graph_AddEdge(i,Hex_Board_Size*Hex_Board_Size+3,1);

		Hex_Board_Graph.Graph_SetEdgeColor(Hex_Board_Size*Hex_Board_Size+3,i,1);
		Hex_Board_Graph.Graph_SetEdgeColor(i,Hex_Board_Size*Hex_Board_Size+3,1);
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
			
			cout << "   ";

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
			cout << "  ";
		}
		
		// Print the line #
		if (i < 9)
		{
			cout << i + 1 << "  ";
		}
		else
		{
			cout << i + 1 << " ";
		}

		for(int j=0; j<Hex_Board_Size;j++)
		{
			// Print the player in each board location
			if(Hex_Board_Graph.Graph_GetNodeColor((Hex_Board_Size*i)+j) == 0)
			{
				cout << ".";
			}
			else if(Hex_Board_Graph.Graph_GetNodeColor((Hex_Board_Size*i)+j) == 1)
			{
				cout << "B";
			}
			else if (Hex_Board_Graph.Graph_GetNodeColor((Hex_Board_Size*i)+j) == 2)
			{
				cout << "R";
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
				cout << "  ";
			}
			
			// Pad the line to shift it over
			cout << "    ";

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

int Hex::Hex_CheckForWinner()
{
	//Initialize Variables

	//Run Code
	if(Hex_Current_Turn == 1)  //Player 1
	{
				
		if(Hex_Player1.Players_GetPlayerColor() == 1) //Player 1 is Blue
		{
			Hex_Board_MST.MST_Path(Hex_Board_Graph, Hex_Board_Size*Hex_Board_Size+2, 1);
		
			//Check for a Player 1 win -> West to East
			if(Hex_Board_MST.MST_Check_Vertices(Hex_Board_Size*Hex_Board_Size+3))
			{
				return 1;
			}
		}
		else //Player 1 is Red
		{
			Hex_Board_MST.MST_Path(Hex_Board_Graph, Hex_Board_Size*Hex_Board_Size, 2);
		
			//Check for a Player 1 win -> North to South
			if(Hex_Board_MST.MST_Check_Vertices(Hex_Board_Size*Hex_Board_Size+1))
			{
				return 1;
			}
		}

	}

	else if(Hex_Current_Turn == 2) //Player 2
	{
				
		if(Hex_Player2.Players_GetPlayerColor() == 1) //Player 2 is Blue
		{
			Hex_Board_MST.MST_Path(Hex_Board_Graph, Hex_Board_Size*Hex_Board_Size+2, 1);
		
			//Check for a Player 1 win -> West to East
			if(Hex_Board_MST.MST_Check_Vertices(Hex_Board_Size*Hex_Board_Size+3))
			{
				return 2;
			}
		}
		else //Player 2 is RED
		{
			Hex_Board_MST.MST_Path(Hex_Board_Graph
				, Hex_Board_Size*Hex_Board_Size, 2);
		
			//Check for a Player 1 win -> North to South
			if(Hex_Board_MST.MST_Check_Vertices(Hex_Board_Size*Hex_Board_Size+1))
			{
				return 2;
			}
		}

	}

	return 0;
}

int Hex::Hex_CheckForWinnerMC()
{
	//Initialize Variables

	//Run Code
	//Generate the MST for Player 1
	if(Hex_Player1.Players_GetPlayerColor() == 1) //Computer is Blue
	{
		Hex_Board_MST.MST_Path(Hex_Board_Graph_MC, Hex_Board_Size*Hex_Board_Size+2, 1);
		
		//Check for a Player 1 win
		if(Hex_Board_MST.MST_Check_Vertices(Hex_Board_Size*Hex_Board_Size+3))
		{
			return 1;
		}
	}
	else //Computer is RED
	{
		Hex_Board_MST.MST_Path(Hex_Board_Graph_MC, Hex_Board_Size*Hex_Board_Size, 2);
		
		//Check for a Player 1 win
		if(Hex_Board_MST.MST_Check_Vertices(Hex_Board_Size*Hex_Board_Size+1))
		{
			return 1;
		}
	}
	
	return 2;
}

//********************************
//
//  Hex Player Working Methods
//
//********************************

void Hex::Hex_PlayerSelection()
{
	
	//Initailize Variables
	int PlayerCount = -1;
	int PlayerColor = -1;
	int PlayerChoiceFlag = -1;
	int PlayerTurnFlag = -1;
	
	//Run Code
	//Select # of Players
	while(PlayerCount < 0 || PlayerCount > 2)
	{
		cout << "Please enter the number of human players (0,1,2): ";
		cin >> PlayerCount;

		cout << endl;
		cout << "Okie Dokie!  You want it like that huh? Fine..." << endl;
		cout << endl;

		if(PlayerCount == 0)
		{
			Hex_Player1.Players_SetPlayerType(1);
			Hex_Player2.Players_SetPlayerType(1);
			cout << "Both Players are Computers (Good Luck with That!)" << endl;
		}
		else if(PlayerCount == 1)
		{
			Hex_Player1.Players_SetPlayerType(1);
			Hex_Player2.Players_SetPlayerType(2);
			cout << "Player #1 is a Computer." << endl;
			cout << "Player #2 is a Human. " << endl;
		}
		else if(PlayerCount == 2)
		{
			Hex_Player1.Players_SetPlayerType(2);
			Hex_Player2.Players_SetPlayerType(2);
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

	//Choose Pick Color or Go First
	cout << "Player 1," << endl << "Would you like to pick a color or go first?" << endl << "(Color=1, Go First=2): ";
	cin >> PlayerChoiceFlag;

	if(PlayerChoiceFlag == 1)
	{
		cout << "Player 1, select a color (Blue=1, Red=2): ";
		cin >> PlayerColor;

		if(PlayerColor == 1)
		{
			Hex_Player1.Players_SetPlayerColor(1);
			Hex_Player2.Players_SetPlayerColor(2);
		}
		else
		{
			Hex_Player1.Players_SetPlayerColor(2);
			Hex_Player2.Players_SetPlayerColor(1);
		}

		cout << endl;

		cout << "Player 2, you get to go first!" << endl;
		Hex_Current_Turn = 2;
		
	}
	else
	{
		cout << "Player 2, select a color (Blue=1, Red=2): ";
		cin >> PlayerColor;

		if(PlayerColor == 1)
		{
			Hex_Player2.Players_SetPlayerColor(1);
			Hex_Player1.Players_SetPlayerColor(2);
		}
		else
		{
			Hex_Player2.Players_SetPlayerColor(2);
			Hex_Player1.Players_SetPlayerColor(1);
		}

		cout << endl;

		cout << "Player 1, you get to go first!";
		Hex_Current_Turn = 1;
		
	}

	cout << endl << endl;
	cout << "***********************************************************" << endl;
	cout << "Here are the players:" << endl;
	
	//Player 1
	cout << "Player #1: " << endl;
	cout << "Color: ";
	if(Hex_Player1.Players_GetPlayerColor() == 1)
	{
		cout << "BLUE" << endl;
	}
	else
	{
		cout << "RED" << endl;
	}
	if(Hex_Current_Turn == 1)
	{
		cout << "Turn: FIRST" << endl; 
	}
	else
	{
		cout << "Turn: SECOND" << endl;
	}

	cout << endl;

	//Player 2
	cout << "Player #2: " << endl;
	cout << "Color: ";
	if(Hex_Player2.Players_GetPlayerColor() == 2)
	{
		cout << "RED" << endl;
	}
	else
	{
		cout << "BLUE" << endl;
	}
	if(Hex_Current_Turn == 2)
	{
		cout << "Turn: FIRST" << endl; 
	}
	else
	{
		cout << "Turn: SECOND" << endl;
	}
	
	cout << "***********************************************************" << endl;
	cout << endl << endl;
	cout << "Have Fun Playing the Game!";

}

int Hex::Hex_GamePlay()
{

	//initialize Variables
	int moveflag = 0;
	int winnerflag = -1;

	//Run Code
	if(Hex_Current_Turn == 1 && Hex_Player1.Players_GetPlayerType() == 1)
	{
		moveflag = Hex_ComputerMoveAI();
	}
	else if(Hex_Current_Turn == 1 && Hex_Player1.Players_GetPlayerType() == 2)
	{
		moveflag = Hex_PlayerMove();
	}
	else if(Hex_Current_Turn == 2 && Hex_Player2.Players_GetPlayerType() == 1)
	{
		moveflag = Hex_ComputerMoveAI();
	}
	else if(Hex_Current_Turn == 2 && Hex_Player2.Players_GetPlayerType() == 2)
	{
		moveflag = Hex_PlayerMove();
	}
	else
	{
		cout << "Something is wrong wih the move selection module!" << endl;
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
	if(moveflag == 1)
	{
		Hex_Current_Turn = 2;
	}
	else
	{
		Hex_Current_Turn = 1;
	}
	
	return 0;

}

int Hex::Hex_PlayerMove()
{
	//Initailize Variables
	int r = -1;
	int successfulmoveflag = 0;
	char c = 'A';
	bool entermoveflag = false;
	
	//Run Code
	cout << endl;
	
	while (successfulmoveflag == 0)
	{

		entermoveflag = false;
		//Player 1
		if(Hex_Current_Turn == 1)
		{
			if(Hex_Player1.Players_GetPlayerColor() == 1)
			{
				cout << "Player 1, you are the Blue Player (B) and it's your turn!" << endl;
			}
			else
			{
				cout << "Player 1, you are the RED Player (R) and it's your turn!" << endl;
			}
		}
		//Player 2
		else if(Hex_Current_Turn == 2)
		{
			if(Hex_Player2.Players_GetPlayerColor() == 1)
			{
				cout << "Player 2, you are the Blue Player (B) and it's your turn!" << endl;
			}
			else
			{
				cout << "Player 2, you are the RED Player (R) and it's your turn!" << endl;
			}
		}
		//Oops, some other number was entered.
		else
		{
			cout << "Something is not right here!  Try again." << endl;
			cout << "Whose turn is it supposed to be?" << endl;
			cout << "(Player1=1 or Player2=2): ";
			
			int Temp_Hex_Current_Turn;
			cin >> Temp_Hex_Current_Turn;
			if(Temp_Hex_Current_Turn == 1)
			{
				Hex_Current_Turn = 1;
				continue;
			}
			else
			{
				Hex_Current_Turn = 2;
				continue;
			}
		}
	
		//Solicit Player Move
		cout << "Please enter your move (e.g. A1, or Q to Quit Game): ";
		cin >> c;
		c=toupper(c);
		//Check for a Quitter
		if(c == 'Q')
		{
			cout << endl << endl;
			cout << "You have chosen to quit the game!  Bye Bye!" << endl;
			return -1;
		}
		
		cin >> r;
		cin.get();
		
		//Check for a valid move (columns and rows are within bounds
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
				
		//Check to see if board is occupied at move location & set move if able
		if(Hex_Board_Graph.Graph_GetNodeColor((Hex_Board_Size*(r-1))+(c-65)) == 0)
		{
			if(Hex_Current_Turn == 1)
			{
				Hex_Board_Graph.Graph_SetNodeColor((Hex_Board_Size*(r-1))+(c-65),Hex_Player1.Players_GetPlayerColor());
				successfulmoveflag = 1;
			}
			else
			{
				Hex_Board_Graph.Graph_SetNodeColor((Hex_Board_Size*(r-1))+(c-65),Hex_Player2.Players_GetPlayerColor());
				successfulmoveflag = 2;
			}
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
		if(Hex_Current_Turn == 1)
		{	
			if(Hex_Board_Graph.Graph_Adjacent((Hex_Board_Size*(r-1))+(c-65),i,Hex_Player1.Players_GetPlayerColor()) && (Hex_Board_Graph.Graph_GetEdgeColor((Hex_Board_Size*(r-1))+(c-65),i) != Hex_Player1.Players_GetPlayerColor()))
			{
					Hex_Board_Graph.Graph_SetEdgeColor((Hex_Board_Size*(r-1))+(c-65),i,Hex_Player1.Players_GetPlayerColor());
					Hex_Board_Graph.Graph_SetEdgeColor(i,(Hex_Board_Size*(r-1))+(c-65),Hex_Player1.Players_GetPlayerColor());
			}
		}
		else
		{
			if(Hex_Board_Graph.Graph_Adjacent((Hex_Board_Size*(r-1))+(c-65),i,Hex_Player2.Players_GetPlayerColor()) && (Hex_Board_Graph.Graph_GetEdgeColor((Hex_Board_Size*(r-1))+(c-65),i) != Hex_Player2.Players_GetPlayerColor()))
			{
					Hex_Board_Graph.Graph_SetEdgeColor((Hex_Board_Size*(r-1))+(c-65),i,Hex_Player2.Players_GetPlayerColor());
					Hex_Board_Graph.Graph_SetEdgeColor(i,(Hex_Board_Size*(r-1))+(c-65),Hex_Player2.Players_GetPlayerColor());
			}
		}

	}

	return successfulmoveflag;

}

int Hex::Hex_ComputerMoveAI()
{

	//initialize Variables
	int MC_currentturn = Hex_Current_Turn;
	int MC_Iterations = 50;
	int currentmove = -1;  //node value
	int actualmove = -1;
	int winnerflag = -1;
	int successfulmoveflag = 0;
	double wincount = 0;
	double wincountavg = 0;
	pair<int,double> temp;
	
	queue<int> q;	//Keeps track of open spaces on board
	vector<int> vq;	//Keeps track of open spaces for MC use
	priority_queue<pair<int,double>, vector<pair<int,double>>,Hex> pq;	//Keeps track each moves wins/trial ratio

	//Run Code
	
	//Make current copy of board positions
	Hex_Board_Graph_MC = Hex_Board_Graph;

	//Fill Queue with open Spaces on Board
	for (unsigned int i = 0; i<Hex_Board_Size*Hex_Board_Size; i++)
	{
		if (Hex_Board_Graph_MC.Graph_GetNodeColor(i) == 0)
		{
			q.push(i);
			vq.push_back(i);
		}
	}
	
	while(!q.empty())
	{
		
		//reset variables
		
		//Get an empty Node from the Queue
		currentmove = q.front();
		if(q.empty())
		{
			break;
		}
		else
		{
			q.pop();
		}

		for (int i=0; i<MC_Iterations; i++)
		{
			//cout << i << " ";
			winnerflag = Hex_ComputerMoveRandomMC(currentmove, MC_currentturn, vq);
			if (winnerflag == 1)
			{
				wincount += 1;
			}

			Hex_Board_Graph_MC = Hex_Board_Graph;
			MC_currentturn = Hex_Current_Turn;

		}

		wincountavg = (wincount/MC_Iterations);
		wincount = 0;
		temp = make_pair(currentmove,wincountavg);
		pq.push(temp);

		Hex_Board_Graph_MC = Hex_Board_Graph;
		MC_currentturn = Hex_Current_Turn;
		
	}

	//Get the best move from the PQ
	temp = pq.top();
	actualmove = temp.first;

	//Check to see if board is occupied at move location & set move if able
	if(MC_currentturn == 1)
	{
		Hex_Board_Graph.Graph_SetNodeColor(actualmove,Hex_Player1.Players_GetPlayerColor());
		successfulmoveflag = 1;
	}
	else
	{
		Hex_Board_Graph.Graph_SetNodeColor(actualmove,Hex_Player2.Players_GetPlayerColor());
		successfulmoveflag = 1;
	}
		
	//Set new Edge Colors (If Any)
	for(int j=0; j<Hex_Graph_Size;j++)
	{
		// Check the adjacency of each node with respect to the current player move
		// Set the edge color if the node is adjacent and the edge color isn't set yet, otherwise don't bother
		if(MC_currentturn == 1)
		{	
			if(Hex_Board_Graph.Graph_Adjacent(actualmove,j,Hex_Player1.Players_GetPlayerColor()) && (Hex_Board_Graph.Graph_GetEdgeColor(actualmove,j) != Hex_Player1.Players_GetPlayerColor()))
			{
					Hex_Board_Graph.Graph_SetEdgeColor(actualmove,j,Hex_Player1.Players_GetPlayerColor());
					Hex_Board_Graph.Graph_SetEdgeColor(j,actualmove,Hex_Player1.Players_GetPlayerColor());
			}
		}
		else
		{
			if(Hex_Board_Graph.Graph_Adjacent(actualmove,j,Hex_Player2.Players_GetPlayerColor()) && (Hex_Board_Graph.Graph_GetEdgeColor(actualmove,j) != Hex_Player2.Players_GetPlayerColor()))
			{
					Hex_Board_Graph.Graph_SetEdgeColor(actualmove,j,Hex_Player2.Players_GetPlayerColor());
					Hex_Board_Graph.Graph_SetEdgeColor(j,actualmove,Hex_Player2.Players_GetPlayerColor());
			}
		}
	}

	return successfulmoveflag;

}

int Hex::Hex_ComputerMoveRandom()
{
	
	//Random Move logic for Computer Player

	//Initailize Variables
	int r = -1;
	int successfulmoveflag = 0;
	char c = 'A';
	bool entermoveflag = false;

	//Run Code
	cout << endl;
	
	while (successfulmoveflag == 0)
	{

		entermoveflag = false;
			
		//Calculating Random Move
		r = rand() % Hex_Board_Size + 1;
		c = rand() % Hex_Board_Size + 66;
		
		//Check for a valid move (columns and rows are within bounds
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
				
		//Check to see if board is occupied at move location & set move if able
		if(Hex_Board_Graph.Graph_GetNodeColor((Hex_Board_Size*(r-1))+(c-65)) == 0)
		{
			if(Hex_Current_Turn == 1)
			{
				Hex_Board_Graph.Graph_SetNodeColor((Hex_Board_Size*(r-1))+(c-65),Hex_Player1.Players_GetPlayerColor());
				successfulmoveflag = 1;
			}
			else
			{
				Hex_Board_Graph.Graph_SetNodeColor((Hex_Board_Size*(r-1))+(c-65),Hex_Player2.Players_GetPlayerColor());
				successfulmoveflag = 2;
			}
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
		if(Hex_Current_Turn == 1)
		{	
			if(Hex_Board_Graph.Graph_Adjacent((Hex_Board_Size*(r-1))+(c-65),i,Hex_Player1.Players_GetPlayerColor()) && (Hex_Board_Graph.Graph_GetEdgeColor((Hex_Board_Size*(r-1))+(c-65),i) != Hex_Player1.Players_GetPlayerColor()))
			{
					Hex_Board_Graph.Graph_SetEdgeColor((Hex_Board_Size*(r-1))+(c-65),i,Hex_Player1.Players_GetPlayerColor());
					Hex_Board_Graph.Graph_SetEdgeColor(i,(Hex_Board_Size*(r-1))+(c-65),Hex_Player1.Players_GetPlayerColor());
			}
		}
		else
		{
			if(Hex_Board_Graph.Graph_Adjacent((Hex_Board_Size*(r-1))+(c-65),i,Hex_Player2.Players_GetPlayerColor()) && (Hex_Board_Graph.Graph_GetEdgeColor((Hex_Board_Size*(r-1))+(c-65),i) != Hex_Player2.Players_GetPlayerColor()))
			{
					Hex_Board_Graph.Graph_SetEdgeColor((Hex_Board_Size*(r-1))+(c-65),i,Hex_Player2.Players_GetPlayerColor());
					Hex_Board_Graph.Graph_SetEdgeColor(i,(Hex_Board_Size*(r-1))+(c-65),Hex_Player2.Players_GetPlayerColor());
			}
		}

	}

	return successfulmoveflag;

}

int Hex::Hex_ComputerMoveRandomMC(int startnode, int currentturn, vector<int> vq)
{
	
	//Random Move logic for Computer Player

	//Initailize Variables
	int successfulmoveflag = 0;
	int winnerflag = 0;
	int currentnode = -1;
	

	//initialize Objects
	

	//Run Code
	
	//initial computer move
	if(currentturn == 1)
	{
		Hex_Board_Graph_MC.Graph_SetNodeColor(startnode,Hex_Player1.Players_GetPlayerColor());
	}
	else
	{
		Hex_Board_Graph_MC.Graph_SetNodeColor(startnode,Hex_Player2.Players_GetPlayerColor());
	}
	
	//Switch Turns
	if(currentturn == 1)
	{
		currentturn = 2;
	}
	else
	{
		currentturn = 1;
	}

	//Begin alternating moves
	//shuffle(vq.front(), vq.back(), mt19937());
	
	for (auto x : vq)
	{

		//reset move flag
		successfulmoveflag = 0;

		//determine next move
		currentnode = x;
		
		//Set move location
		if (currentturn == 1)
		{
			Hex_Board_Graph_MC.Graph_SetNodeColor(currentnode, Hex_Player1.Players_GetPlayerColor());
			successfulmoveflag = 1;

		}
		else
		{
			Hex_Board_Graph_MC.Graph_SetNodeColor(currentnode, Hex_Player2.Players_GetPlayerColor());
			successfulmoveflag = 1;

		}
	
		//Set new Edge Colors (If Any)
		for(int j=0; j<Hex_Graph_Size;j++)
		{
			// Check the adjacency of each node with respect to the current player move
			// Set the edge color if the node is adjacent and the edge color isn't set yet, otherwise don't bother
			if(currentturn == 1)
			{	
				if(Hex_Board_Graph_MC.Graph_Adjacent(currentnode,j,Hex_Player1.Players_GetPlayerColor()) && (Hex_Board_Graph_MC.Graph_GetEdgeColor(currentnode,j) != Hex_Player1.Players_GetPlayerColor()))
				{
						Hex_Board_Graph_MC.Graph_SetEdgeColor(currentnode,j,Hex_Player1.Players_GetPlayerColor());
						Hex_Board_Graph_MC.Graph_SetEdgeColor(j,currentnode,Hex_Player1.Players_GetPlayerColor());
				}
			}
			else
			{
				if(Hex_Board_Graph_MC.Graph_Adjacent(currentnode,j,Hex_Player2.Players_GetPlayerColor()) && (Hex_Board_Graph_MC.Graph_GetEdgeColor(currentnode,j) != Hex_Player2.Players_GetPlayerColor()))
				{
						Hex_Board_Graph_MC.Graph_SetEdgeColor(currentnode,j,Hex_Player2.Players_GetPlayerColor());
						Hex_Board_Graph_MC.Graph_SetEdgeColor(j,currentnode,Hex_Player2.Players_GetPlayerColor());
				}
			}
		}
		
		//Switch Turns
		if(currentturn == 1)
		{
			currentturn = 2;
		}
		else
		{
			currentturn = 1;
		}
	
	}

	//Check for a win after board is filled up
	winnerflag = Hex_CheckForWinnerMC();

	return winnerflag;

}

//********************************
//
//  Hex Overloaded Operator Methods
//
//********************************

int Hex::operator()(const pair<int,double> & p1, const pair<int,double> & p2)
{
	return p1.second<p2.second;
}

