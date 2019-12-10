/*Idea is discussed with friend*/
#include <iostream>
#include <cstdlib>
#include <queue>
#include <algorithm>
using namespace std;

class task{
    public:
    int release;
    int duration;
    int deadline;
    int taskno;
    int starttime;
    int end;
    bool operator<(const task& x) const{
         return (deadline>x.deadline||(deadline==x.deadline&&duration>x.duration));
    }
    bool operator==(const task& x) const{
         return (taskno==x.taskno);
    }
    
};
bool compare(task a,task b){
     return a.release<b.release||(a.release==b.release&&a.deadline<b.deadline)||(a.release==b.release&&a.deadline==b.deadline&&a.duration<b.duration);
}
 
int main(){
    long int n;
    cin>>n;
    task*a=new task [n];
    task*b=new task [n];
    priority_queue<task> pq;
    int currenttime,nexttime,complete;
    for(int i=0;i<n;i++){
         cin>>a[i].release>>a[i].duration>>a[i].deadline;
         b[i].release=a[i].release;
         b[i].duration=a[i].duration;
         b[i].deadline=a[i].deadline;
         a[i].taskno=i+1;
    }
    sort(a,a+n,compare);
    currenttime=a[0].release;
    int j=0;
    task job;
    priority_queue<task> tempjob;
    bool t=false;
    while(currenttime<min(a[n-1].deadline,a[n-1].release+a[n-1].duration)){
        while(j<n&&a[j].release==currenttime){
             pq.push(a[j]);
             j++;
        }
        while(j<n&&currenttime+(pq.top()).duration>(pq.top()).deadline&&!pq.empty()){
             tempjob.push(pq.top());
             pq.pop();
        }
        if(j<n&&pq.empty()){
             int curr = currenttime;
             while(!tempjob.empty() && curr<a[j].release){
                 task temp = tempjob.top();
                 tempjob.pop();
                 if(curr+b[temp.taskno-1].duration<=a[j].release){
                     cout<<curr<<" "<<curr+b[temp.taskno-1].duration<<" "<<temp.taskno<<endl;
                     curr+=b[temp.taskno-1].duration;
                     b[temp.taskno-1].duration=0;
                 }
                 else{
                     cout<<curr<<" "<<a[j].release<<" "<<temp.taskno<<endl;
                     b[temp.taskno-1].duration-=(a[j].release-curr);
                     tempjob.push(temp);
                     break;
                 }
             }
             currenttime=a[j].release;
             continue;
        }
        job=pq.top();
        pq.pop();
        if(!t){
             job.starttime=currenttime;
        }
        complete=currenttime+job.duration;
        nexttime=j<n?min(min(a[j].release,complete),job.deadline):complete;
        job.duration=job.duration-nexttime+currenttime;
        b[job.taskno-1].duration=b[job.taskno-1].duration-nexttime+currenttime;
        pq.push(job);
        t=false;
        if(nexttime==complete){
             job.end=complete;
             cout<<job.starttime<<" "<<job.end<<" "<<job.taskno<<endl;
             pq.pop();
        }
        else if(j<n&&nexttime==a[j].release){
             currenttime=a[j].release;
             while(j<n&&a[j].release==currenttime){
                 pq.push(a[j]);
                 j++;
            }  
             if(!(pq.top()==job)){
                 job.end=currenttime;
                 cout<<job.starttime<<" "<<job.end<<" "<<job.taskno<<endl;
                 job=pq.top();
                 job.starttime=currenttime;
            }
            else{
                 t=true;
            }
        }   
        else if(nexttime==job.deadline){
             job.end=job.deadline;
             cout<<job.starttime<<" "<<job.end<<" "<<job.taskno<<endl;
             pq.pop();
        }
        currenttime=nexttime;
        
    }
    //If not able to schedule all
    for(int i=0;i<n;i++){
        if(b[i].duration!=0){
             cout<<currenttime<<" "<<currenttime+b[i].duration<<" "<<i+1<<endl;
             b[i].duration =0;
             currenttime+=b[i].duration;
        }
    }
    return 0;
}