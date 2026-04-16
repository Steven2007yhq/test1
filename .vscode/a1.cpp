#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int L[10000][10000];
int main() {
    // 请在此处编写代码...
    int n;
    cin>>n;
    int a[N];
    for(int i=0;i<=n-1;i++){
        cin>>a[i];
    }
    L[2][1]=2;
    L[3][3]=9;
    L[3][1]=2;
    L[3][2]=5;
    int sum=0;
    for(int i=0;i<=n-1;i++){
        for(int j=i;j<=n-1;j++){
            if(a[j]>a[j+1]){
                sum++;
            }
        }
    }
    for(int i=n-1;i>=1;i--){
        for(int j=sum;j>=1;j--){
        if(a[i+1]<a[i]){
            swap(a[i],a[i+1]);
            L[i+1][j]=L[i+1][j-1]+j+1;
        }
        else{
            L[i+1][j]=L[i-1][j];
        }    
        }
    }
    cout<<L[n][sum];
    return 0;
}