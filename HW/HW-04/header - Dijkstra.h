//**************************************************************
//
//  C++ Template - DIJKSTRA Header File
//
//**************************************************************

//**************************************************************
//
//  Definition Statements - Begin
//
//**************************************************************

#ifndef HEADER_DIJKSTRA_H_
#define HEADER_DIJKSTRA_H_

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
		void Dijkstra::Dj_Show_Path();

		//Future Methods
		void Dijkstra_Vertices(Graph & g);
		
		//Overloaded Operators
		int operator() (const pair<int,double> & p1, const pair <int,double> & p2);

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