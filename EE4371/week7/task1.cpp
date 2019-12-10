/*all the tasks are sorted with release time,the task whose deadline-currenttime is
least is given high priority.Tasks which cannot be scheduled are given least 
priority of all*/
#include<iostream>
#include<algorithm>
#include<queue>
#define INF 100000
using namespace std;
typedef pair<int, int> pi; 

int main(){
    int n;
    cin>>n;
    int R[n];
    int T[n];
    int D[n];
    for(int i=0;i<n;i++){
        cin>>R[i]>>T[i]>>D[i];
    }
    priority_queue<pi, vector<pi>, greater<pi> > pq;
    vector<pair<int,int> >test;
    for(int i=0;i<n;i++){
        test.push_back(make_pair(R[i],i));
    }
    sort(test.begin(),test.end());
    int index1 = 0;
    bool a[n] = {false};
    for(int i=0;i<n;i++)if(R[i]<R[index1])index1=i;
    int index2=0;
    for(int i=0;i<n;i++)if(R[i]>=R[index2])index2=i;
    pq.push(make_pair(D[index1]-R[index1],index1));
    a[index1] = true;
    int currenttime  = R[index1];
    int res = 0;
    while(!pq.empty()){
        pair<int,int> top = pq.top();
        int endtime = currenttime + T[top.second];
        for(int i=0;i<n;i++){
            int index = test[i].second;
            if(R[index]<=endtime && a[index]==false && T[index]>0){if((D[index]-currenttime)>T[index]){
                pq.push(make_pair(D[index]-currenttime,index));a[index]=true;
                break;
            }
            }
        }
        pair<int,int> top2 = pq.top();
        if(top2.second == top.second){
            if(currenttime!=currenttime+T[top.second])cout<<currenttime<<" "<<currenttime+T[top.second]<<" "<<top.second+1<<endl;
            currenttime+=T[top.second];
            T[top.second] = 0;
            if(currenttime>D[top.second]){
                res++;}
            pq.pop();
            if(pq.empty()){
                bool c=false;
                for(int i=0;i<n;i++){
                    int index = test[i].second;
                    if(a[index]!=true && R[index]<currenttime){
                        a[index]=true;
                        c=true;
                        if((D[index]-currenttime)>T[index]){
                            pq.push(make_pair(D[index]-currenttime,index));
                        }
                        else pq.push(make_pair(INF,index));
                        break;
                    }
                }
                if(c==false){
                    bool s = false;
                    int index3 = index2;
                    for(int i=0;i<n;i++)if(a[i]!=true){if(R[i]<=R[index3])index3=i;s=true;}
                    if(s==true){
                        pq.push(make_pair(D[index3]-currenttime,index3));
                        a[index3]=true;
                        currenttime = R[pq.top().second];}
                }
            }
        }
        else{
            if(currenttime<R[top2.second]){
                cout<<currenttime<<" "<<R[top2.second]<<" "<<top.second+1<<endl;
                T[top.second]-=(R[top2.second]-currenttime);
                priority_queue<pi, vector<pi>, greater<pi> > temp;
                while(!pq.empty()){
                    if(pq.top().second!=top.second)temp.push(pq.top());
                    pq.pop();
                }
                while(!temp.empty()){
                    pq.push(temp.top());
                    temp.pop();
                }
                if(T[top.second]!=0)a[top.second] = false;
                currenttime = R[top2.second];
            }
        }
    }
    //cout<<"deadlinesviolated---"<<res<<endl;
    //for(int i=0;i<n;i++)cout<<T[i]<<endl;
    //for(int i=0;i<n;i++)cout<<a[i]<<endl;
}