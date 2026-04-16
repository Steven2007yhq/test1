#include<bits/stdc++.h>
using namespace std;
class Seqstack{
     private:
         int maxsize;
         int * base;
         int top;
    public:
        Seqstack(int size){
           maxsize=size;
           base = new int[maxsize];
           if(base==NULL){
             cout<<"分配内存失败"<<endl;
             exit(0);
           } 
           top=0;  
            
        }
        ~Seqstack(){
            delete[] base;
        }
        int isempty()const{
            if(top==0){
                return 1;
            }
            else{
                return 0;
            }
        }
        int isfull(){
             if(top==maxsize){
                return 1;
             }
             else{return 0;}
        }
        void Seqstackclear(){
            top=0;
        }
        int Seqstacklength(){
            return top;
        }
        void push(int e){
              if(isfull()){
                  cout<<"栈空间已满"<<endl;
                  exit(0);
              }
               else{
                 base[top++]=e;
               }
        }
        int Pop(){
            if(isempty()){
                cout<<"栈空间空"<<endl;
                exit(0);
            }
            else{
                 return base[--top];
            }
        }
        int gettop(){
            if(isempty()){
                 cout<<"栈为空"<<endl;
                 exit(0);
            }
            else{
                return base[top-1];
            }
        }
   


};
int main(){
     Seqstack a1(20);
     for(int i=0;i<=8;i++){
     a1.push(1);
     a1.push(2);}
     if(!a1.isfull()){
          a1.Pop();
     }
     cout<<a1.gettop()<<endl;
     cout<<a1.Seqstacklength()<<endl;
     return 0;
}