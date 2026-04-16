#include<bits/stdc++.h>
using namespace std;
int recursive(int n,int k){
    if(n==1)return 0;
    else{
        return (recursive(n-1,k)+k)%n;
    }
}
int main(){
    int n,k;
    cin>>n>>k;
    int ans=recursive(n,k);
    cout<<ans;
}