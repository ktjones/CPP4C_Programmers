//**************************************************************
//
//  C++ Template - MST Header File
//
//**************************************************************

//**************************************************************
//
//  Definition Statements - Begin
//
//**************************************************************

#ifndef HEADER_MST_H_
#define HEADER_MST_H_

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
		void MST_Path(const Graph & g, int s=0, int c=0);
		double MST_Path_Size(const Graph & g, int s=0, int c=0);
		void MST_Show_Path();
		bool MST_Check_Vertices(int v);

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