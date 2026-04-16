#include<bits/stdc++.h>
using namespace std;
struct node{
    struct node* next;
    int n;
};
struct Link{
    struct node*head;
};
struct Link b;
int main(){
      b.head=new node[10];
      for(int i=0;i<10;i++){
        b.head[i].n=i;
        if(i<9){
          
          b.head[i].next=&b.head[i+1];}
        else{
            b.head[i].next=NULL;
        }




      }
      struct node*temp=b.head;
      while(temp!=NULL){
         cout<<temp->n<<"\t";
         temp=temp->next;
      }
  delete[] b.head;
    b.head = NULL;

}