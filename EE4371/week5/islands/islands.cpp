#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<list>
#include <algorithm>

using namespace std;
#define Max 1001
#define INF 0x3f3f3f3f


class Graph{
    int V;
    list < pair<int, int> > *adj_list;
    void DFSUtil(int v, bool visited[],int i,vector<int>&connected); 
    public: 
    string *towns;
    Graph(int V);
    void add_edge(int v1,int v2,int w);
    void connectedComponents();
    float avg_shortestPath(int src) ;
};
Graph::Graph(int V) 
{ 
    this->V = V; 
    adj_list = new list<pair<int,int> >[V]; 
    towns = new string[V];
} 
void Graph::add_edge(int v1,int v2,int w){
    adj_list[v1].push_back(make_pair(v2,w));
    adj_list[v2].push_back(make_pair(v1,w));
}
void Graph::connectedComponents() 
{ 
    bool *visited = new bool[V]; 
    for(int v = 0; v < V; v++) 
        visited[v] = false; 
    vector<string>result; 
    for (int v=0; v<V; v++) 
    { 
        if (visited[v] == false) 
        { 
            vector<int> connected;
            DFSUtil(v, visited,0,connected);
            float prev_value = INF;
            string old_cap;
            for(int i=0;i<connected.size();i++){
                float d = avg_shortestPath(connected[i]);
                if(d<prev_value){
                    old_cap = towns[connected[i]];
                    prev_value = d;
                }
                else if(d == prev_value){
                    if(towns[connected[i]]<old_cap)old_cap = towns[connected[i]];
                }
            }
            result.push_back(old_cap);
        } 
    }
    sort(result.begin(),result.end()); 
    for(int i=0;i<result.size();i++){
        cout<<result[i]<<endl;
    }
}
float Graph::avg_shortestPath(int src) 
{ 
    priority_queue< pair<int, int>, vector <pair<int, int> > , greater<pair<int, int> > > pq; 
    // vector<int> dist(V, INF);
    int *dist = new int[V];
    for(int i=0;i<V;i++)dist[i]=INF;
    pq.push(make_pair(0, src)); 
    dist[src] = 0; 
    while (!pq.empty()) 
    { 
        int u = pq.top().second; 
        pq.pop(); 
        list< pair<int, int> >::iterator i; 
        for (i = adj_list[u].begin(); i != adj_list[u].end(); ++i) 
        { 
            int v = (*i).first; 
            int weight = (*i).second;  
            if (dist[v] > dist[u] + weight) 
            { 
                dist[v] = dist[u] + weight; 
                pq.push(make_pair(dist[v], v)); 
            } 
        } 
    }  
    float avg = 0;
    int count=0;
    for (int i = 0; i < V; ++i) 
        if(dist[i]!=INF){
            count++;
            avg +=dist[i];
            }
    return avg/count;
} 
  
void Graph::DFSUtil(int v, bool visited[],int i,vector<int>&connected) 
{ 
    visited[v] = true; 

    connected.push_back(v);
    list<pair<int,int> >::iterator itr; 
    for(itr = adj_list[v].begin(); itr != adj_list[v].end(); ++itr)
        if(!visited[(*itr).first]) 
            DFSUtil((*itr).first, visited,i,connected); 
}

int search(string v,string *towns,int V){
    for(int i = 0;i<V;i++){
        if(towns[i]==v) return i;
        else if(towns[i].length()==0){
            towns[i] = v;
            return i;
        }
    }
    return -1;
}
int main(){
   int V,E;
   cin>>V;
   cin>>E;
   Graph islands(V);
   for(int i=0;i<E;i++){
       string v1,v2;
       int w;
       cin>>v1>>v2>>w;
       int a = search(v1,islands.towns,V);
       int b = search(v2,islands.towns,V);
       islands.add_edge(a,b,w);
       islands.add_edge(b,a,w);
   }
   islands.connectedComponents();

}