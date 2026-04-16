#include<bits/stdc++.h>
using namespace std;
int n,m;
struct Node{
    int l,r;
    int sum;
}tr[12];
void pushup(int u){
    tr[u].sum=tr[u<<1].sum+tr[u<<1|1].sum;
}
void build(int u,int l,int r){
    if(l==r){
        tr[u]={l,r,w[r]};
    }
    else{
        tr[u]={l,r};
        int mid=l+r>>1;
        build(u<<1,l,mid);
        build(u<<1|1,mid+1,r);
        pushup(u);
    }
}
int query(int u,int l,int r){
    if(tr[u].l>=l&&tr[u].r<=r)return tr[u].sum;
    int mid=tr[u].l+tr[u].r>>1;
    int sum=0;
    if(l<=mid)sum=query(u<<1,l,r);
    if(r>mid)sum=query(u<<1|1,l,r);
    return sum;
}
void modify(int u,int x,int v){
    if(tr[u].l==tr[u].r)tr[u].sum+=v;
    else{
        int mid=tr[u].l+tr[u].r>>1;
        if(x<=mid)modify(u<<1,x,v);
        else{modify(u<<1|1,x,v);
        pushup(u);
    }

}}
int main()
{
scanf("%d%d",&n,&m);
for(int i=1;i<=n;i++){
  scanf("%d",&w[i]);
}
build(1,1,n);
int k,a,b;
while(m--){
    scanf("%d")
}



}