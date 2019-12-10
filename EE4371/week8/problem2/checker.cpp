#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    set<int> s;
    while(scanf("%d" , &n) != EOF) {//You need to input till the EOF like this
        //your code goes here. 
        s.insert(n);
    }  
    cout<<s.size()<<endl;
}