#ifndef __MONTECARLO
#define __MONTECARLO

#include "ShortestPath.H"

class MonteCarlo
{
public:

    /*
        @brief: constructor for Graph object
    */
    MonteCarlo() {};

    /*
        @brief: destructor for Graph object
    */
    ~MonteCarlo() {};

    /*
        @brief: run dijkstras on randomly generated graphs of 20% and 40% density
                will generalize in future assignments

        @return: NULL
    */
    void run_simulation();

    /*
        @brief: computes avg path length of graph

        @return: average length
    */
    double compute_avg(ShortestPath &sp);

private:
    static const unsigned int SRC_VERTEX = 0;
};

#endif
