//
//	Graph.cpp
//
//	Created on: Nov 6, 2013
//		Author: JFM
//
//	This class is meant to manage a graph 
//

#include "Graph.h"

template <class ValuesType> // We include that, because we want nodes and edges values to be declared by the user
// The constructor of the class, we set the parameters of the graph to its inital values.
Graph<ValuesType>::Graph(){auto_Graph_Shape = true; Graph_Directed = false; Graph_Weighted = true;StartGraph();}

template Graph<int>::Graph();
template Graph<char*>::Graph();

template <class ValuesType> // We include that, because we want nodes and edges values to be declared by the user
// This method retrieves a list of nodes, in terms of row and column that have some value
vector<int> Graph<ValuesType>::get_nodes_by_value(ValuesType search_value){
	
	vector<int> fund_node_list(0);
	
	for (int i = 0; i<nodes_number; ++i){
		if (nodes[i] == search_value){fund_node_list.push_back(i);};
	};

	return fund_node_list;
};

template vector<int> Graph<int>::get_nodes_by_value(int);
template vector<int> Graph<char*>::get_nodes_by_value(char*);

template <class ValuesType> // We include that, because we want nodes and edges values to be declared by the user
// This method copies the graph to some other graph
void Graph<ValuesType>::copy_graph(Graph<ValuesType> &Target){
	Target.set_nodes_number(nodes_number);
	if (Graph_Matrix){
		Target.Set_Graph_Shape_Matrix();
	}
	else{Target.Set_Graph_Shape_List();
	};

	Target.Enable_Graph_Directed(Graph_Directed);
	Target.Enable_Graph_Weighted(Graph_Weighted);

	for (int i = 0; i < nodes_number; ++i){Target.set_node_value(i,nodes[i]);};
	for (int i = 0; i < edges_number; ++i){
		for (int j = 0; j < i; ++j){
			if (adjacent(i,j)){
				Target.add_edge(i,j,get_distance(i,j));Target.set_edge_value(i,j,get_edge_value(i,j));
			};
		};
		for (int j = i+1; j < edges_number; ++j){
			if (adjacent(i,j)){
				Target.add_edge(i,j,get_distance(i,j));Target.set_edge_value(i,j,get_edge_value(i,j));
			};
		};
	};
};

template void Graph<int>::copy_graph(Graph<int> &);
template void Graph<char*>::copy_graph(Graph<char*> &);

template <class ValuesType> // We include that, because we want nodes and edges values to be declared by the user
// This function reads a graph from a file
bool Graph<ValuesType>::read_graph_from_file(string file_name){
	
	// We open the file
	ifstream input_file;

	input_file.open(file_name);

	if (input_file.is_open()){
		int number_of_nodes;
		int node_from;
		int node_to;
		double cost;

		// First number is the number of nodes
		input_file >> number_of_nodes;

		set_nodes_number(number_of_nodes);
		Enable_Graph_Weighted(true);

		// As the graph file is containing all the possible edges, not only the half, we set the graph Directed
		// parameter to false, because even if it is directed, we will read all the edges
		Enable_Graph_Directed(false);

		// Until the file has ended, we read from, to and cost/distance
		while( ! input_file.eof() ){
			input_file >> node_from;
			input_file >> node_to;
			input_file >> cost;

			add_edge(node_from,node_to,cost);

		};

		input_file.close();
		return true;
	};
			
	return false;
};

template bool Graph<int>::read_graph_from_file(string);
template bool Graph<char*>::read_graph_from_file(string);

template <class ValuesType> // We include that, because we want nodes and edges values to be declared by the user
// once we have constructed the graph, we set the number of nodes
void Graph<ValuesType>::set_nodes_number(int n_nodes){
		
	// we can change the number of nodes, but we must be aware, everything will be destroyed!!!
	if (Graph_Started) StartGraph();
		
	nodes_number = n_nodes; 
	nodes.resize(nodes_number);
	for (int i = 0; i<nodes_number;	++i) nodes[i] = static_cast<ValuesType>(0);

	max_edges_number = nodes_number*(nodes_number-1); // this number is important in order to know whether the graph is sparse or dense

	// even we have an algorithm that determines the shape of the graph, the user is allowed to change it by him/herself
	if (auto_Graph_Shape) Graph_Matrix = false;	

	nodes_index.resize(nodes_number);

	if (Graph_Matrix) {

		// When we have a Matrix, we have a completed set of vectors, the advantages, is that they will not grow or decrease,
		// but in the other hand they will use more memory. Our solution: let the program choose the one wich is better fitted for your graph
		edges.resize(nodes_number*nodes_number);
		nodes_connections.resize(nodes_number*nodes_number);
			
		for (int i = 0; i<nodes_number;++i) nodes_index[i]=nodes_number*i;

		distances.resize(nodes_number*nodes_number);
		clear_Matrix(edges, nodes_connections, distances);
	}
	else {

		// Here we have a list distribution, so in the very beginning, no edge will exist!!
		for (int i = 0; i<nodes_number;++i) nodes_index[i]=0;

	}
}

template void Graph<int>::set_nodes_number(int);
template void Graph<char*>::set_nodes_number(int);

