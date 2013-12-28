//
//  Homework 2 for Coursera Class - C++ for C Programmers
//

//
// All files are combined into this one source file for ease of peer grading
// Although it is acknowledged that breaking the files up by classes and
// using headers is better style for larger programs
//

#include <iostream>
#include <iomanip> // Used to format cout
#include <list>
#include <vector>
#include <random>

using namespace std;

// *****************************************************************************
//
// Class defintion: NodeValue
// - Used to hold (node, value) pairs of (int, double)
// - Elements of open/closed sets in Dijkstra's Algorithm implementation
//
// *****************************************************************************

class NodeValue{

public:
    // Contructors and Destructors
    NodeValue(int n, double v): node(n), value(v) {}
    ~NodeValue() {}
    
    // Getters and Setters
    int getNode() {return node;}
    void setNode(int n) {node = n;}
    double getValue() {return value;}
    void setValue(double v) {value =v;}

private:
    int node;
    double value;
};

// ****************************************************************************
//
// Class defintion: PriorityQueue
// - Implementation of a priority queue of NodeValue elements
// - Used for open/closed sets in Dijkstra's Algorithm
// - Priority queue implemented as a list from the standard library
//
// ****************************************************************************

class PriorityQueue {
    
public:
    PriorityQueue() {}
    ~PriorityQueue() {}
    
    // Add a new NodeValue pair to priority queue
    void insertNode(int n, double v) {
        NodeValue* nodeValue;
        nodeValue = new NodeValue(n,v);
        
        list<NodeValue>::iterator i;
        for (i=pq.begin(); i != pq.end(); ++i) {
            if ((*i).getValue() > v) {
                pq.insert(i, *nodeValue);
                delete nodeValue;
                return;
            }
        }
        pq.push_back(*nodeValue);
        delete nodeValue;
    };
    
    // Returns a pointer to the minimum NodeValue pair and removes it from priority queue
    NodeValue* min() {
        NodeValue *minNodeValue = &(*pq.begin());
        pq.pop_front();
        return minNodeValue;
    };
    
    // Returns size of priority queue
    int size() {return  (int)pq.size();}
    
    // Returns whether priority queue is empty
    bool isEmpty() {return size() == 0;}
    
    // Returns whether a particular node is in the priority queue
    bool containsNode(int n) {
        list<NodeValue>::iterator i;
        for (i=pq.begin(); i!=pq.end(); ++i) {
            if (n == (*i).getNode()) {
                return true;
            }
        }
        return false;
    };
    
    // Returns value of a node from a particular NodeValue pair
    // Returns 0 if node is not in the queue
    double valueNode(int n) {
        list<NodeValue>::iterator i;
        for (i=pq.begin(); i!=pq.end(); ++i) {
            if (n == (*i).getNode()) {
                return (*i).getValue();
            }
        }
        return 0;
    }
    
    // Replaces the value of a NodeValue pair in the queue
    // Nothing happens if node is not in the queue
    void replaceNodeValue(int n, double v) {
        list<NodeValue>::iterator i;
        for (i=pq.begin(); i!=pq.end(); ++i) {
            if (n == (*i).getNode()) {
                pq.erase(i);
                insertNode(n, v); // Call to insertNode ensures queue stays ordered
                return;
            }
        }
    }
    
    // Prints out the contents of the priority queue for debugging purposes
    void print() {
        list<NodeValue>::iterator i;
        for (i=pq.begin(); i != pq.end(); ++i) {
            cout << "Node: " << (*i).getNode() << " Value: " << (*i).getValue() <<  endl;
        }
    }
    
private:
    list<NodeValue> pq;
};

// ****************************************************************************
//
// Class defintion: Graph
// - Undirected graph implementation where only edges have values(lengths)
// - Edges represented as an adjacency matrix using a 2D array of doubles
// - Edge lengths assumed to be positive. A entry of 0 implies no edge
//
// ****************************************************************************

class Graph {

public:
    int nNodes; // number of vertices in graph
    
