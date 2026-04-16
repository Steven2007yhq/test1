#include<bits/stdc++.h>
using namespace std;
const int N=1000;
int a[N][26];
int idx;
int cnt[N];
void insert(char b[]){
    int p=0;
    for(int i=0;b[i];i++){
        int u=b[i]-'a';
        if(!a[p][u])
        {
            a[p][u]=++idx;
        }
        p=a[p][u];
    }
    cnt[p]++;
}
int query(char b[]){
    int p=0;
    for(int i=0;b[i];i++){
        int u=b[i]-'a';
        if(!a[p][u]){
            return 0;
            break;
        }
        p=a[p][u];
    }
    return cnt[p];
}
int main(){
    int n;
    char str[5];
    scanf("%d",&n);
    while(n--){
        char op[2];
        scanf("%s%s",op,str);
        if(op[0]=='i')insert(str);
        else{
            cout<<query(str);
        }
    }
    return 0;
}