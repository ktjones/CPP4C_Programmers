//
//	Hex_Game.h
//
//	Created on: Nov 10, 2013
//		Author: JFM
//
//	This class is meant to manage a Hex Game
//

#ifndef HEX_GAME_H_
#define HEX_GAME_H_

#include <iostream>
#include <vector>
#include <time.h> // The time class will be used to reset the random number generator
#include "Graph.h"
#include "ShortestPathAlgo.h"

using namespace std;

enum HEX_Colors{EMPTY, PLAYER1, PLAYER2};

class Hex_Game{
public:
	Hex_Game(int number_of_rows, bool Rule_Variant);

	int Game();

private:

	void Print_Board();

	void Copy_Game(Hex_Game &temp_Game);

	int MonteCarlo(Hex_Game Temp_Game);

	inline void Print_Position(int row, int column){
		if (Hex_Graph.get_node_value(row*Rows+column) == EMPTY) cout << ".";
		if (Hex_Graph.get_node_value(row*Rows+column) == PLAYER1) cout << "X";
		if (Hex_Graph.get_node_value(row*Rows+column) == PLAYER2) cout << "O";
	};

	void Human_Play(int &row, int &column);
	void Computer_Play(int &row, int &column, bool print=true);

	bool Check_Game_is_ended();

	inline bool Check_Legal_Move(int row, int column){

		if ((row<0)||(column<0)){cout << "Row or Column lower than 0"<<endl; return false;};
		if ((row>Rows-1) || (column>Rows-1)){cout << "Row or Column higher than "<<Rows<<"-1"<<endl;return false;};
		
		if(Hex_Graph.get_node_value(row*Rows+column)==EMPTY){
			return true;
		}
		else{ cout << "Position is already filled"<<endl;return false;};
	};

	void Perform_Move(int row, int column);

	Graph<int> Hex_Graph;
	bool Swapping_in_PLAYER2_First_Movement_Rule;
	int Rows;
	bool Game_Settled;

	bool Player1_human;
	bool Player2_human;

	bool Computer_Random_Player;

	int Computer_Montecarlo_Search_Number;
	int Computer_Montecarlo_Search_Number0;

	int Winner;

	int turn;

};

#endif // HEX_GAME_H_