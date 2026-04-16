#include<bits/stdc++.h>
using namespace std;
const int N=1e3;
vector<int> a(N);
void merge(int l,int mid,int r){
    int i=l;
    int j=mid+1;
    int temp[N];
    int k=0;
    while(i<=mid&&j<=r){
        if(a[i]<a[j]){temp[k++]=a[i];i++;}
        else{ temp[k++]=a[j];j++;}
    }
    while(i<=mid){
        temp[k++]=a[i];
        i++;
    }
    while(j<=r){
        temp[k++]=a[j];
        j++;
    }
    for(int i=l,k=0;i<=r;i++,k++){
        a[i]=temp[k];
    }
}
void merge_sort(int l,int r){
    if(l==r) return;
    else{
        int mid=(l+r)/2;
        merge_sort(l,mid);
        merge_sort(mid+1,r);
        merge(l,mid,r);
    }
}

int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    merge_sort(1,n);
    for(int i=1;i<=n;i++){
        printf("%d\n",a[i]);
    }
}