#include<bits/stdc++.h>
using namespace std;
bool isalph(int a){
    if(a==1){
        return false;
    }
    else if(a==2){
        return true;
    }
    else if(a%2==0){
        return false;
    }
    else{
        for(int i=3;i<=sqrt(a);i++){
            if(a%i==0){
                return false;
                break;
            }
          
        }
        return true;
    }
}
bool flag;
int main(){
    int i=1,t;
    int sum=0;
  do{
    flag=isalph(i);
    if(flag){
        sum++;
    }
    i++;
    if(sum==2025){
        t=i;
        break;
    }
  }while(sum<2026);
  t--;
  cout<<t;







}