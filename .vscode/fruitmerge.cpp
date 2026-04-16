#include<bits/stdc++.h>
using namespace std;
const int N=1e7+10;
int n;
long long a[N];
long long dp[1000][1000];
long long s[N];
int main(){
 
  cin>>n;
  for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
  }
    s[1]=a[1];
  for(int i=2;i<=n;i++){
      s[i]=s[i-1]+a[i];
  }
  for(int i=1;i<=n;i++){
      dp[i][i]=0;
  }
  for(int len=2;len<=n;len++){
     for(int i=1;i+len-1<=n;i++){
            int j = i + len - 1;              
            dp[i][j] = 1e18;
        for(int k=i;k<j;k++){
          dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]+s[j]-s[i-1]);
        }
            
        }
     }
     cout<<dp[1][n];
  }
  



    
