#include<bits/stdc++.h>
using namespace std;
const int N=1e3;
vector<int> a(N);
void insertsort(int n){
   for(int i=0;i<n;i++){
      int j=i-1;
      int key=a[i];
      while(j>=0&&key<a[j]){
      
        a[j+1]=a[j];
        j--;
      }
      a[j+1]=key;
   }
}
int main(){

   int n;
   scanf("%d",&n);
   for(int i=0;i<n;i++){
    scanf("%d",&a[i]);
   }
   insertsort(n);
   for(int i=0;i<n;i++){
    cout<<a[i]<<endl;
   }







}




