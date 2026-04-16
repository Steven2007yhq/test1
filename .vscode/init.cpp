#include<bits/stdc++.h>
using namespace std;
const int N=1e5;
int b[N];
int remax(int n){
    if(n==1)return b[0] ;
    else{
        return max(b[n-1],remax(n-1));
    }
}
int main(){
    int a;
    cin>>a;
    for(int i=0;i<a;i++){
        scanf("%d",&b[i]);
    }
    int max=remax(a);
    cout<<max;
}