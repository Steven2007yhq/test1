#include<bits/stdc++.h>
using namespace std;

// 广义表节点类
template<class T>
class GenListNode{
public:
    // 修正：默认构造函数需要初始化所有成员
    GenListNode(){
        utype = 0;
        tlink = NULL;
        info.ref = 0;
    }
    // 拷贝构造函数
    GenListNode(const GenListNode<T>& RL){  // 修正：添加 const 修饰
        utype = RL.utype;
        tlink = RL.tlink;
        info = RL.info;
    }
    // 修正：提供友元声明，让 GenList 可以访问私有成员
    friend class GenList<T>;
private:
    GenListNode<T>* tlink;  // 指向下一个节点的指针
    int utype;              // 节点类型：0-表头，1-原子，2-子表
    union {
        int ref;            // 表头的引用计数
        T value;            // 原子节点的值
        GenListNode<T>* hlink;  // 子表的表头指针
    } info;
};

// 用于存储节点信息的辅助类
template<class T>
class Items{
public:
    int utype;
    union{
        int ref;
        T value;
        GenListNode<T>* hlink;
    } info;
    Items(){
        utype = 0;
        info.ref = 0;
    }
    // 修正：添加 const 修饰
    Items(const Items<T>& RL){
        utype = RL.utype;
        info = RL.info;
    }
};

// 广义表主类
template<class T>
class GenList{
public:
    // 构造函数：创建空的广义表（表头节点）
    GenList(){
        first = new GenListNode<T>();  // 修正：将 first 赋值（原代码未赋值）
        assert(first != NULL);
        first->utype = 0;  // 表头节点类型为 0
        first->info.ref = 1;  // 表头引用计数初始化为 1
    }

    // 析构函数：释放所有节点
    ~GenList(){
        Remove(first);  // 调用私有删除函数
        first = NULL;
    }

    // 获取广义表的表头（修正逻辑错误：返回 true 表示成功）
    bool Head(Items<T>& x){  // 修正：添加模板参数 T
        if (first->tlink == NULL) return false;  // 空表，无表头
        x.utype = first->tlink->utype;
        x.info = first->tlink->info;
        return true;  // 修正：原代码错误返回 false
    }

    // 获取广义表的表尾（剩余部分）
    bool Tail(GenList<T>& It){
        if (first->tlink == NULL) return false;
        // 清空目标表的原有内容
        if (It.first != NULL) {
            It.Remove(It.first);
        }
        It.first->utype = 0;
        It.first->info.ref = 1;
        It.first->tlink = Copy(first->tlink->tlink);  // 拷贝表尾节点
        return true;
    }

    // 获取第一个节点（表头后的第一个节点）
    GenListNode<T>* firstNode() {  // 修正：函数名避免和成员变量 first 冲突
        if (first->tlink == NULL) {
            return NULL;
        } else {
            return first->tlink;
        }
    }

    // 获取指定节点的下一个节点
    GenListNode<T>* Next(GenListNode<T>& elem) {
        return elem.tlink;
    }

    // 拷贝广义表
    void Copy(const GenList<T>& R) {
        if (first != NULL) {
            Remove(first);  // 释放当前表的内容
        }
        first = Copy(R.first);  // 拷贝传入的广义表
    }

    // 获取广义表的长度（顶层元素个数）
    int Length() {
        return Length(first->tlink);  // 从第一个元素开始计算
    }

    // 获取广义表的深度
    int depth() {
        return depth(first->tlink);
    }

    // 重载输入运算符，用于创建广义表
    friend istream& operator>>(istream& in, GenList<T>& L) {
        if (L.first->tlink != NULL) {
            L.Remove(L.first->tlink);  // 清空原有内容
        }
        L.Createlist(in, L.first->tlink);  // 创建新的广义表
        return in;
    }

private:
    GenListNode<T>* first;  // 广义表的表头节点

