#include<iostream>

using namespace std;

int main(){
    int n = 1085;
    int x[n];
    int y[n];
    int z[n];
    for(int i=0;i<n;i++){
        cin>>x[i];
        cin>>y[i];
        cin>>z[i];
    }
    for(int i=0;i<n-1;i++){
        if(x[i]>y[i])cout<<i<<"wrong1"<<endl;
        if(x[i]<y[i-1])cout<<i<<"wrong2"<<endl;
    }
    int a[1000] = {0};
    for(int i=0;i<n;i++){
        a[z[i]-1]=1;
    }
    for(int i=0;i<1000;i++){
        if(a[i]!=1)cout<<i+1<<"wrong3"<<endl;
    }
    string s;
    cin>>s;
    cout<<s<<endl;
    for(int i=0;i<1000;i++){
        int a;
        cin>>a;
        if(a!=0)cout<<i+1<<"wrong4"<<endl;
    }
    for(int i=0;i<1000;i++){
        int a;
        cin>>a;
        if(a!=1)cout<<i+1<<"wrong5"<<endl;
    }
}