template <class ValuesType> // We include that, because we want nodes and edges values to be declared by the user
// The same as was stated above is valid for edges, may be we want an edge "Route 66"
bool Graph<ValuesType>::set_edge_value(int node_from, int node_to, ValuesType value){ 
	if(!adjacent(node_from,node_to)) return false;
	if(!Graph_Directed) if(!adjacent(node_to, node_from)) return false;

	// This is quite important, for setting a value on an edge, it must exists. If it doesn't the program will give
	// the user a false as a result. Also, we must know where is settled our edge within our vector.

	int position = edge_position_in_list(node_from, node_to);
		
	edges[position] = value;

	// If we have an undirected graph, it is logical to think that the edge in the back has the same value.
	if(!Graph_Directed) {
		position = edge_position_in_list(node_to, node_from);
		edges[position] = value;
	}
		
	return true;
};

template bool Graph<int>::set_edge_value(int, int, int);
template bool Graph<char*>::set_edge_value(int, int, char*);

template <class ValuesType> // We include that, because we want nodes and edges values to be declared by the user
double Graph<ValuesType>::get_distance(int node_from, int node_to){

	// we have two ways to look for distances, depending on the shape of the graph
	if (Graph_Matrix){
		return distances[node_from*nodes_number + node_to];
	}
	else{
		int upper_limit = upper_limit_node_index(node_from);

		for (int i = nodes_index[node_from]; i < upper_limit; ++i) {
			if (nodes_connections[i] == node_to) return distances[i];
		};
	}
		
	// If look for the distance between two nodes that are not connected we get a 0, it is recommended to check previosly that
	// those nodes are adjacent!
	return 0.0;
};

template double Graph<int>::get_distance(int, int);
template double Graph<char*>::get_distance(int, int);

template <class ValuesType> // We include that, because we want nodes and edges values to be declared by the user
// This function give the user a false if two nodes are not connected, and a true if they are so
bool Graph<ValuesType>::adjacent(int node_from, int node_to){

	if (Graph_Matrix){
		if (nodes_connections[node_from*nodes_number + node_to] == 1) {
			return true;
		}
		else {
			return false;
		}
	}
	else{
		bool returning_value = false;
		int upper_limit = upper_limit_node_index(node_from);

		for (int i = nodes_index[node_from]; i < upper_limit; ++i) {
			if (nodes_connections[i] == node_to) returning_value = true;
		};

		return returning_value;
	};
};

template bool Graph<int>::adjacent(int, int);
template bool Graph<char*>::adjacent(int, int);

template <class ValuesType> // We include that, because we want nodes and edges values to be declared by the user
// When we want to know which nodes are connected to one specific node, this is the propper function
vector<int> Graph<ValuesType>::neighbors(int node_from){

	vector<int>nodes_neighbors;

	// In a matrix graph, we look the row of the matrix and look for ones
	if (Graph_Matrix){
		for (int i = 0; i<nodes_number; ++i) 
			if (nodes_connections[nodes_number*node_from + i] == 1) nodes_neighbors.push_back(i);
	}
	// while in a list graph, we directly copy the list associated with the node of study
	else{
		for (int i = nodes_index[node_from]; i<upper_limit_node_index(node_from); ++i)
			nodes_neighbors.push_back(nodes_connections[i]);
	}

	return nodes_neighbors;
};

template vector<int> Graph<int>::neighbors(int);
template vector<int> Graph<char*>::neighbors(int);

template <class ValuesType> // We include that, because we want nodes and edges values to be declared by the user
// We call this function to add an edge
void Graph<ValuesType>::edge_addition(int node_from, int node_to, double distance){
		
	// In a matrix graph we put a '1' and the distance in the propper place
	if (Graph_Matrix){
		nodes_connections[node_from*nodes_number + node_to] = 1;
		if (Graph_Weighted){
			distances[node_from*nodes_number + node_to] = distance;
		}
		else{
			distances[node_from*nodes_number + node_to] = 1.0;
		}
		edges_number+=1;
	}
	// While in a list graph we must increase the vectors accordingly to the edge we are adding
	else{
			
		int position = edge_position_in_list(node_from, node_to);
		vector<ValuesType>::iterator position_eit;
		vector<int>::iterator position_it;
		vector<double>::iterator position_dit;

		if (adjacent(node_from,node_to)){
			// Maybe we want to change some edge distance, in this case, vectors must not be increased
			if (Graph_Weighted){
				distances[position] = distance;
			}
			else{
				distances[position] = 1.0;
			}
		}
		else{
			position_eit = edges.insert(edges.begin() + position,static_cast<ValuesType>(0));
			position_it = nodes_connections.insert(nodes_connections.begin() + position, node_to);
			if (Graph_Weighted){
				position_dit = distances.insert(distances.begin() + position, distance);
			}
			else{
				position_dit = distances.insert(distances.begin() + position, 1.0);
			}
			edges_number +=1;
			// The program needs to know where a node list begin inside the node, here we tell the program
			if (node_from < nodes_number-1) for(int i = node_from + 1; i<nodes_number; ++i) nodes_index[i] += 1;
		}
	}
};

