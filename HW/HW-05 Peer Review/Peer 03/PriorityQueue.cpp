//
//	PriorityQueue.cpp
//
//	Created on: Nov 6, 2013
//		Author: JFM
//
//	This class is meant to manage a queue 
//

#include "PriorityQueue.h"

// Let the user know whether the item is contained or not within a queue
bool PriorityQueue::contains(int node){
	bool status = false;
	for(unsigned int i = 0; i<nodes.size(); ++i) if (nodes[i] == node) status = true;
	return status;
};

// Maybe the user need to now wich position occupies one particular item
int PriorityQueue::node_position(int node){
	for (unsigned int i = 0; i<nodes.size(); ++i) if (nodes[i] == node) return i;
	return 0;
};

// Or the value that has this item
double PriorityQueue::node_value(int node){
	for (unsigned int i = 0; i<nodes.size(); ++i) if (nodes[i] == node) return values[i];
	return 0.0;
};

// looks for the item with the lowest value
int PriorityQueue::min_position(){
	
	double min;
	int pos = 0;

	if (values.size()>0){
		min = values[0];
	}
	else{
		return -1;
	};

	for (unsigned int i = 1; i<values.size(); ++i) if (values[i] < min) {min = values[i]; pos = (int)i;};

	return pos;
};