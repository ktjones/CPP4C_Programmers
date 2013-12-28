//***************************************************************************************************
//
//  C++ Template Program
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
//  Global Variable Declaration
//
//********************************





//********************************
//
//  Compound Type Declaration Section
//
//********************************





//********************************
//
//  Function Declaration Section
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
	int NodeCount = 6;
	double GraphDensity = 0.2;
	GraphMatrixADT GraphM = GraphMatrixADT(NodeCount, GraphDensity);

	//*  Main Code
	
	//GraphM.GraphMatrixADT_FillGraph();
	GraphM.GraphMatrixADT_ManualCreateGraph();
	GraphM.GraphMatrixADT_ShowEdge();
	
	cout << endl << endl;

	
	ShortestPathAlgo Dijkstra = ShortestPathAlgo();
	
	int source = 0;
	int destination = 4;
	Dijkstra.ShortestPathAlgo_Calc(source, destination, GraphM);
		
	//*  Program End
	//   - wait until user is ready before terminating program
	//   - to allow the user to see the program results

	cout << endl << endl;
	system("PAUSE");
	return 0;
}

//***************************************************************************************************
//
//  Functions Begin Here
//
//***************************************************************************************************

//********************************
//
//	Function #1
//

    //*  Variable Declaration

	//*  Main Code

	//*  Program End

//********************************
