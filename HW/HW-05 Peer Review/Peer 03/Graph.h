//
//	Graph.h
//
//	Created on: Nov 6, 2013
//		Author: JFM
//
//	This class is meant to manage a graph directed/undirected
//

#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector> // This line allows us to use vector class
#include <iostream>
#include <fstream> // This line allows us to use input/output files

using namespace std;

enum Graph_Colors{RED, BLUE, GREEN, YELLOW, CYAN, MAGENTA, BLACK, WHITE};

template <class ValuesType> // We include that, because we want nodes and edges values to be declared by the user
class Graph{
public:
	// The constructor of the class, we set the parameters of the graph to its inital values.
	Graph();
	
	// This method retrieves a list of nodes, in terms of row and column that have some value
	vector<int> get_nodes_by_value(ValuesType search_value);

	// This method copies the graph to some other graph
	void copy_graph(Graph<ValuesType> &Target);

	// This method reads a graph from a file
	bool read_graph_from_file(string file);

	// once we have constructed the graph, we set the number of nodes
	void set_nodes_number(int n_nodes);

	// The user is allowed to toggle off the auto shape function
	inline void Enable_Auto_Shape_Graph(bool enable){
		auto_Graph_Shape=enable;
		if (enable) {
			if (edges_number<max_edges_number/2) {
				if (Graph_Matrix) matrix_to_list();
			};
			if (edges_number>max_edges_number/2) {
				if (!Graph_Matrix) list_to_matrix();
			};
		}; 
	};

	inline bool get_Auto_Shape_Graph_Status(){return auto_Graph_Shape;};

	// If the user wants to, the graph will have a Matrix shape
	inline void Set_Graph_Shape_Matrix(){
		auto_Graph_Shape=false;
		if (!Graph_Matrix) list_to_matrix();
	};

	// If the user wants to, the graph will have a List shape
	inline void Set_Graph_Shape_List(){
		auto_Graph_Shape=false;
		if (Graph_Matrix) matrix_to_list();
	};

	inline bool get_Graph_Shape_Matrix_Status(){return Graph_Matrix;};

	// Graph can be Weithed or Unweithed
	inline void Enable_Graph_Weighted(bool enable){Graph_Weighted = enable;};

	inline bool get_Graph_Weighted_Status(){return Graph_Weighted;};

	// Graph can be Directed or Undirected
	inline void Enable_Graph_Directed(bool enable){Graph_Directed = enable;};

	inline bool get_Graph_Directed_Status(){return Graph_Directed;};

	// There are some parameters, that the user has access to
	inline int get_nodes_number(){return nodes_number;};

	inline int get_edges_number(){return edges_number;};

	// When we are using a graph, maybe we want to number the nodes, or maybe we want to put a char on each node
	// Examples: "City 1", 1, 1.0, ...
	inline bool set_node_value(int node, ValuesType value){ if(node>nodes_number-1) return false;nodes[node]=value; return true;};

	inline ValuesType get_node_value(int node){ if(node>nodes_number-1) return 0; return nodes[node];};

	// The same as was stated above is valid for edges, may be we want an edge "Route 66"
	bool set_edge_value(int node_from, int node_to, ValuesType value);

	inline ValuesType get_edge_value(int node_from, int node_to){ 
		if(!adjacent(node_from,node_to)) return 0;
		int position = edge_position_in_list(node_from, node_to);
		
		return edges[position];
	};

	// We must add edges to the graph
	inline bool add_edge(int node_from, int node_to, double distance = 1.0){

		if (node_from > nodes_number-1) return false;
		if (node_to > nodes_number-1) return false;

		if (distance < 0) return false; 

		// Importan issue: Nodes must be within the node list, and distances are positive. Otherwise, we get a false.

		edge_addition(node_from, node_to,distance); // This function is private, we will see it later

		// If we have an undirected graph, the edge is the same forward and backward
		if (!Graph_Directed) edge_addition(node_to, node_from, distance);

		// If the auto_graph is activated, we study the possibility of changing the graph shape
		if (auto_Graph_Shape) {
			if (edges_number>max_edges_number/2) {
				if (!Graph_Matrix) list_to_matrix();
			};
		};

		return true;

	};

	//Sometimes edges go out of our world
	inline bool remove_edge(int node_from, int node_to){

		if (node_from > nodes_number-1) return false;
		if (node_to > nodes_number-1) return false;

		if (!adjacent(node_from,node_to)) return false;

		edge_removal(node_from,node_to); // This function is private, we will see it later

		// Same as add_edge
		if (!Graph_Directed) edge_removal(node_to, node_from);

		if (auto_Graph_Shape) {
			if (edges_number<max_edges_number/2) {
				if (Graph_Matrix) matrix_to_list();
			};
		};

		return true;

	};

	double get_distance(int node_from, int node_to);

	// This function give the user a false if two nodes are not connected, and a true if they are so
	bool adjacent(int node_from, int node_to);

	// When we want to know which nodes are connected to one specific node, this is the propper function
	vector<int> neighbors(int node_from);

	// We can set wich Algorithm is going to be used at MST calculation
	inline void set_Prim_MST_Algorithm(){Prim_MST = true;};

	inline void set_Kruskal_MST_Algorithm(){Prim_MST = false;};

	// This function outputs a true for Prim and false for Kruskal
	inline bool get_Prim_or_Kruskal_MST_Algorithm(){return Prim_MST;};

private:

	// When we reset a graph we erase everything that is inside it.
	inline void StartGraph(){

		if (auto_Graph_Shape) Graph_Matrix = false;

		nodes_number = 0;
		edges_number = 0;
		max_edges_number = 0;

		nodes.resize(0);
		edges.resize(0);
		nodes_connections.resize(0);
		nodes_index.resize(0);
		distances.resize(0);

		Graph_Started = false;
	};

	// We call this function to add an edge
	void edge_addition(int node_from, int node_to, double distance);

	// its not really different from edge addition
	void edge_removal(int node_from, int node_to);

	// this function changes the shape of the graph from list to matrix
	void list_to_matrix();

	// this function changes the shape of the graph from matrix to list
	void matrix_to_list();

	// When we create a Matrix, we must ensure that at time = 0 the matrix is empty
	void clear_Matrix( vector<ValuesType> &edges_v, vector<int> &node_connections_v, vector<double> &distance_v);

	// Depending on the shape, we can look for a edge inside our vectors
	int edge_position_in_list(int node_from, int node_to);

	// When we are using a list graph this function is helpfull for knowing the upper limit of one node list within our vector
	inline int upper_limit_node_index(int node){
		if (node == nodes_number-1) {
			return edges_number;
		}
		else{
			return nodes_index[node+1];
		}
	};

	int nodes_number; // number of nodes
	int edges_number; // number of edges

	vector<ValuesType> nodes; // value of each node
	vector<ValuesType> edges; // value of each edge
	vector<int> nodes_connections; // the vector where we note the connections of each node
	vector<int> nodes_index; // the list that contains the number of connections that have each node
	vector<double> distances;// distances of each edge

	// There are also some parameters that set up the graph, and help to decide the shape if auto mode is on
	int max_edges_number;

	bool auto_Graph_Shape;
	bool Graph_Matrix;
	bool Graph_Directed;
	bool Graph_Weighted;

	bool Prim_MST;

	bool Graph_Started;

};

#endif // GRAPH_H_ 
