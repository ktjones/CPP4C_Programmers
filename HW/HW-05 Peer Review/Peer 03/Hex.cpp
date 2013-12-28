//
//	Graph.h
//
//	Created on: Nov 6, 2013
//		Author: JFM
//
//	This class is meant to manage a graph directed/undirected
//

#include "Hex.h"

Hex_Game::Hex_Game(int number_of_rows, bool Rule_Variant=true){

	srand(int(time(NULL)));
	Game_Settled = true;
	Rows = number_of_rows;
	turn = PLAYER1;

	Winner = EMPTY;

	Swapping_in_PLAYER2_First_Movement_Rule = Rule_Variant;

	Hex_Graph.set_nodes_number(Rows*Rows);
	Hex_Graph.Set_Graph_Shape_Matrix();
	Hex_Graph.Enable_Graph_Directed(false);
	Hex_Graph.Enable_Graph_Weighted(false);

	for (int i = 0; i<Rows*Rows; ++i){Hex_Graph.set_node_value(i,EMPTY);};

	for (int i = 0; i < Rows -1; ++i){

		Hex_Graph.add_edge(i*Rows,(i+1)*Rows);
		Hex_Graph.set_edge_value(i*Rows,(i+1)*Rows,EMPTY);

		for (int j = 1; j < Rows; ++j){
			Hex_Graph.add_edge(i*Rows+j,i*Rows+j-1);
			Hex_Graph.set_edge_value(i*Rows+j,i*Rows+j-1,EMPTY);

			Hex_Graph.add_edge(i*Rows+j,(i+1)*Rows+j-1);
			Hex_Graph.set_edge_value(i*Rows+j,(i+1)*Rows+j-1,EMPTY);

			Hex_Graph.add_edge(i*Rows+j,(i+1)*Rows+j);
			Hex_Graph.set_edge_value(i*Rows+j,(i+1)*Rows+j,EMPTY);
		};

		Hex_Graph.add_edge(Rows*(Rows-1)+i,Rows*(Rows-1)+i+1);
		Hex_Graph.set_edge_value(Rows*(Rows-1)+i,Rows*(Rows-1)+i+1,EMPTY);

	};
};

void Hex_Game::Copy_Game(Hex_Game &temp_Game){
	
	vector<int> Player1_moves = Hex_Graph.get_nodes_by_value(PLAYER1);
	vector<int> Player2_moves = Hex_Graph.get_nodes_by_value(PLAYER2);

	int row;
	int column;

	for (int i=0; i<int(Player1_moves.size()); ++i){
		column = Player1_moves[i]%Rows;
		row = (Player1_moves[i]-column)/Rows;
		temp_Game.Perform_Move(row,column);
		
		if (i<int(Player2_moves.size())){
			column = Player2_moves[i]%Rows;
			row = (Player2_moves[i]-column)/Rows;
			temp_Game.Perform_Move(row,column);
		};
	};
};
		

