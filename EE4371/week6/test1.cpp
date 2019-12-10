#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<list>
#include<queue>
using namespace std;
# define INF 0x3f3f3f3f 

typedef pair<int, int> iPair; 
  
// This class represents a directed graph using 
// adjacency list representation 
class Graph 
{ 
    int V;
    list< pair<int, int> > *adj; 
  
public: 
    Graph(int V);  // Constructor 
  
    // function to add an edge to graph 
    void addEdge(int u, int v, int w); 
  
    // Print MST using Prim's algorithm 
    int  primMST(vector<iPair>coord); 
}; 
  
// Allocates memory for adjacency list 
Graph::Graph(int V) 
{ 
    this->V = V; 
    adj = new list<iPair> [V]; 
} 
  
void Graph::addEdge(int u, int v, int w) 
{ 
    adj[u].push_back(make_pair(v, w)); 
    adj[v].push_back(make_pair(u, w)); 
} 
  
// Prints shortest paths from src to all other vertices 
int Graph::primMST(vector<iPair>coord) 
{ 
    priority_queue< iPair, vector <iPair> , greater<iPair> > pq; 
  
    int src = 0; 
    vector<int> key(V, INF); 
    vector<int> parent(V, -1); 
    vector<bool> inMST(V, false); 
    pq.push(make_pair(0, src)); 
    key[src] = 0; 
    while (!pq.empty()) 
    { 
        int u = pq.top().second; 
        pq.pop(); 
  
        inMST[u] = true;
        list< pair<int, int> >::iterator i; 
        for (i = adj[u].begin(); i != adj[u].end(); ++i) 
        { 
            int v = (*i).first; 
            int weight = (*i).second; 
            if (inMST[v] == false && key[v] > weight) 
            { 
                key[v] = weight; 
                pq.push(make_pair(key[v], v)); 
                parent[v] = u; 
            } 
        } 
    } 
    int length = 0;
    for (int i = 1; i < V; ++i){
        int d = abs(coord[parent[i]].first-coord[i].first)+abs(coord[parent[i]].second-coord[i].second);
        length+=d;
        cout<<parent[i]<<"-"<<i<<endl;
    } 
    return length;    
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
    vector<iPair> dist;
    for(int i=0;i<N+1;i++){
        int d  = abs(coord[i].first-coord[0].first) + abs(coord[i].second-coord[0].second);
        dist.push_back(make_pair(d,i));
    }
    sort(dist.begin(),dist.end());
    int total = 0;
    vector<iPair> test;
    test.push_back(make_pair(0,0));
    int V = N+1;
    Graph g(V);
    for(int i=1;i<N+1;i++){
        int temp = INF;
        int temp2 = 0;
        int temp3 = 0;
        for(int j=0;j<test.size();j++){
            int d = abs(dist[i].first - test[j].first) +abs(dist[i].second - test[j].second);
            if(d<temp){
                temp = d;
                temp3 = dist[i].second;
                temp2 = test[j].second;
            }
        }
        test.push_back(dist[i]);
        total+=temp;
        cout<<temp3<<" "<<temp2<<"  "<<temp<<endl;
        //g.addEdge(temp2,temp3,temp);
    }
    cout<<"length required -- "<<total<<endl;
    // int V = N+1;
    // Graph g(V);
    // for(int i=0;i<N+1;i++){
    //     for(int j=i+1;j<N+1;j++){
    //         int x1 = coord[i].first;
    //         int y1 = coord[i].second;
    //         int x2 = coord[j].first;
    //         int y2 = coord[j].second;
    //         int d = abs(x2-x1) + abs(y2-y1);
    //         int r  = abs(x1-clx)+abs(y1-cly)+abs(x2-clx)+abs(y2-cly);
    //         if(d<=r)g.addEdge(i,j,d);
    //     }
    // }
    // vector<iPair> quad1;
    // vector<iPair> quad2;
    // vector<iPair> quad3;
    // vector<iPair> quad4;
    // vector<iPair> quad;
    // int p = coord[0].first;
    // int q = coord[0].second;
    // quad1.push_back(make_pair(0,0));
    // quad2.push_back(make_pair(0,0));
    // quad3.push_back(make_pair(0,0));
    // quad4.push_back(make_pair(0,0));
    // quad.push_back(make_pair(0,0));
    // for(int i=1;i<N+1;i++){
    //     int x = coord[i].first;
    //     int y = coord[i].second;
    //     int d  = abs(x-p)+abs(y-q);
    //     if(x>p && y>p)quad1.push_back(make_pair(d,i));
    //     else if(x<p && y>q) quad2.push_back(make_pair(d,i));
    //     else if(x<p && y<q) quad3.push_back(make_pair(d,i));
    //     else if(x>p && y<q)quad4.push_back(make_pair(d,i));
    //     else quad.push_back(make_pair(d,i));
    // }
    // sort(quad1.begin(),quad1.end());
    // sort(quad2.begin(),quad2.end());
    // sort(quad3.begin(),quad3.end()); 
    // sort(quad4.begin(),quad4.end());
    // sort(quad.begin(),quad.end());
    // int V;
    // V = quad1.size();
    // Graph a(V);
    // for(int i=0;i<V;i++){
    //     for(int j=i+1;j<V;j++){
    //         a.addEdge(quad1[i].second,quad1[j].second,quad1[j].first-quad1[i].first);
    //     }
    // }
    // int total = 0;
    // total+=a.primMST(coord);
    // V = quad2.size();
    // Graph b(V);
    // for(int i=0;i<V;i++){
    //     for(int j=i+1;j<V;j++){
    //         b.addEdge(quad2[i].second,quad2[j].second,quad2[j].first-quad2[i].first);
    //     }
    // }
    // total+=b.primMST(coord);
    // V = quad3.size();
    // Graph c(V);
    // for(int i=0;i<V;i++){
    //     for(int j=i+1;j<V;j++){
    //         c.addEdge(quad3[i].second,quad3[j].second,quad3[j].first-quad3[i].first);
    //     }
    // }
    // total+=c.primMST(coord);
    // V = quad4.size();
    // Graph d(V);
    // for(int i=0;i<V;i++){
    //     for(int j=i+1;j<V;j++){
    //         d.addEdge(quad4[i].second,quad4[j].second,quad4[j].first-quad4[i].first);
    //     }
    // }
    // total+=d.primMST(coord);
    // V = quad.size();
    // Graph e(V);
    // for(int i=0;i<V;i++){
    //     for(int j=i+1;j<V;j++){
    //         e.addEdge(quad[i].second,quad[j].second,quad[j].first-quad[i].first);
    //     }
    // }
    // total+=e.primMST(coord);
    //cout<<"total lenght---"<<g.primMST(coord)<<endl;
    return 0; 
} 