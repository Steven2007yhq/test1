#include<bits/stdc++.h>
using namespace std;
const int N=21;
int a[N],c[N];
bool b[N];
int k[2];
bool stated[N];
int target;
vector<int> t[21];
int Hash(int x){
    return x/1000;
}
void dfs(int y,int x){
   
    int l=t[Hash(a[x])].size();
    
    
    if(y==2&&k[0]<k[1]){
        cout<<k[0]<<" "<<k[1]<<endl;
        return ;
    }
    else{
        for(int i=0;i<l;i++){
            if(!stated[i]){
            k[y]=t[Hash(a[x])][i];
            stated[i]=true;
            dfs(y+1,x);
            stated[i]=false;
        }

        }
    }
}
void query(int x){
    if(t[Hash(target-a[x])].size()==0){
        return ;
    }
    else{
        if(Hash(target-a[x])==Hash(a[x])&&b[Hash(a[x])]==true){
    
        dfs(0,x);
        b[Hash(a[x])]=false;
    }
        else{
            if(b[Hash(target-a[x])]==true){
            for(int i=0;i<t[Hash(a[x])].size();i++){
                for(int j=0;j<t[Hash(target-a[x])].size();j++){
                    cout<<t[Hash(a[x])][i]<<" "<<t[Hash(target-a[x])][j]<<endl;

                }
            }
            b[Hash(target-a[x])]=false;
            b[Hash(a[x])]=false;

        }

        }
    }
}

int main(){
    scanf("%d",&target);
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
         scanf("%d",&a[i]);
         t[Hash(a[i])].push_back(i);
         b[Hash(a[i])]=true;
    }
    for(int i=1;i<=n;i++){
        query(i);
    }

}