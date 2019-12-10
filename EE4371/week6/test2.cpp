#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<list>
#include<queue>
using namespace std;
# define INF 0x3f3f3f3f 

typedef pair<int, int> iPair; 

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
    //for(int i=0;i<N+1;i++)cout<<dist[i].first <<" "<<dist[i].second<<endl;
    int total = 0;
    vector<int> test;
    int Ne = 0;
    test.push_back(0);
    vector<iPair> output;
    for(int i=1;i<N+1;i++){
        int temp = INF;
        int temp2 = 0;
        int temp3 = 0;
        for(int j=0;j<test.size();j++){
            int d = abs(coord[dist[i].second].first - coord[test[j]].first)+abs(coord[dist[i].second].second - coord[test[j]].second);
            if(d<temp){
                temp = d;
                temp2 = dist[i].second;
                temp3 = test[j];
            }
        }
        //cout<<temp<<endl;
        total+=temp;
        test.push_back(dist[i].second);
        //test.push_back(make_pair(coord[temp3].first,coord[temp2].second));
        if(coord[temp3].first!=coord[temp2].first && coord[temp3].second!=coord[temp2].second){
            coord.push_back(make_pair(coord[temp3].first,coord[temp2].second));
            Ne++;
            test.push_back(N+Ne);
            //cout<<temp3<<" "<<N+Ne<<endl;
            //cout<<N+Ne<<" "<<temp2<<endl;
            output.push_back(make_pair(temp3,N+Ne));
            output.push_back(make_pair(N+Ne,temp2));
        }
        //else cout<<temp3<<" " <<temp2<<endl;
        else output.push_back(make_pair(temp3,temp2));
        //output.push_back(make_pair(,));
    }
    cout<<Ne<<endl;
    for(int i=N+1;i<=N+Ne;i++)cout<<coord[i].first<<" "<<coord[i].second<<endl;
    cout<<output.size()<<endl;
    for(int i=0;i<output.size();i++)cout<<output[i].first<<" "<<output[i].second<<endl;
    cout<<"length required -- "<<total<<endl;
    return 0; 
} 