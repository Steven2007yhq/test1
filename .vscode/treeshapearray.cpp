#include<bits/stdc++.h>
using namespace std;
int tr[11];
int lowbit(int x)
{
    return x&-x;
}
void add(int x,int v){
    for(int i=x;i<11;i+=lowbit(i)){
        tr[i]+=v;
    }
}
int query(int x){
    int res=0;
    for(int i=x;i>0;i-=lowbit(i)){
        res+=tr[i];
    }
    return res;
}
int main(){
    int a[10];
    for(int i=0;i<10;i++){
        scanf("%d",&a[i]);
    }
    for(int i=0;i<10;i++){
        add(i+1,a[i]);
    }
    add(2,1);
    for(int i=1;i<11;i++){
        cout<<tr[i]<<' ';
    }
    int b;
    b=query(9)-query(2);
    cout<<b;
}
