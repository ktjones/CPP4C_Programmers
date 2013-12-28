#ifndef __SHORTESTPATH
#define __SHORTESTPATH

#include "Graph.H"
#include <queue>
#include <map>
#include <set>
#include <utility>
#include <list>

class ShortestPath
{
public:

    // Priority queue comparator
    class closet_vertex
    {
    public:
        closet_vertex(){};
        ~closet_vertex(){};
        bool operator() (pair<unsigned int, double> x, pair<unsigned int, double> y)
        {
            return x.second > y.second;
        }
    };

    /*
        @brief: constructor for ShortestPath object
    */
    ShortestPath(Graph &G);

    /*
        @brief: destructor for ShortestPath object
    */
    ~ShortestPath() {};

    /*
        @brief: runs Dijkstras algorithm on a graph

        @return: int - 0 failure, otherwise success
    */
    int run_Dijkstras(Graph &G, unsigned int src);

    /*
        @brief: return shortest path from src to dest

        @return: sequence of vertices in shortest path
    */
    list<unsigned int> path(unsigned int src, unsigned int dest);

    /*
        @brief: return shortest path from src to dest

        @return: cost of path as int
    */
    double path_size(unsigned int src, unsigned int dest);

    /*
        @brief: clear out iv_closed_set and resets cur_dist

        @return: NULL
    */
    void reset_structures(Graph &G);

    /*
        @brief: print all internal structures

        @return: NULL
    */
    void print_step();

    /*
        @brief: print iv_shortest_path_costs and iv_shortest_paths

        @return: NULL
    */
    void print_results();

private:
    set<unsigned int> iv_closed_set;
    map<unsigned int, double> iv_cur_dist;
    map<unsigned int, unsigned int> iv_previous_vertex;

    // Distance is from 1..10, set arbirtarly large number for inf
    static constexpr double MAX_DISTANCE = 999999.0;

    // Stores the next shortest link in the shortest path calculation on top
    priority_queue<pair<unsigned int, double>,
                   vector< pair<unsigned int, double> >,
                   closet_vertex> iv_vertex_queue;

    // Map of all path_sizes - (<src,dest>, cost)
    map< pair<unsigned int, unsigned int>, double > iv_shortest_path_costs;
    // Map of all shortest paths - (<src,dest>, path)
    map< pair<unsigned int, unsigned int>, list<unsigned int> > iv_shortest_paths;
};

#endif
