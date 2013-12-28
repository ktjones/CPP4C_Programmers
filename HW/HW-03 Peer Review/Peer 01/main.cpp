#include<iostream>
#include<time.h>
#include<stdlib.h>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

static const int GRAPH_DENSITY = 40;

//structure to store adjacency list.
typedef struct node
{
	node *next;
	int data;
	int cost;
	node()
	{
		next = NULL;
		data = 0;
		cost = 0;
	}

	node(int data, int cost)
	{
		this->data = data;
		this->cost = cost;
		this->next = NULL;
	}
} NODE;

//structure to store path information in the form of triplets.
typedef struct edgeinfo
{
	int from;
	int to;
	int cost;
	edgeinfo()
	{
		this->from = 0;
		this->to = 0;
		this->cost = 0;
	}

	edgeinfo(int from, int to, int cost)
	{
		this->from = from;
		this->to = to;
		this->cost = cost;
	}
} edgeInfo;

class graph
{
private:
	//Adjacency list 
	vector<NODE*> adjList;

	//number of vertices.
	int v;

	//number of edges.
	int e;

public:

	//default constructor.
	graph()
	{
		adjList.empty();
		this->v = 0;
		this->e = 0;
	}

	//constructor initializing the graph with number of vertices and edges.
	graph(int v, int e)
	{
		adjList.resize(v);
		this->v = v;
		this->e = e;
		for (int i = 0; i < v; ++i)
		{
			NODE * temp = new NODE(i, 0);
			adjList[i] = temp;
		}
	}

	//constructor initializing the adjacency matrix using filename
	//file should have information in the form - first line should be number of vertices
	//all the other lines containing path infomarion in the form of - to,from,cost
	graph(string filename)
	{
		ifstream myfile;
		myfile.open(filename);

		//read the number of vertices in the graph.
		myfile>>v;
		adjList.resize(v);
		this->e = 0;

		//allocate memory for nodes.
		for (int i = 0; i < v; ++i)
		{
			NODE * temp = new NODE(i, 0);
			adjList[i] = temp;
		}

		//Fill the adjacency list using the information on the file.
		while(!myfile.eof())
		{
			int from;
			int to;
			int cost;
			myfile>>from;
			myfile>>to;
			myfile>>cost;
			insertEdge(from, to, cost);
			this->e++;
		}
		myfile.close();
	}

	~graph()
	{
		for (int i = 0; i < adjList.size(); ++i)
		{
			NODE * temp = adjList[i];

			while (temp != NULL)
			{
				NODE * cur = temp;
				temp = temp->next;
				delete cur;
			}
		}
		adjList.clear();
	}

	//Return number of edges.
	int V()
	{
		return v;
	}

	//Return number of edges.
	int E()
	{
		return e;
	}

	//Returns list of all out going nodes and cost.
	NODE * getListOfOutNodes (int from)
	{
		return adjList[from];
	}

	//Check whether a particular node is adjacent to node
	int adjacent (int nodeFromo, int nodeTo)
	{
		NODE * iter = adjList[nodeFromo];
		while (iter != NULL && iter->data != nodeTo)
			iter = iter->next;
		if (iter->data == nodeTo)
		{
			return true;
		}
		return false;
	}

	int getCostOfEdge(int nodeFromo, int nodeTo)
	{
		NODE * iter = adjList[nodeFromo];
		while (iter != NULL && iter->data != nodeTo)
			iter = iter->next;
		if ((iter != NULL) && (iter->data == nodeTo))
		{
			return iter->cost;
		}
		return 0;
	}

	//Insert edge from the vertex to edge of the cost.
	void insertEdge(int from, int to, int cost)
	{
		NODE *temp = new NODE(to, cost);
		NODE *iter = adjList[from];

		while (iter->next != NULL)
			iter = iter->next;
		iter->next = temp;
	}

	//generate the random graph based on density.
	void generategraph(int density);
};

//generate the random graph based on density.
void graph::generategraph(int density)
{
	srand(time(0));
	for (int i = 0; i < v; ++i)
	{
		for (int j = 0; j < e; ++j)
		{
			if (i != j)
			{
				if ((rand() % 100) < density)
				{
					int cost = rand() % 100;
					insertEdge(i, j, cost);
					cout<<"from :"<<i<<" to : "<<j<<" cost : "<<cost<<endl;
				}
			}
		}
	}
}

//class which contains methods and data for finding a Minimum spanning tree of a graph
//Graph should contain vertices as adjacency list.
class MST
{
private:
	graph * G;
	vector<edgeInfo> pathInfo;
	vector<edgeInfo> result;
	vector<bool> bPathInfo;
	vector<int> vertices;
public:
	MST()
	{
		G = NULL;
		pathInfo.resize(0);
		bPathInfo.resize(0);
	}