    // 递归拷贝节点
    GenListNode<T>* Copy(GenListNode<T>* ls) {
        if (ls == NULL) return NULL;
        GenListNode<T>* newNode = new GenListNode<T>(*ls);  // 拷贝当前节点
        newNode->tlink = Copy(ls->tlink);  // 拷贝下一个节点
        // 如果是子表，递归拷贝子表的内容
        if (newNode->utype == 2) {
            newNode->info.hlink = Copy(ls->info.hlink);
        }
        return newNode;
    }

    // 修正：补充函数体（原代码只有声明）
    int Length(GenListNode<T>* ls) {
        int len = 0;
        while (ls != NULL) {
            len++;
            ls = ls->tlink;
        }
        return len;
    }

    // 修正：补充函数体（原代码只有声明）
    int depth(GenListNode<T>* ls) {
        if (ls == NULL) return 1;  // 空表深度为 1
        int max_depth = 0;
        while (ls != NULL) {
            int d = 0;
            if (ls->utype == 2) {  // 子表，递归计算子表深度
                d = depth(ls->info.hlink);
            } else {  // 原子节点，深度为 0
                d = 0;
            }
            if (d > max_depth) max_depth = d;
            ls = ls->tlink;
        }
        return max_depth + 1;  // 加 1 是当前层的深度
    }

    // 比较两个广义表是否相等（补充实现）
    bool equal(GenListNode<T>* ls, GenListNode<T>* t) {
        if (ls == NULL && t == NULL) return true;
        if (ls == NULL || t == NULL) return false;
        if (ls->utype != t->utype) return false;
        // 根据节点类型比较内容
        if (ls->utype == 1) {  // 原子节点
            if (ls->info.value != t->info.value) return false;
        } else if (ls->utype == 2) {  // 子表
            if (!equal(ls->info.hlink, t->info.hlink)) return false;
        }
        // 比较下一个节点
        return equal(ls->tlink, t->tlink);
    }

    // 递归释放节点内存
    void Remove(GenListNode<T>* ls) {
        if (ls == NULL) return;
        // 先释放子表（如果有）
        if (ls->utype == 2) {
            Remove(ls->info.hlink);
        }
        GenListNode<T>* next = ls->tlink;
        delete ls;
        Remove(next);  // 释放下一个节点
    }

    // 从输入流创建广义表（核心逻辑，简化实现）
    void Createlist(istream& in, GenListNode<T>*& ls) {
        char ch;
        in >> ch;  // 读取第一个字符（通常是 '(' 或原子）
        if (ch == ')') {  // 空表
            ls = NULL;
            return;
        }
        if (ch == '(') {  // 子表
            ls = new GenListNode<T>();
            ls->utype = 2;  // 标记为子表节点
            Createlist(in, ls->info.hlink);  // 递归创建子表
            in >> ch;  // 读取 ')'
        } else {  // 原子节点
            ls = new GenListNode<T>();
            ls->utype = 1;  // 标记为原子节点
            ls->info.value = (T)ch;  // 假设 T 是字符类型，可根据实际调整
        }
        // 读取分隔符
        in >> ch;
        if (ch == ',') {  // 还有下一个元素
            Createlist(in, ls->tlink);
        }
    }
};

// 测试代码
int main() {
    GenList<char> gl;
    cout << "请输入广义表（格式示例：(a,(b,c),d)）：";
    cin >> gl;

    cout << "广义表长度：" << gl.Length() << endl;
    cout << "广义表深度：" << gl.depth() << endl;

    Items<char> head;
    if (gl.Head(head)) {
        cout << "广义表表头：";
        if (head.utype == 1) {
            cout << head.info.value << endl;
        } else if (head.utype == 2) {
            cout << "子表" << endl;
        }
    }

    GenList<char> tailGl;
    if (gl.Tail(tailGl)) {
        cout << "表尾长度：" << tailGl.Length() << endl;
    }

    return 0;
}