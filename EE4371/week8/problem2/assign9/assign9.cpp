/*Implemented dinic algorithm for maximum flow from geeksforgeeks
The algorithm runs bfs in every iteration and assign levels to all nodes , a flow is possible 
for levels 0,1,2,3....It creates residual graph  with it. The algorithm terminates
if no more flow is possible. Finally we do bfs at source and print flow in each edge.*/
#include<iostream>
#include<vector>
#include<queue>
#include<map>
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
	void printAllPathsUtil(int u, int d, bool visited[], int path[],
							vector<vector<int> > &paths,int &path_index);
	void printAllPaths(int s, int d,int X,int total);
	void print(vector<vector<int> >&paths,vector<int> &trucks,vector<pair<double,pair<int,int> > > &value);
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
				adj[e.v][e.rev].flow -= temp_flow; 
				return temp_flow; 
			} 
		} 
	} 

	return 0; 
} 
void Graph::printAllPaths(int s, int d,int X,int total) 
{ 
	// Mark all the vertices as not visited 
	bool *visited = new bool[V]; 

	// Create an array to store paths 
	int *path = new int[V]; 
    vector<vector<int> >paths;
	int path_index = 0; // Initialize path[] as empty 

	// Initialize all vertices as not visited 
	for (int i = 0; i < V; i++) 
		visited[i] = false; 
    int l = 0;
	// Call the recursive helper function to print all paths 
	printAllPathsUtil(s, d, visited, path,paths,path_index); 
    vector<pair<double,pair<int,int> > > value;
    int number = paths.size();
    double sum = 0;
    for(int i=0;i<number;i++){
        double latency = 0;
        int bottleneck = INF;
        for(int j=0;j<paths[i].size()-1;j++){
            vector<edge>::iterator it;
            for (it = adj[paths[i][j]].begin(); it != adj[paths[i][j]].end(); it++) 
            { 
                edge &e = *it;
                if(e.v==paths[i][j+1]){
                    int cap;
                    if(e.speed==60)cap=100;
                    else if(e.speed==40)cap=50;
                    else cap=20;
                    if(bottleneck>cap)bottleneck=cap;
                    latency+=e.dist/double(e.speed);
                    break;
                }
            }   
        }
        sum+=latency;
        value.push_back(make_pair(latency,make_pair(i,bottleneck)));
        //sort(value.begin(),value.end());
    }
    vector<int>trucks;
    // if(total<X){
    //     int temp = 0;
    //     for(int i=0;i<value.size();i++){
    //         temp+=value[i].second.second;
    //         trucks.push_back(value[i].second.second);
    //         if(temp>total){

    //         }
    //     }
    // }
    // else{

    // }
    int temp=0;
    for(int i=number-1;i>=0;i--){
        double temp2 = value[i].first/sum;
        if(i==0){
            trucks.push_back(X-temp);
        }
        else{
            temp+=int(temp2*X);
            trucks.push_back(int(temp2*X));
        }
    }
    //trucks.push_back(X);
    print(paths,trucks,value);

}
void Graph::printAllPathsUtil(int u, int d, bool visited[], int path[],
							vector<vector<int> >&paths, int &path_index) 
{ 
	// Mark the current node and store it in path[] 
	visited[u] = true; 
    path[path_index]=u;
	path_index++; 

	// If current vertex is same as destination, then print 
	// current path[] 
	if (u == d) 
	{ 
        vector<int> temp;
		for (int i = 0; i<path_index; i++){
            
            temp.push_back(path[i]);
        }
        paths.push_back(temp); 
	} 
	else // If current vertex is not destination 
	{ 
		// Recur for all the vertices adjacent to current vertex 
		vector<edge>::iterator i; 
		for (i = adj[u].begin(); i != adj[u].end(); ++i) 
			if (!visited[(*i).v] && (*i).flow>0) 
				printAllPathsUtil((*i).v, d, visited, path,paths, path_index); 
	} 

	// Remove current vertex from path[] and mark it as unvisited 
	path_index--; 
	visited[u] = false; 
}
void Graph::print(vector<vector<int> >&paths,vector<int> &trucks,vector<pair<double,pair<int,int> > > &value) 
{ 
    map<pair<int,int>,int> res;
    for(int i=0;i<trucks.size();i++){
        int temp = value[i].second.first;
         for(int j=0;j<paths[temp].size()-1;j++){
            //cout<<paths[temp][j]<<" "<<paths[temp][j+1]<<" "<<trucks[i]<<endl;

            pair<int,int> a = make_pair(paths[temp][j],paths[temp][j+1]);
            if(res.find(a)!=res.end()){
                res.find(a)->second+=trucks[i];
            }
            else{
                res.insert(pair<pair<int,int>,int>(a,trucks[i]));
            }

        }
     }
    for (map<pair<int,int>,int>::iterator it=res.begin(); it!=res.end(); ++it)
        if(it->second>0)cout << it->first.first <<" " << it->first.second << " "<<it->second<<endl;
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
	int X;
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
	cin>>s>>t>>X;
	int total = g.DinicMaxflow(s,t);
	g.printAllPaths(s, t,X,total);
	return 0; 
} 
