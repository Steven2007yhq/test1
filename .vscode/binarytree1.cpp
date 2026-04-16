#include<bits/stdc++.h>
using namespace std;
const int N=10;
int h,e[N],ne[N][2],p[N],idx=1;
void add_node(int x){
    e[idx]=x;
    ne[idx][0]=idx*2;
    ne[idx][1]=idx*2+1;
    p[idx]=idx/2;
    idx++;
}
int main(){
    int t,n;
    scanf("%d",&n);
    for(int i=1;i<=1;i++){
        scanf("%d",&t);
        e[i]=t;

        h=i;
        p[idx]=h;
        ne[idx][0]=idx*2;
        ne[idx][1]=idx*2+1;
        idx++;
    }
    for(int i=2;i<=n;i++){
        scanf("%d",&t);
        add_node(t);
    }
     int l=2;
     cout<<e[l]<<" "<<p[l];
     l=ne[l][0];
     cout<<e[l]<<" "<<p[l];
     l=ne[p[l]][1];
     cout<<e[l]<<" "<<p[l];





}