int Hex_Game::Game(){
	
	bool first_move = true;
	bool second_move = false;
	
	bool Game_finished = false;

	int answer;

	int row;
	int column;

	Player1_human = true;
	Player2_human = false;

	Computer_Random_Player = false;

	Computer_Montecarlo_Search_Number = 4;
	Computer_Montecarlo_Search_Number0 = int((120.0/(1.5*(Rows*Rows)/(49.0)))/Computer_Montecarlo_Search_Number);
	
	while(!Game_finished){

		Print_Board();

		if (turn == PLAYER1){cout << "Player 1 to play:"<<endl;};
		if (turn == PLAYER2){cout << "Player 2 to play:"<<endl;};

		if ((second_move) && (Swapping_in_PLAYER2_First_Movement_Rule)){

			if (Player2_human){

				while(second_move){

					answer = 0;
					cout<< "Do you want to swap sides?(0=n/1=y):";
					cin >> answer;

					while (cin.fail()){
						cin.clear();
						cin.ignore(std::numeric_limits<int>::max(),'\n');
						cout << "Enter an int value:";
						cin >> answer;
					};

					if (answer == 0){second_move=false;cout<<"So, now choose your movement:"<<endl;}
					else{
						if(answer == 1){
							second_move=false;
							cout<<"So, now you are Player 1, Player 2 to play:"<<endl;
							Player2_human = Player1_human;
							Player1_human = true;}
						else{cout<<"Sorry, but it seems like I have not understood your commitment"<<endl;
						};
					};
				};
			}
			else{
				if(Hex_Graph.get_node_value(Rows/2*(Rows+1)) == PLAYER1){
					cout<<"Computer to swap sides"<<endl;
					cout<<"Player 2 to play:"<<endl;
					Player2_human = Player1_human;
					Player1_human = false;
					second_move=false;
				};

			};
		};

		if (turn == PLAYER1){
			if(Player1_human) {
				Human_Play(row, column);
			}
			else{
				Computer_Play(row, column);
			};
		};
		if (turn == PLAYER2){
			if(Player2_human) {
				Human_Play(row, column);
			}
			else{
				Computer_Play(row, column);
			};
		};
		Perform_Move(row,column);

		if (first_move){first_move = false; second_move = true;};

		Game_finished = Check_Game_is_ended();

	};
	
	cout << endl;
	if (Winner==PLAYER1){cout << "And the winner is PLAYER1!"<<endl;}
	if (Winner==PLAYER2){cout << "And the winner is PLAYER2!"<<endl;}

	return Winner;
};

void Hex_Game::Human_Play(int &row, int &column){
			
	bool correct_play=false;	

	while (!correct_play){
		
		cout << "Row to fill(0 to "<<Rows-1<<"): ";
		cin >> row;
		while (cin.fail()){
			cin.clear();
			cin.ignore(std::numeric_limits<int>::max(),'\n');
			cout << "Enter an int value:";
			cin >> row;
		};
		cout << "Column to fill(0 to "<<Rows-1<<"): ";
		cin >> column;
		while (cin.fail()){
			cin.clear();
			cin.ignore(std::numeric_limits<int>::max(),'\n');
			cout << "Enter an int value:";
			cin >> column;
		};
		
		correct_play = Check_Legal_Move(row, column);

		if (!correct_play){cout << "Oops, that was an illegal move, try again" << endl;};
	};
};

void Hex_Game::Computer_Play(int &row, int &column, bool print){

	bool computer_already_played = false;

	if (Hex_Graph.get_node_value(Rows/2*(Rows+1)) == EMPTY){
		row = Rows/2;
		column = Rows/2;
		computer_already_played = true;
	};

	if (!computer_already_played){

		vector<int> nodes_available = Hex_Graph.get_nodes_by_value(EMPTY);
		int node_selected;

		if (Computer_Random_Player){
			node_selected = nodes_available[rand() % nodes_available.size()];
			column = node_selected % Rows;
			row = (node_selected-column)/Rows;
		}
		else{
			
			vector<int> scores(nodes_available.size());
			vector<int> nodes_played;
			int contador;

			if (int(nodes_available.size())>Computer_Montecarlo_Search_Number0){
				contador = Computer_Montecarlo_Search_Number0;
			}
			else{
				contador = int(nodes_available.size());
			};

			for (int i = 0; i<contador; ++i){
		
				Hex_Game temp_Game(Rows,false);
				Copy_Game(temp_Game);

				int node_number;

				if (int(nodes_available.size())>Computer_Montecarlo_Search_Number0){
					node_number = int(rand() % nodes_available.size());
				}
				else{
					node_number = i;
				};
				
				node_selected = nodes_available[node_number];
				nodes_available.erase(nodes_available.begin()+node_number);
				nodes_played.push_back(node_selected);

				column = node_selected % Rows;
				row = (node_selected-column)/Rows;
				temp_Game.Perform_Move(row,column);
				scores[i] = 0;

				for (int j = 0; j<Computer_Montecarlo_Search_Number; ++j){

					scores[i] += MonteCarlo(temp_Game);

					cout << "*";
				};

			};
			cout<<endl;

			int top_score = 0;
			

			for (int i = 0; i<contador; ++i){
				if (scores[i]>top_score){
					node_selected = nodes_played[i];
					top_score = scores[i];
				};
			};
			column = node_selected % Rows;
			row = (node_selected-column)/Rows;
				
		};
	};

	if (print) {cout << "Computer plays row "<<row<<", column "<<column<<endl;};
	return;
};

