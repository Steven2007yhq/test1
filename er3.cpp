#include<bits/stdc++.h>
using namespace std;
int main(){
    float a[1][3];
    float b[4][4],c[4][4];
    float sum[4][4];
    for(int i=0;i<=2;i++){
       cin>>a[0][i];
    }
    for(int i=0;i<=3;i++){
        for(int j=0;j<=3;j++){
            cin>>b[i][j];
        }
    }
    for(int i=0;i<=3;i++){
        for(int j=0;j<=3;j++){
            cin>>c[i][j];
        }
    }
   for(int i=0;i<=3;i++){
        for(int j=0;j<=3;j++){
            for(int k=0;k<=2;k++){
                sum[i][j]+=b[i][j]*a[0][k]+c[i][j]*a[0][k];
            }
        }
    }
   for(int i=0;i<=3;i++){
        for(int j=0;j<=3;j++){
            cout<<sum[i][j]<<"  ";
        }
        cout<<endl;
    }


}