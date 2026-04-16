#include<bits/stdc++.h>
using namespace std;
const int N=1e5;
int e[N],ne[N],idx,head;
void init(){
    head=-1;
    idx=0;
}
void add_to_head(int x){
    
    e[idx]=x;
    ne[idx]=head;
    head=idx;
    idx++;
}
void remove(int k){
    ne[k]=ne[ne[k]];
}
void add(int k,int x){
    e[idx]=x;
    ne[idx]=ne[k];
    ne[k]=idx;
    idx++;
}
int main(){
    init();
    int m;
    cin>>m;
    while(m--){
        
        char s;
        cin>>s;
        if(s=='H'){
            int k;
            cin>>k;
            add_to_head(k);
        }
        else if(s=='D'){
            int k;
            cin>>k;
            remove(k-1);
        }
        else{
            int k,x;
            cin>>k>>x;
            add(k-1,x);
        }

    }
    for(int i=head;i!=-1;i=ne[i]){
        cout<<e[i]<<" ";
    }
}