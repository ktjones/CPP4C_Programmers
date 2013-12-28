//*******************************
//
//  C++ Support Files 
//	- MST Class
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
#include "header - Graph.h"
#include "header - MST.h"

using namespace std;

//***************************************************************************************************
//
//  Support Program Section - MST Class
//
//***************************************************************************************************

//********************************
//
//  MST Constructors
//
//********************************

MST::MST() : MST_Shortest_Path(), MST_Shortest_Path_Size(0)
{
		
}

MST::~MST()
{
		
}

//********************************
//
//   MST Working Methods
//
//********************************

void MST::MST_Path(const Graph & g, int s, int c)
{

	//Initialization of variables
	unsigned int VisitedNodeCount = 0;
	MST_Shortest_Path.clear();
	int CurrentNode = s;
	
	//Initial creation of Algo containers
	pair<pair<int,int>,double> temp;
	vector<int> MST_Visited(g.GraphAM.size());
	vector<int> MST_Evaluated(g.GraphAM.size());
	priority_queue<pair<pair<int,int>,double>, vector<pair<pair<int,int>,double>>,MST> MST_PQ;		// MST_Priority Queue with a helper class to provide 
	
	//Broadcast start of Algorith

	//cout << "Starting 'Minimum Spanning Tree Algorithm!'" << endl << endl;

	//MST Step #1
	//	Initialize the visited set to 0
	for (unsigned int i=0; i<g.GraphAM.size(); i++)
	{
		MST_Visited[i] = 0;	// sets each element (Visited Flag) to 0. 
	}

	//MST Step #2
	MST_Visited[CurrentNode] = 1;
	VisitedNodeCount += 1;	
	
	//MST Step #3
	//	Start iterations
	while (VisitedNodeCount < g.GraphAM.size())
	{
		//  Run through the Visited Set, Stopping on nodes that have NOT been visited and whose Edge Color matches the criteria
		for (unsigned int j=0; j<g.GraphAM.size(); j++)
		{
			if (g.GraphAM[CurrentNode][j].second > 0 && MST_Visited[j] != 1 && g.GraphAM[CurrentNode][j].first == c)
			{
				MST_PQ.push(make_pair(make_pair(CurrentNode,j),g.GraphAM[CurrentNode][j].second));
			}
		}
		
		if(!MST_PQ.empty())
		{
			temp = MST_PQ.top();					//  Grab the least weighted edge
			MST_PQ.pop();							//  Remove it from the queue
		}
		else
		{
			return;
		}
		// check to see if the least weighted edge has been visited, if so, try again.
		while(MST_Visited[temp.first.second] == 1 && !MST_PQ.empty())
		{
			temp = MST_PQ.top();				
			MST_PQ.pop();						
		}
			
		MST_Shortest_Path.push_back(temp);	//  Push the value into the Path Structure for safe keeping 
		MST_Visited[temp.first.second] = 1;	//  Set the selected "To" Node as visited (Set = 1 in Visited Vector)		
		CurrentNode = temp.first.second;	//	Set CurrentNode to "To" Node that was popped
		VisitedNodeCount += 1;
		
	}

	return;

}

double MST::MST_Path_Size(const Graph & g, int s, int c)
{

	MST_Path(g, s, c);

	MST_Shortest_Path_Size = 0;

	for (unsigned int i=0; i<MST_Shortest_Path.size(); i++)
	{
		
		MST_Shortest_Path_Size += MST_Shortest_Path[i].second;

	}
	
	return MST_Shortest_Path_Size;

}

void MST::MST_Show_Path()
{

	//Broadcast which Method is being executed
	cout << endl;
	cout << "Displaying the Minimum Spanning Tree Path:" << endl;

	//Display the Path
	for (unsigned int i=0;i<MST_Shortest_Path.size();i++)
	{

		cout << "Edge #" << i+1 << ": (" << MST_Shortest_Path[i].first.first << "," << MST_Shortest_Path[i].first.second << ") : " << MST_Shortest_Path[i].second << endl;

	}

	return;

}

bool MST::MST_Check_Vertices(int v)
{

	for(unsigned int i=0; i<MST_Shortest_Path.size(); i++)
	{
		//Check to see if node v is in the list	
		if(v==MST_Shortest_Path[i].first.first || v==MST_Shortest_Path[i].first.second)
		{
			return true;
		}
		
	}

	return false;
	
}

//********************************
//
//   MST Overloaded Operators
//
//********************************

int MST::operator()(const pair<pair<int,int>,double> & p1, const pair<pair<int,int>,double> & p2)
{
	return p1.second>p2.second;
}
