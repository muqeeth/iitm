#include<iostream>
using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;
};
Node *newnode(int data){
    Node * temp = NULL;
    temp = new Node;
    temp->data = data ;
    temp->left = temp->right =NULL;
}
Node* insert(Node* root,int data){
    if(root==NULL) return newnode(data);
    else if(data<root->data){
        root->left = insert(root->left,data);
    } 
    else if(data>root->data){
        root->right = insert(root->right,data);
    }
}

void inorder(Node * root){
    if(root == NULL) return;
    else{
        inorder(root->left);
        cout<<root->data<<endl;
        inorder(root->right);
    }
}

void preorder(Node * root){
    if(root==NULL) return;
    else{
        cout<<root->data<<endl;
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(Node* root){
    if(root==NULL) return ;
    else{
        postorder(root->left);
        postorder(root->right);
        cout<<root->data<<endl;
    }
}

int main(){
    int N;
    cin>>N;
    Node * root = NULL;
    while(N--){
        int data;
        cin>>data;
        if(root==NULL) root = insert(root,data);
        else{
            insert(root,data);
        }
    }
    inorder(root);
    preorder(root);
    postorder(root);
}