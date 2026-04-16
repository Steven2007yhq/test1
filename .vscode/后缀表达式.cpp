#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <unordered_map>
#include <cctype> // 用于isdigit函数

// 中缀表达式转逆波兰表达式（后缀表达式）
std::vector<std::string> infix2rpn(const std::string& s) {
    // 运算符优先级映射：+、-为1，*、/为2
    std::unordered_map<char, int> pri = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};
    std::vector<std::string> output; // 存储后缀表达式（用string兼容数字和运算符）
    std::stack<char> op_stack;       // 运算符栈
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
            // 截取数字子串并加入输出列表
            output.push_back(s.substr(i, j - i));
            i = j; // 跳过已处理的数字位
        }
        // 处理左括号：直接入栈
        else if (c == '(') {
            op_stack.push(c);
            i++;
        }
        // 处理右括号：弹出栈内运算符直到左括号
        else if (c == ')') {
            while (!op_stack.empty() && op_stack.top() != '(') {
                output.push_back(std::string(1, op_stack.top())); // char转string
                op_stack.pop();
            }
            op_stack.pop(); // 弹出左括号（不加入输出）
            i++;
        }
        // 处理四则运算符：按优先级弹出栈内运算符
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            // 栈非空 + 栈顶不是左括号 + 栈顶优先级 >= 当前运算符优先级 → 弹出
            while (!op_stack.empty() && op_stack.top() != '(' && pri[op_stack.top()] >= pri[c]) {
                output.push_back(std::string(1, op_stack.top()));
                op_stack.pop();
            }
            op_stack.push(c); // 当前运算符入栈
            i++;
        }
        // 跳过空格等无效字符
        else {
            i++;
        }
    }

    // 弹出栈中剩余的所有运算符
    while (!op_stack.empty()) {
        output.push_back(std::string(1, op_stack.top()));
        op_stack.pop();
    }

    return output;
}

// 辅助函数：打印后缀表达式（方便验证）
void printRPN(const std::vector<std::string>& rpn) {
    for (size_t k = 0; k < rpn.size(); k++) {
        std::cout << rpn[k];
        if (k != rpn.size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}

// 测试示例
int main() {
    // 测试用例1：基础运算
    std::string expr1 = "1+2*3";
    std::cout << "中缀: " << expr1 << " → 后缀: ";
    printRPN(infix2rpn(expr1)); // 预期：1 2 3 * +

    // 测试用例2：带括号
    std::string expr2 = "(1+2)*3";
    std::cout << "中缀: " << expr2 << " → 后缀: ";
    printRPN(infix2rpn(expr2)); // 预期：1 2 + 3 *

    // 测试用例3：混合运算
    std::string expr3 = "10/2+3*4";
    std::cout << "中缀: " << expr3 << " → 后缀: ";
    printRPN(infix2rpn(expr3)); // 预期：10 2 / 3 4 * +

    return 0;
}