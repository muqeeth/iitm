/* I have edges from every node to every other node and prims algorithm
using matrix representation is implemented to give mst.
The complexity is O(V*V)*/
#include <cstdlib>
#include <iostream> 
#include <limits.h> 
#include <stdbool.h> 
using namespace std;
int minKey(int key[], bool mstSet[],int V) 
{ 
int min = INT_MAX, min_index; 

for (int v = 0; v < V; v++) 
	if (mstSet[v] == false && key[v] < min) 
		min = key[v], min_index = v; 

return min_index; 
} 
struct coord{
    int x;
    int y;
};
int printMST(int parent[], int n, int** graph) 
{ 
for (int i = 1; i < n; i++) 
	cout<<parent[i]<<" "<<i<<endl; 
} 

void primMST(int** graph,int V) 
{ 
	int parent[V];  
	int key[V];  
	bool mstSet[V]; 
    long long int weight=0;
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
        weight+=graph[i][parent[i]];
    } 
	printMST(parent, V, graph); 
   // cout<<weight<<"\n";
} 

int main() 
{ 
    int X,Y,n,k,xlck,yclk,v;   
    cin>>X>>Y;
    cin>>xlck>>yclk;
    cin>>n;
    v=n+1;
    struct coord* coord=new struct coord [v];
    coord[0].x=xlck;
    coord[0].y=yclk;
    for(int i=1;i<v;i++){
        cin>>coord[i].x>>coord[i].y;
    }
    int** graph=new int* [v];
    for(int i=0;i<v;i++){
        graph[i]=new int [v];
    }
    for(int i=0;i<v;i++){
        for(int j=0;j<v;j++){
            graph[i][j]=abs(coord[i].x-coord[j].x)+abs(coord[i].y-coord[j].y);
        }
    }
    cout<<"0"<<endl;
    cout<<n<<endl;
	primMST(graph,v); 
    
	return 0; 
} 
