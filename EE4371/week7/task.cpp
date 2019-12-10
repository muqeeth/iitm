/*all the tasks are sorted with release time,the task whose deadline-currenttime is
least is given high priority.Tasks which cannot be scheduled are given least 
priority of all*/
#include<iostream>
#include<algorithm>
#include<vector>
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
    vector<pi> pq;
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
    pq.push_back(make_pair(D[index1],index1));
    a[index1] = true;
    int currenttime  = R[index1];
    int res = 0;
    while(!pq.empty()){
        pair<int,int> top = pq.front();
        int endtime = currenttime + T[top.second];
        int p = INF;
        int q;
        for(int i=0;i<n;i++){
            int index = test[i].second;
            if(R[index]<endtime && a[index]==false && T[index]>0){if((D[index]-currenttime)>T[index]){
                if((D[index])<=p){
                    p = D[index];
                    q = index;
                }
            }
            }
        }
        if(p!=INF){
            pq.push_back(make_pair(p,q));
            a[q] = 1;
        }
        sort(pq.begin(),pq.end());
        pair<int,int> top2 = pq.front();
        if(top2.second == top.second){
            if(currenttime!=currenttime+T[top.second])cout<<currenttime<<" "<<currenttime+T[top.second]<<" "<<top.second+1<<endl;
            currenttime+=T[top.second];
            T[top.second] = 0;
            if(currenttime>D[top.second]){
                cout<<"deadlineviolate"<<top.second+1<<endl;
                res++;}
            pq.erase(pq.begin());
            if(pq.empty()){
                bool c=false;
                int p = INF;
                int q=-1;
                for(int i=0;i<n;i++){
                    int index = test[i].second;
                    if(R[index]<currenttime && a[index]==false){
                        q = index;
                        c=true;
                        if((D[index]-currenttime)>T[index]){
                        if((D[index])<=p){
                            p = D[index];
                            q = index;
                        }
                    }
                    }
                }
                if(p!=INF){pq.push_back(make_pair(p,q));a[q]=1;}
                else if(q!=-1) {pq.push_back(make_pair(INF,q));a[q]=1;}
                sort(pq.begin(),pq.end());
                if(c==false){
                    bool s = false;
                    int index3 = index2;
                    for(int i=0;i<n;i++)if(a[i]!=1){if(R[i]<=R[index3])index3=i;s=true;}
                    if(s==true){
                        pq.push_back(make_pair(D[index3],index3));
                        sort(pq.begin(),pq.end());
                        a[index3]=1;
                        currenttime = R[pq.front().second];}
                    else{
                        for(int i=0;i<n;i++){
                            if(T[i]!=0){
                                pq.push_back(make_pair(D[i],i));
                            }
                        }
                        sort(pq.begin(),pq.end());
                    }
                }
            }

        }
        else{
            if(currenttime<R[top2.second]){
                cout<<currenttime<<" "<<R[top2.second]<<" "<<top.second+1<<endl;
                T[top.second]-=(R[top2.second]-currenttime);
                pq.erase(pq.begin()+top.second);
                a[top.second]=0;
                currenttime = R[top2.second];
            }
        }
    }
    cout<<"deadlinesviolated---"<<res<<endl;
    //for(int i=0;i<n;i++)cout<<T[i]<<endl;
    //for(int i=0;i<n;i++)cout<<a[i]<<endl;
}