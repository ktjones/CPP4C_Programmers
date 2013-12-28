//
//	ShortestPathAlgo.cpp
//
//	Created on: Nov 6, 2013
//		Author: JFM
//
//	This class is meant to manage a Shortest Path Algorithm
//

#include "ShortestPathAlgo.h"

template <class ValuesType> // We include that, because we want nodes and edges values to be declared by the user
// gives back the collection of vertex that are contained within a graph
vector<ValuesType> ShortestPathAlgo<ValuesType>::vertices(Graph<ValuesType> Graphic){
	int n_vertex = Graphic.get_nodes_number();
	vector<ValuesType> vertexs(n_vertex);
	for (int i = 1; i<n_vertex; ++i) vertexs[i]=Graphic.get_node_value(i);
	return vertexs;
};
	
template vector<int> ShortestPathAlgo<int>::vertices(Graph<int>);
template vector<char*> ShortestPathAlgo<char*>::vertices(Graph<char*>);

template <class ValuesType> // We include that, because we want nodes and edges values to be declared by the user
// looks for the shortest path from one node to other
vector<int> ShortestPathAlgo<ValuesType>::path(Graph<ValuesType> graphic, int beginning, int ending, bool &status){

	// First, we clear all the tools related to the quest
	nodes.clear();
	queue.clear();
	nodes_passed.clear();
	vector<int> zeros(1);
	// Second, we create the priorityqueue that will manage the quest
	create_priorityqueue(graphic,beginning);
	
	

	// There are two options, we can find out out path, or we can run out paths to look for, this information will be inside status var
	while(!(queue.top_node()==ending) ){
		if (queue.size() == 0) {
			status = false;

			return zeros;
		}
			
		update_queue(graphic);

	};
	status = true;
	return nodes[queue.top_position()];
};

template vector<int> ShortestPathAlgo<int>::path(Graph<int>, int, int, bool &);
template vector<int> ShortestPathAlgo<char*>::path(Graph<char*>, int, int, bool &);

template <class ValuesType> // We include that, because we want nodes and edges values to be declared by the user
// Given a graph and a path inside it, we calculate the distance of the path
double ShortestPathAlgo<ValuesType>::path_distance(Graph<ValuesType> graphic, vector<int> path){
	double distance=0.0;

	for(unsigned int i = 0; i<path.size()-1; ++i){ 
			
		if (graphic.adjacent(path[i],path[i+1])) {
			distance += graphic.get_distance(path[i],path[i+1]);
		}
		else{ return 0.0;}
	};
	return distance;
};

template double ShortestPathAlgo<int>::path_distance(Graph<int>, vector<int>);
template double ShortestPathAlgo<char*>::path_distance(Graph<char*>, vector<int>);

template <class ValuesType> // We include that, because we want nodes and edges values to be declared by the user
// When we start our quest, we look for every neighbor of the starting node
void ShortestPathAlgo<ValuesType>::create_priorityqueue(Graph<ValuesType> graphic, int node){
	
	vector<int> neighbors;
	vector<int> row(2);

	bool status;
	ValuesType temporal_value;
	bool go_ahead;


	status = nodes_passed.Insert(node,0.0);

	neighbors = graphic.neighbors(node);

	row[0] = node;

	for (unsigned int i = 0; i<neighbors.size();++i){
		
		// if we look for a particular edge value, we must know if this edge has it
		if (look_for_particular_edges){
			go_ahead = true;
			temporal_value = graphic.get_edge_value(node,neighbors[i]);
			for (int j = 0; j<(int)edges_value.size(); ++j){
				if (edges_value[j] == temporal_value) {go_ahead = false;break;};
			};
			if (go_ahead) continue;
		};
		
		status = queue.Insert(neighbors[i],graphic.get_distance(node,neighbors[i]));
		row[1] = neighbors[i];
			
		nodes.push_back(row);
	};
};

template void ShortestPathAlgo<int>::create_priorityqueue(Graph<int>, int);
template void ShortestPathAlgo<char*>::create_priorityqueue(Graph<char*>, int);

template <class ValuesType> // We include that, because we want nodes and edges values to be declared by the user
void ShortestPathAlgo<ValuesType>::update_queue(Graph<ValuesType> graphic){
	
	// on the next steps, we select the suitable way that is closest to the beginning
	int current_position = queue.top_position();
	int current_node = queue.top_node();
	double current_distance=queue.top_value();
	bool status;
	ValuesType temporal_value;
	bool go_ahead;

	vector<int> neighbors;
	vector<int> row;

	status = nodes_passed.Insert(current_node,current_distance);

	row.resize(nodes[current_position].size());
	row.assign(nodes[current_position].begin(),nodes[current_position].end());

	// we look for the neighbors of the current node
	neighbors = graphic.neighbors(current_node);

	for (unsigned int i = 0; i<neighbors.size(); ++i){
		// if we look for a particular edge value, we must know if this edge has it
		if (look_for_particular_edges){
			go_ahead = true;
			temporal_value = graphic.get_edge_value(current_node,neighbors[i]);
			for (int j = 0; j<(int)edges_value.size(); ++j){
				if (edges_value[j] == temporal_value) {go_ahead = false;break;};
			};
			if (go_ahead) continue;
		};

		// and, by definition, if a node has been selected before, we cannot find a shortest way to go to it.
		if (nodes_passed.contains(neighbors[i])){ 
			continue;	};
			
		row.push_back(neighbors[i]);				
		// maybe we can find two ways to get to the same node, in that case we keep the shortest one
		if (queue.contains(neighbors[i])){
			if (queue.node_value(neighbors[i])>current_distance + graphic.get_distance(current_node,neighbors[i])){
				nodes[queue.node_position(neighbors[i])].resize(row.size());
				nodes[queue.node_position(neighbors[i])].assign(row.begin(), row.end());
				queue.chgPriority(neighbors[i],current_distance + graphic.get_distance(current_node,neighbors[i]));
			}
				
		}
		// or we are getting a new possibility
		else{
			status = queue.Insert(neighbors[i], current_distance + graphic.get_distance(current_node,neighbors[i]));
			nodes.push_back(row);
		}

		row.pop_back();
	};
		
	// every posible move that has been yet analyzed, must be pass from the possibities to the explored paths
	nodes.erase(nodes.begin() + current_position);
	queue.minPriority();

	return;

};

template void ShortestPathAlgo<int>::update_queue(Graph<int>);
template void ShortestPathAlgo<char*>::update_queue(Graph<char*>);