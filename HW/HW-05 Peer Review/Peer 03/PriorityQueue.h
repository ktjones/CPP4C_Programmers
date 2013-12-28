//
//	PriorityQueue.h
//
//	Created on: Nov 6, 2013
//		Author: JFM
//
//	This class is meant to manage a queue
//

#ifndef PriorityQueue_H_
#define PriorityQueue_H_

#include <vector> // This line allows us to use vector class

using namespace std;

// the PriorityQueue class
class PriorityQueue {

public:
	// We can change the value of the item in a queue
	inline bool chgPriority(int node, double value){

		// if the item is not contained, we cannot change it, so we get a false. As values are distances, they must be positive
		if (!contains(node)) return false;
		if (value < 0.0) return false;

		// We look for the position of one node, and we change the value of it
		int position = node_position(node);
		values[position] = value;

		return true;
	};

	// We look for the item that has the lowest value, and we erase it
	inline void minPriority(){
		
		int pos = min_position();
		nodes.erase(nodes.begin()+pos);
		values.erase(values.begin()+pos);
	};

	// Maybe we want to clear the queue, here we can do it
	inline void clear(){nodes.clear(); values.clear();};

	// Let the user know whether the item is contained or not within a queue
	bool contains(int node);

	// Maybe the user need to now wich position occupies one particular item
	int node_position(int node);

	// Or the value that has this item
	double node_value(int node);

	// When we insert some item, if the item is contained in the queue, we get a false
	inline bool Insert(int node, double value, bool check_existance = true){
		if(check_existance){if(contains(node)) return false;};

		nodes.push_back(node);
		values.push_back(value);

		return true;
	};

	// Some data about the item with the lowest value
	inline int top_position(){return min_position();};
	inline int top_node(){
		int min_pos = min_position();if(min_pos>-1){
			return nodes[min_position()];
		}
		else{
		return -1;
		};
	};
	inline double top_value(){return values[min_position()];};

	// Gives back the size of the queue
	inline int size(){return nodes.size();};

private:

	// looks for the item with the lowest value
	int min_position();

	vector<int> nodes; // vector of items
	vector<double> values; // the value of each item

};

#endif // PriorityQueue_H_ 