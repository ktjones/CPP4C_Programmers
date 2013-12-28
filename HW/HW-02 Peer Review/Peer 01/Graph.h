#ifndef __GRAPH
#define __GRAPH

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <stdlib.h>     // srand, rand
#include <time.h>       // time

using namespace std;

class Graph
{
public:

    static const unsigned int NUM_VERTICES = 50;

    /*
        @brief: constructor for Graph object
    */
    Graph();

    /*
        @brief: destructor for Graph object
    */
    ~Graph(){};

    /*
        @brief: return number of vertices in the graph

        @return: number of vertices
    */
    int num_vertices();

    /*
        @brief: return number of edges in the graph

        @return: number of edges
    */
    int num_edges();

    /*
        @brief: returns the value associated to the edge (x,y)
                also tests whether there is an edge from node x to node y
                because 0 means no edge

        @return: cost of edge, if 0 no edge
    */
    int get_edge_value(unsigned int x, unsigned int y);

    /*
        @brief: list all vertices y such that there is an edge from x to y

        @return: neighboring vertices
    */
    vector<unsigned int> neighbors(unsigned int x);

    /*
        @brief: generates a random graph as an adj matrix

        @return: NULL
    */
    void generate_random(double density, double range_start,
                         double range_end);

    /*
        @brief: prints graph

        @return: NULL
    */
    void print();

private:
    // TODO: Number of actual paths, assigned but not used
    unsigned int NUM_PATHS;
    unsigned int iv_num_edges;
    // Graph ADT stored as 2D vector
    vector<vector<unsigned int> > iv_adj_matrix;

};

#endif
