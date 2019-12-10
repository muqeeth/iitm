#include<iostream>
#include<stdlib.h>
#include<iomanip>
using namespace std;

int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

int max_tasks(int start[],int end[],int n){
    int temp1=0;
    int temp2=0;
    int i = 0;
    int j = 0;
    while(i<n &&j<n){
        if(start[i]<end[j]){
            temp1++;
            if(temp1>temp2) temp2 =temp1;
            i++;
        }
        else{
            temp1--;
            j++;
        }
    }
    return temp2;
}

int main(){
    int n;
    cin>>n;
    int end_time = 0;
    double avg=0;
    int *start = new int[n];
    int *end = new int[n];
    for(int i=0;i<n;i++){
        cin>>start[i];
        int temp;
        cin>>temp;
        avg+=temp;
        int temp2;
        temp2 = start[i]+temp;
        if(temp2>end_time) end_time = temp2;
        end[i] = temp2;
    }
    cout<<end_time<<endl;
    qsort(end,n,sizeof(end[0]),compare);
    cout<<max_tasks(start,end,n)<<endl;
    avg = avg / end_time;
    cout<<fixed<<setprecision(4)<<avg<<endl;
}