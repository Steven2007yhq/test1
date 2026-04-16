#include<bits/stdc++.h>
using namespace std;
const int N=1e5;
int l[N],r[N],e[N],idx;
void init(){
    r[0]=1;
    l[1]=0;
    idx=2;
}
void add(int k,int x){
    e[idx]=x;
    r[idx]=r[k];
    l[idx]=k;
    l[r[k]]=idx;
    r[k]=idx;
}
void remove(int k){
    l[r[k]]=l[k];
    r[l[k]]=r[k];
}
int main(){
   
}