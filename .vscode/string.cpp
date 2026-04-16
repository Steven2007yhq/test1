#include<bits/stdc++.h>
using namespace std;

class String {
private:
    char* ch;
    int len;  // 改为len（有效字符数，不含'\0'），避免与size()函数冲突
public:
    // 1. 默认构造函数（空字符串）
    String() {
        len = 0;
        ch = new char[1];  // 仅存'\0'
        if (ch == NULL) {  // 修复：== 判断
            cerr << "存储分配失败" << endl;
            exit(1);
        }
        ch[0] = '\0';
    }

    // 2. C风格字符串初始化构造函数
    String(const char* init) {
        if (init == NULL) {  // 处理空指针
            len = 0;
            ch = new char[1];
            ch[0] = '\0';
            return;
        }
        len = strlen(init);  // len是有效字符数（不含'\0'）
        ch = new char[len + 1];  // 预留'\0'位置
        if (ch == NULL) {
            cerr << "存储分配失败" << endl;
            exit(1);
        }
        strcpy(ch, init);
    }

    // 3. 拷贝构造函数
    String(const String& ob) {
        len = ob.len;
        ch = new char[len + 1];
        if (ch == NULL) {
            cerr << "存储分配失败\n";
            exit(1);
        }
        strcpy(ch, ob.ch);
    }

    // 4. 析构函数
    ~String() {
        delete[] ch;
    }

    // 5. 获取有效字符长度（修复函数名冲突）
    int length() const {
        return len;
    }

    // 6. 截取子串（修复：返回值改为值，而非引用）
    String operator()(int pos, int sub_len) {
        String temp;
        // 边界检查：pos越界 或 长度为负
        if (pos < 0 || sub_len < 0 || pos >= len) {
            temp.len = 0;
            temp.ch[0] = '\0';
            return temp;
        }
        // 修正截取长度（避免越界）
        int actual_len = (pos + sub_len > len) ? (len - pos) : sub_len;
        temp.len = actual_len;
        // 重新分配内存
        delete[] temp.ch;
        temp.ch = new char[actual_len + 1];
        if (temp.ch == NULL) {
            cerr << "存储分配失败" << endl;
            exit(1);
        }
        // 拷贝子串
        for (int i = 0, j = pos; i < actual_len; i++, j++) {
            temp.ch[i] = ch[j];
        }
        temp.ch[actual_len] = '\0';
        return temp;
    }

    // 7. 重载==运算符
    bool operator==(const String& ob) const {
        return strcmp(ch, ob.ch) == 0;
    }

    // 8. 重载!=运算符
    bool operator!=(const String& ob) const {
        return strcmp(ch, ob.ch) != 0;
    }

    // 9. 重载!运算符（判断是否为空）
    bool operator!() const {
        return len == 0;
    }

    // 10. 赋值运算符重载（修复内存分配顺序）
    String& operator=(const String& ob) {
        if (this == &ob) {  // 自赋值检查
            cout << "字符串自身赋值，无需处理！\n";
            return *this;
        }
        // 第一步：释放原有内存
        delete[] ch;
        // 第二步：分配新内存（用ob的长度）
        len = ob.len;
        ch = new char[len + 1];
        if (ch == NULL) {
            cerr << "存储分配失败" << endl;
            exit(1);
        }
        // 第三步：拷贝内容
        strcpy(ch, ob.ch);
        return *this;
    }

    // 11. 重载+=运算符（修复内存分配）
    String& operator+=(const String& ob) {
        if (ob.len == 0) return *this;  // 空字符串无需拼接
        // 计算新长度：原有效字符 + 待拼接有效字符 + '\0'
        int new_len = len + ob.len;
        char* temp = ch;  // 保存原地址
        // 分配新内存
        ch = new char[new_len + 1];
        if (ch == NULL) {
            cerr << "存储分配失败" << endl;
            exit(1);
        }
        // 拷贝原字符串 + 拼接新字符串
        strcpy(ch, temp);
        strcat(ch, ob.ch);
        // 释放原内存，更新长度
        delete[] temp;
        len = new_len;
        return *this;
    }

    // 12. 暴力查找子串（修复结束条件）
    int find(const String& pat) const {
        if (len == 0 || pat.len == 0) return -1;  // 空串返回-1
        int i = 0, j = 0;
        while (i < len && j < pat.len) {
            if (ch[i] == pat.ch[j]) {
                i++;
                j++;
            } else {
                i = i - j + 1;
                j = 0;
            }
        }
        // 匹配成功：j遍历完模式串
        if (j == pat.len) return i - j;
        return -1;
    }

    // 13. KMP查找（修复逻辑错误）
    int KMP_Find(const String& pat, int next[]) {
        if (len == 0 || pat.len == 0) return -1;
        int i = 0, j = 0;
        while (i < len && j < pat.len) {
            if (j == -1 || ch[i] == pat.ch[j]) {
                i++;
                j++;
            } else {
                j = next[j];
            }
        }
        // 匹配成功
        if (j == pat.len) return i - j;
        return -1;
    }

    // 14. 获取KMP的next数组（适配len定义）
    void getNext(int next[]) const {  // 加const：不修改成员变量
        int j = 0, k = -1;
        next[0] = -1;
        while (j < len) {  // len是有效字符数
            if (k == -1 || ch[j] == ch[k]) {
                j++;
                k++;
                next[j] = k;
            } else {
                k = next[k];
            }
        }
    }

    // 新增：打印字符串（方便测试）
    void print() const {
        cout << ch << endl;
    }

    // 新增：获取底层字符数组（方便测试）
    const char* c_str() const {
        return ch;
    }
};

// 测试代码
int main() {
    // 1. 构造函数测试
    String s1;
    String s2("hello");
    String s3(s2);
    cout << "s2内容："; s2.print();  // 输出hello
    cout << "s2长度：" << s2.length() << endl;  // 输出5

    // 2. 赋值运算符测试
    s1 = s2;
    cout << "s1赋值后："; s1.print();  // 输出hello

    // 3. 拼接测试
    String s4(" world");
    s2 += s4;
    cout << "s2拼接后："; s2.print();  // 输出hello world
    cout << "s2拼接后长度：" << s2.length() << endl;  // 输出11

    // 4. 子串截取测试
    String s5 = s2(6, 5);  // 从索引6截取5个字符
    cout << "s2截取子串："; s5.print();  // 输出world

    // 5. 暴力查找测试
    int pos1 = s2.find(s5);
    cout << "暴力查找world位置：" << pos1 << endl;  // 输出6

    // 6. KMP查找测试
    int next[100];
    s5.getNext(next);
    int pos2 = s2.KMP_Find(s5, next);
    cout << "KMP查找world位置：" << pos2 << endl;  // 输出6

    // 7. 运算符测试
    cout << "s1 == s3？" << (s1 == s3) << endl;  // 输出1（true）
    cout << "s1 != s5？" << (s1 != s5) << endl;  // 输出1（true）
    cout << "s1为空？" << !s1 << endl;  // 输出0（false）

    return 0;
}