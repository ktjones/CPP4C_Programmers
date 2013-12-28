#include <iostream>
#include <vector>
#include <stdlib.h>
#include <queue>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


//~~~~~MY DATA STRUCTURES ARE A LITTLE DIFFERENT FROM THOSE SUGGESTED ON COURSERA, PLEASE TAKE TIME TO READ THROUGH THE CODE~~~~~
//~~~~~THANKS FOR GRADING~~~~~


//~~~~~~MISCELLANEOUS CLASSES AND METHODS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Create an empty nxn matrix
template <class T>
inline vector<vector<T> > create_matrix(int n){
  vector<vector<T> > M(n);
  for (int i=0;i<n;++i)
    M[i].resize(n);
  return M;
}

//Print matrix for testing graph
template <class T>
inline void print_matrix(vector<vector<T> > M){
  cout << endl;

  for(int i=0;i<M.size();++i) {

    for(int j=0;j<M[i].size();++j)
      cout << M[i][j] << " ";

    cout << endl;
  }

  cout << endl;
}

//Reverse a vector
inline vector<int> reverse(vector<int> sequence){
  vector<int> rsequence;

  for (int i=sequence.size()-1;0<=i;--i)
    rsequence.push_back(sequence[i]);

  return rsequence;
}

//A special class to be put in priority-queue, consisting of a vertex number and its current distance from the root
class vert_dist{  
public:
  int vert;
  int dist;
  vert_dist(int v, int d){
    vert = v;
    dist = d;
  }
};

//Again to be used in priority-queue, comparing 2 pairs (vert,dist) according to dist
class compare_vert {  
public:
  bool operator()(vert_dist v1, vert_dist v2)
    {
      if (v1.dist > v2.dist) return true;
      else return false;
    }
};

//Defining our priority queue. This will automatically sort the vertices according to their tentative distance from START
typedef priority_queue<vert_dist,vector<vert_dist >,compare_vert > vert_queue;  

//Data structure representing a path, consisting of path length and the sequence of vertices in it
class path {  
public:
  int length;
  vector<int> sequence; 

  path (int l, vector<int> s) {
    length = l;
    sequence = s;
  }

  //Display path length and the sequence of vertices
  void display(){
    cout << "Path length: " << length << endl;
    cout << "Sequence";
    for (int i=0;i<sequence.size();++i)
      cout << " -> " << sequence[i];
    cout << endl;
  }
};


//Data structure representing a tree
class tree {
public:
  int cost;
  vector<int> connectivity;   //If (i,j) is an edge then connectivity[i] = j

  tree(int c,vector<int> cn){
    cost = c;
    connectivity = cn;
  }

  void display(){
    cout << "Cost: " << cost << endl;
    cout << "Edges: " << endl;
    for(int i=0;i<connectivity.size();++i){
      if (connectivity[i] == i)
	cout << "The root is " << i << endl;
      else if (connectivity[i] != -1)
	cout << "(" << i << "," << connectivity[i] << ")" << endl;
    }
  }
};




//~~~~~~~~~~~~~~~~~~~~~~~~~~~MAIN GRAPH CLASS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class graph{
  int nvert; //Number of vertices
  vector<vector<bool> > adjacency;  //Adjacency matrix
  vector<vector<int> > edges;  //Matrix storing edge lengths
  vector<int> nodevalues;  //Node values, so far no use

