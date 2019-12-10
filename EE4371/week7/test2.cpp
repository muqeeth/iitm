#include<iostream>
#include<queue>
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
    int index1 = 0;
    bool a[n] = {false};
    for(int i=0;i<n;i++)if(R[i]<R[index1])index1=i;
    pq.push(make_pair(D[index1]-R[index1],index1));
    a[index1] = true;
    int currenttime  = R[index1];
    int res = 0;
    while(!pq.empty()){
        // for(int i=0;i<n;i++)cout<<T[i]<<" ";
        // cout<<endl;
        // for(int i=0;i<n;i++)cout<<a[i]<<" ";
        // cout<<endl;
        pair<int,int> top = pq.top();
        int endtime = currenttime + T[top.second];
        //cout<<currenttime<<"   "<<endtime<<endl;
        for(int i=0;i<n;i++){
            if(R[i]<=endtime && a[i]==false && T[i]>0){pq.push(make_pair(D[i]-currenttime,i));a[i]=true;}
        }
        // for(int i=0;i<n;i++)cout<<a[i]<<" ";
        // cout<<endl;
        pair<int,int> top2 = pq.top();
        if(top2.second == top.second){
            //cout<<"1hi"<<endl;
            if(currenttime!=currenttime+T[top.second])cout<<currenttime<<" "<<currenttime+T[top.second]<<" "<<top.second+1<<endl;
            currenttime+=T[top.second];
            T[top.second] = 0;
            if(currenttime>D[top.second])res++;
            pq.pop();
            if(pq.empty()){
                int index2=0;
                for(int i=0;i<n;i++)if(R[i]>=R[index2])index2=i;
                bool s = false;
                for(int i=0;i<n;i++)if(a[i]!=1){if(R[i]<=R[index2])index2=i;s=true;}
                if(s==true){
                    pq.push(make_pair(D[index2]-R[index2],index2));
                    a[index2]=1;
                    currenttime = R[pq.top().second];
                    }
            }
        }
        else{
            if(currenttime!=R[top2.second]){
                cout<<currenttime<<" "<<R[top2.second]<<" "<<top.second+1<<endl;
                T[top.second]-=(R[top2.second]-currenttime);
                currenttime = R[top2.second];
            }
        }
    }
    cout<<"deadlines violated---"<<res<<endl;
}