#include<bits/stdc++.h>
using namespace std;
int main(){
      string x;
      cin>>x;
      bool flag=false;
      for(char i:x){
         if(isdigit(i)){
            flag=true;


         }
      }
      if(flag){
          int a=stoi(x);
          if(a<=60&&a!=0){
              cout<<a*3+10;
          }
          else if(a<=120&&a!=0){
             cout<<a*a+2*a+50;
          }
          else if(a<=600&&a!=0){
             cout<<5*a-20;
          }
          else if(a<=1440&&a!=0){
             cout<<a/5-100;
          }
          else if(a==0){
             cout<<0;
          }
          else{
            cout<<"input error";
          }







      }
      else{
        cout<<"input error"<<endl;
      }









}












