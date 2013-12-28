#include <iostream>
#include <list>
#include <vector>
#include <time.h>
#include <algorithm>
using namespace std;
//using the STL <list>container to contain node and its corresponding edge value
class graph{
	public:
		int V(){return size;};	//returns the number of vertices in the graph
		double Edge(){int sum=0;
			for(int i=0;i<size;i++){
				for(int j=i;j<size;j++)
				if (G[i][j]) {sum++;}}
			return sum;
		};	//returns the number of edges in the graph
		bool adjacent(int x, int y){
			return G[x][y];
		};	//tests whether there is an edge from node x to node y
		int numofneighbors(int x){
			int sum=0;
			for(int i=0;i<size;i++){
			if(G[x][i]) sum++;
			}
			return sum;
		};	//returns the number of neighbors of node x
		int* neighbors(int x){
			int*p,j=0;p=new int[size];
			for (int i=0;i<size;i++){
				if(G[x][i]){*(p+j)=i;j++;}
			}
			return &p[0];
		};	//lists all nodes y such that there is an edge from x to y.
		void add(int x,int y){
			if (G[x][y]==0)
				G[x][y]=G[y][x]=true;
		};		//adds to G the edge from x to y, if it is not there.
		void del(int x, int y){
			if (G[x][y])
				G[x][y]=G[x][y]=false;
		};	//removes the edge from x to y, if it is there.
		//int get_node_value(int x){};
		//int set_node_value(int x, int a){};
		double get_edge_value(int x,int y){
			return E[x][y];
		};	//get the edge value between node x and node y
		void set_edge_value(int x, int y,double v){
			E[x][y]=E[y][x]=v;
		};	///set the edge value between node x and node y
		void disp(){
			cout<<"This is the adjacency matrix"<<endl;
			for(int i=0;i<size;i++){
				for (int j=0;j<size;j++){
					cout<<G[i][j]<<" ";
				}
				cout<<endl;
			}
			cout<<"This is the edge matrix"<<endl;
			for(int i=0;i<size;i++){
				for (int j=0;j<size;j++){
					cout<<E[i][j]<<"       ";
				}
				cout<<endl;
			}
		};	//display the graph
		void generate(int s,double d,double r){
				size=s;density=d;range=r;
				srand(time(0));G=new bool*[size];E=new double*[size];
				for (int i=0;i<size;++i) {
					G[i]=new bool[size]; E[i]=new double[size];
				}
				for(int i=0;i<size;i++){
				for(int j=i;j<size;j++){
				if (i==j){G[i][j]=false;}
				else {G[i][j]=G[j][i]=((rand()/double(RAND_MAX))<density);
				}}}
				for(int i=0;i<size;i++){
				for(int j=i;j<size;j++){
					if (G[i][j]){
						E[i][j]=E[j][i]=range*(double((rand()%901+100)/100.0))/10.0;}	//random number between 1 and 10
						else E[i][j]=E[j][i]=0;
				}}
				};	//generate a graph 
		graph(int s=50,double d=0.1,double r=10):size(s),density(d),range(r){
				srand(time(0));G=new bool*[size];E=new double*[size];
				for (int i=0;i<size;++i) {
					G[i]=new bool[size]; E[i]=new double[size];
				}
				for(int i=0;i<size;i++){
				for(int j=i;j<size;j++){
				if (i==j){G[i][j]=false;}
				else {G[i][j]=G[j][i]=((rand()/double(RAND_MAX))<density);
				}}}
				for(int i=0;i<size;i++){
				for(int j=i;j<size;j++){
					if (G[i][j]){
						E[i][j]=E[j][i]=range*(double((rand()%901+100)/100.0))/10.0;}
						else E[i][j]=E[j][i]=0;
				}}
				};	//initialize the graph
	private:
		int size;double density;double range;
		bool **G;
		double **E;
};

class data{
public:
	data(int a,double b):node(a),edge(b){};
	bool operator < (const data&i)const{		//overload the operator< for using openset.sort() function,which only depend the edge value
		return (edge<i.edge);
	};
	bool operator==(const data&i)const{			//overload for using find() and count() function
		return (node==i.node);
	};
	int node;
	double edge;
};	//create a new data container, and overload operators for the use of .sort() and find() function in the stl

typedef list<data>mytype;	//create a new type,which is a list and the type of it's element is "data"

class ShortestPath{
public:
	ShortestPath(int s=50,double d=0.1,double r=10){	//initializing a graph contained in class ShortestPath by calling the method .generate()
		g.generate(s,d,r);
	}

	graph get_graph(){return g;};

