#include<bits/stdc++.h>
using namespace std;
vector<int> a(5);
bool stated[6];
void dfs(int n){
    bool flag;
    if(n==4){
        for(int i=1;i<=5;i++){
            if(stated[i]==true){
              flag=true;
            }
        }
        if(flag){
            for(int i=0;i<5;i++){
                cout<<a[i]<<" ";
            }
        }
    }
    for(int i=1;i<=5;i++){
        if(stated[i]!=true){
            a[n]=i;
            stated[i]=true;
        }
        dfs(n+1);
    }
}
int main(){
    for(int i=1;i<=5;i++){
        stated[i]=false;
    }
     dfs(0);
     return 0;
}