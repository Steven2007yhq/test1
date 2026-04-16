#include<bits/stdc++.h>
using namespace std;
template<class Type> class Linkqueue;
template<class Type>class Linkqueuenode{
    friend class Linkqueue<Type>;
    public:
      Linkqueuenode(Type &e, Linkqueuenode<Type> *p=NULL){
        elem=e;
        next=p;
      }
    private:
      Type elem;
      Linkqueuenode<Type> *next;

};
template<class Type>
class Linkqueue{
    public:
  
   Linkqueue(){
       front=NULL;
       rear=NULL;
    }
    ~Linkqueue(){Linkqueueclear();}
    int isempty()const{
        return front==NULL;

    }
    void Linkqueueclear(){
        while(front!=NULL){
             Linkqueuenode<Type>* p=front;
             front=front->next;
             delete p;
        }
    }
    int Linkqueuelength(){
        int n=0;
        Linkqueuenode<Type> *p=front;
        while(p!=rear){
            p=p->next;
            n++;
        }
        n++;
        return n;
    }
    Type getfront(){
        if(front==NULL){
            cout<<"队列已空"<<endl;
            exit(0);
        }
        Type e=front->elem;
        return e;
    }
    void inqueue(Type e){
        if(front==NULL){
            front=rear=new Linkqueuenode<Type>(e,NULL);

        }
        else{
            rear=rear->next=new Linkqueuenode<Type>(e,NULL);

        }
    }
    Type outqueue(){
        if(isempty()){
           cout<<"链队列为空"<<endl;
           exit(0);
        }
        Linkqueuenode<Type> *p=front;
        Type e=p->elem;
        front=front->next;
        if(front==NULL){
            rear=NULL;
        }
        delete p;
        return e;

    }
    private:
       Linkqueuenode<Type> *front,*rear;  
};
int main() {
    cout << "===== 测试int类型的链式队列 =====" << endl;
    Linkqueue<int> q;

    // 1. 初始状态
    cout << "\n1. 初始队列状态：" << endl;
    cout << "队列是否为空：" << (q.isempty() ? "是" : "否") << endl;
    cout << "队列长度：" << q.Linkqueuelength() << endl;

    // 2. 入队操作
    cout << "\n2. 入队元素 10, 20, 30：" << endl;
    q.inqueue(10);
    q.inqueue(20);
    q.inqueue(30);

    // 3. 入队后状态
    cout << "\n3. 入队后状态：" << endl;
    cout << "队列长度：" << q.Linkqueuelength() << endl;
    cout << "队头元素：" << q.getfront() << endl;

    // 4. 出队操作
    cout << "\n4. 连续出队2个元素：" << endl;
    q.outqueue();
    q.outqueue();

    // 5. 出队后状态
    cout << "\n5. 出队后状态：" << endl;
    cout << "队列长度：" << q.Linkqueuelength() << endl;
    cout << "队头元素：" << q.getfront() << endl;

    // 6. 清空队列
    cout << "\n6. 清空队列：" << endl;
    q.Linkqueueclear();
    cout << "队列是否为空：" << (q.isempty() ? "是" : "否") << endl;

    // 7. 测试空队列出队
    cout << "\n7. 空队列尝试出队：" << endl;
    q.outqueue();

    // 测试string类型队列（验证模板通用性）
    cout << "\n===== 测试string类型的链式队列 =====" << endl;
    Linkqueue<string> q2;
    q2.inqueue("hello");
    q2.inqueue("world");
    cout << "队列长度：" << q2.Linkqueuelength() << endl;
    q2.outqueue();
    cout << "队头元素：" << q2.getfront() << endl;

    return 0;
}