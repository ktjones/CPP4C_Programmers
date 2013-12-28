//*******************************
//
//  C++ Support File 
//	- Graph Class
//
//*******************************

//*******************************
//
//  Standard Header
//
//*******************************

#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <string>
#include "header - Graph.h"

using namespace std;

//***************************************************************************************************
//
//  Support Program Section - Graph Class
//
//***************************************************************************************************

//********************************
//
//  Graph Constructors & Destructors
//
//********************************

Graph::Graph(int n, double d) : Gr_Nodes(n), Gr_Density(d), Gr_Randomfill(false) 
{

	//Resize graph to accomodate # of nodes
	GraphAM.resize(Gr_Nodes);
	
	//Create edge, and initialize to 0.0
	for (int i=0;i<Gr_Nodes;i++)
	{
		for (int j=0;j<Gr_Nodes;j++)
		{
			GraphAM[i].push_back(make_pair(0,0));
		}
	}
	
	//Chatty Ctor
	//cout << "Graph Constructed using Default Ctor" << endl;

	return;

}

Graph::Graph(bool rf, int n, double d) : Gr_Nodes(n), Gr_Density(d), Gr_Randomfill(rf) 
{

	//Resize graph to accomodate # of nodes
	GraphAM.resize(Gr_Nodes);
	
	//Create edge, and initialize to 0.0
	for (int i=0;i<Gr_Nodes;i++)
	{
		for (int j=0;j<Gr_Nodes;j++)
		{
			GraphAM[i].push_back(make_pair(0,0));
		}
	}
	
	//Flag for filling graph randomly or manually
	if (Gr_Randomfill == true)
	{
		Graph_FillGraphRandomly();
	}
	else
	{
		Graph_FillGraphManually();
	}

	return;

}

Graph::Graph(string & fname) : Gr_Density(1.0), Gr_Randomfill(false)
{
	
	//Open the file and read in the first line, then close the file
	fstream fin;
	fin.open(fname);
	fin >> Gr_Nodes;
	fin.close();

	//Resize graph to accomodate # of nodes
	GraphAM.resize(Gr_Nodes);
	
	//Create each edge, and initialize to 0.0
	for (int i=0;i<Gr_Nodes;i++)
	{
		for (int j=0;j<Gr_Nodes;j++)
		{
			GraphAM[i].push_back(make_pair(0,0));
		}
	}

	Graph_FillGraphbyFile(fname);
		
	return;

}

Graph::~Graph()
{
}

//********************************
//
//  Graph Fill Methods
//
//********************************

void Graph::Graph_FillGraphRandomly()
{
	
	//Variable initialization
	double randdensity;
	double randedgeweight;

	//Zero Out All Entries
	for (int i=0; i<Gr_Nodes;i++)
	{
		for (int j=0;j<Gr_Nodes;j++)
		{
			GraphAM[i][j].second = 0.0;
		}
	}
	
	//Broadcast Fill Method
	cout << "Initiating 'Fill by Random Edge Generation!'" << endl << endl;

	//Randomly Select edges using the "if the randon number is less than 20%, then an edge exists"	
	for (int i=0; i<Gr_Nodes;i++)
	{
		for (int j=i;j<Gr_Nodes;j++)
		{

			if(j == i)
			{
				continue;
			}
			else
			{
				randdensity = ((double) rand()/(RAND_MAX+1));

				if (randdensity < Gr_Density)
				{
					randedgeweight = (double) (rand() % 9000 + 1000)/1000;
					GraphAM[i][j].second = randedgeweight;
					GraphAM[j][i].second = randedgeweight;
				}
			}

		}
	}
	
	return;
}

void Graph::Graph_FillGraphManually()
{

	//Variable creation
	double x;
	
	//Broadcast Fill Method
	cout << "Initiating 'Fill by Manual Entry!'" << endl << endl;

	//Run through graph and obtain user input
	for (int i=0;i<Gr_Nodes;i++)
	{
		for (int j=0;j<Gr_Nodes;j++)
		{
			cout << "Enter the cost of edge [" << i+1 << "],[" << j+1 << "]: ";
			cin >> x;
			GraphAM[i][j].second = x;
		}
	}
	
	return;

}

void Graph::Graph_FillGraphbyFile(string & fname)
{
	
	//Create variables
	int inputNodeFrom = -1;
	int inputNodeTo = -1;
	int inputcost = -1;
	
	fstream fin;
	fin.open(fname);
	fin >> inputNodeFrom;
		
	//Zero Out All Entries
	for (int i=0; i<Gr_Nodes;i++)
	{
		for (int j=0;j<Gr_Nodes;j++)
		{
			GraphAM[i][j].second = 0.0;
		}
	}

	//Broadcast Fill Method
	cout << "Initiating 'Fill by File!' using file: " << fname << endl << endl;
	
	//Read edge data from file and assign to correct location
	while (!fin.eof())
	{
		fin >> inputNodeFrom >> inputNodeTo >> inputcost;
		GraphAM[inputNodeFrom][inputNodeTo].second = inputcost;
	}

	fin.close();

	return;
	
}


