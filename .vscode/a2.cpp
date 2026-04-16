#include<bits/stdc++.h>
using namespace std;

int main(){
    // 初始化待拆分的字符串（修复核心问题：给num赋值）
    int w,e;
    cin>>w>>e;
    
    getchar();
    string num;
    getline(cin,num);
    // 创建stringstream对象，关联到num字符串
    stringstream ss(num);  
    
    int a;         // 存储提取的整数部分
    string b;      // 存储提取的剩余字符串部分
    ss >> a >> b;  // 从流中依次提取整数和字符串
    
    // 输出结果，这里会输出 123abc
    cout << a <<" "<< b << endl;  
    
    // 额外示例：测试其他格式的字符串
    string num2 = "456def789";
    stringstream ss2(num2);
    int a2;
    string b2;
    ss2 >> a2 >> b2;
    cout << a2 << b2 << endl;  // 输出 456def789（因为def789整体是字符串）
    
    return 0;
}