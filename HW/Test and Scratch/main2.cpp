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

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <time.h>

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

void FillGraph(int n, vector<vector<double>> & v, double d);
void ShowEdge(int n, vector<vector<double>> & v);


//***************************************************************************************************
//
//  Main Program Section
//
//***************************************************************************************************

int main(int nNumberofArgs, char* pszArgs[])
{
	//*  Variable Declaration
	srand(time(0));
	int nodes = 5;
	double density = 1.0;
	
	vector<vector<double>> testgraph (nodes, vector<double>(nodes));
	


	//*  Main Code
	FillGraph(nodes, testgraph, density);
	ShowEdge(nodes, testgraph);


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

void FillGraph(int n, vector<vector<double>> & v, double d)
{

	double randdensity;
	double randedgeweight;

	for (int i=0; i<n;i++)
	{
		for (int j=0;j<n;j++)
		{

			if(j == i)
			{
				continue;
			}

			if(v[i][j] > 0.0)
			{
				continue;
			}

			randdensity = ((double) rand()/(RAND_MAX+1));
			
			if (randdensity <= d)
			{
				
				randedgeweight = ((double) rand()/(RAND_MAX+1)) * 10;
				v[i][j] = randedgeweight;
				v[j][i] = randedgeweight;
								
			}
		
		}
	}

}

void ShowEdge(int n, vector<vector<double>> & v)
{

	vector<double>::iterator it;

	std::cout.precision(1);
	std::cout.setf( std::ios::fixed, std:: ios::floatfield);

	for (int i=0;i<n;i++)
	{
		for (it=v[i].begin(); it != v[i].end(); it++)
		{
			cout << *it << " ";
		}
		
		cout << endl;

	}
	
	return;

}