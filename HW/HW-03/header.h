//**************************************************************
//
//  C++ Template - Header File
//
//**************************************************************

//**************************************************************
//
//  Definition Statements - Begin
//
//**************************************************************

#ifndef HEADER_H_
#define HEADER_H_

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
		
		int Gr_Nodes;
		bool Gr_Randomfill;
		double Gr_Density;
		vector<vector<pair<int,double>>> GraphAM;

	public:
		
		//Constructors
		Graph(int n = 0, double d = 0.2);
		Graph(bool rf, int n = 0, double d = 0.2);
		Graph(string & filename);
		~Graph();

		//Working methods
		int Graph_NoVertices();
		int Graph_NoEdges();
		void Graph_FillGraphRandomly();
		void Graph_FillGraphbyFile(string & fname);
		void Graph_FillGraphManually();
		bool Graph_Adjacent(int x, int y);
		void Graph_Neighbors(int x);
		void Graph_AddEdge(int x, int y, double weight);
		void Graph_DeleteEdge(int x, int y);
		double Graph_GetEdgeValue(int x, int y);
		void Graph_SetEdgeValue(int x, int y, double weight);

		//Friend functions & Classes
		friend class Dijkstra;
		friend class MST;

		//Future methods
		double Graph_GetNodeValue(int x);
		void Graph_SetNodeValue(int x, double weight);
		
		//My Methods
		void Graph_ShowEdge();
		
};

//*******************************
//
//  Class - Dijkstra Algo
//
//*******************************

class Dijkstra
{

	private:

		vector<int> Dj_Shortest_Path;
		double Dj_Shortest_Path_Size;
		
	public:
		
		//constructors
		Dijkstra();
		~Dijkstra();

		//Working Methods
		void Dijkstra_Path(int s, int d, const Graph & g);
		double Dijkstra_Path_Size(int s, int d, const Graph & g);
		void Dj_Show_Path();

		//Future Methods
		void Dijkstra_Vertices(Graph & g);
		
		//Overloaded Operators
		int operator() (const pair<int,double> & p1, const pair <int,double> & p2);

};

//*******************************
//
//  Class MST - Minimum Spanning Tree
//
//*******************************

class MST
{

	private:

		vector<pair<pair<int,int>,double>> MST_Shortest_Path;
		double MST_Shortest_Path_Size;
		
	public:
		
		//constructors
		MST();
		~MST();

		//Working Methods
		void MST_Path(int s, const Graph & g);
		void MST_Path(int s, const Graph & g, int c=1);
		double MST_Path_Size(int s, const Graph & g, int c=1);
		void MST_Show_Path();
		
		//Future Methods
		void MST_Vertices(Graph & g);
		
		//Overloaded Operators
		int operator() (const pair<pair<int,int>,double> & p1, const pair<pair<int,int>,double> & p2);

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