    // Graph constructor that allocates and initializes the adjacency matrix
    Graph(int n):nNodes(n) {
        // Allocate 2D array of size nNodes x nNodes for edge lengths
        edges = new double*[nNodes];
        for (int i=0; i < nNodes; i++) {
            edges[i] = new double[nNodes];
        }
        
        // Set all edge lengths to 0, implying no connections
        for (int i=0; i < nNodes; i++) {
            for (int j=0; j < nNodes; j++) {
                edges[i][j] = 0;
            }
        }
    }
    
    // Fills graph edges randomly according given distribution with lengths
    void createRandomEdges(double density, double minLength, double maxLength) {
        // Seed and create random number generators to select edges (int) and costs (real)
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> realDis(minLength,maxLength);
        uniform_int_distribution<> intDis(0, nNodes-1);
        
        int edgesLeft = nNodes*(nNodes - 1)/2 * density; // Fixed number of edges to create

        //Create new edges picking randomly from possible combinations until complete
        while (edgesLeft > 0) {
            int n1 = intDis(gen);
            int n2 = intDis(gen);
            if (n1 != n2) { // Ensure not same node
                if (get_edge_value(n1, n2) == 0) { // Ensure edge not already assigned a value
                    set_edge_value(n1, n2, realDis(gen));
                    edgesLeft--;
                }
            }
        }
    }
    
    // Set edge value between two nodes
    void set_edge_value(int n1, int n2, double v) {
        if (n1 < nNodes && n2 < nNodes) {
            edges[n1][n2] = edges[n2][n1] = v;
        } else {
            cout << "Attempt to access graph outside bounds" << endl;
        }
    }
    
    // Retrieve edge value between two nodes
    double get_edge_value(int n1, int n2) {
        if (n1 < nNodes && n2 < nNodes) {
            return edges[n1][n2];
        } else {
            cout << "Attempt to access graph outside bounds" << endl;
            return 0;
        }
    }
    
    // Tests if there is an edge between two nodes
    bool adjacent(int n1, int n2) {
        return edges[n1][n2];
    }
    
    // Returns a list of NodeValue pairs of all nodes that share an edge with a particular node
    // Callers need to delete the return list to avoid memory leaks as it is created in this method
    // Note to graders: I know this isn't ideal OO structure. Any suggestions to avoid this problem appreciated
    list<NodeValue>* successors(int n) {
        list<NodeValue> *lstSuccessors = new list<NodeValue>;
        // Loop through nodes and add NodeValue pairs to list if an edge exists
        for (int i=0; i < nNodes; ++i) {
            if (adjacent(i, n)) {
                NodeValue *nodeValue = new NodeValue(i, edges[i][n]);
                lstSuccessors->push_front(*nodeValue);
                delete nodeValue;
            }
        }
        return lstSuccessors;
    }
    
    // Prints out the edges' adjacency matrix for debugging
    void print() {
        for (int i=0; i < nNodes; i++) {
            for (int j=0; j < nNodes; j++) {
                cout << setw(5) << setprecision(2) << get_edge_value(i, j) << "\t";
            }
            cout << endl;
        }
    }
    
    // Deletes 2D array of edges when graph is sent to destructor
    ~Graph() {
        for (int i(0); i < nNodes; i++) {
            delete edges[i];
        }
        delete edges;
    };

private:
    double **edges; // 2D array of edge lengths

};

// ****************************************************************************
//
// Class defintion: SHortestPath
// - Class to implement Dijkstra's shortest path algorithm
// - Created by passing pointer to a Graph
//
// ****************************************************************************

class ShortestPath {
    
public:
    ShortestPath(Graph* g): g(g) {}
    ~ShortestPath() {}
    
