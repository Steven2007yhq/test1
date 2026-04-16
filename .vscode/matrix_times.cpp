#include<bits/stdc++.h>
using namespace std;
const int N=10;
int n;
int a[N][N],b[N][N],c[N][N];
void sum_up(int a[][N],int b[][N],int k1,int k2,int t1,int t2,int k3,int k4,int t3,int t4){
    if(k2==k1&&t1==t2&&k3==k4&&t3==t4){
        c[k1][t1]=a[k1][t1]*b[k1][t1];
    }
    else if((k2-k1==1)&&(t2-t1==1)){
        c[k1][t1]=a[k1][t1]*b[k1][t1]+a[k1][t2]*b[k2][t1];
        c[k1][t2]=a[k1][t1]*b[k1][t2]+a[k1][t2]*b[k2][t2];
        c[k2][t1]=a[k2][t1]*b[k1][t1]+a[k2][t2]*b[k2][t1];
        c[k2][t2]=a[k2][t1]*b[k1][t2]+a[k2][t2]*b[k2][t2];
    }
    else{

        sum_up(a,b,k1,(k1+k2)/2,t1,(t1+t2)/2);
        sum_up(a,b,k1,(k1+k2)/2,(t1+t2)/2+1,t2);
        sum_up(a,b,(k1+k2)/2+1,k2,t1,(t1+t2)/2);
        sum_up(a,b,(k1+k2)/2+1,k2,(t1+t2)/2+1,t2);
    }
}
void value_up(int a[][N],int b[][N],int k1,int k2,int t1,int t2){
    for(int i=k1;i<=k2;i++){
        for(int j=t1;j<=t2;j++){
            c[i][j]=a[i][j]+b[i][j];
        }
    }
}
int main(){
    
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            scanf("%d",&a[i][j]);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            scanf("%d",&b[i][j]);
        }
    }
    sum_up(a,b,1,n,1,n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            printf("%d ",c[i][j]);
        }
        cout<<endl;
    }
}