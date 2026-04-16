#include<bits/stdc++.h>
using namespace std;
vector<int> a(5);
bool stated[6];
void dfs(int n){
   
    if(n==5){

            for(int i=0;i<5;i++){
                cout<<a[i]<<" ";
            }
            cout<<endl;
            return;
    }
    for(int i=1;i<=5;i++){
        
            a[n]=i;
            
            dfs(n+1);       
    }
}
int main(){

     dfs(0);
     return 0;
}