// Hex.cpp : Defines the entry point for the console application.

// Assiggment5 Cpp for C programer
// 12/01/2013
// compiler: MSFT Visual Studio 2012

#include<vector>
#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<string>
#include<ctime>
#include<random>
#include<chrono>
using namespace std;

class node{
public:	
	node(int n=0):n(n) {};
	int get_n() {return n;};	
private:
	int n;

};

class edge{
public:
	edge(int n1, int n2)
	{
		start = node(n1);
		start = node(n2);
	}

private:
	node start;
	node end;

};

enum class StoneColor {EMPTY, RED, BLUE};


class HexGraph{
public:
	HexGraph(int hsize): size(hsize*hsize),board_side(hsize), seed(time(0)) // hsize is 1 dimension as 11 in 11 by 11 board
	{
		edgelist=vector<vector<edge>>(size);
		stone = vector<StoneColor>(hsize*hsize, StoneColor::EMPTY);
		
	}

	// specifically for Hex game
	bool has_won(StoneColor player, const vector<StoneColor>& stone)
	{
		// assuming player Red goes North/South and Blue player goes first
		if (StoneColor::RED== player)
		{
			const int board_side = sqrt(size);
			int j = 0;
			vector<bool> prev_open(board_side, false);
			vector<bool> curr_open(board_side, false);

			for (int i = 0; i < board_side; i++)
				curr_open[i]= (stone[i]==player);
			for (int i = 1; i < board_side; i++)
			{
				prev_open = curr_open;
				curr_open = vector<bool>(board_side, false);

				for (j = 0; j<board_side-1; j++)
				{
					if (stone[i*board_side+j]==player && (prev_open[j] ||prev_open[j+1]) )
						curr_open[j]= true;
					else
						curr_open[j]= false;
				}
				if (stone[i*board_side+j]==player && prev_open[j])
					curr_open[j]= true;
				else
					curr_open[j]= false;

				
			}

			for (int i=0; i< board_side; i++)
				if(curr_open[i])
					return true;			
		
			return false;
		}
		else if (StoneColor::BLUE== player)
		{
			const int board_side = sqrt(size);
			int j = 0;
			vector<bool> prev_open(board_side, false);
			vector<bool> curr_open(board_side, false);

			for (int i = 0; i < board_side; i++)
				curr_open[i]= (stone[i]==player);
			for (int i = 1; i < board_side; i++)
			{
				prev_open = curr_open;
				curr_open = vector<bool>(board_side, false);

				for (j = 0; j<board_side-1; j++)
				{
					if (stone[j*board_side+i]==player && (prev_open[j] ||prev_open[j+1]) )
						curr_open[j]= true;
					else
						curr_open[j]= false;
				}
				if (stone[j*board_side+i]==player && prev_open[j])
					curr_open[j]= true;
				else
					curr_open[j]= false;

				
			}

			for (int i=0; i< board_side; i++)
				if(curr_open[i])
					return true;			
		
			return false;
		}
		

	}

	StoneColor who_won_efficient(vector<StoneColor> stone) // this version is efficient but only applicable when the whole board is full
	{
		if (has_won(StoneColor::RED, stone))
			return StoneColor::RED;			
		else
			return StoneColor::BLUE;
	}

	StoneColor who_won() // this version is less efficient but is applicable at each move
	{
		if (has_won(StoneColor::RED, stone))
			return StoneColor::RED;			
		else if (has_won(StoneColor::BLUE, stone)) 
			return StoneColor::BLUE;
		else
			return StoneColor::EMPTY; // empty means neither wins
	}

	// draw the HexBoard
	void draw()
	{
		char drawSymbol;
		int hsize= board_side;
		for (int i=1; i<=hsize; i++)
		{
			for (int j=1; j<=2*(i-1); j++)
				cout<<" ";
			for (int j=1; j<=hsize; j++)
			{
				// when drawing on the screen, X --> BLUE, O --> RED, . --> EMPTY
				if (stone[(i-1)*hsize + (j-1)]==StoneColor::BLUE)
					drawSymbol = 'X';
				else if (stone[(i-1)*hsize + (j-1)]==StoneColor::RED)
					drawSymbol = 'O';
				else
					drawSymbol = '.';
				cout<< drawSymbol;
				if (j!=hsize)
					cout<<" - ";
				else
					cout<<endl;
			}
			if (i!=hsize)
			{
				for (int j=1; j<=2*i-1; j++)
					cout<<" ";
				cout<<"\\";
				for (int j=2; j<=hsize; j++)
				{										
					cout<<" / \\";
				}
				cout<<endl;
			}
					
		}
	}

	bool validMove(int x, int y)
	{		
		return stone[(x-1)*board_side + y-1] == StoneColor::EMPTY;
	}
	