template void Graph<int>::edge_addition(int, int, double);
template void Graph<char*>::edge_addition(int, int, double);

template <class ValuesType> // We include that, because we want nodes and edges values to be declared by the user
// its not really different from edge addition
void Graph<ValuesType>::edge_removal(int node_from, int node_to){
		
	if (Graph_Matrix){
		nodes_connections[node_from*nodes_number + node_to] = 0;
		distances[node_from*nodes_number + node_to] = 0.0;
			
		edges_number-=1;
	}
	else{
			
		int position = edge_position_in_list(node_from, node_to);
			
		edges.erase(edges.begin()+position);
		nodes_connections.erase(nodes_connections.begin()+position);
		distances.erase(distances.begin()+position);

		edges_number-=1;

		if (node_from < nodes_number-1) for(int i = node_from + 1; i<nodes_number; ++i) nodes_index[i] -= 1;
	}
};

template void Graph<int>::edge_removal(int, int);
template void Graph<char*>::edge_removal(int, int);

template <class ValuesType> // We include that, because we want nodes and edges values to be declared by the user
// this function changes the shape of the graph from list to matrix
void Graph<ValuesType>::list_to_matrix(){
	vector<ValuesType> temp_edges(nodes_number*nodes_number);
	vector<int> temp_nodes_connections(nodes_number*nodes_number);
	vector<double> temp_distances(nodes_number*nodes_number);
	int upper_limit;

	clear_Matrix(temp_edges, temp_nodes_connections, temp_distances);

	for (int i = 0; i<nodes_number;++i) {
		upper_limit = upper_limit_node_index(i);
		for (int j = nodes_index[i]; j<upper_limit; ++j){
			temp_edges[nodes_number*i+nodes_connections[j]] = edges[j];
			temp_nodes_connections[nodes_number*i+nodes_connections[j]] = 1;
			temp_distances[nodes_number*i+nodes_connections[j]] = distances[j];
		};
		nodes_index[i] = nodes_number*i;
	};

	edges.assign(temp_edges.begin(), temp_edges.end());
	nodes_connections.assign(temp_nodes_connections.begin(), temp_nodes_connections.end());
	distances.assign(temp_distances.begin(), temp_distances.end());

	Graph_Matrix = true;
};

template void Graph<int>::list_to_matrix();
template void Graph<char*>::list_to_matrix();

template <class ValuesType> // We include that, because we want nodes and edges values to be declared by the user
// this function changes the shape of the graph from matrix to list
void Graph<ValuesType>::matrix_to_list(){
	vector<ValuesType> temp_edges(edges_number);
	vector<int> temp_nodes_connections(edges_number);
	vector<double> temp_distances(edges_number);
	int position = 0;

	for (int i = 0; i < nodes_number; ++i){
		nodes_index[i] = position;
		for(int j = 0; j < nodes_number; ++j){
			if (nodes_connections[nodes_number*i + j] == 1) {
				temp_edges[position] = edges[nodes_number*i+j];
				temp_nodes_connections[position] = j;
				temp_distances[position] = distances[nodes_number*i+j];
				position += 1;
			};
		};
	};

	edges.resize(edges_number);
	nodes_connections.resize(edges_number);
	distances.resize(edges_number);

	edges.assign(temp_edges.begin(), temp_edges.end());
	nodes_connections.assign(temp_nodes_connections.begin(), temp_nodes_connections.end());
	distances.assign(temp_distances.begin(), temp_distances.end());

	Graph_Matrix = false;
};

template void Graph<int>::matrix_to_list();
template void Graph<char*>::matrix_to_list();

template <class ValuesType> // We include that, because we want nodes and edges values to be declared by the user
// When we create a Matrix, we must ensure that at time = 0 the matrix is empty
void Graph<ValuesType>::clear_Matrix( vector<ValuesType> &edges_v, vector<int> &node_connections_v, vector<double> &distance_v){
	for (int i = 0; i<nodes_number; ++i){
		for (int j = 0; j<nodes_number; ++j){
			edges_v[nodes_number*i + j] = static_cast<ValuesType>(0);
			node_connections_v[nodes_number*i + j] = 0;
			distance_v[nodes_number*i + j] = 0.0;
		};
	};
};

template void Graph<int>::clear_Matrix(vector<int> &, vector<int> &, vector<double> &);
template void Graph<char*>::clear_Matrix(vector<char*> &, vector<int> &, vector<double> &);

template <class ValuesType> // We include that, because we want nodes and edges values to be declared by the user
// Depending on the shape, we can look for a edge inside our vectors
int Graph<ValuesType>::edge_position_in_list(int node_from, int node_to){
		
		if (Graph_Matrix) return nodes_number*node_from + node_to;

		int position=nodes_index[node_from];

		for (int i = nodes_index[node_from]; i<upper_limit_node_index(node_from);++i){
			if(nodes_connections[i]<node_to) position = i + 1;
		};
		
		return position;
	};

template int Graph<int>::edge_position_in_list(int, int);
template int Graph<char*>::edge_position_in_list(int, int);
