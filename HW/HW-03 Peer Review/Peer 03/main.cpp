// C++ program for Prim's Minimum Spanning Tree (MST) algorithm. 
 
#include <iostream>
#include <limits.h>
#include <fstream>
#include <cstdlib>
//#include <Windows.h>

using namespace std;
 
// Number of vertices in the graph
const int V = 20;

class Graph {
public:
	Graph() {
		numVertex = V;
		gDensity = 0;
		maxEdist = 0;
		numEdge = 0;
		AGraph = new int*[V];
        for (int i=0; i<V; i++)
			AGraph[i] = new int[V];
	}
	Graph(string filename){
		gDensity = 0;
		maxEdist = 0;
		numEdge = 0;
		AGraph = new int*[V];
        for (int i=0; i<V; i++)
			AGraph[i] = new int[V];
		for (int i = 0; i < V; i++)
			for (int j = 0; j < V; j++)
				AGraph[i][j] = INT_MAX;
		ifstream myfile;
		myfile.open(filename);
		if(!myfile) { // file could not be opened
			cerr << "Error: file could not be opened" << endl;
			exit(1);
		}
		myfile >> numVertex;
		//cout << "numvertex = " << numVertex;
		int a, b, c;
		while (!myfile.eof()) {
			myfile >> a >> b >> c;
			AGraph[a][b] = c;
			//cout << "line is " << a << b << c << endl;
		}
		for (int i = 0; i < V; i++)
			AGraph[i][i] = 0;
		/*
		for (int i = 0; i < V; i++) {
		cout << "\n" ;
		for (int j = 0; j < V; j++)
			cout << AGraph[i][j] << "\t";
		}
		*/
	}
	

	int Get(int i, int j) {
		return AGraph[i][j];
	}
	~Graph() {
		for (int i = 0; i < V; i++)
			delete [] AGraph[i];
		delete [] AGraph;
	}
private:
	int **AGraph;
	double gDensity;
	int maxEdist;
	int numVertex;
	int numEdge;

};

 
// A utility function to find the vertex with minimum key value, from
// the set of vertices not yet included in MST
int minKey(int key[], bool mstSet[])
{
   // Initialize min value
   int min = INT_MAX, min_index;
 
   for (int v = 0; v < V; v++)
     if (mstSet[v] == false && key[v] < min)
         min = key[v], min_index = v;
 
   return min_index;
}
 
// A utility function to print the constructed MST stored in parent[]
int printMST(int parent[], int n, Graph PP)
{
   cout << "Edge \tWeight" << endl;
   for (int i = 1; i < V; i++)
      cout << parent[i] << "-" <<  i << " \t" << PP.Get(i,parent[i]) << endl;
   return 0;
}
 
// Function to construct and print MST for a graph represented using adjacency
// matrix representation
void primMST(Graph PP)
{
     int parent[V]; // Array to store constructed MST
     int key[V];   // Key values used to pick minimum weight edge in cut
     bool mstSet[V];  // To represent set of vertices not yet included in MST
 
     // Initialize all keys as INFINITE
     for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;
 
     // Always include first 1st vertex in MST.
     key[0] = 0;     // Make key 0 so that this vertex is picked as first vertex
     parent[0] = -1; // First node is always root of MST 
 
     // The MST will have V vertices
     for (int count = 0; count < V-1; count++)
     {
        // Pick thd minimum key vertex from the set of vertices
        // not yet included in MST
        int u = minKey(key, mstSet);
 
        // Add the picked vertex to the MST Set
        mstSet[u] = true;
 
        // Update key value and parent index of the adjacent vertices of
        // the picked vertex. Consider only those vertices which are not yet
        // included in MST
        for (int v = 0; v < V; v++)
 
           // AGraph[u][v] is non zero only for adjacent vertices of m
           // mstSet[v] is false for vertices not yet included in MST
           // Update the key only if AGraph[u][v] is smaller than key[v]
          if (PP.Get(u,v) && mstSet[v] == false && PP.Get(u,v) <  key[v])
             parent[v]  = u, key[v] = PP.Get(u,v);
     }
 
     // print the constructed MST
     printMST(parent, V, PP);
}
 // driver program to test above function
int main()
{
	//SetCurrentDirectoryA( "C:\\Users\\Renato\\" );
	Graph PP("sample1.dat");
	primMST(PP); 
    return 0;
}