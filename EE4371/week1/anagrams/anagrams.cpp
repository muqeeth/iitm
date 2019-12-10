#include<iostream>
#include<string.h>
# define MAX 35
using namespace std;

void _swap(char * a, char *b){
    char temp = *a;
    *a = *b;
    *b = temp;
}
int partition(char a[],int l,int r){
    char pivot = a[r];
    int i = l-1;
    for(int j = l;j<=r-1;j++){
        if(a[j]<=pivot){
            i++;
            if(i!=j) _swap(&a[i],&a[j]);
        }
    }
    _swap(&a[i+1],&a[r]);
    return i+1;
}
void sort(char a[],int l,int r){
    if(l>=r) return ;
    else{
        int p = partition(a,l,r);
        sort(a,l,p-1);
        sort(a,p+1,r);
    }
}
int partition1(char a[][MAX],int temp1[],int l,int r){
    int i = l-1;
    for(int j = l;j<=r-1;j++){
        if(strcmp(a[j],a[r])<=0){
            i++;
            if(i!=j) {
                    char temp[MAX];
                    strcpy(temp,a[i]);
                    strcpy(a[i],a[j]);
                    strcpy(a[j],temp);
                    int temp2 =  temp1[i];
                    temp1[i] = temp1[j];
                    temp1[j] = temp2;
            }
        }
    }
    char temp[MAX];
    int temp2;
    strcpy(temp,a[i+1]);
    strcpy(a[i+1],a[r]);
    strcpy(a[r],temp);
    temp2 = temp1[i+1];
    temp1[i+1] =temp1[r];
    temp1[r] = temp2;    
    return i+1;
}
void sort1(char a[][MAX],int temp1[],int l,int r){
    if(l>=r) return ;
    else{
        int p = partition1(a,temp1,l,r);
        sort1(a,temp1,l,p-1);
        sort1(a,temp1,p+1,r);
    }
}
int partition4(char a[][MAX],int l,int r){
    int i = l-1;
    for(int j = l;j<=r-1;j++){
        if(strcmp(a[j],a[r])<=0){
            i++;
            if(i!=j) {
                    char temp[MAX];
                    strcpy(temp,a[i]);
                    strcpy(a[i],a[j]);
                    strcpy(a[j],temp);
            }
        }
    }
    char temp[MAX];
    int temp2;
    strcpy(temp,a[i+1]);
    strcpy(a[i+1],a[r]);
    strcpy(a[r],temp);    
    return i+1;
}
void sort4(char a[][MAX],int l,int r){
    if(l>=r) return ;
    else{
        int p = partition4(a,l,r);
        sort4(a,l,p-1);
        sort4(a,p+1,r);
    }
}
int partition2(int a[],int st[],int en[],int l,int r){
    int i = l-1;
    for(int j = l;j<=r-1;j++){
        if(a[j]<=a[r]){
            i++;
            if(i!=j) {
                    int temp;
                    temp = a[i];
                    a[i] = a[j];
                    a[j] = temp;
                    temp = st[i];
                    st[i] = st[j];
                    st[j] = temp;
                    temp = en[i];
                    en[i] = en[j];
                    en[j] = temp;
            }
        }
    } 
    int temp;
    temp = a[i+1];
    a[i+1] = a[r];
    a[r] = temp;
    temp = st[i+1];
    st[i+1] = st[r];
    st[r] = temp;
    temp = en[i+1];
    en[i+1] = en[r];
    en[r] = temp;  
    return i+1;
}
void sort2(int a[],int st[],int en[],int l,int r){
    if(l>=r) return ;
    else{
        int p = partition2(a,st,en,l,r);
        sort2(a,st,en,l,p-1);
        sort2(a,st,en,p+1,r);
    }
}

int main(){
    int N;
    cin>>N;
    char input[N][MAX];
    for(int i=0;i<N;i++){
        cin>>input[i];
    }
    char temp[N][MAX];
    int temp1[N];
    for(int i=0;i<N;i++){
        char t[MAX];
        strcpy(t,input[i]);
        sort(t,0,strlen(t)-1);
        strcpy(temp[i],t);
        temp1[i] = i;
    }
    sort1(temp,temp1,0,N-1);
    // for(int i=0;i<N;i++){
    //     cout<<temp[i]<<temp1[i]<<endl;
    // }
    int i=0;
    int count = 0;
    while(i<N-1){
        int s = 0;
        while(strcmp(temp[i],temp[i+1])==0){
            i++;
            s=1;
        }
        if(s==1)count++;
        i++;
    }
    cout<<count<<endl;
    int st[count];
    int en[count];
    int min[count];
    i = 0;
    int j = 0;
    while(i<N-1){
        if(strcmp(temp[i],temp[i+1])==0) {
            st[j] = i;
            min[j] = temp1[i];
            while(strcmp(temp[i],temp[i+1])==0) {
                i++;
                if(temp1[i]<min[j]) min[j]=temp1[i];
            }
            en[j] = i;
            j++;
            }
        i++;
    }
    // for(int i=0;i<count;i++){
    //     cout<<st[i]<<" "<<en[i]<<" "<<" "<<min[i] <<endl;
    // }
    sort2(min,st,en,0,count-1);
    // for(int i=0;i<count;i++){
    //     cout<<st[i]<<" "<<en[i]<<" "<<" "<<min[i] <<endl;
    // } 
    for(int i=0;i<count;i++){
        int len = en[i]-st[i]+1;
        cout<<len<<endl;
        char output[len][MAX];
        for(int j=st[i];j<=en[i];j++){
            strcpy(output[j-st[i]],input[temp1[j]]);
        }
        sort4(output,0,len-1);
        for(int i=0;i<len;i++){
            cout<<output[i]<<endl;
        }
    }
}