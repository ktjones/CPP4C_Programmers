/*
 * HWFive.cpp
 *
 *  Created on: 2013-11-30
 *      Author: bob
 *      I reuse the code of HW4 to build a Hex game on an 11 by 11 board.
 *      The computer is able to play Hex intelligently against a human, using Monte Carlo methods
 *      your input format is i,j, where i is the index of row and j is the index of column.
 *      Generating a random serial input, I use the method random_shuffle from the new C++11 library <random>
 *      The computational time for a computer move is no more than 2 minutes, which is approximate 90 seconds on my computer
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <limits>
#include <fstream>
#include <sstream>
#include <queue>
#include <map>
#include <functional>
#include <algorithm>
#include <random>
#include <time.h>
using namespace std;

typedef double priorityType;
typedef pair<int,priorityType> Type_Queue_Element;

template<class T>
T str2num(string s){
    T num;
    stringstream ss(s);
    ss>>num;
    ss.str("");
    return num;
}

typedef double type_edge;
const int INF=60000;
enum class Color{WHITE, RED, BLUE};

class Graph {
public:
//need to do: distance range as parameters
	Graph(int N=7);  // build for hex game
	Graph(const Graph &other); // copy constructor
	Graph& operator = (const Graph &other); // assign constructor
	virtual ~Graph();
	int V(void);                              // returns the number of vertices in the graph
	int E(void);                              // returns the number of edges in the graph
	bool adjacent(int x, int y);      // tests whether there is an edge from node x to node y.
	vector<int> neighbors(int x,Color color=Color::WHITE);           // lists all nodes y such that there is an edge from x to y.
	void add(int x,int y, type_edge v);            //adds to G the edge from x to y, if it is not there.
	void deleteE(int x,int y);        //removes1 the edge from x to y, if it is there.
	Color get_node_value(int x);        //returns the value associated with the node x.
	void set_node_value(int x,Color a);  //sets the value associated with the node x to a.
	type_edge get_edge_value(int x,int y);  //returns the value associated to the edge (x,y).
	int set_edge_value (int x,int y,type_edge v); //sets the value associated to the edge (x,y) to v.
	//void control(Graph &other);

private:
	int size;   //the number of vertices in the graph
	int nEdge; // the number of edges in the graph
	bool** graph;   // Connectivity matrix
	type_edge** weight;
    Color * nodes;    // the color of nodes
	type_edge prob();
	type_edge length(type_edge minEdgeLen,type_edge maxEdgeLen);
};

inline type_edge Graph::prob(){
	return rand()/static_cast<float>(RAND_MAX);
}

inline type_edge Graph::length(type_edge minEdgeLen,type_edge maxEdgeLen){
	return minEdgeLen+(maxEdgeLen-1)*(rand()/static_cast<float>(RAND_MAX));
}

Graph::Graph(int N):size(N*N+4){  // build for hex game   4 is virtual nodes!!!   They are N*N(north),N*N+1(south),N*N+2(east), N*N+3(west)
	nEdge=0;
	 // 2 three neighbors corners, 2 two neighbors corners, (N-2) four neighbors edges. (N-2)^2  6 neighbors internal nodes
	graph = new bool*[size];
	weight = new type_edge*[size];
	nodes = new Color[size];
	for(int i = 0; i <size; ++i){ // first initialization
		graph[i] = new bool[size]();
		weight[i]= new type_edge[size]();
		set_node_value(i,Color::WHITE); // WHITE as not occupied
	}
	int north=N*N;
	int south=north+1;
	int east=south+1;
	int west=east+1;
	set_node_value(north,Color::RED);
	set_node_value(south,Color::RED);
	set_node_value(east,Color::BLUE);
	set_node_value(west,Color::BLUE);
			// virtual nodes

	for(int i = 0; i <size-4; ++i){ //
		int row=i/N;
		int col=i%N;

		if(row==0){ // north N*N   RED
			graph[i][north]=graph[north][i]=true;
			weight[i][north]=weight[north][i]=1.0;
		}


		if(row==N-1){ //(south) N*N+1  RED
			graph[south][i]=graph[i][south]=true;
			weight[south][i]=weight[i][south]=1.0;
		}

		if(col==0){ //(east) N*N+2   BLUE
			graph[east][i]=graph[i][east]=true;
			weight[east][i]=weight[i][east]=1.0;
		}
		if(col==N-1){ //(west) N*N+3   BLUE
			graph[west][i]=graph[i][west]=true;
			weight[west][i]=weight[i][west]=1.0;
		}


		if(row-1>=0){       // up
			graph[i][(row-1)*N+col]=true;
			weight[i][(row-1)*N+col]=1.0;
			nEdge++;
		}

		if(row-1>=0 && col+1<N){       // upRight
			graph[i][(row-1)*N+col+1]=true;
		    weight[i][(row-1)*N+col+1]=1.0;
		    nEdge++;
		}

		if(col-1>=0){       // left
			graph[i][row*N+col-1]=true;
			weight[i][row*N+col-1]=1.0;
			nEdge++;
		}

		if(col+1<N){       // right
			graph[i][row*N+col+1]=true;
			weight[i][row*N+col+1]=1.0;
			nEdge++;
		}

		if(row+1<N && col-1>=0){       // downleft
			graph[i][(row+1)*N+col-1]=true;
			weight[i][(row+1)*N+col-1]=1.0;
			nEdge++;
		}

		if(row+1<N){       // down
			graph[i][(row+1)*N+col]=true;
			weight[i][(row+1)*N+col]=1.0;
			nEdge++;
		}

	}
	nEdge=nEdge/2;//cout<<nEdge<<endl;
	if (nEdge!=3*N*N-4*N+1) cout<<"nEdge not right!!"<<endl;
}

Graph::Graph(const Graph &other){ // copy constructor
	size=other.size; //
	nEdge=other.nEdge; //
	graph = new bool*[size];
	weight = new type_edge*[size];
	nodes = new Color[size];
	for(int i = 0; i <size; ++i){ // first initialization
		graph[i] = new bool[size]();
		weight[i]= new type_edge[size]();
		set_node_value(i,other.nodes[i]); // copy the values
		}

	for (int i = 0; i < size; ++i)
		for(int j = i; j < size; ++j){
			graph[j][i]=graph[i][j]=other.graph[i][j];
			weight[i][j]=weight[j][i]=other.weight[i][j];
		}
}

Graph& Graph::operator = (const Graph &other){ // assign constructor

	if(this == &other)
	return *this;
// first delete
	for(int i = 0; i <size; ++i){
		delete[] graph[i]; //release low dimension
		delete[] weight[i];
		}
	delete[] graph; // release high dimension
	delete[] weight;
	delete[] nodes;
	graph=NULL;
	weight=NULL;
// then allocate
	size=other.size;
    nEdge=other.nEdge;
	graph = new bool*[size];
	weight = new type_edge*[size];
	nodes = new Color[size];
	for(int i = 0; i <size; ++i){ // first initialization
		graph[i] = new bool[size]();
		weight[i]= new type_edge[size]();
		set_node_value(i,other.nodes[i]); // copy the values
		}
	for (int i = 0; i < size; ++i)
		for(int j = i; j < size; ++j){
			graph[j][i]=graph[i][j]=other.graph[i][j];
			weight[i][j]=weight[j][i]=other.weight[i][j];
		}
	return *this;
}

Graph::~Graph() {
	// TODO Auto-generated destructor stub
	for(int i = 0; i <size; ++i){
	delete[] graph[i]; //release low dimension
	delete[] weight[i];
	}
	delete[] graph; // release high dimension
	delete[] weight;
	delete[] nodes;
    graph=NULL;
    weight=NULL;
    //cout<<"call Graph destructor"<<endl;
}

 int Graph::V(){   // returns the number of vertices in the graph
	return this->size;
}

 int Graph::E(){ // returns the number of edges in the graph
	return this->nEdge;
}

int Graph::set_edge_value (int x,int y,type_edge v){ // can be done if only edge exist. always check graph[x][y] before set weight
	if (graph[x][y]) weight[x][y]=v;
	return 0;
}

type_edge Graph::get_edge_value(int x,int y){
	return weight[x][y];
}

bool Graph::adjacent(int x, int y){  // tests whether there is an edge from node x to node y.
	return graph[x][y];
}

vector<int> Graph::neighbors(int x,Color color){ // lists all nodes y such that there is an edge from x to y.
	vector<int> neibs;
	for(int y=0;y<size;y++)
		if(graph[x][y]==true && x!=y && color==get_node_value(y))
			neibs.push_back(y);
	return neibs;
}

void Graph::add(int x,int y, type_edge v){            //adds to G the edge from x to y, if it is not there.
	if (x == y) {
	//	cout<<"no loop"<<endl;
		graph[x][y]=false;
		weight[x][y]=0.0;
	} else {
		if(graph[x][y]!=true){   // it was not there
			nEdge+=static_cast<unsigned int>(graph[x][y]);   //count the number of edges
		    graph[x][y] = true;
		    graph[y][x] = graph[x][y];
		//type_edge egWght=length();
		    set_edge_value(x,y,v);
		    set_edge_value(y,x,v);
		}
	}
}

void Graph::deleteE(int x,int y){        //removes the edge from x to y, if it is there.
	graph[x][y]=false;
	weight[x][y]=0.0;
}

Color Graph::get_node_value(int x){        //returns the value associated with the node x.
	return nodes[x];
}

void Graph::set_node_value(int x,Color a){  //sets the value associated with the node x to a.
    nodes[x]=a;
}

/////////////////////////
class PriorityQueue {
public:
	PriorityQueue();
	virtual ~PriorityQueue();
	void chgPrioirity(Type_Queue_Element queue_element,priorityType priority); //changes the priority (node value) of queue element.
	void chgPrioirity(int node,priorityType priority); //changes the priority (node value) of queue element.
	void minPrioirty(); // removes the top element of the queue.
	bool contains(Type_Queue_Element queue_element); // does the queue contain queue_element.
	bool contains(int node); // does the queue contain queue_element.
	void Insert(Type_Queue_Element queue_element); // insert queue_element into queue
	Type_Queue_Element top();  //returns the top element of the queue.
	int size(); // return the number of queue_elements.
	bool empty();  // if it is empty?
	void clear(); // clear the queue
private:
        vector<Type_Queue_Element> data;
};


bool Comp(const Type_Queue_Element & s1, const Type_Queue_Element &s2){
       return s1.second > s2.second;
}

struct CompareFirst{
  CompareFirst(int val) : val_(val) {}
  bool operator()(const Type_Queue_Element & elem) const {
    return val_ == elem.first;
  }
  private:
    int val_;
};

PriorityQueue::PriorityQueue() {
	// TODO Auto-generated constructor stub
	//make_heap (data.begin(),data.end(),Comp);
}

PriorityQueue::~PriorityQueue() {
	// TODO Auto-generated destructor stub
}

void PriorityQueue::Insert(Type_Queue_Element queue_element){
	//data.insert(pair<int, int>(1, queue_element));
	//make_heap (data.begin(),data.end(),Comp);
	data.push_back(queue_element);
	push_heap(data.begin(),data.end(), Comp);
}

void PriorityQueue::minPrioirty(){ // removes the top element of the queue.
	pop_heap(data.begin(),data.end(),Comp );
	data.pop_back();
}

Type_Queue_Element PriorityQueue::top(){
	return data.front();
}

int PriorityQueue::size(){
	return data.size();
}

bool PriorityQueue::empty(){
	return data.empty();
}

void PriorityQueue::chgPrioirity(Type_Queue_Element queue_element,priorityType priority){
	vector<Type_Queue_Element >::iterator iterResult=find(data.begin(),data.end(), queue_element);
	iterResult->second=priority;
	make_heap (data.begin(),data.end(),Comp); // sort again
}

void PriorityQueue::chgPrioirity(int node,priorityType priority){ //
	vector<Type_Queue_Element >::iterator iterResult=find_if(data.begin(),data.end(), CompareFirst(node));
	iterResult->second=priority;
	make_heap (data.begin(),data.end(),Comp); // sort again
}

bool PriorityQueue::contains(Type_Queue_Element queue_element){ // does the queue contain queue_element.
	vector<Type_Queue_Element >::iterator iterResult=find_if(data.begin(),data.end(), CompareFirst(queue_element.first));
	return iterResult!=data.end();
}

bool PriorityQueue::contains(int node){ // does the queue contain queue_element.
	vector<Type_Queue_Element >::iterator iterResult=find_if(data.begin(),data.end(), CompareFirst(node));
	return iterResult!=data.end();
}

void PriorityQueue::clear(){
	//vector <int>().swap(data);
  data.clear(); //not decrease capacity

}

//////////////////// class Prim
class Prim {
public:
	Prim(Graph &R);
	virtual ~Prim();
	void mst(int root=0,const char *out_file_name="MST.txt"); // return MST tree. root node and Graph
	void mst(int root,Color color); // return MST tree. root node and Graph

	bool contains(int x, Color color);

private:
	Graph *G; // a pointer to a graph
	type_edge *dist;   //array of distances from the source to each vertex
	int *edges;     // array indicating, for a given vertex, which vertex in the tree it is closest to
	//in the end, represent MST. edges[i]=j means the precedent node of i is j
	PriorityQueue Q;
	bool ownGraph;  // it is created by you or not
	//vector<int> mstree;
};

const int NO_EDGE=-1;
const int ROOT_EDGE=numeric_limits<int>::max();

Prim::Prim(Graph &R){  // given a graph
	G=&R;
	ownGraph=false; // not created by you, you cannot delete!!
	int size=G->V();  // number of vertices
    dist=new type_edge[size];   //array of distances from the source to each vertex
    edges=new int[size];   // array indicating, for a given vertex, which vertex in the tree it is closest to
    for(int i=0;i<size;i++){  // initialization
    	dist[i]=INF;    // equal to infinite
        edges[i]=NO_EDGE;
        Q.Insert(Type_Queue_Element (i,dist[i]));  // assign V[G] to Q
    }
}

Prim::~Prim() {
	if(ownGraph==true){
		delete G;
		G=NULL;
	}
	delete dist;
	delete edges;
	dist=NULL;
	edges=NULL;
	// TODO Auto-generated destructor stub
}

void Prim::mst(int root,Color color){
	Q.clear();
	int size=G->V();  // number of vertices
	for(int i=0;i<size;i++){
		dist[i]=1000.0;
		edges[i]=NO_EDGE;
		if(G->get_node_value(i)==color){  // only choose the same color
		    	//dist[i]=INF;    // equal to infinite
			//cout<<"insert node!"<<i<<" and dist is "<<dist[i]<<endl;
		Q.Insert(Type_Queue_Element (i,dist[i]));  // assign V[G] to Q
		}
	}
	dist[root]=0.0;
	if(!Q.contains(root)) cout<<"not include root !!"<<endl;
	else {
		Q.chgPrioirity(root,dist[root]);   //dist[i] and priority value in priority queue must be synchronized
		edges[root]=ROOT_EDGE;
		while(!Q.empty()){
			Type_Queue_Element currElement=Q.top();
            Q.minPrioirty();  // remove from priority queue
			int currNode=currElement.first;
			if(edges[currNode]!=NO_EDGE){
				dist[currNode]=currElement.second;
				vector<int> neibs=G->neighbors(currNode,color);
				for(unsigned int i=0;i<neibs.size();i++){
					if(Q.contains(neibs[i]) && (G->get_edge_value(neibs[i],currNode)<dist[neibs[i]]) ){
						edges[neibs[i]]=currNode;
						dist[neibs[i]]=G->get_edge_value(neibs[i],currNode);
						Q.chgPrioirity(neibs[i],dist[neibs[i]]);
					}
				}
			}

		}
	}
}

bool Prim::contains(int x, Color color){ // does MST contains node x with color
	//int size=G->V();
	bool found_it=false;
    if(edges[x]!=NO_EDGE) found_it=true;
	//found_it=find(&edges[0],&edges[G->V()-1],x);cout<<"found_it is "<<*found_it<<endl;
	if(G->get_node_value(x)==color && found_it) return true;
	//if(found_it) return true;
	else return false;
}

////////////////////////////////////////////////// class HexGame
const int MonteCarloTrials=1000;

template<class T>
string num2str(T num){
	string s;
    stringstream ss;
    ss << num;
    ss >> s;
    ss.str("");
    return s;
}
enum class PLAYMODE{RANDOM, AI, MAN};
class HexGame {
public:
	HexGame(int N=11); // number of nodes
	virtual ~HexGame();
    void drawBoard();
    char mark(Color c);  // White: '.'  Blue: 'x'  RED: 'o'
    void game(bool first);  // first will choose blue
    int move(Color color);
    bool win(int x,Color color,int first); // if color wins after move to node x
    bool gameOver();   // game finish, return the winner
    int MontoCarloAI(Color color); // return the position
   // bool winMC(int x,Color color,Graph &gPrim); // if color wins after move to node x
    bool winMC(Color color,Graph &gPrim); // if color wins after move to node x
private:
	Graph *G;
	//Color **nodes;    // the color of nodes
    int N;
    deque<int> unoccupied;

};

HexGame::HexGame(int N):N(N) {
	// TODO Auto-generated constructor stub
	G=new Graph(N);
	int size=G->V();
	for(int i=0;i<size-4;i++){
		unoccupied.push_back(i);  // initialize the unoccupied nodes exclude the virtual nodes
	}
	drawBoard();
    bool first;
    cout<<"let's start to play!!!"<<endl<<"do you want to play first? input 0 for no, 1 for yes. If the number you input is neither 0 nor 1 ,it will be decided by the program ";
    cin>>first;
    cin.clear();
    cin.sync();
    first=first%2;
    game(first);
}

HexGame::~HexGame() {
	// TODO Auto-generated destructor stub
	delete G;
}

char HexGame::mark(Color c){  // White: '.'  Blue: 'x'  Red: 'o'
	if (c==Color::WHITE) return '.';
	else if(c==Color::RED) return 'o';
	else return 'x';  // BLUE
}

void HexGame::drawBoard(){
	int size=G->V(); // number of nodes
	string slash="\\";
	string yIndex;   // four blank, for alignment
	string xIndex;
	int alB;
	for(int i=1;i<N;i++)
	{
		slash=slash+" / \\";
	    if (i<N-1) cout<<" ";
	    else if(i==N-1)cout<<"    North "<<endl;
	   // yIndex=yIndex+num2str<int>(i-1)+"   ";
	    alB=i-1;
	    yIndex=yIndex+num2str<int>(alB)+"   ";
	}
	alB++;
	yIndex=yIndex+num2str<int>(alB);
	cout<<"    "+yIndex<<endl;
	for(int i=0;i<size-4;i++){
		int row=i/N;
		int col=i%N;
		Color color=G->get_node_value(i);
		if(col==0){  // the first element in the column
			xIndex=num2str<int>(row);
			if(row==N/2)xIndex="WEST "+xIndex;
			//if(row!=0) xIndex=" "+xIndex;
			while(xIndex.size()<4+static_cast<unsigned int>(row*2) ){
				xIndex=" "+xIndex;
			}
			cout<<xIndex<<mark(color)<<" - ";// only three blank, for alignment
		}
		else if(col==N-1){  // the last element in the column
			cout<<mark(color)<<row;
			if(row==N/2)cout<<"   EAST";
			cout<<endl;
			for(int i=0;i<2*row+1;i++)
				cout<<" ";
			if(row!=N-1){ // not the last row
				cout<<"    "<<slash<<endl; // four blank, for alignment
			}else {
				cout<<"   "<<yIndex<<endl;
				cout<<string(xIndex.size(),' ')<<"South"<<endl;
			}
		}
		else{    // the middle ones
			cout<<mark(color)<<" - ";
		}
	}
}

int HexGame::move(Color color){
    int x,row,col;
    char dot;
	do {
		cin.clear();
		cin.sync();
		cout<<"please input the row and columnnumber (0-"<<N-1<<")  ,the format is nRow,nCol "<<endl;
		cin>>row>>dot>>col;
		x=row*N+col;
		if(row>=0 && row<N && col>=0 && col<N && G->get_node_value(x)==Color::WHITE){
			G->set_node_value(x,color);
		    drawBoard();
		    auto iter=find(unoccupied.begin(),unoccupied.end(),x);
		    unoccupied.erase(iter);   // remove the occupied one
		    break;
		}
	}while(1);
	return x;   // return the move position
}

void HexGame::game(bool first){  // first will choose blue
	int currentPosition=0;
	Color your_color,computer_color;
	cout<<(first?"you choose to play first, your color is BLUE and your direction is from west to east.":"you are a gentleman, you will play after computer your color is RED, and your direction is from north to east")<<endl;
	if(first){
		your_color=Color::BLUE;
		computer_color=Color::RED;
		currentPosition=move(your_color);
		cout<<"your move is "<<"("<<(currentPosition/N)<<" , "<<currentPosition%N<<" )"<<endl;
	}else {
		your_color=Color::RED;
		computer_color=Color::BLUE;
	}

				do{
					clock_t start,finish;
					double totaltime;
					start=clock();
					currentPosition=MontoCarloAI(computer_color);
					finish=clock();
					totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
					cout<<"\n it takes "<<totaltime<<"seconds"<<endl;
					cout<<"the move of computer is "<<"("<<(currentPosition/N)<<" , "<<currentPosition%N<<" )"<<endl;
					if(win(currentPosition,computer_color,first))break;
					// your move
					currentPosition=move(your_color);
					if(win(currentPosition,your_color,first))break;
				}while(1);
				cout<<"game finish!!"<<endl;
}

bool HexGame::win(int x,Color color,int first){ // if color wins
	Prim* p=new Prim(*G);
	p->mst(x,color);  // calculate MST

   if(color==Color::RED){   // north, south
    	int north=N*N;
    	int south=north+1;
    	if(p->contains(north,color) && p->contains(south,color) ){
    		if(first) cout<<"you lost!!!red wins!!"<<endl;
        	else cout<<"you win!!! red wins!!"<<endl;
        	delete p;
        	return true;
         }
   } else if (color==Color::BLUE){    // east, west
    	int east=N*N+2;
    	int west=east+1;
    	if(p->contains(east,color) && p->contains(west,color) ){
    		if(first) cout<<"you win!!! blue wins!!"<<endl;
    		else cout<<"you lost! blue wins!!! "<<endl;
    	    delete p;
    	    return true;
    	}
   }
	delete p;
    return false;
}

bool HexGame::winMC(Color color,Graph &gPrim){ // if color wins after move to node x
	Prim* p=new Prim(gPrim);
	if(color==Color::RED){   // north, south
		int north=N*N;
	    int south=north+1;
	    p->mst(north,color);  // calculate MST

	    if(p->contains(south,color) ){
	    	delete p;
	        return true;
	    }
	}
	else if (color==Color::BLUE){    // east, west
		int east=N*N+2;
	    int west=east+1;
	    p->mst(east,color);  // calculate MST

	    if(p->contains(west,color) ){
	    	delete p;
	    	return true;
	    }
	}
	delete p;
	return false;
}


int HexGame::MontoCarloAI(Color color) {
	// TODO Auto-generated constructor stub
	cout<<"computer is thinking..."<<endl;
    int pMax,nWinsMax=0;
    Color oppCol;
    if(color==Color::RED)  oppCol=Color::BLUE;
    else  oppCol=Color::RED;
	for(auto position:unoccupied){  // unsorted unoccupied
		int nwins=0;
		Graph cfgG=*G; //make a copy to current configuration
		if(cfgG.get_node_value(position)==Color::WHITE)
			cfgG.set_node_value(position,color);
		else cout<<"something wrong on unoccupied"<<endl;
		auto cfgUnoccupied=unoccupied;
		auto iter=find(cfgUnoccupied.begin(),cfgUnoccupied.end(),position);
		cfgUnoccupied.erase(iter);// removes the element in position
		if(winMC(color,cfgG)){
			pMax=position;
			break; // if wins
		}
		for(int i=0;i<MonteCarloTrials;i++){ // for all monte carlo trials
			Graph cpG=cfgG; //make a copy
			auto cpUnoccupied=cfgUnoccupied;
			random_shuffle(cpUnoccupied.begin(), cpUnoccupied.end());  // generate a random series
			while(!cpUnoccupied.empty()){
                // it's opponent's turn
				int pos=cpUnoccupied.front();
				cpUnoccupied.pop_front(); //removes the first element
				if(cpG.get_node_value(pos)==Color::WHITE) cpG.set_node_value(pos,oppCol);
				else {
					cout<<"pos is "<<pos<<" something wrong with unoccupied in oppCol"<<endl;
				    cout<<( (cpG.get_node_value(pos)==Color::BLUE)?"BLUE":"RED" )<<endl;
				    cout<<"oppCol is "<<( (oppCol==Color::BLUE)?"BLUE":"RED" )<<endl;
				}
				if(!cpUnoccupied.empty()){
					pos=cpUnoccupied.front();
					cpUnoccupied.pop_front(); //removes the first element
					if((cpG.get_node_value(pos)==Color::WHITE) )cpG.set_node_value(pos,color);
				}
			}
			if(winMC(color,cpG))nwins++;
			// after fill up the board
		}   // end of one trial

		if(nwins>nWinsMax){
			nWinsMax=nwins;
			pMax=position;
		}
	}  // for each next possible move
	auto iter=find(unoccupied.begin(),unoccupied.end(),pMax);
	unoccupied.erase(iter);   // remove the occupied one
	G->set_node_value(pMax,color);
	drawBoard();
	return pMax;
}

int main(){
	int N=11;  // play on a 11*11 board
	HexGame hx(N);  // initialize and start to play
}