	void move(int i, int j, StoneColor k)
	{
		// precondition: BoardNode shouldn't be Blank
		// mark it in nodeArray
		if (validMove(i, j))
			stone[(i-1)*board_side + j-1]= k;		
	}

	void get_AI_MC_move(int& x,int& y, StoneColor AI)
	{
		int i,j,k,BestNodeIndex;
		double MaxWinningProb = -1.0;
		int NumOfSimulations = 5000;
		StoneColor player, winner;
		


		if (AI==StoneColor::RED)
			player =StoneColor::BLUE;
		else
			player =StoneColor::RED;

		vector<int> EmptyNodeIndex;
		for (int k=0; k<size; k++)
			if (stone[k]==StoneColor::EMPTY)
				EmptyNodeIndex.push_back(k);

		double WinningProb;

		// loop through possible moves
		for (i=0; i<EmptyNodeIndex.size(); i++)					
		{
			// investigate the move at EmptyNodeIndex[i] 
			WinningProb= 0.0;
			for (j=0; j<NumOfSimulations; j++)		
			{
				vector<int> temp = EmptyNodeIndex;
				vector<StoneColor> StoneNext = stone;
				StoneNext[EmptyNodeIndex[i]] = AI;

				unsigned thisseed = std::chrono::system_clock::now().time_since_epoch().count();
				shuffle(temp.begin(), temp.end(), default_random_engine(thisseed));
				
				int count=0;
				for (k=0; k<temp.size(); k++)
				{
					if (temp[k]!=EmptyNodeIndex[i])
					{
						if (count<(temp.size()-1)/2)
							StoneNext[temp[k]] = AI;
						else
							StoneNext[temp[k]] = player;
						count++;
					}
				}
				winner = who_won_efficient(StoneNext);
				if (winner==AI)
					WinningProb++;
			}
			WinningProb= WinningProb/NumOfSimulations; 
			if (WinningProb> MaxWinningProb)
			{
				MaxWinningProb = WinningProb;
				BestNodeIndex = EmptyNodeIndex[i];
			}
		}
		
		x = BestNodeIndex/board_side + 1;
		y = BestNodeIndex%board_side + 1;
		
	}

	void play()
	{	
		string symbol;		
		bool firstplayer; // whether the player choose to play first, i.e. choose to play X;
		cout<< "Welcome to the Hex Game! Please choose to play X or O. X will play first." << endl;
		cout <<"key in X or O and press Enter>>";
		cin >> symbol;
		while(symbol!="X" && symbol!="O")
		{
			cout<<"Wrong input. Please key in X or O and then press Enter>>";
			cin >> symbol;
		}

		firstplayer = symbol=="X";
	
		// some more initilization
		StoneColor playerSymbol = (symbol=="X")?StoneColor::BLUE:StoneColor::RED;
		StoneColor AISymbol = (symbol=="X")?StoneColor::RED:StoneColor::BLUE;
		StoneColor winner;
		bool playerTurn = firstplayer; // denote whether it is currently player's turn or not
		bool gameOver = false; // denote whether either one has won the game;
		
		int x; int y;int round = 1;
		// set seed for MC simulation
		srand(seed);

		while (!gameOver)
		{
		
			if (playerTurn)
			{
				// only draw the board if its player turn
				cout << endl << "---------------Round " << round++ << " ---------------" << endl;
				draw();
				cout << "Please input the x coordinate of your next move and press Enter>>";
				cin >> x;
				cout << "Please input the y coordinate of your next move and press Enter>>";
				cin >> y;

				// determine if the move is valid			 
				while (!validMove(x, y))
				{
					cout << "Invalid move. Please try again: "<< endl;
					cout << "Please input the x coordinate of your next move and press Enter>>";
					cin >> x;
					cout << "Please input the y coordinate of your next move and press Enter>>";
					cin >> y;
				}

			
				// update graph
				move(x,y,playerSymbol);			
			}
			else
			{
				//AI turn
				//Best move determined by MC simulation
				get_AI_MC_move(x,y, AISymbol);

				// update graph
				move(x,y,AISymbol);						
			}

			// check whether some player wins --> BoardNode::Blank means neither wins
			winner = who_won(); 
			if (winner==playerSymbol)
			{		
				gameOver = true;
				cout << "Congratulations! You win!" << endl;
			}
			else if (winner==AISymbol)
			{		
				gameOver = true;
				cout << "Sorry, you lost!" << endl;
			}

			// change turn;
			playerTurn=!playerTurn;
		}
	
		// print the final board 
		cout << endl << "---------------Final Board: Round " << round-1 << " ---------------" << endl;
		draw();
		return;
	}


private:
	vector<vector <edge>> edgelist; //actually unused in this implementation
	int size; // hsize * hsize
	int board_side; // hsize
	vector<StoneColor> stone;
	unsigned int seed;
};


int main()
{
	HexGraph myHexGame(11);
	myHexGame.play();
	return 0;
}