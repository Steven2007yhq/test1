#include<bits/stdc++.h>
using namespace std;
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <cctype> // 用于isdigit函数

// 计算单个运算：op是运算符，b是右操作数，a是左操作数（注意顺序！）
double compute(char op, double b, double a) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            // 简单的除零保护（Python默认抛异常，C++需手动处理）
            if (b == 0) {
                cerr << "Error: Division by zero!" << std::endl;
                return 0;
            }
            return a / b;
        default: return 0;
    }
}

// 双栈法计算中缀表达式
double calculate_two_s(const std::string& s) {
    // 运算符优先级映射：+、-为1，*、/为2
    unordered_map<char, int> pri = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};
    stack<double> num_s; // 数字栈
    stack<char> op_s;    // 运算符栈
    int n = s.size();
    int i = 0;

    while (i < n) {
        char c = s[i];
        // 处理多位数（数字）
        if (isdigit(c)) {
            int j = i;
            // 找到连续数字的结束位置
            while (j < n && isdigit(s[j])) {
                j++;
            }
            // 截取子串并转换为double，压入数字栈
            double num = stod(s.substr(i, j - i));
            num_s.push(num);
            i = j; // 跳过已处理的数字位
        }
        // 处理左括号
        else if (c == '(') {
            op_s.push(c);
            i++;
        }
        // 处理右括号：计算括号内所有运算
        else if (c == ')') {
            while (!op_s.empty() && op_s.top() != '(') {
                char op = op_s.top();
                op_s.pop();
                double b = num_s.top();
                num_s.pop();
                double a = num_s.top();
                num_s.pop();
                num_s.push(compute(op, b, a));
            }
            op_s.pop(); // 弹出左括号（不参与计算）
            i++;
        }
        // 处理四则运算符
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            // 当前运算符优先级 <= 栈顶运算符优先级时，先计算栈顶
            while (!op_s.empty() && op_s.top() != '(' && pri[c] <= pri[op_s.top()]) {
                char op = op_s.top();
                op_s.pop();
                double b = num_s.top();
                num_s.pop();
                double a = num_s.top();
                num_s.pop();
                num_s.push(compute(op, b, a));
            }
            op_s.push(c); // 压入当前运算符
            i++;
        }
        // 跳过空格等无效字符
        else {
            i++;
        }
    }

    // 处理栈中剩余的运算符
    while (!op_s.empty()) {
        char op = op_s.top();
        op_s.pop();
        double b = num_s.top();
        num_s.pop();
        double a = num_s.top();
        num_s.pop();
        num_s.push(compute(op, b, a));
    }

    // 返回结果（栈空则返回0）
    return num_s.empty() ? 0 : num_s.top();
}

// 测试示例
int main() {
    // 测试用例1：基础运算
    string expr1 = "1+2*3";
    cout << expr1 << " = " << calculate_two_s(expr1) << std::endl; // 预期7

    // 测试用例2：带括号
    string expr2 = "(1+2)*3";
    cout << expr2 << " = " << calculate_two_s(expr2) << std::endl; // 预期9

    // 测试用例3：混合运算
    string expr3 = "10/2+3*4";
    cout << expr3 << " = " << calculate_two_s(expr3) << std::endl; // 预期17

    return 0;
}