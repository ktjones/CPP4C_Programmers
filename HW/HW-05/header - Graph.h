//**************************************************************
//
//  C++ Template - GRAPH Header File
//
//**************************************************************

//**************************************************************
//
//  Definition Statements - Begin
//
//**************************************************************

#ifndef HEADER_GRAPH_H_
#define HEADER_GRAPH_H_

#include <iostream>
#include <vector>
#include <string>

using namespace std;

//**************************************************************
//
//  Code Body - Begin
//
//**************************************************************

//*******************************
//
//  Graph Class
//	- Implemented as Adjacency Matrix
//
//*******************************

class Graph
{
	private:
		
		//Standard Variables
		int Gr_Nodes;
		bool Gr_Randomfill;
		double Gr_Density;

		//Objects
		vector<vector<pair<int,double>>> GraphAM;
				
	public:
		
		//Constructors & Destructors
		Graph(int n = 0, double d = 0.2);
		Graph(bool rf, int n = 0, double d = 0.2);
		Graph(string & filename);
		~Graph();

		//Fill Methods
		void Graph_FillGraphRandomly();
		void Graph_FillGraphbyFile(string & fname);
		void Graph_FillGraphManually();
		
		//Working methods
		int Graph_NoVertices();
		int Graph_NoEdges();
		bool Graph_Adjacent(int x, int y, int c=0);
		void Graph_Neighbors(int x, int c=0);
		void Graph_AddEdge(int x, int y, double weight, int c=0);
		void Graph_DeleteEdge(int x, int y);
		double Graph_GetEdgeValue(int x, int y);
		int Graph_GetEdgeColor(int x, int y);
		void Graph_SetEdgeValue(int x, int y, double weight);
		void Graph_SetEdgeColor(int x, int y, int c);
		double Graph_GetNodeValue(int x);
		int Graph_GetNodeColor(int x);
		void Graph_SetNodeValue(int x, double weight);
		void Graph_SetNodeColor(int x, int c);

		//Friend functions & Classes
		friend class Dijkstra;
		friend class MST;

		//My Methods
		void Graph_ShowEdge();
		
};

//**************************************************************
//
//  Code Body - End
//
//**************************************************************

//**************************************************************
//
//  Definition Statements - End
//
//**************************************************************

#endif