	MST(graph * g)
	{
		this->G = g; 
		bPathInfo.resize(g->V());
		vertices.resize(g->V());
		result.resize(G->V() - 1);
	}

	~MST()
	{
		pathInfo.clear();
		bPathInfo.clear();
		result.clear();
		G = NULL;
	}

	//Method to find out which edge should be picked next. 
	int processToEdges(int from, vector<int> vertices);
	
	//Get all the outgoing nodes in the form of triplets in edgeInfo
	vector<edgeInfo> pathInfoFrom(int from);

	// Given a graph containing vertices and path information in terms of adjacency matrix
	// find out the Minimun Spanning Tree using Prims algorithm.
	void findMSTUsingPRIMS();

	//Print the Minimum spanning Tree
	void printMST();
};

void MST::printMST()
{
	int i = 0, j = 0;
	int totalCost = 0;
	ofstream myfile;
	myfile.open ("example.txt");
	

	myfile << "The resulting MST :" << endl;
	
	while (i < (result.size()))
	{
		int cost = G->getCostOfEdge(result[i].from,result[i].to);
		totalCost += cost;
		myfile<<"from : " << result[i].from << " to : " << result[i].to << " cost : " << cost <<endl;
		++i;
	}
	myfile << "Total cost of the tree : "<<totalCost;
	myfile.close();
}

// Given a graph containing vertices and path information in terms of adjacency matrix
// find out the Minimum Spanning Tree using Prims algorithm.
void MST::findMSTUsingPRIMS()
{
	vector<int> edges;
	vector<int> possibleEdges;
	int numVertices = 0;
	//start with vertex zero.
	int vertex = 0;
	int from = 0;
	vertices[numVertices++] = vertex;
	while (numVertices < (G->V()))
	{
		vertex = processToEdges(vertex, vertices);

		if (vertex != 0)
		{
			vertices[numVertices] = vertex;
			numVertices++;
		}
	}
	vertices.resize(numVertices - 1);
}

//Method to find out which edge should be picked next. 
vector<edgeInfo> MST::pathInfoFrom(int from)
{
	NODE * iter = G->getListOfOutNodes (from);
	vector<edgeInfo> ret(100);
	iter = iter->next;
	int size = 0;
	while(iter != NULL)
	{
		edgeInfo a = edgeInfo(from,iter->data, iter->cost);
		ret[size] = a;
		iter = iter->next;
		size++;
	}
	ret.resize(size);
	return ret;
}

//Method to find out which edge should be picked next. 
int MST::processToEdges(int from, vector<int> vertices)
{
	vector<edgeInfo> tempPathInfo;
	int minVal = INT_MAX;
	int minIndex = 0;
	int numEdges = 0;
	static int res = 0;
	
	//Get information about all the adjacent nodes of vertex - from.
	if (!bPathInfo[from])
	{
		tempPathInfo = pathInfoFrom(from);
		bPathInfo[from] = true;
	}


	if (pathInfo.size() == 0)
	{
		//Find the next vertex which is nearest to open set.
		for (int i = 0; i < tempPathInfo.size();++i)
		{
			if (minVal > tempPathInfo[i].cost)
			{
				minIndex = i;
				minVal = tempPathInfo[i].cost;
			}
			pathInfo.push_back(tempPathInfo[i]);
		}

		result[res++] = pathInfo[minIndex];
		//resetting cost value so that it wont be considered again.
		pathInfo[minIndex].cost = INT_MAX;
		//resetting cost value so that it wont be considered again.
		return pathInfo[minIndex].to;
	} 
	else
	{
		//Push all the node info got from graph for a particular.
		for (int i = 0;i < tempPathInfo.size(); ++i)
		{
			pathInfo.push_back(tempPathInfo[i]);
		}

		//Find the next vertex which is nearest to open set.
		for (int i = 0; i < pathInfo.size();++i)
		{
			if (pathInfo[i].cost < minVal)
			{
				if (find(vertices.begin(),vertices.end(), pathInfo[i].to) == vertices.end())
				{
					minIndex = i;
					minVal = pathInfo[i].cost;
				}
			}
		}

		result[res++] = pathInfo[minIndex];

		//resetting cost value so that it wont be considered again.
		pathInfo[minIndex].cost = INT_MAX;

		//Return the vertex which is nearest any vertex in the open set.
		return pathInfo[minIndex].to;
	}
}

//starting point of our execution.
int main()
{
	graph * g = new graph("test.txt");
	MST * m = new MST(g);
	m->findMSTUsingPRIMS();
	m->printMST();

	cout << endl << endl;

	system("PAUSE");
	return 0;
}
