/* I have edges from every node to every other node and krusal algorithm
is implemented to give mst.The complexity is O(V*V)*/
#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<list>
#include<queue>
using namespace std; 
typedef  pair<int, int> iPair; 

struct Graph 
{ 
    int V, E; 
    vector< pair<int, iPair> > edges;  
    Graph(int V, int E) 
    { 
        this->V = V; 
        this->E = E; 
    } 
    void addEdge(int u, int v, int w) 
    { 
        edges.push_back(make_pair(w,make_pair(u,v))); 
    } 
    int kruskalMST(); 
};  
struct DisjointSets 
{ 
    int *parent, *rnk; 
    int n; 
    DisjointSets(int n) 
    { 
        this->n = n; 
        parent = new int[n+1]; 
        rnk = new int[n+1];  
        for (int i = 0; i <= n; i++) 
        { 
            rnk[i] = 0;  
            parent[i] = i; 
        } 
    } 
    int find(int u) 
    { 
        if (u != parent[u]) 
            parent[u] = find(parent[u]); 
        return parent[u]; 
    } 
    void merge(int x, int y) 
    { 
        x = find(x), y = find(y);
        if (rnk[x] > rnk[y]) 
            parent[y] = x; 
        else
            parent[x] = y; 
  
        if (rnk[x] == rnk[y]) 
            rnk[y]++; 
    } 
}; 
 
  
int Graph::kruskalMST() 
{ 
    int mst_wt = 0; 
    sort(edges.begin(), edges.end()); 
    DisjointSets ds(V); 
    vector< pair<int, iPair> >::iterator it; 
    for (it=edges.begin(); it!=edges.end(); it++) 
    { 
        int u = it->second.first; 
        int v = it->second.second; 
  
        int set_u = ds.find(u); 
        int set_v = ds.find(v); 
        if (set_u != set_v) 
        { 
            cout << u << " " << v << endl; 
            mst_wt += it->first;  
            ds.merge(set_u, set_v); 
        } 
    } 
  
    return mst_wt; 
} 
int main() 
{ 
    int n,m;
    cin>>n>>m; 
    int clx,cly;
    cin>>clx>>cly;
    int N;
    cin>>N;
    vector<iPair> coord;
    coord.push_back(make_pair(clx,cly));
    for(int i=0;i<N;i++){
        int x,y;
        cin>>x>>y;
        coord.push_back(make_pair(x,y));
    }
    int Ne  = 0;

    int V = N+1;
    Graph g(V,(V*(V-1))/2);
    for(int i=0;i<N+1;i++){
        for(int j=i+1;j<N+1;j++){
            int x1 = coord[i].first;
            int y1 = coord[i].second;
            int x2 = coord[j].first;
            int y2 = coord[j].second;
            int d = abs(x2-x1) + abs(y2-y1);
            g.addEdge(i,j,d);
            // if(i!=0){
            //     int r = abs(x2-clx) + abs(y2-cly);
            //     if(d<r)g.addEdge(i,j,d);
            // }
            // else{
            //     g.addEdge(i,j,d);
            // }
        }
    }
    cout<<Ne<<endl;
    cout<<N+Ne<<endl;
    int mst_wt = g.kruskalMST(); 
    cout << "\nWeight of MST is " << mst_wt; 
  
    return 0; 
}