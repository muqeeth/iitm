/*Matrix A of M*N-1 size is taken. First row of matriz is filled with teams from 2 to N ie A[0] to A[N-2]
. The next row is made by circularly shifting above row by one.This will ensure pattern not being 
repeated.In each row, assuming numbering from 0 to N-2, The first team is allowed 
to play with A[N-3],A[N-4] with A[N-2].The next N-2 teams are paired as A[j] and A[N-5-j] j moves by 
2 every step.Since a matrix of size M*N-1 is used complexity is O(MN).
*/
#include<iostream>

using namespace std;

int main(){
    int N;
    int M;
    cin>>N>>M;
    int** a = new int*[M];
    for(int i = 0; i < M; ++i)
        a[i] = new int[N-1];
    if(N==2){
        cout<<1<<" "<<2<<endl;
        return 0;
    }
    for(int i=0;i<M;i++){
        for(int j=0;j<N-1;j++){
            if(i==0){
                a[i][j] = (j+2);
            }
            else{
                a[i][j] = a[i-1][(j+N-2)%(N-1)];
            }
        }
    }
    // for(int i=0;i<M;i++){
    //     for(int j=0;j<N-1;j++){
    //         cout<<a[i][j]<<" " ;
    //     }
    //     cout<<endl;
    // }
    for(int i=0;i<M;i++){
        cout<<1<<" "<<a[i][N-3]<<endl;
        for(int j=0;j<N-2;j+=2){
            if(j==N-4)cout<<a[i][j]<<" "<<a[i][j+2]<<endl;
            else cout<<a[i][j]<<" "<<a[i][N-5-j]<<endl;
        }
    }
    return 0;
}