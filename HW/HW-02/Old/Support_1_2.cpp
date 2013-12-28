//*******************************
//
//  C++ Support File - Graph Class
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
#include "header.h"

using namespace std;

//***************************************************************************************************
//
//  Support Program Section - Graph Class
//
//***************************************************************************************************

//********************************
//
//  Graph Constructors
//
//********************************

GraphMatrixADT::GraphMatrixADT(int n, double d) : nodes(n), density(d)
{

	GraphEdge.resize(nodes);
	
	for (int i=0;i<nodes;i++)
	{
		for (int j=0;j<nodes;j++)
		{
			GraphEdge[i].push_back(make_pair(j,0));
		}
	}
	
	return;

}

GraphMatrixADT::~GraphMatrixADT()
{
}

//********************************
//
//  Graph Working Methods
//
//********************************


int GraphMatrixADT::GraphMatrixADT_NoVertices()
{

	return nodes;

}

int GraphMatrixADT::GraphMatrixADT_NoEdges()
{

	int NoEdges = 0;

	for (int i=0;i<nodes;i++)
	{
		
		for (int j=0;j<nodes;j++)
		{
			if (GraphEdge[i][j].second > 0)
			{
				NoEdges += 1;
			}
		}
		
	}

	return NoEdges;
}

void GraphMatrixADT::GraphMatrixADT_FillGraph()
{

	double randdensity;
	double randedgeweight;

	for (int i=0; i<nodes;i++)
	{
		for (int j=0;j<nodes;j++)
		{

			if(j == i)
			{
				continue;
			}
			else if(GraphEdge[i][j].second > 0.0)
			{
				continue;
			}
			else
			{
				randdensity = ((double) rand()/(RAND_MAX+1));

				if (randdensity < density)
				{
					randedgeweight = ((double) rand()/(RAND_MAX+1)) * 10;
					GraphEdge[i][j].second = randedgeweight;
					GraphEdge[j][i].second = randedgeweight;
				}
			}

		}
	}

}

//********************************
//
//  Graph Future Methods
//
//********************************

bool GraphMatrixADT::GraphMatrixADT_Adjacent(int x, int y)
{

	cout << "Nothing here to see yet" << endl;

	return false;

}

void GraphMatrixADT::GraphMatrixADT_Neighbors(int x, int y)
{

	cout << "Nothing here to see yet" << endl;

	return;

}

void GraphMatrixADT::GraphMatrixADT_AddEdge(int x, int y)
{

	cout << "Nothing here to see yet" << endl;

	return;

}

void GraphMatrixADT::GraphMatrixADT_DeleteEdge(int x, int y)
{

	cout << "Nothing here to see yet" << endl;

	return;

}

double GraphMatrixADT::GraphMatrixADT_GetNodeValue(int x)
{

	cout << "Nothing here to see yet" << endl;

	return 0.0;

}

void GraphMatrixADT::GraphMatrixADT_SetNodeValue(int x, double a)
{

	cout << "Nothing here to see yet" << endl;

	return;

}

double GraphMatrixADT::GraphMatrixADT_GetEdgeValue(int x, int y)
{

	cout << "Nothing here to see yet" << endl;

	return 0.0;

}

void GraphMatrixADT::GraphMatrixADT_SetEdgeValue(int x, int y, double a)
{

	cout << "Nothing here to see yet" << endl;

	return;

}

//********************************
//
//  Graph My Methods
//
//********************************

void GraphMatrixADT::GraphMatrixADT_ManualCreateGraph()
{
	/*
	pair<int,double> newcolumn;
	double x;
	
	for (int i=0;i<nodes;i++)
	{
		for (int j=0;j<nodes;j++)
		{
			cout << "Enter the cost of edge [" << i+1 << "],[" << j+1 << "]: ";
			cin >> x;
			GraphEdge[i].push_back(newcolumn);
			GraphEdge.at(i).push_back(make_pair(j,x));
		}
	}
	*/
		
	GraphEdge[0][1].first = 1;
	GraphEdge[0][1].second = 7;

	GraphEdge[0][2].first = 2;
	GraphEdge[0][2].second = 9;

	GraphEdge[0][5].first = 5;
	GraphEdge[0][5].second = 14;

	GraphEdge[1][0].first = 0;
	GraphEdge[1][0].second = 7;

	GraphEdge[1][2].first = 2;
	GraphEdge[1][2].second = 10;

	GraphEdge[1][3].first = 3;
	GraphEdge[1][3].second = 15;

	GraphEdge[2][0].first = 0;
	GraphEdge[2][0].second = 9;

    GraphEdge[2][1].first = 1;
	GraphEdge[2][1].second = 10;

	GraphEdge[2][5].first = 5;
	GraphEdge[2][5].second = 2;
	
	GraphEdge[2][3].first = 3;
	GraphEdge[2][3].second = 11;
	
	GraphEdge[3][1].first = 1;
	GraphEdge[3][1].second = 15;

	GraphEdge[3][2].first = 2;
	GraphEdge[3][2].second = 11;

	GraphEdge[3][4].first = 4;
	GraphEdge[3][4].second = 6;
	
	GraphEdge[4][3].first = 3;
	GraphEdge[4][3].second = 6;

	GraphEdge[4][5].first = 5;
	GraphEdge[4][5].second = 9;
	
    GraphEdge[5][0].first = 0;
	GraphEdge[5][0].second = 14;

	GraphEdge[5][2].first = 2;
	GraphEdge[5][2].second = 2;

	GraphEdge[5][4].first = 4;
	GraphEdge[5][4].second = 9;

	return;

}

void GraphMatrixADT::GraphMatrixADT_ShowEdge()
{

	std::cout.precision(1);
	std::cout.setf( std::ios::fixed, std:: ios::floatfield);

	for (int i=0;i<nodes;i++)
	{
		for (int j=0;j<nodes;j++)
		{
			cout << GraphEdge[i][j].second << " ";
		}
		
		cout << endl;

	}
	
	return;

}
