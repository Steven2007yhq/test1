#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
const int M=2*N;
int p[N];
int ne[N];
int find(int x){
    if(p[x]!=x){
        p[x]=find(p[x]);
    }
    return p[x];
}
int main() {
    // 请在此处编写代码...
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        p[i]=i;
    }
    while(m--){
        int o,q;
        scanf("%d%d",&o,&q);
        p[q]=o;
    }
    multiset<int> a;
    int sum=0,p=1;
    for(int i=1;i<=n;i++){
        
        a.insert(find(i));
        if(a.count(find(i))==2){
            sum++;
            p=i;
            ne[p]=p;
        }
    }
    int sum2=0;
    while(sum>0){
        for(int i=1;i!=0;i=ne[i]){
        a.erase(a.find(find(i)));}
        sum=0,p=1;
    for(int i=1;i<=n;i++){
        if(a.count(find(i))==2){
            sum++;
            p=i;
            ne[p]=p;
        }
    }
        sum2++;
    }
    cout<<sum2;
    return 0;
}