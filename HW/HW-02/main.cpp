//***************************************************************************************************
//
//  C++ Program 
//	- Homework #2 - Dijkstra Algorithm
//
//***************************************************************************************************
//*******************************
//
//  Standard Header
//
//*******************************

#include <iostream>
#include <time.h>
#include "header.h"

using namespace std;


//********************************
//
//  Pre-Program Declarations
//
//********************************




//***************************************************************************************************
//
//  Main Program Section
//
//***************************************************************************************************

int main(int nNumberofArgs, char* pszArgs[])
{
	//*  Variable Declaration
	srand(time(0));
	int NodeCount = 50;
	int MCLoopCount = 1000;

	double GraphDensity = 0;
	double Path_Size = 0;
	double No_Paths = 0;
	double Path_Size_Sum = 0;
	double Path_Size_Average = 0;
	double Path_Size_Sum_MC = 0;
	double Path_Size_Average_MC = 0;
	
	//* Object Declaration

	ShortestPathAlgo Dijkstra = ShortestPathAlgo();

	//*  Main Code
		
	//Monte Carlo Run #1

	GraphDensity = 0.2;

	Graph Graph1 = Graph(NodeCount, GraphDensity);	

	//Graph1.Graph_FillGraph();
	//Graph1.Graph_ShowEdge();

	
	for (int i=0; i<MCLoopCount;i++)
	{
		
		Graph1.Graph_FillGraph();
		//Graph1.Graph_ShowEdge();

		cout << endl << endl;

		Path_Size = 0;
		No_Paths = 0;
		Path_Size_Sum = 0;
		Path_Size_Average = 0;
		
		for (int j=0; j<NodeCount;j++)
		{
			int source = 0;
			int destination = j;
		
			Path_Size = Dijkstra.ShortesPathAlgo_Path_Size(source, destination, Graph1);

			if(Path_Size == 0)
			{
				continue;
			}
			else
			{
				Path_Size_Sum += Path_Size;
				No_Paths += 1;
			}
		}

		Path_Size_Average = Path_Size_Sum/No_Paths;
		Path_Size_Sum_MC += Path_Size_Average;

	}
	
	Path_Size_Average_MC = Path_Size_Sum_MC/MCLoopCount;
	
	cout << "Monte Carlo Run #1: " << endl;
	cout << "Graph Size: " << NodeCount << endl;
	cout << "Graph Density: " << GraphDensity << endl;
	cout << "Number of Monte Carlo Runs: " << MCLoopCount << endl;
	cout << "Average Path Size: " << Path_Size_Average_MC << endl;

	cout << endl << endl;

	//Monte Carlo Run #2

	Path_Size_Sum_MC = 0;
	Path_Size_Average_MC = 0;

	GraphDensity = 0.4;

	Graph Graph2 = Graph(NodeCount, GraphDensity);	

	for (int i=0; i<MCLoopCount;i++)
	{
		
		Graph2.Graph_FillGraph();

		Path_Size = 0;
		No_Paths = 0;
		Path_Size_Sum = 0;
		Path_Size_Average = 0;
		
		for (int j=0; j<NodeCount;j++)
		{
			int source = 0;
			int destination = j;
		
			Path_Size = Dijkstra.ShortesPathAlgo_Path_Size(source, destination, Graph2);

			if(Path_Size == 0)
			{
				continue;
			}
			else
			{
				Path_Size_Sum += Path_Size;
				No_Paths += 1;
			}
		}

		Path_Size_Average = Path_Size_Sum/No_Paths;
		Path_Size_Sum_MC += Path_Size_Average;
			
	}

	Path_Size_Average_MC = Path_Size_Sum_MC/MCLoopCount;
	cout << "Monte Carlo Run #2: " << endl;
	cout << "Graph Size: " << NodeCount << endl;
	cout << "Graph Density: " << GraphDensity << endl;
	cout << "Number of Monte Carlo Runs: " << MCLoopCount << endl;
	cout << "Average Path Size: " << Path_Size_Average_MC << endl;


	//*  Program End
	//   - wait until user is ready before terminating program
	//   - to allow the user to see the program results

	cout << endl << endl;
	system("PAUSE");
	return 0;
}

