#include<bits/stdc++.h>
using namespace std;
int main(){
    char a[10],b[5];
    cin>>a+1>>b+1;
    int ne[10];
    for(int i=1,j=0;i<=10;i++){
        if(j&&a[i]!=a[j+1])j=ne[j];
        if(a[i]==a[j+1])j++;
        ne[i]=j;
    }
    for(int i=1,j=0;i<=5;i++){
        if(j&&a[j+1]!=b[i])j=ne[j];
        if(b[i]==a[j+1])j++;
        if(j==10){
            printf("%d ",i-5+1);
            j=ne[j];
        }
    }
}