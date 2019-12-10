#include <iostream>
#include <cstdlib>
#include <queue>
#include <algorithm>
using namespace std;

class task{
    public:
    int start;
    int duration;
    int deadline;
    int taskno;
    int begin;
    int end;
    bool operator<(const task& x) const{
        return (deadline>x.deadline||(deadline==x.deadline&&duration>x.duration));
    }
    bool operator==(const task& x) const{
        return (taskno==x.taskno);
    }
    
};
bool compstart(task a1,task a2){
    return a1.start<a2.start||(a1.start==a2.start&&a1.deadline<a2.deadline)||(a1.start==a2.start&&a1.deadline==a2.deadline&&a1.duration<a2.duration);
}
 
int main(){
    //take input
    long int n;
    int count=0;
    cin>>n;
    task*a=new task [n];
    task*b=new task [n];
    // task*b=new task [n];
    for(int i=0;i<n;i++){
        cin>>a[i].start>>a[i].duration>>a[i].deadline;
        b[i].start=a[i].start;
        b[i].duration=a[i].duration;
        b[i].deadline=a[i].deadline;
        a[i].taskno=i+1;
    }
    //sort the a according to start time
    sort(a,a+n,compstart);
    //priority queue for inserting at each time
    priority_queue<task> pq;
    int present,next,complete;
    present=a[0].start;
    int j=0;
    task job,tempjob;
    bool x=false;
    //cout<<"hello1\n";
    while(present<min(a[n-1].deadline,a[n-1].start+a[n-1].duration)){
        while(j<n&&a[j].start==present){
            pq.push(a[j]);
            j++;
        }
        //take the best one and evaluate the next time

        while(j<n&&present+(pq.top()).duration>(pq.top()).deadline&&!pq.empty()){
            
            pq.pop();
        }
        if(j<n&&pq.empty()){
            present=a[j].start;
            continue;
        }
        
        job=pq.top();
        pq.pop();
        if(!x){
            job.begin=present;
        }
        complete=present+job.duration;
        //evaluate next
        next=j<n?min(min(a[j].start,complete),job.deadline):complete;
        job.duration=job.duration-next+present;
        b[job.taskno-1].duration=b[job.taskno-1].duration-next+present;
        //cout<<"hello4\n";
        pq.push(job);
        x=false;
        if(next==complete){
        job.end=complete;
        //cout<<"hello1\n";
        cout<<job.begin<<" "<<job.end<<" "<<job.taskno<<"\n";
        pq.pop();
        }
        else if(j<n&&next==a[j].start){
             present=a[j].start;
             while(j<n&&a[j].start==present){
                 pq.push(a[j]);
                 j++;
            }  
             if(!(pq.top()==job)){
                 job.end=present;
                 //cout<<"hello2\n";
                 cout<<job.begin<<" "<<job.end<<" "<<job.taskno<<"\n";
                 job=pq.top();
                 job.begin=present;
            }
            else{
                x=true;
            }
        
        }   
        else if(next==job.deadline){
            job.end=job.deadline;
            //cout<<"hello3\n";
            cout<<job.begin<<" "<<job.end<<" "<<job.taskno<<"\n";
            pq.pop();
        }
        present=next;
        
    }
    for(int i=0;i<n;i++){
        if(b[i].duration!=0){
            count++;
        }
    }
    //no. of tasks not completely performed
    cout<<count<<"\n";
    return 0;
}