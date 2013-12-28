#include "ShortestPath.H"
#include "Graph.H"

constexpr double ShortestPath::MAX_DISTANCE;

ShortestPath::ShortestPath(Graph &G)
{
    reset_structures(G);
}

int ShortestPath::run_Dijkstras(Graph &G, unsigned int src)
{
    // Itertae through (num_vertices - 1) paths from src to dest
    for (unsigned int dest = 0; dest < G.num_vertices(); ++dest)
    {
        // Skip self path
        if (src != dest)
        {
            cout<<"### Searching for path from "<<src<<" to "<<dest<<endl;

            // Push src to queue
            pair<unsigned int, double> cur_vertex(src,0);
            iv_vertex_queue.push(cur_vertex);
            bool dest_found = 0;

            while (!iv_vertex_queue.empty())
            {
                vector<unsigned int> neighbors;
                cur_vertex = iv_vertex_queue.top();

                // Get neighbors of next closest vertex if not in closed set
                if (iv_closed_set.count(cur_vertex.first) == 0)
                {
                    if (cur_vertex.first == dest)
                    {
                        dest_found = 1;
                        break;
                    }

                    neighbors = G.neighbors(cur_vertex.first);
                    iv_vertex_queue.pop();
                    iv_closed_set.insert(cur_vertex.first);
                    print_step();
                }
                else
                {
                    // if already in closed set
                    iv_vertex_queue.pop();
                    continue;
                }
                for (int v = 0; v < neighbors.size(); ++v)
                {
                    if (iv_closed_set.count(neighbors[v]) == 0)
                    {
                        double neighbor_dist = G.get_edge_value(cur_vertex.first,neighbors[v]);
                        double dist = cur_vertex.second + neighbor_dist;

                        if (dist < iv_cur_dist[neighbors[v]])
                        {
                            // update distance and previous vertex of v
                            iv_cur_dist[neighbors[v]] = dist;
                            iv_previous_vertex[neighbors[v]] = cur_vertex.first;

                            // keep shortest dist from cur_vertex to v
                            pair<unsigned int, double> tmp_pair(neighbors[v],dist);
                            iv_vertex_queue.push(tmp_pair);
                        }
                    }
                }
            }
            // If dest found, add path and cost
            if (dest_found)
            {
                cout<<"### Path found from "<<src<<" to "<<dest<<endl;

                // Add shortest path to map
                pair<unsigned int, unsigned int> tmp_pair(src,dest);
                unsigned int tmp_vertex = dest;
                while ( tmp_vertex != src )
                {
                    iv_shortest_paths[tmp_pair].push_front(tmp_vertex);
                    tmp_vertex = iv_previous_vertex[tmp_vertex];
                }
                iv_shortest_paths[tmp_pair].push_front(src);

                // Add cost to shortet path cost
                iv_shortest_path_costs[tmp_pair] = iv_cur_dist[dest];
            }
            else
            {
            // Decrement due to not counting empty paths for average
            // Graph::NUM_PATHS--;
            }
        reset_structures(G);
        }
    }
    print_results();
    return 1;
}

list<unsigned int> ShortestPath::path(unsigned int src, unsigned int dest)
{
    pair<unsigned int, unsigned int> tmp_pair(src,dest);
    return iv_shortest_paths[tmp_pair];
}

double ShortestPath::path_size(unsigned int src, unsigned int dest)
{
    pair<unsigned int, unsigned int> tmp_pair(src,dest);
    return iv_shortest_path_costs[tmp_pair];
}

void ShortestPath::reset_structures(Graph &G)
{
    for (unsigned int i = 0; i < G.num_vertices(); ++i)
    {
        // Set each vertex to MAX_DISTANCE - sudo infinity
        if( iv_cur_dist.count(i) == 0 )
        {
            pair<unsigned int, double> tmp_pair(i,MAX_DISTANCE);
            iv_cur_dist.insert(tmp_pair);
        }
            iv_cur_dist[i] = MAX_DISTANCE;
    }

    while (!iv_vertex_queue.empty())
    {
        iv_vertex_queue.pop();
    }

    iv_closed_set.clear();
    iv_previous_vertex.clear();
}

void ShortestPath::print_step()
{
    cout<<"--- Priority Queue"<<endl;
    cout<<"("<<iv_vertex_queue.top().first<<","<<iv_vertex_queue.top().second;
    cout<<")"<<endl;

    cout<<"--- Closed Set"<<endl;
    for (set<unsigned int>::iterator it = iv_closed_set.begin();
         it != iv_closed_set.end(); ++it)
    {
        cout<<*it<<" ";
    }
    cout<<endl;

    cout<<"--- Cur Distances"<<endl;
    for (map<unsigned int, double>::iterator it = iv_cur_dist.begin();
         it != iv_cur_dist.end(); ++it)
    {
        cout<<"("<<it->first<<","<<it->second<<") ";
    }

    cout<<"\n--- iv_Previous_vertex Paths"<<endl;
    for (map<unsigned int, unsigned int >::iterator it = iv_previous_vertex.begin();
         it != iv_previous_vertex.end(); ++it)
    {
        cout<<it->first<<":"<<it->second<<endl;
    }
    cout<<"--------------------------------\n\n";
}

void ShortestPath::print_results()
{
    cout<<"---ShortestPath Costs"<<endl;
    for (map< pair<unsigned int, unsigned int>, double >::iterator it =
         iv_shortest_path_costs.begin();it!=iv_shortest_path_costs.end();++it)
    {
        cout<<"("<<it->first.first<<","<<it->first.second<<") = "<<
        it->second<<endl;
    }

    cout<<"---Shortest Paths"<<endl;
    for (map< pair<unsigned int, unsigned int>, list<unsigned int> >
         ::iterator it = iv_shortest_paths.begin();it!=iv_shortest_paths.end();
         ++it)
    {
        cout<<"("<<it->first.first<<","<<it->first.second<<") = ";

        for (list<unsigned int>::iterator lit = it->second.begin();
             lit != it->second.end(); lit++)
        {
            cout<<*lit<<" ";
        }
        cout<<endl;
    }
}