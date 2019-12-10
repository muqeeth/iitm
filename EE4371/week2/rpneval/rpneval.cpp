#include<iostream>
#include <sstream>
#include <stdlib.h>
#include <iomanip>  
#include<string>
using namespace std;
#define max 256

class Stack
{
    private:
    double arr[max];
    int Top;
    public:
    Stack(){
        Top=-1;
    }
    void push(double x){
        if(Top == max-1){
            cout<<"Stack is full"<<endl;
            return;
        }
        Top++;
        arr[Top] = x;
    }
    double top(){
        return arr[Top];
    }
    void pop(){
        if(Top == -1){
            cout<<"Stack is empty"<<endl;
            return;
        }
        Top--;
    }
    int isempty(){
        if(Top == -1) return 1;
        else return 0;
    }
};

int main()
{
    for(string a;getline(cin,a);){
        Stack s;
        stringstream  ss;
        string y;
        ss << a;
        int t = 1;
        while(!ss.eof()){
            ss>>y;
            if(y=="+"){
                double p;
                double q;
                if(s.isempty()!=1){
                    p = s.top();
                    s.pop();
                }
                else{
                    t=0;
                    break;
                }
                if(s.isempty()!=1){
                    q = s.top();
                    s.pop();
                }
                else{
                    t=0;
                    break;
                }
                double r = q+p;
                s.push(r);
            }
            else if(y=="-"){
                double p;
                double q;
                if(s.isempty()!=1){
                    p = s.top();
                    s.pop();
                }
                else{
                    t=0;
                    break;
                }
                if(s.isempty()!=1){
                    q = s.top();
                    s.pop();
                }
                else{
                    t=0;
                    break;
                }
                double r = q-p;
                s.push(r);
            }
            else if(y=="*"){
                double p;
                double q;
                if(s.isempty()!=1){
                    p = s.top();
                    s.pop();
                }
                else{
                    t=0;
                    break;
                }
                if(s.isempty()!=1){
                    q = s.top();
                    s.pop();
                }
                else{
                    t=0;
                    break;
                }
                double r = q*p;
                s.push(r);
            }
            else if(y=="/"){
                double p;
                double q;
                if(s.isempty()!=1){
                    p = s.top();
                    if(p==0){
                        t =0;
                        break;
                    }
                    s.pop();
                }
                else{
                    t=0;
                    break;
                }
                if(s.isempty()!=1){
                    q = s.top();
                    s.pop();
                }
                else{
                    t=0;
                    break;
                }
                double r = q/p;
                s.push(r);
            }
            else{
                s.push(atof(y.c_str()));
            }
        }
        if(t==1){
            double out = s.top();
            s.pop();
            //double output = stof(out);
            if(s.isempty()==1) cout<<setprecision(4)<<fixed<<out<<endl;
            else cout<<"ERROR"<<endl;
        }
        else{
            cout<<"ERROR"<<endl;
        }
    }
}