int Hex_Game::MonteCarlo(Hex_Game Temp_Game){
	
	Temp_Game.Player1_human = false;
	Temp_Game.Player2_human = false;

	Temp_Game.Computer_Random_Player = true;

	bool Game_finished = false;
	int row;
	int column;

	while(!Game_finished){

		Temp_Game.Computer_Play(row, column,false);
		Temp_Game.Perform_Move(row,column);
		// Temp_Game.Print_Board();

		Game_finished = Temp_Game.Check_Game_is_ended();

	};

	if (turn == Temp_Game.Winner){
		return 100;
	}
	else{
		return 0;
	};

};


void Hex_Game::Print_Board(){

	cout << endl << " Current board is:" << endl << endl;
	
	cout << "  O";

	for (int i = 1; i < Rows; ++i){cout << "   O";};

	cout << endl;

	cout << " X ";

	Print_Position(0,0);

	for (int i = 1; i < Rows; ++i){

		cout << " - ";
		Print_Position(0,i);

	};

	cout << " X" << endl;

	for (int i = 1; i < Rows; ++i){

		for (int j = 0; j < 2*i+2; ++j){cout << " ";};

		cout << char(92);

		for (int j = 1; j < Rows; ++j){cout << " / " << char(92);};

		cout << endl;

		for (int j = 0; j < 2*i+1; ++j){cout << " ";};

		cout << "X ";

		Print_Position(i,0);

		for (int j = 1; j < Rows; ++j){

			cout << " - ";
			Print_Position(i,j);

		};

		cout << " X" <<endl;
	
	};
	
	for (int i = 0; i < 2*Rows+2; ++i){cout << " ";};

	cout << "O";

	for (int i = 1; i < Rows; ++i){cout << "   O";};

	cout << endl;
};


void Hex_Game::Perform_Move(int row, int column){

	vector<int> neighbors;

	int node = row*Rows+column;

	neighbors = Hex_Graph.neighbors(node);

	for(int i = 0; i<(int)neighbors.size(); ++i){

		if (Hex_Graph.get_node_value(neighbors[i])==turn){Hex_Graph.set_edge_value(node,neighbors[i],turn);};

	};

	Hex_Graph.set_node_value(node, turn);

	if (turn == PLAYER1){turn = PLAYER2;}else{turn = PLAYER1;};

};

bool Hex_Game::Check_Game_is_ended(){

	bool Game_ended;
	vector<int> way;
	vector<int> look_for(1);
	
	ShortestPathAlgo<int> Path;
	
	// First we check for winner in rows (PLAYER1)
	// If turn is Player2, it means, player 1 was the last to move, so this is the one we check
	
	if (turn == PLAYER2){
		look_for[0] = PLAYER1;
		Path.Set_Search_for_Particular_Edges(look_for);
		for (int i = 0; i<Rows; ++i){

			if (!(Hex_Graph.get_node_value(i*Rows) == PLAYER1)) continue;

			for (int j = 0; j < Rows; ++j){
			
				if (!(Hex_Graph.get_node_value((j+1)*Rows-1) == PLAYER1)) continue;
				way = Path.path(Hex_Graph,Rows*i,Rows*(j+1)-1,Game_ended);
				if (Game_ended){Winner = PLAYER1; return true;};

			};

		};
	}
	else{

		// Second we check for winner in columns (PLAYER2)
		look_for[0] = PLAYER2;
		Path.Set_Search_for_Particular_Edges(look_for);
		for (int i = 0; i<Rows; ++i){

			if (!(Hex_Graph.get_node_value(i) == PLAYER2)) continue;

			for (int j = 0; j < Rows; ++j){
			
				if (!(Hex_Graph.get_node_value((Rows-1)*Rows+j) == PLAYER2)) continue;
				way = Path.path(Hex_Graph,i,(Rows-1)*Rows+j,Game_ended);
				if (Game_ended){Winner = PLAYER2; return true;};

			};
		};

	};

	return false;

};