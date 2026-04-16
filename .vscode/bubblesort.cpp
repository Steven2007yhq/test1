#include<bits/stdc++.h>
using namespace std;
const int N=1e3;
vector<int> a(N);
void bubble_sort(int n){
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){
            if(a[i]>a[j]){
                swap(a[i],a[j]);
            }
        }
    }
}
int main(){
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    bubble_sort(n);
    for(int i=0;i<n;i++){
        printf("%d\n",a[i]);
    }









}