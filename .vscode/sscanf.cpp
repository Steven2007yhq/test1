#include<bits/stdc++.h>
using namespace std;
int main(){
   string line;
   int a=0,b=0,n=0;
   char c[6]={0};
   char d='\0';
   
   // 新增：添加输入提示，告诉用户需要输入什么格式的内容
   cout << "请输入格式如 1:2:wert.x 的内容，输入后按回车：" << endl;
   
   getline(cin,line);
   n=sscanf(line.c_str(),"%d:%d:%5s.%c",&a,&b,c,&d);

   cout<<"a "<<a<<"b "<<b<<"c "<<c<<"d "<<d<<"  "<<n<<endl; // 新增endl，确保输出换行
   return 0;
}