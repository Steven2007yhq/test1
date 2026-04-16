#include<bits/stdc++.h>
using namespace std;
const int N=1e3;
vector<int> a(N);
int partition(int l,int r){
    int t=a[l];
    while(l<r){
        while(l<r&&a[r]>=t){
            r--;
            

    }
    a[l]=a[r];
    while(l<r&&a[l]<=t){
        l++;
    }
    a[r]=a[l];
}
a[l]=t;
return l;
}
void Quick_sort(int l,int r){
    if(l>=r)return ;
    else{
        int mid=partition(l,r);
        Quick_sort(l,mid-1);
        Quick_sort(mid+1,r);
    }
}
int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    Quick_sort(1,n);
    for(int i=1;i<=n;i++){
        printf("%d ",a[i]);
    }
}