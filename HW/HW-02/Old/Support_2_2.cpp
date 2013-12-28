//*******************************
//
//  C++ Support Files - ShortestPathAlgo
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
//  Support Program Section - ShortestPathAlgo Class
//
//***************************************************************************************************

//********************************
//
//  ShortestPathAlgo Constructors
//
//********************************

ShortestPathAlgo::ShortestPathAlgo()
{
		
}

ShortestPathAlgo::~ShortestPathAlgo()
{
		
}

//********************************
//
//   ShortestPathAlgo Working Methods
//
//********************************

double ShortestPathAlgo::ShortestPathAlgo_Calc(int s, int d, const GraphMatrixADT & g)
{

	//Initial creation of Algo containers
	vector<vector<pair<int, double>>> Dj_Graph;		//contains copy of Matrix
	vector<int> Dj_Parent(g.GraphEdge.size());		//contains parent information
	priority_queue<pair<int,double>,vector<pair<int,double>>,Comparison> Dj_PQ;
	pair<int, double> temp;							//temp object representing the current node pair

	//Copy Graph to local container
	Dj_Graph.resize(g.GraphEdge.size());
	
	for (unsigned int i=0;i<g.GraphEdge.size();i++)
	{
		for (unsigned int j=0;j<g.GraphEdge.size();j++)
		{
			Dj_Graph[i].push_back(make_pair(g.GraphEdge[i][j].first,g.GraphEdge[i][j].second));
		}
	}
	
	//Initialize Parent Vector to default value of -1
	for (int i=0;i<g.GraphEdge.size();i++)
	{
		Dj_Parent[i] = -1;
	}

	//Djikstra Step #1
	//Set all costs to infinity (MAX value), set source node cost to zero
	for (unsigned int i=0;i<Dj_Graph.size();i++)
	{
		for (unsigned int j=0;j<Dj_Graph.size();j++)
		{
			Dj_Graph[i][j].second = numeric_limits<double>::max();
		}
	}
	
	Dj_Graph[s][s].second = 0.0;

	//Djikstra Step #2
	//Push Initial Source node and cost into Priority Queue
	Dj_PQ.push(Dj_Graph[s][s]);

	//Djikstra Step #3
	// Start iterations
	
	while(!Dj_PQ.empty())
	{

		temp = Dj_PQ.top();	//
	
		if(temp.first == d)
		{
			break;
		}

		Dj_PQ.pop();

		for (unsigned int j=0;j<g.GraphEdge[temp.first].size();j++)
		{
			if(g.GraphEdge[temp.first][j].second == 0)
			{
				continue;
			}
			if(Dj_Graph[temp.first][g.GraphEdge[temp.first][j].first].second > Dj_Graph[temp.first][temp.first].second + g.GraphEdge[temp.first][j].second)
			{

				Dj_Graph[temp.first][g.GraphEdge[temp.first][j].first].second = Dj_Graph[temp.first][temp.first].second + g.GraphEdge[temp.first][j].second;
				Dj_Parent[g.GraphEdge[temp.first][j].first] = temp.first;
				temp.second = Dj_Graph[temp.first][g.GraphEdge[temp.first][j].first].second;
				temp.first = g.GraphEdge[temp.first][j].first;
				Dj_PQ.push(temp);

			}

		}

	}

	Dj_ShortestPath.clear();
	int p = d;
	Dj_ShortestPath.push_back(d);
	
	while(p!=s)
	{
		p = Dj_Parent[p];
		Dj_ShortestPath.push_back(p);
	}


	return 0;

}


//********************************
//
//   ShortestPathAlgo My Methods
//
//********************************


