#include<bits/stdc++.h>
#include<thread>
#include<memory>
using namespace std;
const int N=1e2;
int a[N];
void output(int a[]){
    for(int i=0;a[i];i++){
        cout<<a[i]<<endl;
    }
}

void input(int a[],int n){
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
}
int main(){
    int n;
    cin>>n;
    thread t1(input,a,n);
    t1.join();
    thread t2(output,a);
    if(t2.joinable()){
        t2.join();
    }
    return 0;
}