public:
  //Initializer
  graph(int n = 0) {
    reset(n);
  }
  
  //Wipe graph data
  void reset(int n){
    nvert = n;         
    adjacency = create_matrix<bool>(n);
    edges = create_matrix<int>(n);    

    nodevalues.resize(nvert);
    nodevalues.clear();
  }

  //Read from file
  void read_edge_list(char* filename){
    ifstream infile(filename);
    string line;
    int n,a,b,v;
    
    infile >> n;
    reset(n);

    while (getline(infile, line)){
      infile >> a;
      infile >> b;
      infile >> v;

      set_double_edge(a,b,v);
    }
  }

  //Return size
  int size() {
    return nvert;
  }

  //Get edge length
  int get_edge(int i,int j) {
    return edges[i][j];
  }

  //Set edge length AND adjacency
  void set_edge(int i,int j, int value) {
    adjacency[i][j] = true;
    edges[i][j] = value;
  }

  //for double edge
  void set_double_edge(int i, int j, int value){
    set_edge(i,j,value);
    set_edge(j,i,value);
  }

  //Deleting adjacency, return edge length to 0
  void delete_edge(int i, int j) {
    adjacency[i][j] = false;
    edges[i][j] = 0;
  }

  //for double edge
  void delete_double_edge(int i, int j){
    delete_edge(i,j);
    delete_edge(j,i);
  }

  int get_node(int i){
    return nodevalues[i];
  }

  void set_node(int i, int value){
    nodevalues[i] = value;
  }

  //Check if 2 vertices are adjacent
  bool adjacent(int i,int j) {
    return adjacency[i][j];
  }

  //Return a vector containing all neighbors of i
  vector<int> neighbors(int i) {
    vector<int> neigh;
    for (int j=0;j<nvert;j++)
      if (adjacent(i,j)) neigh.push_back(j);
    return neigh;
  }

  //Return adjacency matrix
  vector<vector<bool> > adjacency_matrix() {
    return adjacency;
  }

  //Return the whole matrix with all edge lengths
  vector<vector<int> > edge_matrix() {
    return edges;
  }

  //Compute the shortest path between i and j, return a path structure
  //Note that we are not implementing shortes_path as a separated class but an inherent function of a given graph
  path shortest_path(int i, int j);

  //Search for minimum spanning tree
  tree minimum_spanning_tree(int root = 0);

  //Randomize according to given density and range
  void randomize(double density,int range);  
};

//Minimum spanning tree, using Prim's algorithm and priority queue
tree graph::minimum_spanning_tree(int root){
  int cost=0, current_vert, lookat_vert, new_distance ;
  vector<int> connectivity(nvert), y;
  vector<bool> done(nvert);
  vert_queue myqueue; //This queue updates each unvisited vertex's distance to the nearest visited one

  for(int i=0;i<nvert;++i)
    connectivity[i] = -1;  

  connectivity[root] = root;  //The root is just connected to itself
  myqueue.push(vert_dist(root,0));  //Push the root into the queue as the first element

  while(!myqueue.empty()){
    current_vert = myqueue.top().vert;  //This is the vertex with least distance from the visited ones

    if(!done[current_vert]){  //Make sure this is an unvisited vertex
      cost += myqueue.top().dist;  //Add in the cost
      y = neighbors(current_vert);  //Now look at the neighbors of this vertex

      for(int i=0;i<y.size();++i){
	lookat_vert = y[i];
	if (!done[lookat_vert]){  //Skip the visited neightbors
	  new_distance = edges[lookat_vert][current_vert];
	  if ((connectivity[lookat_vert] == -1) || (edges[lookat_vert][connectivity[lookat_vert]] > new_distance)){  
	    connectivity[lookat_vert] = current_vert;  //Update connectivity if a shorter edge is found
	    myqueue.push(vert_dist(lookat_vert, new_distance));  //Try to update the distance of this neighbor and push that in the queue
	  }
	}
      }

      done[current_vert] = true;  //Mark as visited
    }

    myqueue.pop();  //And remove from queue
  }

  return tree(cost,connectivity);
}

//Dijkstra Algorithm for shortest path
path graph::shortest_path (int i, int j) {
  vector<int> found_sequence;  //The sequence of vertices forming the shortest path

  if (i == j) {  //The trivial case when START = STOP
    found_sequence.push_back(i);
    return path(0,found_sequence);
  }
  else
    {       
      vector<bool> done(nvert);  //To keep track of visited vertices
      vector<int> precede(nvert);  //Which vertex precedes which? For latter use in reconstructing the sequence
      vector<int> distance(nvert);  //Tentative distance from START
      
      for (int k=0;k<nvert;++k)	{  //Set everything at distance -1 except START
	  distance[k] = -1;
	  precede[k] = -1;
      }
      
      distance[i] = 0;  //Set START at distance 0
      
      vert_queue my_queue;  //Declare an empty queue of nodes with tentative vertices
      vert_dist x(i,0);  //Current node, having a vertex index and its tentative distance
      vector<int> y;  //To contain all neighbors of the current node

      my_queue.push(x);  //Push START with distance 0 to the queue

      int current_vert, lookat_vert;  //Current vertex and its possible neighbors
      int new_distance;  //To update distance                 
      
      while(!my_queue.empty()){	
	x = my_queue.top();  //Get the node with shortest tentative distance
	my_queue.pop();  //And move it out of the queue		
	current_vert = x.vert;  //Get the vertex index
	
	if (done[current_vert] == false){	  
	  y = neighbors(current_vert);	//Get all neighbors  

	  for (int k=0;k<y.size();++k){	    
	    lookat_vert = y[k];
	    if (!done[lookat_vert]){  //Do this unless visited before
	      new_distance = distance[current_vert] + edges[current_vert][lookat_vert];
	      if ((distance[lookat_vert] == -1) || (new_distance < distance[lookat_vert])) {  //If a shorter path is known
		my_queue.push(vert_dist(lookat_vert,new_distance));  //Push in queue
		distance[lookat_vert] = new_distance;  //Update distance
		precede[lookat_vert] = current_vert;  //Update precedence
	      }
	    }
	  }
	  done[current_vert] = true;  //Mark as visited
	  if (current_vert == j) break;  //Break when reach STOP
	}
      }

      if (done[j] == true){  //If a path to j is found, i.e j was visited
	found_sequence.push_back(j);

	for (int k=0; k<nvert;++k){
	  if (precede[found_sequence[k]] == -1) break;  //Trace back the sequence
	  else found_sequence.push_back(precede[found_sequence[k]]);	  
	}
	
	found_sequence = reverse(found_sequence);  //Reverse the sequence
      }
      
      return path(distance[j],found_sequence);
    } 
}

