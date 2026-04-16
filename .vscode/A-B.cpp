#include<bits/stdc++.h>
using namespace std;
int n,c;
const int N=1e3+10;
int a[N],ans[2];
bool stated[N];
vector<pair<int,int>> k;
void dfs(int m,int n){
 
    if(m==2&&ans[0]-ans[1]==c){
        k.push_back(make_pair(ans[0],ans[1]));
        return;
       }
    else{
        for(int i=0;i<n;i++){
            if(!stated[i]){
               ans[m]=a[i];
               stated[i]=true;
               dfs(m+1,n);
               stated[i]=false;
            }
            
        }
    }
}
int main(){
     scanf("%d%d",&n,&c);
    for(int i=0;i<n;i++){
         scanf("%d",&a[i]);
    
    }
    dfs(0,n);
    cout<<k.size();
    return 0;
    






}