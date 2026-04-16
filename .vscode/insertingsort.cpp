#include<bits/stdc++.h>
using namespace std;
const int N=1e3;
vector<int> a(N);
vector<int> b(N);
void insertsort(int n){
    int t=0;
    b[0]=a[0];
    for(int i=1;i<n;i++){
        for(int j=0;j<=t;j++){
            if(a[i]<b[j]){
                b[j]=a[i];
                for(int k=j;k<=t;k++){
                    b[k+1]=b[k];
                }
                break;
            }
            else{
                continue;
            }
            
            
        }
        t++;
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
        printf("%d\n",b[i]);
    }
}