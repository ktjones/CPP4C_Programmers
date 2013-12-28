
//   (*) Convert this program to C++
//   (*) change to C++ io
//   (*) change to one line comments
//   (*) change defines of constants to const
//   (*) change array to vector<>
//   (n/a) inline any short function

#include <iostream>								// Header for IO functionality.
#include <vector>								// Header for Vector template class.

using namespace std;							// Using directive for Namespace STD.

void sum(int & p, int n, vector<int> & d);		// function prototype for SUM.  Arguments are references, as opposed to pointers, 
												// which simplifies the function code.

int main()
{

	const int N = 40;				// creates a CONST, called N, and sets its value to 40

	int accum = 0;					// creates INT variable ACCUM, sets equal to 0.
	vector<int> data(N);			// creates a VECTOR object called DATA, sets type to INT, size to N.
	
	for(int i = 0; i < N; ++i)		// FOR loop, initializes I in the loop header, I expires when loop does.
	{
		data[i] = i;				// Sets DATA element [i] to value of loop #.
	}
	
	sum(accum, N, data);			// calls function SUM.  Sends objects directly (as opposed to references or pointers).
    
	cout << "sum is: " << endl;		
	cout << accum;					// Displays accumulated SUM.
	
	cout << endl << endl;			// Adds some blank lines in prep for this 
	system("PAUSE");				// system call to keep the console window open.

	return 0;						

}

void sum(int & p, int n, vector<int> & d)
{
	
	p = 0;
	
	for(int i = 0; i < n; ++i)		// standard FOR loop, summing the values and placing them into P.
	{
		p = p + d[i];
	}

}

/*****************************************************************/

// ORIGINAL 'C' CODE

/*****************************************************************/

/*  Convert this program to C++
*   change to C++ io
*   change to one line comments
*   change defines of constants to const
*   change array to vector<>
*   inline any short function
*/

/*
#include <stdio.h>
#define N 40
void sum(int*p, int n, int d[])
{
  int i;
  *p = 0;
  for(i = 0; i < n; ++i)
     *p = *p + d[i];
}
int main()
{
   int i;
   int accum = 0;
   int data[N];
   for(i = 0; i < N; ++i)

      data[i] = i;

    sum(&accum, N, data);
    printf("sum is %d\n", accum);
	return 0;
}
*/