    // Implementation of Dijkstra's algorithm to find shortest path between start and destination nodes
    // Returns 0 if no connected path
    double shortestPath(int s, int d) {
        // Initialize open and closed sets
        PriorityQueue *closed, *open;
        closed = new PriorityQueue();
        open = new PriorityQueue();
        
        // Put start node into closed set with distance of 0
        closed->insertNode(s, 0);
        // Populate open set with successors
        list<NodeValue> *lstSuccessors;
        lstSuccessors = g->successors(s);
        for (list<NodeValue>::iterator i=lstSuccessors->begin(); i != lstSuccessors->end(); ++i) {
            open->insertNode((*i).getNode(), (*i).getValue());
        }
        delete lstSuccessors; // Delete since Graph.successors creates a new instance of list
        
        // Look for shortest distance until found or open set is empty
        while (!open->isEmpty()) {
            // Take minimum value from open set
            NodeValue *nextNode = open->min();
            closed->insertNode(nextNode->getNode(), nextNode->getValue());
            // Check if already at destination
            if (nextNode->getNode() == d) {
                double distance = nextNode->getValue();
                delete open;
                delete closed;
                return distance;
            }
            // Otherwise, collect successors and update open set
            list<NodeValue> *lstSuccessors;
            lstSuccessors = g->successors(nextNode->getNode());
            for (list<NodeValue>::iterator i=lstSuccessors->begin(); i != lstSuccessors->end(); ++i) {
                int newNode = (*i).getNode();
                double newDistance = nextNode->getValue() + (*i).getValue();
                if (!open->containsNode(newNode) && !closed->containsNode(newNode)) {
                    open->insertNode(newNode, newDistance);
                } else if (open->valueNode(newNode) > newDistance ) {
                    open->replaceNodeValue(newNode, newDistance);
                }
            }
            delete lstSuccessors; // Delete since Graph.successors creates a new instance of list
        }
        delete open;
        delete closed;
        return 0;
    };
    
    // Return average path length from 1st node (0) to all other nodes
    double avePathLength() {
        double totalLength = 0;
        int pathsFound = 0;
        // Loop through all nodes and call shortestPath
        for (int i=1; i < g->nNodes; i++) {
            double pathLength = shortestPath(0, i);
            if (pathLength != 0) {
                totalLength += pathLength;
                pathsFound++;
            }
        }
        return pathsFound == 0 ? 0 : totalLength / pathsFound;
    }
    
private:
    Graph* g;
};

// ****************************************************************************
//
// Main loop
// - Monte Carol Simulation of average shortest path using 2 different graph densities
//
//
// ****************************************************************************

int main()
{
    // Set up parameters for 2 Monte Carlo simulations
    const int nRuns = 10000;
    const int N = 50;
    const double density1 = 0.20;
    const double density2 = 0.40;
    const double edgeMin = 1.0;
    const double edgeMax = 10.0;
    
    // Accumulator variables used to calculate averages
    double accum1 = 0, accum2 = 0;
    int nRunsActual1 = 0, nRunsActual2 = 0; // Necessary to track for cases when no paths exist (rare but possible)
    ShortestPath *sp1, *sp2;
    
    // Run 2 Monte Carlo simulations to find shortest path
    for (int i=0; i<nRuns; ++i) {
        Graph g1(N), g2(N);
        g1.createRandomEdges(density1, edgeMin, edgeMax);
        g2.createRandomEdges(density2, edgeMin, edgeMax);
        sp1 = new ShortestPath(&g1);
        sp2 = new ShortestPath(&g2);
        double ave1 = sp1->avePathLength(); // 0 if no paths exist (rare but possible)
        double ave2 = sp2->avePathLength(); // 0 if no paths exist (rare but possible)
        delete sp1;
        delete sp2;
        accum1 += ave1;
        accum2 += ave2;
        // Add 1 if run generates at least 1 path
        if (ave1) {nRunsActual1++;}
        if (ave2) {nRunsActual2++;}
    }
    
    // Output results
    cout << "Average path lengths for graphs with " << N << " nodes and edges between "  << edgeMin << " and " << edgeMax << " in length:" << endl;
    cout << "Density: " << density1 << "\tAve Length: " << accum1 / nRunsActual1 << endl;
    cout << "Density: " << density2 << "\tAve Length: " << accum2 / nRunsActual2 << endl;
    
    return 0;
}


