#include<bits/stdc++.h>
using namespace std;
vector<int> a(10);
vector<int> res;
vector<int> discretize(vector<int> &a){
    vector<int> temp(a);
    sort(temp.begin(),temp.end());
    temp.erase(unique(temp.begin(),temp.end()));
    vector<int> res;
    for(int x:a){
       res.push_back(lower_bound(temp.begin(),temp.end(),x)-temp.begin()+1);
    }
    return res;
}
int main(){
    for(int i=0;i<=9;i++){
        cin>>a[i];
    }
    res=discretize(a);
    for(int i=0;i<=9;i++){
        cout<<res[i];
    }
}