//For Monte-Carlo randomization
void graph::randomize (double density,int range) {
  double pick = 0;  //probability variable
  edges = create_matrix<int>(nvert);
  adjacency = create_matrix<bool>(nvert);

  for (int i=0;i<nvert;++i)
    for (int j=i+1;j<nvert;++j){
	pick = rand() % 100;
	pick = pick/100;	
	if (pick < density)
	  set_double_edge(i,j,(rand()%range +1));
    }
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


int main() {    
  
  graph g;

  //Put data in "MST_data.txt"
  g.read_edge_list("MST_data.txt");

  tree t = g.minimum_spanning_tree();
  t.display();

  cout << endl << endl;

  system("PAUSE");

 

  /*HOMEWORK 1 STUFF
  graph graph1(50), graph2(50);
  double average1, average2;
  double final1, final2;
  int count1, count2, dist1, dist2;

  srand (time(NULL));
  
  //RE-RANDOMIZE 100 TIMES
  for (int i=0;i<1000;++i){    
    graph1.randomize(0.4,10);
    graph2.randomize(0.6,10);

    average1 = average2 = 0;
    count1 = count2 = 0;

    for (int j=0;j<50;++j){
      dist1 = graph1.shortest_path(0,j).length;
      dist2 = graph2.shortest_path(0,j).length;
      
      if (dist1 >= 0){
	average1 += dist1;
	++count1;
      }

      if (dist2 >= 0){
	average2 += dist2;
	++count2;
      }
    }

    average1 /= count1;
    average2 /= count2;

    cout << "ITERATION " << i << endl;
    cout << "Average shortest path length with 0.4 edge density: " << average1 << endl;
    cout << "Average shortest path length with 0.6 edge density: " << average2 << endl << endl;

    final1 += average1;
    final2 += average2;
  }

  final1 /= 1000;
  final2 /= 1000;
  
  cout << endl << "Limit average shortest path with density 0.4 after 100 iterations " << final1 << endl;
  cout << endl << "Limit average shortest path with density 0.6 after 100 iterations " << final2 << endl;
  */

  /*FINER DENSITY, MORE VERTICES
  graph random_graph(100);
  double average;
  int count, dist;
     
  for (double i=0.01;i<=1;i=i+0.01){
    cout << "Density " << i << " " ;    
    random_graph.randomize(i,10);    

    average = 0;
    count = 0;
  
    for (int j=0; j<random_graph.size();++j){
      dist = random_graph.shortest_path(0,j).length;    
      if (dist >= 0) {
        average += dist;
	++count;
      }
    }
      
    average /= count;
    
    cout << "Average path: " << average << endl;
  }
  */
  

  /* EXAMPLE IN LECTURE
  graph mygraph(9);
  
  mygraph.set_edge(0,1,4);
  mygraph.set_double_edge(0,2,3);
  mygraph.set_edge(0,4,7);
  mygraph.set_edge(1,3,1);
  mygraph.set_edge(2,4,4);
  mygraph.set_edge(3,4,3);
  mygraph.set_edge(3,5,1);
  mygraph.set_edge(4,5,1);
  mygraph.set_edge(4,6,5);
  mygraph.set_edge(4,8,3);
  mygraph.set_double_edge(5,7,2);
  mygraph.set_edge(5,8,4);
  mygraph.set_edge(7,8,3);
  mygraph.set_edge(8,6,5);

  path p = mygraph.shortest_path(0,8);
  p.display(); 
  */
}


//need to fix:
//multi initializers for class graph
//destructor
//correct pointers for parameters
//class matrix
//class path
//correct public/private
