#include<bits/stdc++.h>
using namespace std;
void display(int n,int limit){
    if(n>limit){
      return;
      }
    else{
        for(int i=1;i<=n;i++){
            cout<<n<<" ";
        }
        display(n+1,limit);
    }
}
int main(){
    int n,m;
    cin>>n>>m;
    display(n,m);
    return 0;
}