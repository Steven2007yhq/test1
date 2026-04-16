#include<bits/stdc++.h>
using namespace std;
int n;

const int N=5*1e5+10;
vector<int> temp(N);
int a[N];
int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
        
    }
    
    temp[0]=a[0];
    long long ans=0;
    for(int i=1;i<n;i++){
        int len=temp.size();
        auto l=upper_bound(temp.begin(),temp.end(),a[i]);
        int cnt=temp.end()-l;
        ans+=cnt;
        temp.insert(l,a[i]);
    }
    cout<<ans;
}