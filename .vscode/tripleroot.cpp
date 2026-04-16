#include<bits/stdc++.h>
using namespace std;
#define N 1000
int main(){
     int a[N][N];
     int n,m,k;
     scanf("%d%d%d",&n,&m,&k);
     for(int i=0;i<n;i++){
      for(int j=0;j<m;j++){
         scanf("%d",&a[i][j]);
      }
     }
     int l1,r1,l2,r2;
     while(k--){
        scanf("%d%d%d%d",&l1,&r1,&l2,&r2);
        int sum1=0,sum2=0,sum3=0,sum4=0;
        for(int i=0;i<l1-1;i++){
          for(int j=0;j<r1-1;j++){
              sum1+=a[i][j];
          }
        }
        for(int i=0;i<l1-1;i++){
          for(int j=0;j<r2;j++){
              sum2+=a[i][j];
          }
        }
           for(int i=0;i<l2;i++){
          for(int j=0;j<r1-1;j++){
              sum3+=a[i][j];
          }
        }
           for(int i=0;i<l2;i++){
          for(int j=0;j<r2;j++){
              sum4+=a[i][j];
          }
        }
        cout<<sum4-sum2-sum3+sum1<<endl;
     }
}