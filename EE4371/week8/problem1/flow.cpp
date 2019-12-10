// C++ program to print all paths from a source to destination. 
#include<iostream> 
#include <list> 
#include<iterator>
#include "graph.h"
using namespace std; 
#define INF 0x3f3f3f3f

// A directed graph using adjacency list representation 
class Graph{
    int V;
    list < pair<int, double> > *adj;
	void printAllPathsUtil(int , int , bool [], int [], int &);
    public: 
    Graph(int V);
    void add_edge(int v1,int v2,double w);
	void printAllPaths(int s, int d);
	 	
};
Graph::Graph(int V) 
{ 
    this->V = V; 
    adj = new list<pair<int,double> >[V]; 
} 
void Graph::add_edge(int v1,int v2,double w){
    adj[v1].push_back(make_pair(v2,w));
    adj[v2].push_back(make_pair(v1,w));
} 

// Prints all paths from 's' to 'd' 
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

// A recursive function to print all paths from 'u' to 'd'. 
// visited[] keeps track of vertices in current path. 
// path[] stores actual vertices and path_index is current 
// index in path[] 
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
		for (int i = 0; i<path_index; i++) 
			cout << path[i] << " "; 
		cout << endl; 
	} 
	else // If current vertex is not destination 
	{ 
		// Recur for all the vertices adjacent to current vertex 
		list<pair<int, double> >::iterator i; 
		for (i = adj[u].begin(); i != adj[u].end(); ++i) 
			if (!visited[(*i).first]) 
				printAllPathsUtil((*i).first, d, visited, path, path_index); 
	} 

	// Remove current vertex from path[] and mark it as unvisited 
	path_index--; 
	visited[u] = false; 
} 

// Driver program 
int main() 
{ 
	// Create a graph given in the above diagram 
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

	int s = 888, d = 874; 
	cout << "Following are all different paths from " << s 
		<< " to " << d << endl; 
	G.printAllPaths(s, d); 

	return 0; 
} 
