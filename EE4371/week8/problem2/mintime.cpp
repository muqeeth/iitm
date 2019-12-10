/*Implemented dinic algorithm for maximum flow from geeksforgeeks
The algorithm runs bfs in every iteration and assign levels to all nodes , a flow is possible 
for levels 0,1,2,3....It creates residual graph  with it. The algorithm terminates
if no more flow is possible. Finally we do bfs at source and print flow in each edge.*/
#include<iostream>
#include<vector>
#include<queue>
#include<list>
#include<algorithm>
#include<limits.h>
#include"graph.h"
#define INF 10000
using namespace std; 

struct edge 
{ 
	int v ; 
	int flow ; 
	int C;
	int rev ;
	double dist; 
	int speed;
}; 

class Graph 
{ 
	int V; 
	double *level ; 
	vector< edge > *adj; 
public : 
	Graph(int V) 
	{ 
		adj = new vector<edge>[V]; 
		this->V = V; 
		level = new double[V]; 
	}  
	void addEdge(int u, int v, int C,double dist,int speed) 
	{ 
		edge a = {v, 0, C, adj[v].size(),dist,speed};  
		edge b = {u, 0, 0, adj[u].size(),dist,speed}; 
		adj[u].push_back(a); 
		adj[v].push_back(b);
	} 

	bool BFS(int s, int t); 
	int sendFlow(int s, int flow, int t, int ptr[]); 
	int DinicMaxflow(int s, int t); 
	void printAllPathsUtil(int u, int d, bool visited[], 
							int path[], int &path_index);
	void printAllPaths(int s, int d);
	void print(int s,int t);
}; 

// bool Graph::BFS(int s, int t) 
// { 
// 	for (int i = 0 ; i < V ; i++) 
// 		level[i] = -1; 

// 	level[s] = 0;
// 	priority_queue< pair<double, int>, vector <pair<double, int> > , greater<pair<double, int> > > q; 
// 	q.push(make_pair(0,s)); 

// 	vector<edge>::iterator i ; 
// 	while (!q.empty()) 
// 	{ 
// 		pair<double,int> u = q.top(); 
// 		q.pop(); 
// 		for (i = adj[u.second].begin(); i != adj[u.second].end(); i++) 
// 		{ 
// 			edge &e = *i; 
// 			if (level[e.v] < 0 && e.flow < e.C) 
// 			{ 
// 				level[e.v] =level[u.second]+1 ;
// 				q.push(make_pair(e.dist/e.speed,e.v)); 
// 			} 
// 		} 
// 	} 
// 	return level[t] < 0 ? false : true ; 
// } 
bool Graph::BFS(int s, int t) 
{ 
	for (int i = 0 ; i < V ; i++) 
		level[i] = -1; 

	level[s] = 0;
	list< int > q; 
	q.push_back(s); 

	vector<edge>::iterator i ; 
	while (!q.empty()) 
	{ 
		int u = q.front(); 
		q.pop_front(); 
		for (i = adj[u].begin(); i != adj[u].end(); i++) 
		{ 
			edge &e = *i; 
			if (level[e.v] < 0 && e.flow < e.C) 
			{ 
				level[e.v] = level[u] + 1; 

				q.push_back(e.v); 
			} 
		} 
	} 
	return level[t] < 0 ? false : true ; 
}

int Graph::sendFlow(int u, int flow, int t, int start[]) 
{ 
	if (u == t) 
		return flow; 
 
	for ( ; start[u] < adj[u].size(); start[u]++) 
	{ 
		edge &e = adj[u][start[u]]; 
									
		if (level[e.v] == level[u]+1 && e.flow < e.C) 
		{ 

			int curr_flow = min(flow, e.C - e.flow); 

			int temp_flow = sendFlow(e.v, curr_flow, t, start);  
			if (temp_flow > 0) 
			{ 
				e.flow += temp_flow; 	
				adj[e.v][e.rev].flow -= temp_flow; 
				return temp_flow; 
			} 
		} 
	} 

	return 0; 
} 
void Graph::printAllPaths(int s, int d) 
{ 
	// Mark all the vertices as not visited 
	bool *visited = new bool[V]; 

	// Create an array to store paths 
	int *path = new int[V]; 
	int path_index = 0; // Initialize path[] as empty 

	// Initialize all vertices as not visited 
	for (int i = 0; i < V; i++) 
		visited[i] = false; 

	// Call the recursive helper function to print all paths 
	printAllPathsUtil(s, d, visited, path, path_index); 
}
void Graph::printAllPathsUtil(int u, int d, bool visited[], 
							int path[], int &path_index) 
{ 
	// Mark the current node and store it in path[] 
	visited[u] = true; 
	path[path_index] = u; 
	path_index++; 

	// If current vertex is same as destination, then print 
	// current path[] 
	if (u == d) 
	{ 
		for (int i = 0; i<path_index; i++){
            cout << path[i] << " ";
        } 

		cout << endl; 
	} 
	else // If current vertex is not destination 
	{ 
		// Recur for all the vertices adjacent to current vertex 
		vector<edge>::iterator i; 
		for (i = adj[u].begin(); i != adj[u].end(); ++i) 
			if (!visited[(*i).v] && (*i).flow>0) 
				printAllPathsUtil((*i).v, d, visited, path, path_index); 
	} 

	// Remove current vertex from path[] and mark it as unvisited 
	path_index--; 
	visited[u] = false; 
}
void Graph::print(int s, int t) 
{ 
	for(int u=0;u<V;u++){
		vector<edge>::iterator i ;
		for (i = adj[u].begin(); i != adj[u].end(); i++) 
		{ 
			edge &e = *i;
			if((*i).flow>0){
				cout<<u<<" "<<e.v<<" "<<e.flow<<endl;
			}  
		}
	}
} 
int Graph::DinicMaxflow(int s, int t) 
{ 

	if (s == t) 
		return -1; 

	int total = 0; 
	//cout<<BFS(s,t)<<endl;
	while (BFS(s, t) == true) 
	{ 
		int *start = new int[V+1]; 
		while (int flow = sendFlow(s, INT_MAX, t, start))  
			{total += flow;} 
	}
	//print(s,t); 
	//cout<<total<<endl;
	return total; 
} 

int main() 
{ 
	graph G;
	G.read_graph("tn_graph.txt");
    int V = G.no_nodes;
    int E = G.no_edges;
    Graph g(V);
	int x = 500;
    for(int i=0;i<E;i++){
        int d;
		int speed;
        if(G.edges[i].type=='p'){d=100;speed=60;}
        else if(G.edges[i].type=='s'){d=50;speed=40;}
        else {d=20;speed=30;}
        g.addEdge(G.edges[i].nodes[0],G.edges[i].nodes[1],d,G.edges[i].distance,speed);
        g.addEdge(G.edges[i].nodes[1],G.edges[i].nodes[0],d,G.edges[i].distance,speed);
    }
	int s;
	int t;
	cin>>s>>t;
	g.DinicMaxflow(s,t);
	g.printAllPaths(s, t);
	return 0; 
} 
