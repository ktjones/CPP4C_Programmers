//
//	ShortestPathAlgo.h
//
//	Created on: Nov 6, 2013
//		Author: JFM
//
//	This class is meant to manage a Shortest Path Algorithm
//

#ifndef ShortestPathAlgo_H_
#define ShortestPathAlgo_H_

#include <vector> // This line allows us to use vector class

#include "Graph.h"
#include "PriorityQueue.h"

using namespace std;

// Here, as we used a general graph class, we must use also a general ShortestPathAlgo class, thats why we have this template
template <class ValuesType>
class ShortestPathAlgo{
public:
	// We set by default the search for any edge
	inline ShortestPathAlgo(){look_for_particular_edges = false;};

	// gives back the collection of vertex that are contained within a graph
	vector<ValuesType> vertices(Graph<ValuesType> Graphic);

	// looks for the shortest path from one node to other
	vector<int> path(Graph<ValuesType> graphic, int beginning, int ending, bool &status);

	// Given a graph and a path inside it, we calculate the distance of the path
	double path_distance(Graph<ValuesType> graphic, vector<int> path);

	// This functions allows us to switch between particular and any endge search
	inline void Set_Search_for_Particular_Edges(vector<ValuesType> search_values_in){
		look_for_particular_edges = true; 
		edges_value.clear(); 
		edges_value.assign(search_values_in.begin(),search_values_in.end());
	};

	inline void Set_Search_for_Any_Edges(){look_for_particular_edges = false;};

private:

	// When we start our quest, we look for every neighbor of the starting node
	void create_priorityqueue(Graph<ValuesType> graphic, int node);

	void update_queue(Graph<ValuesType> graphic);

	vector<vector<int>> nodes; // These are the step that we must do to get from the initial node to every possible node
	PriorityQueue queue; // These are the possible future step that can be done, if this queue size is zero, there is no possible path
	PriorityQueue nodes_passed; // These are the node we have yet visited, by definition we cannot find a shortest way to get to them
	bool look_for_particular_edges; //This boolean variable selects a search for one edge or for any
	vector<ValuesType> edges_value; // This variable stores the value we are looking for
};

#endif // ShortestPathAlgo_H_