	double path_size(int u,int w){			//return the shortest path value using Dijkstra's algorithm
		openset.clear();closedset.clear();	//clean the openset and closedset
		data node_end(w,0);					//define the destination node
		data node_begin(u,0);				//define the starting node
		closedset.push_back(node_begin);	//put the starting node in the closedset
		int num=0;
		double input = 0;
		while (1){
				num=count(closedset.begin(),closedset.end(),node_end);		//return whether the destination node is in the closedset
				if (num!=0){break;}											//when node w is in the closed set, stop
				for (int i=0;i<g.numofneighbors(closedset.back().node);i++){	//get the number of nodes which the latest node in closed set could reach, start loop
					int n2=*(g.neighbors(closedset.back().node)+i);		//n2 means the ith node that the latest node in closedset could reach 
					int n1;												//the node number of latest node in closedset
					double closed_edge; double open_edge;
					//double input;			//which should equals the edge value in the open set
					int num1=count(closedset.begin(),closedset.end(),data(n2,1));	//find whether the node n2 is in the closed set, if n2 is already in the closed set,dont do anything
					if (num1==0)													//if node n2 is not in the closed set
					{
					n1=closedset.back().node; closed_edge=closedset.back().edge;	
					open_edge=g.get_edge_value(n1,n2);
					input = closed_edge + open_edge;
					}																//compute the edge value(input)
					int num2=count(openset.begin(),openset.end(),data(n2,1));		
				if (num2!=0 && find(openset.begin(),openset.end(),data(n2,1))->edge<=input){}	//if n2 is already in the openset and its edge value(input) doesn't improve the original one,dont updat
				else
					openset.push_back(data(n2,input));
				}																				//else, update the openset value
				if (openset.size()<=0){break;}			
				openset.sort();																	//sort the openset according to its edge value, ascending
				closedset.push_back(openset.front());											//put the first element of openset into closed set
				openset.pop_front();															//remove the first element of openset
		};																						//repeat!!!
		if (num!=0){return closedset.back().edge;}												//if there exists a path,return the path value
		else {return 0;}																		//if not, return 0;
		};


		vector<int> path(int u,int w){															//return the route of shortest path, since it has nothing to do with the result in this assignment,you can skip it:)
		openset.clear();closedset.clear();
		data node_end(w,0);
		data node_begin(u,0);closedset.push_back(node_begin);
		int num=0;
		while (1){
				num=count(closedset.begin(),closedset.end(),node_end);
				if (num!=0){break;}//when node w is in the closed set, stop
				for (int i=0;i<g.numofneighbors(closedset.back().node);i++){	//get the number of nodes which the latest node in closed set could reach, start loop
					int n2=*(g.neighbors(closedset.back().node)+i);	//n2 means the ith node the latest node in closedset could reach 
					int n1;	//the node number of latest node in closedset
					double closed_edge; double open_edge;
					double input;	//which should equals the edge value in the open set
					int num1=count(closedset.begin(),closedset.end(),data(n2,1));
					if (num1==0)
					{
					n1=closedset.back().node;closed_edge=closedset.back().edge;
					open_edge=g.get_edge_value(n1,n2);
					input = closed_edge + open_edge;
					}
					int num2=count(openset.begin(),openset.end(),data(n2,1));
				if (num2!=0 && find(openset.begin(),openset.end(),data(n2,1))->edge<=input){}
				else
					openset.push_back(data(n2,input));
				}
				if (openset.size()<=0){break;}			
				openset.sort();
				closedset.push_back(openset.front());
				openset.pop_front();				
				}
				
		vector<int>d;	//a container which contains the route
		int n=closedset.size();	
		double size;int node;	//get the node and put it into d(contains the route)
		if (num!=0)	//when there exits a path
		{
			size=closedset.back().edge;
			node=closedset.back().node;	//start with the destination
			d.push_back(node);
			while(1){
			mytype::iterator i=closedset.begin();
			for (;i!=closedset.end();++i)	//go through the entire closed set
			{
				
				double s1=size-(i->edge);
				double s2=g.get_edge_value((i->node),node);
				if ( (s1==s2) && s2!=0 )				
				{
					d.push_back((i->node));
					size=(i->edge);
					node=(i->node);
					cout<<endl;
					break;
				}
			}
				int n=0;			
				for(int i=0;i<d.size();++i)	//go through the entire route set
				{
					cout<<d[i]<<endl;
					if (d[i] == u){n=1;}
				}
				if (n==1){break;}
			}
		return d;
		}
		//d.clear();d.push_back(-1);	//means there is no path
		//return d;
	};
private:
	graph g;
	mytype openset;
	mytype closedset;
};

int main(){
	double SUM=0;
	for(int i=0;i<1000;i++){
	ShortestPath map1(50,0.2,10);	//generating 50-nodes graph which density is 0.2，range is 10 in each test, 1000 graph in total
	double sum=0;int n=0;
	for (int i=0;i<50;i++){
		//cout<<i<<endl;
	if (map1.path_size(0,i)!=0){
		n++;sum=sum+map1.path_size(0,i);};
	};
	sum=sum/n;
	SUM=SUM+sum;
}
	SUM=SUM/1000;					//make 1000 trials and compute the average

	cout<<"########################################"<<endl;
	cout<<"Test started..."<<endl;
	cout<<"density=20%: the average path size is about "<<SUM<<endl;
	//cout<<n<<endl;
 	SUM=0;
	for(int i=0;i<1000;i++){
	double sum=0;int n=0;
	ShortestPath map2(50,0.4,10);	//generating 50-nodes graph which density is 0.4，range is 10 in each test, 1000 graph in total
	sum=0;n=0;
	for (int i=0;i<50;i++){
		//cout<<i<<endl;
		if(map2.path_size(0,i)!=0){
			n++;sum=sum+map2.path_size(0,i);
		}
	}
	sum=sum/n;
	SUM=SUM+sum;					
	};
	SUM=SUM/1000;					//make 1000 trials and compute the average
	cout<<"density=40%: the average path size is about "<<SUM<<endl;
	cout<<"...test ended"<<endl;
	cout<<"#########################################"<<endl;
}