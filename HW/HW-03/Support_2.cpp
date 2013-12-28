//*******************************
//
//  C++ Support Files 
//	- Dijkstra Class
//	
//*******************************

//*******************************
//
//  Standard Header
//
//*******************************

#include <iostream>
#include <vector>
#include <time.h>
#include <queue>
#include <numeric>
#include "header.h"

using namespace std;

//***************************************************************************************************
//
//  Support Program Section - Dijkstra Class
//
//***************************************************************************************************

//********************************
//
//  Dijkstra Constructors
//
//********************************

Dijkstra::Dijkstra() : Dj_Shortest_Path(), Dj_Shortest_Path_Size(0)
{
		
}

Dijkstra::~Dijkstra()
{
		
}

//********************************
//
//   Dijkstra Working Methods
//
//********************************

void Dijkstra::Dijkstra_Path(int s, int d, const Graph & g)
{

	//Initial creation of Algo containers
	vector<double> Dj_Costs(g.GraphAM.size());										// Dj_Costs: vector holding costs, the size of the vector is equal to the number of nodes.
	vector<int> Dj_Parent(g.GraphAM.size());										// Dj_Parent: vector holding information on the parent nodes, the size is equal to the # of nodes.
	vector<int> Dj_Visited(g.GraphAM.size());
	priority_queue<pair<int,double>, vector<pair<int,double> >, Dijkstra> Dj_PQ;	// Dj_Priority Queue with a helper class to provide Greater Than Comparison operator

	//Dijkstra Step #1
	//	Initialize cost element matrix to MAX Value
	//	Initialize Parent Vector to default value of -1
	for(unsigned int i = 0 ;i < g.GraphAM.size(); i++)
	{
		Dj_Costs[i] = std::numeric_limits<double>::max();	// sets each element (Distances) to the max float number.
		Dj_Parent[i] = -1;									// sets each element (Parent Node #) to -1. 
		Dj_Visited[i] = 0;									// sets each element (Visited Flag) to 0. 
	}

	//	Sets the SOURCE node to cost to of ZERO.
	Dj_Costs[s] = 0.0;

	
	//Dijkstra Step #2
	//	Push Initial Source node and cost into Priority Queue
	Dj_PQ.push(make_pair(s,Dj_Costs[s]));
	

	//Dijkstra Step #3
	//	Start iterations
	while(!Dj_PQ.empty())
	{
		
		int u = Dj_PQ.top().first;
		
		if(u == d)
		{
			break;
		}

		Dj_PQ.pop();											//remove the first element from Priority Queue
	 
		Dj_Visited[u] = 1;

		for(unsigned int i=0; i < g.GraphAM[u].size(); i++)	// loop through the nodes adjacent to this node
		{
			int v = g.GraphAM[u][i].first;					// node # of neighbor
			double w = g.GraphAM[u][i].second;				// cost associated with node #
			
			if (w == 0)											// skip if there is no pathway
			{
				continue;
			}
			
			if ((Dj_Costs[u]+w < Dj_Costs[v]) && Dj_Visited[v] != 1)
			{
				Dj_Costs[v] = Dj_Costs[u]+w;
				Dj_Parent[v] = u;
				Dj_PQ.push(make_pair(v,Dj_Costs[v]));
			}
		}
	}

	Dj_Shortest_Path.clear();
	int pathnode = d;
	Dj_Shortest_Path.push_back(d);
	
	//Step #4 - Reconstruct the Path
	while(pathnode != s)
	{
		pathnode = Dj_Parent[pathnode];
		Dj_Shortest_Path.push_back(pathnode);
	}

	reverse(Dj_Shortest_Path.begin(),Dj_Shortest_Path.end());

	return;

}

double Dijkstra::Dijkstra_Path_Size(int s, int d, const Graph & g)
{

	//Variable Initialization
	Dj_Shortest_Path_Size = 0;

	//Determine the Dijkstra Shortest Path
	Dijkstra_Path(s, d, g);

	//Run Loop to Sum the Path Length
	if (Dj_Shortest_Path[0] != s)
	{
		return 0;
	}
	else
	{
		for (unsigned int i=0; i<Dj_Shortest_Path.size()-1;i++)
		{

			Dj_Shortest_Path_Size += g.GraphAM[Dj_Shortest_Path[i]][Dj_Shortest_Path[i+1]].second;

		}
	}
	
	return Dj_Shortest_Path_Size;

}

void Dijkstra::Dj_Show_Path()
{

	//Broadcast what method is running
	cout << endl;
	cout << "Displaying the Dijkstra Shortest Path:" << endl;

	//Display the path
	for (unsigned int i=0;i<Dj_Shortest_Path.size();i++)
	{

		cout << "Node #: " << Dj_Shortest_Path[i] << endl;

	}

	return;

}

//********************************
//
//   Dijkstra Future Methods
//
//********************************

void Dijkstra_Vertices(Graph & g)
{

	cout << "Nothing here to see yet" << endl;

	return;
	
}

//********************************
//
//   Dijkstra Overloaded Operators
//
//********************************

int Dijkstra::operator()(const pair<int,double>& p1, const pair<int,double> &p2)
{
	return p1.second>p2.second;
}
