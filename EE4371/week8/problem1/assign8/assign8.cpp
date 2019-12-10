/*Implemented dinic algorithm for maximum flow from geeksforgeeks
The algorithm runs bfs in every iteration and assign levels to all nodes , a flow is possible 
for levels 0,1,2,3....It creates residual graph  with it. The algorithm terminates
if no more flow is possible. Finally we print flow >0 in each edge.*/
#include<iostream>
#include<vector>
#include<queue>
#include<list>
#include<algorithm>
#include<limits.h>
#include"graph.h"
using namespace std; 

struct edge 
{ 
	int v ; 
	int flow ; 
	int C;
	int rev ; 
}; 

class Graph 
{ 
	int V; 
	int *level ; 
	vector< edge > *adj; 
public : 
	Graph(int V) 
	{ 
		adj = new vector<edge>[V]; 
		this->V = V; 
		level = new int[V]; 
	}  
	void addEdge(int u, int v, int C) 
	{ 
		edge a = {v, 0, C, adj[v].size()};  
		edge b = {u, 0, 0, adj[u].size()}; 
		adj[u].push_back(a); 
		adj[v].push_back(b);
	} 

	bool BFS(int s, int t); 
	int sendFlow(int s, int flow, int t, int ptr[]); 
	int DinicMaxflow(int s, int t); 
	void print(int s,int t);
}; 

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
				// cout<<u<<" "<<e.v<<" "<<e.flow<<endl;	
				adj[e.v][e.rev].flow -= temp_flow; 
				return temp_flow; 
			} 
		} 
	} 

	return 0; 
} 
void Graph::print(int s, int t) 
{ 
	bool visited[V]={0};
	for(int u=0;u<V;u++){
		visited[u]=1;
		vector<edge>::iterator i ;
		for (i = adj[u].begin(); i != adj[u].end(); i++) 
		{ 
			edge &e = *i;
			if((*i).flow>0 && visited[(*i).v]==0){
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
	while (BFS(s, t) == true) 
	{ 
		int *start = new int[V+1]; 
		while (int flow = sendFlow(s, INT_MAX, t, start))  
			{total += flow;} 
	} 
	print(s,t);
	//cout <<"max flow"<<total<<endl;
	return total; 
} 

int main() 
{ 
	graph G;
	G.read_graph("tn_graph.txt");
    int V = G.no_nodes;
    int E = G.no_edges;
    Graph g(V);
    for(int i=0;i<E;i++){
        int d;
        if(G.edges[i].type=='p')d=100;
        else if(G.edges[i].type=='s')d=50;
        else d=20;
        g.addEdge(G.edges[i].nodes[0],G.edges[i].nodes[1],d);
        g.addEdge(G.edges[i].nodes[1],G.edges[i].nodes[0],d);
    }
	int s;
	int t;
	cin>>s>>t;
	g.DinicMaxflow(s,t);
	return 0; 
} 
