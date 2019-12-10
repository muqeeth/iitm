#include <cstdlib>
#include <iostream> 
#include <limits.h> 
#include <stdbool.h> 
using namespace std;
int minKey(int key[], bool mstSet[],int V) 
{ 
// Initialize min value 
int min = INT_MAX, min_index; 

for (int v = 0; v < V; v++) 
	if (mstSet[v] == false && key[v] < min) 
		min = key[v], min_index = v; 

return min_index; 
} 
struct point{
    int x;
    int y;
};
int printMST(int parent[], int n, int** graph) 
{ 
for (int i = 1; i < n; i++) 
	cout<<parent[i]<<" "<<i<<"\n"; 
} 

void primMST(int** graph,int V) 
{ 
	int parent[V];  
	int key[V];  
	bool mstSet[V]; 
    long long int sum=0;
	for (int i = 0; i < V; i++) 
		key[i] = INT_MAX, mstSet[i] = false; 
	key[0] = 0;	 
	parent[0] = -1;   
	for (int count = 0; count < V-1; count++) 
	{ 
 		int u = minKey(key, mstSet,V); 
		mstSet[u] = true; 
		for (int v = 0; v < V; v++) 
		if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) 
			parent[v] = u, key[v] = graph[u][v]; 
	} 
    for(int i=1;i<V;i++){
        sum+=graph[i][parent[i]];
    }
	// print the constructed MST 
	printMST(parent, V, graph); 
    //cout<<sum<<"\n";
} 

int main() 
{ 
    int X,Y,n,k,xo,yo,v;   
    cin>>X>>Y;
    cin>>xo>>yo;
    cin>>n;
    v=n+1;
    struct point* points=new struct point [v];
    points[0].x=xo;
    points[0].y=yo;
    for(int i=1;i<v;i++){
        cin>>points[i].x>>points[i].y;
    }
    int** graph=new int* [v];
    for(int i=0;i<v;i++){
        graph[i]=new int [v];
    }
    for(int i=0;i<v;i++){
        for(int j=0;j<v;j++){
            graph[i][j]=abs(points[i].x-points[j].x)+abs(points[i].y-points[j].y);
        }
    }
    cout<<"0\n";
    cout<<n<<"\n";
	// Print the solution 
	primMST(graph,v); 
    
	return 0; 
} 
