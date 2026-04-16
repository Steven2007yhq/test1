#include<bits/stdc++.h> 
using namespace std;

// 节点类：模板参数名Type，友元用T避免冲突
template<typename Type>  
class Linkstacknode{
    template<typename T>
    friend class Linkstack;
public:
    Linkstacknode(const Type &e, Linkstacknode<Type>*p = NULL) 
        : elem(e), next(p) {}
private:
    Type elem;
    Linkstacknode<Type> *next;
};

// 栈类：模板参数名Type
template<typename Type> 
class Linkstack{
public:
    Linkstack() : top(NULL) {}

    ~Linkstack() { clear(); }

    bool isempty() const { return top == NULL; }

    void clear() {
        auto p = top;
        while(p != NULL) {
            auto q = p;
            p = p->next;
            delete q;
        }
        top = NULL;
    }

    void push(const Type &e) {
        auto p = new Linkstacknode<Type>(e, top);
        if(!p) throw bad_alloc();
        top = p;
    }

    Type Pop() {
        if(isempty()) throw runtime_error("链栈为空");
        auto p = top;
        top = top->next;
        Type val = p->elem;
        delete p;
        return val;
    }

private:
    Linkstacknode<Type> *top;
};

// 测试代码
int main() {
    Linkstack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);

    cout << "出栈元素：" << s.Pop() << endl; // 输出3
    cout << "栈是否为空：" << s.isempty() << endl; // 输出0（非空）

    return 0;
}