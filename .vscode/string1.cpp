#include<bits/stdc++.h>
using namespace std;
int n;
const int N=1e3+10;
int a[N];
set<int> b;
void quick_sort(int a[],int l,int r){
    if (l >= r) return;
    int x=a[l];
    int i=l-1;
    int j=r+1;
    while(i<j){
        do {i++;} while(x>a[i]);
        do {j--;} while(x<a[j]);
        if(i<j)swap(a[i],a[j]);
        
    }
    quick_sort(a,l,j);
    quick_sort(a,j+1,r);
}
int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
        b.insert(a[i]);
    }
    int i=0;
    for(int x:b){
        a[i]=x;
        i++;
    }
    int l=0;
    int r=i-1;
    quick_sort(a,l,r);
    for(int i=0;i<=r;i++){
        printf("%d",a[i]);
    }
}