//********************************
//
//  Graph Working Methods
//
//********************************

int Graph::Graph_NoVertices()
{

	return Gr_Nodes;

}

int Graph::Graph_NoEdges()
{

	int NoEdges = 0;

	//Counts number of edges
	for (int i=0;i<Gr_Nodes;i++)
	{
		
		for (int j=0;j<Gr_Nodes;j++)
		{
			if (GraphAM[i][j].second > 0)
			{
				NoEdges += 1;
			}
		}
		
	}

	return NoEdges;
}

bool Graph::Graph_Adjacent(int x, int y, int c)
{

	//Create variables
	
	//Run Code
	if(c==0)
	{
		if(GraphAM[x][y].second > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if(GraphAM[y][y].first==c && GraphAM[x][y].second > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
}

void Graph::Graph_Neighbors(int x, int c)
{

	//Create variables
	
	//Run Code
	cout << "List of Nodes that share Edges with Node " << x << ": " << endl;
	
	if(c==0)
	{
		for(int i=0; i<Gr_Nodes; i++)
		{
			if(i == x)
			{
				continue;
			}
			else if(GraphAM[x][i].second > 0)
			{
				cout << "Node: " << i << endl;
			}
		}
	}
	else
	{
		for(int i=0; i<Gr_Nodes; i++)
		{
			if(i == x)
			{
				continue;
			}
			else if(GraphAM[x][i].first==c && GraphAM[x][i].second>0)
			{
				cout << "Node: " << i << endl;
			}
		}
	}

	return;
}

void Graph::Graph_AddEdge(int x, int y, double weight, int c)
{

	//Create variables
	
	//Run Code
	if(c==0)
	{
		if(GraphAM[x][y].second > 0)
		{
			cout << "Edge already exists!  Use SetEdge instead." << endl;
		}
		else
		{
			GraphAM[x][y].second = weight;
		}
	}
	else
	{
		if(GraphAM[x][y].second > 0)
		{
			cout << "Edge already exists!  Use SetEdge instead." << endl;
		}
		else
		{
			GraphAM[x][y].first = c;
			GraphAM[x][y].second = weight;
		}
	}
	
	return;

}

void Graph::Graph_DeleteEdge(int x, int y)
{

	GraphAM[x][y].first = 0;
	GraphAM[x][y].second = 0.0;

	return;

}

double Graph::Graph_GetEdgeValue(int x, int y)
{

	//Create variables
	
	//Run Code

	return GraphAM[x][y].second;

}

int Graph::Graph_GetEdgeColor(int x, int y)
{

	//Create variables
	
	//Run Code

	return GraphAM[x][y].first;

}

void Graph::Graph_SetEdgeValue(int x, int y, double weight)
{

	//Create variables
	
	//Run Code
	if(GraphAM[x][y].second == 0)
	{
		cout << "Edge doesn't exist!  Use AddEdge instead." << endl;
	}
	else
	{
		GraphAM[x][y].second = weight;
	}

	return;

}

void Graph::Graph_SetEdgeColor(int x, int y, int c)
{

	//Create variables
	
	//Run Code
	if(GraphAM[x][y].second == 0)
	{
		cout << "Edge doesn't exist!  Use AddEdge instead." << endl;
	}
	else
	{
		GraphAM[x][y].first = c;
	}

	return;

}

double Graph::Graph_GetNodeValue(int x)
{

	//Create variables
	
	//Run Code

	return GraphAM[x][x].second;

}

int Graph::Graph_GetNodeColor(int x)
{

	//Create variables
	
	//Run Code

	return GraphAM[x][x].first;

}

void Graph::Graph_SetNodeValue(int x, double weight)
{
	
	//Create variables
	
	//Run Code
	GraphAM[x][x].second = weight;

	return;

}

void Graph::Graph_SetNodeColor(int x, int c)
{
	
	//Create variables
	
	//Run Code
	GraphAM[x][x].first = c;

	return;

}

//********************************
//
//  Graph My Methods
//
//********************************

void Graph::Graph_ShowEdge()
{

	//Set Output Precision to 1 place after decimal
	cout.precision(1);
	cout.setf( std::ios::fixed, std:: ios::floatfield);

	//Loop through the nodes and display edge weights
	for (int i=0;i<Gr_Nodes;i++)
	{
		for (int j=0;j<Gr_Nodes;j++)
		{
			cout << GraphAM[i][j].second << " ";
		}
		
		cout << endl;

	}
	
	return;

}
