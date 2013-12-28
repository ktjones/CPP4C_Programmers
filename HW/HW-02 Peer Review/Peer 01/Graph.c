#include "Graph.H"

Graph::Graph():iv_adj_matrix(NUM_VERTICES, vector<unsigned int>(NUM_VERTICES))
{
    NUM_PATHS = NUM_VERTICES;
}

int Graph::num_vertices()
{
    return NUM_VERTICES;
}

int Graph::num_edges()
{
    return iv_num_edges;
}

int Graph::get_edge_value(unsigned int x, unsigned int y)
{
    return iv_adj_matrix[x][y];
}

vector<unsigned int> Graph::neighbors(unsigned int x)
{
    vector<unsigned int> neighbors;

    for (unsigned int i = 0; i < NUM_VERTICES; ++i)
    {
        if (iv_adj_matrix[x][i] && x!=i)
        {
            neighbors.push_back(i);
        }
    }

    return neighbors;
}

void Graph::generate_random(double density, double range_start,
                        	double range_end)
{
    if (density < 0.0 || density > 1.0)
    {
        cerr<<"Graph::generate_random - Incorrect Density (0..1)"<<endl;
        exit (EXIT_FAILURE);
    }

    if (range_start < 1.0 || range_end > 10.0)
    {
        cerr<<"Graph::generate_random - Incorrect Range (1..10)"<<endl;
        exit (EXIT_FAILURE);
    }

    // initialize number of edges
    iv_num_edges = 0;

    // initialize random seed
    srand (time(NULL));

    for (unsigned int i = 0; i < NUM_VERTICES; ++i)
    {
        for(unsigned int j = i + 1; j < NUM_VERTICES; ++j)
        {
            double prob = (((double) rand()) / RAND_MAX);
            if (prob < density)
            {
                double edgeLength = range_start + ((range_end - range_start) * prob);
                iv_adj_matrix[i][j] = iv_adj_matrix[j][i] = edgeLength;
                iv_num_edges++;
            }
        }
    }
}

void Graph::print()
{
    for (int i = 0; i < NUM_VERTICES; ++i)
    {
        cout<<"\t"<<i;
    }
    cout<<endl;

    for (unsigned int i = 0; i < NUM_VERTICES; ++i)
    {
        for(unsigned int j = 0; j < NUM_VERTICES; ++j)
        {
            if(j==0)
            {
                cout<<i<<"\t";
            }
            cout << iv_adj_matrix[i][j] << "\t";
        }
        cout<<endl;
    }
}