#include<bits/stdc++.h>
#include<random>
using namespace std;
int dfs_cnt = 0;
double b[4];
vector<string> t;
vector<string> temp;

// 精简符号表（减少递归量，避免内存耗尽）
map<int,string> hash_map={
    {1,"("},{15,")"},{16,"+"},{17,"-"},{18,"*"},{19,"/"},
    {6,")+("},{7,")-("},{8,")*("},{9,")/("},{10,"+("},{11,"-("},{12,"*("},{13,"/("}
};


double compute(char c, double b_val, double a_val) {
    switch (c) {
        case '+': return a_val + b_val; 
        case '-': return a_val - b_val;
        case '*': return a_val * b_val;
        case '/': 
         
            if (fabs(b_val) < 1e-9) return 1e18;
            return a_val / b_val;
        default: return 0;
    }
}

void dfs(int n) {
    if (dfs_cnt > 20000) return;
    dfs_cnt++;

    if(n == 5) {
        stack<char> op;

        bool flag = true;

        // 校验括号匹配
        for(int i=0; i<=4 && flag; i++) {
            for(char c : temp[i]) {
                if(c == '(') {
                    op.push('(');
                } else if(c == ')') { 
                    if(op.empty()) {
                        flag = false;
                        break;
                    }
                    op.pop();
                }
            }
        }

        // 拼接表达式并校验首尾运算符
        string full_expr = temp[0] + to_string((int)b[0]) + temp[1] + to_string((int)b[1]) +
                           temp[2] + to_string((int)b[2]) + temp[3] + to_string((int)b[3]) + temp[4];
        
        if(op.empty() && !full_expr.empty()) {
            bool first_ok = (full_expr[0] != '+' && full_expr[0] != '-' && 
                             full_expr[0] != '*' && full_expr[0] != '/');
            bool last_ok  = (full_expr.back() != '+' && full_expr.back() != '-' && 
                             full_expr.back() != '*' && full_expr.back() != '/');
            bool connect_ok = true;//connect_OK为AI优化
    int len = full_expr.size();
    for(int k=0; k<len-1 && connect_ok; k++){
        char curr = full_expr[k];
        char next = full_expr[k+1];
        
        // 情况1：当前是数字/右括号 → 下一个必须是 运算符/右括号
        if(isdigit(curr) || curr == ')'){
            if(!(next == '+' || next == '-' || next == '*' || next == '/' || next == ')')){
                connect_ok = false;
            }
        }
        // 情况2：当前是运算符/左括号 → 下一个必须是 数字/左括号
        else if(curr == '+' || curr == '-' || curr == '*' || curr == '/' || curr == '('){
            if(!(isdigit(next) || next == '(')){
                connect_ok = false;
            }
        }
    }
    
    // 最终flag = 首尾合法 + 连接合法
    flag = first_ok && last_ok && connect_ok;
        } else {
            flag = false;
        }

        if(flag) {
            t.push_back(full_expr);
        }
        return;
    }

    // 递归生成符号组合
    for(auto& pair : hash_map) {
        temp.push_back(pair.second);
        dfs(n+1);
        temp.pop_back();
    }
}

bool judgement(string s) {
    unordered_map<char, int> pri = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};
    stack<double> num_s; 
    stack<char> op_s;    
    int n = s.size();
    int i = 0;

    while (i < n) {
        char c = s[i];
        if (isdigit(c)) {
            int j = i;
            while (j < n && isdigit(s[j])) j++;
            double num = stod(s.substr(i, j - i));
            num_s.push(num);
            i = j; 
        }
        else if (c == '(') {
            op_s.push(c);
            i++;
        }
        else if (c == ')') {
            if (op_s.empty()) return false;
            
            while (!op_s.empty() && op_s.top() != '(') {
                if (num_s.size() < 2) return false;
                
                char op = op_s.top(); op_s.pop();
                double b_val = num_s.top(); num_s.pop();
                double a_val = num_s.top(); num_s.pop();
                num_s.push(compute(op, b_val, a_val));
            }
            
            if (!op_s.empty()) {
                op_s.pop();
            } else {
                return false;
            }
            i++;
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!op_s.empty() && op_s.top() != '(' && pri[c] <= pri[op_s.top()]) {
                if (num_s.size() < 2) return false;
                
                char op = op_s.top(); op_s.pop();
                double b_val = num_s.top(); num_s.pop();
                double a_val = num_s.top(); num_s.pop();
                num_s.push(compute(op, b_val, a_val));
            }
            op_s.push(c); 
            i++;
        }
        else {
            i++;
        }
    }

    // 处理剩余运算符
    while (!op_s.empty()) {
        if (num_s.size() < 2) return false;
        char op = op_s.top(); op_s.pop();
        double b_val = num_s.top(); num_s.pop();
        double a_val = num_s.top(); num_s.pop();
        num_s.push(compute(op, b_val, a_val));
    }

    // 最终判定
    if (num_s.empty() || isinf(num_s.top()) || isnan(num_s.top())) {
        return false;
    }
    return fabs(num_s.top() - 24) < 1e-5;
}

int main() {
    srand(time(0));
    int o;
    cout << "请输入测试组数：";
    cin >> o;
    int success_cnt = 0; 
    int total_cnt = o;   

    while(o--) {
    t.clear();
    temp.clear();
    dfs_cnt = 0;
        for(int i=0; i<=3; i++) {
            int m;
            do {
                m = rand() % 14;
            } while(m == 0);
            b[i] = (double)m;
        }


        cout << "\n第" << (total_cnt - o) << "组测试 - 随机牌组：";
        for(int i=0; i<4; i++) cout << (int)b[i] << " ";
        cout << endl;

    
        dfs(0);
        bool l = false;
        set<string> unique_expr; 
        for (string sd : t) {
            if (judgement(sd) && unique_expr.find(sd) == unique_expr.end()) {
                cout << "  解法：" << sd << " = 24!" << endl;
                l = true;
                unique_expr.insert(sd);
                break; 
            }
        }

        if(l) {
            success_cnt++;
            cout << "  结果：成功" << endl;
        } else {
            cout << "  结果：不能得到24！" << endl;
        }
    }

    
    cout << "\n===== 测试结果统计 =====" << endl;
    cout << "总测试组数：" << total_cnt << endl;
    cout << "成功组数：" << success_cnt << endl;


    return 0; 
}