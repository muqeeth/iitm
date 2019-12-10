/*We do dijkstra at each of the given nodes of sequence.so we have shortest path from each node 
of the tour to all other nodes.In the given sequence we move in shortest path
from node1 to node 2 and node 2 to node 3,so on till node k to node 1.Dijkstras algorithm takes
O(ElogV) and since it is run on k given nodes Complexity O(KElogV).In order to take
minpath for the tour,shortest path from one node to another node in sequence is added.
*/
#include<iostream>
#include "graph.h"
#include<queue>
#include<vector>
#include<list>

using namespace std;
#define INF 0x3f3f3f3f

class Graph{
    int V;
    list < pair<int, double> > *adj_list;
    public: 
    Graph(int V);
    void add_edge(int v1,int v2,double w);
    double shortestPath(int src,int des) ;
    void printpath(int parent[], int des);
};
Graph::Graph(int V) 
{ 
    this->V = V; 
    adj_list = new list<pair<int,double> >[V]; 
} 
void Graph::add_edge(int v1,int v2,double w){
    adj_list[v1].push_back(make_pair(v2,w));
    adj_list[v2].push_back(make_pair(v1,w));
}
void Graph::printpath(int parent[],int des){
    if(parent[des]==-1)return;
    printpath(parent,parent[des]);
    cout<<des<<endl;
}
double Graph::shortestPath(int src,int des) 
{ 
    priority_queue< pair<int, int>, vector <pair<int, int> > , greater<pair<int, int> > > pq; 
    // vector<int> dist(V, INF);
    double *dist = new double[V];
    int *parent = new int[V];
    for(int i=0;i<V;i++){
        dist[i]=INF;
        parent[i]=-1;
    }
    pq.push(make_pair(0, src)); 
    dist[src] = 0; 
    while (!pq.empty()) 
    { 
        int u = pq.top().second; 
        pq.pop(); 
        list< pair<int, double> >::iterator i; 
        for (i = adj_list[u].begin(); i != adj_list[u].end(); ++i) 
        { 
            int v = (*i).first; 
            double weight = (*i).second;  
            if (dist[v] > dist[u] + weight) 
            { 
                parent[v] = u;
                dist[v] = dist[u] + weight; 
                pq.push(make_pair(dist[v], v)); 
            } 
        } 
    }
    printpath(parent,des);  
    return dist[des];
}

int main(){
	graph g;
	g.read_graph("tn_graph.txt");
	// g.print_nodes();
	// g.print_edges();
    int V = g.no_nodes;
    int E = g.no_edges;
    Graph G(V);
    for(int i=0;i<E;i++){
        G.add_edge(g.edges[i].nodes[0],g.edges[i].nodes[1],g.edges[i].distance);
    }
    int K;
    cin>>K;
    int a[K];
    for(int i=0;i<K;i++)cin>>a[i];
    double distance = 0;
    cout<<a[0]<<endl;
    for(int i=0;i<K-1;i++){
        distance+=G.shortestPath(a[i],a[i+1]);
    }
    distance+=G.shortestPath(a[K-1],a[0]);
    g.destructor(); 
    //cout<<endl;
    //cout<<"min distance is"<<distance<<endl;
	return 0;
}