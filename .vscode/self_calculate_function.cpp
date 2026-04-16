#include<bits/stdc++.h>
using namespace std;
const int N=1e3+10;
string s;
queue<int> a;
queue<char> b;
int t;
int main(){
    getline(cin,s);
    for(char c:s){
        if(isdigit(c)){
            a.push(c-'0');
        }
        else{
            b.push(c);
        }
    }
    int l1=b.size();
    int l2=a.size();
    int i=0;
    int j=0,m=0,s=0;
   while(i<l1){
    if(b[i]=='('){
        i++;
        t++;
    }
    if(b[i]=='+'||b[i]=='-')
  { j++;
    i++;
  } 
   if(b[i]=='*'){
       m=j;
       a[j]=b[i]*b[i+1];
       m++;
       while(m<l2-1){
        a[m]=a[m+1];
        m++;
       }
       s=i;
       while(s<l1-1){
        b[s]
       }
   }
   }

}