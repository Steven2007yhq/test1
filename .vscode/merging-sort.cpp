#include<bits/stdc++.h>
using namespace std;
int a[10];
int temp[10];
void Mergesort(int a[],int l,int r){
    if(l>=r)return ;
    int mid=l+r>>1;
    Mergesort(a,l,mid);
    Mergesort(a,mid+1,r);
    int k=0;
    int i=l,j=mid+1;
    while(i<=mid&&j<=r){
        if(a[i]<=a[j]){
            temp[k++]=a[i++];
            
        }
        if(a[i]>a[j]){
            temp[k++]=a[j++];
        }
    }
    while(i<=mid){
        temp[k++]=a[i++];
    }
    while(j<=r){
        temp[k++]=a[j++];
    }
    for(i=l,k=0;i<=r;i++,k++){
        a[i]=temp[k];
    }
}
int main(){
    for(int i=0;i<=9;i++){
        scanf("%d",&a[i]);
    }
    int l=0;int r=9;
    Mergesort(a,l,r);
    for(int i=0;i<=9;i++){
        printf("%d\t",a[i]);
    }
}