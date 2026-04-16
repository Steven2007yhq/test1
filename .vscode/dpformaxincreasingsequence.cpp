#include<bits/stdc++.h>
using namespace std;
int a[10];
int dp[10];
int main(){
    for(int i=0;i<10;i++)
    {
        scanf("%d",&a[i]);
    }
    for(int i=0;i<10;i++){
        dp[i]=1;
    }
    for(int i=0;i<10;i++){
        for(int j=0;j<i;j++){
            if(a[j]<a[i]){
                dp[i]=max(dp[i],dp[j]+1);
            }
        }
    }
    int ans=0;
    for(int i=0;i<10;i++){
     ans=max(ans,dp[i]);
    }
    cout<<ans;
    return 0;
}