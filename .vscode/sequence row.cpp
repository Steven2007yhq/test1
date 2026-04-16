#include<bits/stdc++.h>
using namespace std;
class Seqqueue{
    private:
         int front,rear;
         int * queue;
         int maxsize;
    public:
         Seqqueue(int size=10){
             front=rear=0;
             maxsize=size;
             queue=new int[maxsize];
             if(!queue){cout<<"内存分配失败"<<endl;
                       exit(0);}
         }
         ~Seqqueue(){delete[] queue;}
         int isempty()const{
            return rear==front;              
         }
         int isfull()const{
            return front==(rear+1)%maxsize;
         }
         void Seqqueueclear(){
              front=rear=0;
         }
         int Seqqueuelength()const{
              return (rear-front+maxsize)%maxsize;
         }
         void inqueue(int e){
            if(front==(rear+1)%maxsize){
                 cout<<"队列已满"<<endl;
                 exit(0);
            }
            queue[rear]=e;
            rear=(rear+1)%maxsize;
         }
         int outqueue(){
            if(rear==front){
                cout<<"队列已空"<<endl;
                exit(0);
            }
            int e=queue[front];
            front=(front+1)%maxsize;
            return e;
         }
         int getfront(){
            if(rear==front){
                cout<<"队列已空"<<endl;
                exit(0);
            }
            int e=queue[front];
            return e;
         }
         
};
int main(){
    
    cout << "===== 初始化容量为5的循环队列（实际可用4个位置）=====" << endl;
    Seqqueue q(5); // 创建容量为5的队列

    // 1. 测试初始状态
    cout << "\n1. 初始队列状态：" << endl;
    cout << "队列是否为空：" << (q.isempty() ? "是" : "否") << endl;
    cout << "队列是否已满：" << (q.isfull() ? "是" : "否") << endl;
    cout << "队列当前长度：" << q.Seqqueuelength() << endl;

    // 2. 测试入队操作（插入4个元素，填满队列）
    cout << "\n2. 入队4个元素（10, 20, 30, 40）：" << endl;
    q.inqueue(10);
    q.inqueue(20);
    q.inqueue(30);
    q.inqueue(40);

    // 3. 测试队列满的状态
    cout << "\n3. 队列填满后的状态：" << endl;
    cout << "队列是否为空：" << (q.isempty() ? "是" : "否") << endl;
    cout << "队列是否已满：" << (q.isfull() ? "是" : "否") << endl;
    cout << "队列当前长度：" << q.Seqqueuelength() << endl;

    // 4. 测试队列满时入队（预期失败）
    cout << "\n4. 尝试入队第5个元素（50）：" << endl;
    q.inqueue(50);

    // 5. 测试获取队头元素
    cout << "\n5. 获取队头元素：" << endl;
    q.getfront();

    // 6. 测试出队操作
    cout << "\n6. 连续出队2个元素：" << endl;
    q.outqueue();
    q.outqueue();

    // 7. 出队后的队列状态
    cout << "\n7. 出队2个元素后的状态：" << endl;
    cout << "队列当前长度：" << q.Seqqueuelength() << endl;
    q.getfront(); // 此时队头应为30

    // 8. 测试继续入队（队列有空闲位置）
    cout << "\n8. 入队新元素50（队列有空闲）：" << endl;
    q.inqueue(50);
    cout << "队列当前长度：" << q.Seqqueuelength() << endl;

    // 9. 测试清空队列
    cout << "\n9. 清空队列：" << endl;
    q.Seqqueueclear();
    cout << "队列是否为空：" << (q.isempty() ? "是" : "否") << endl;

    // 10. 测试空队列出队（预期失败）
    cout << "\n10. 空队列尝试出队：" << endl;
    q.outqueue();

    // 11. 测试空队列获取队头（预期失败）
    cout << "\n11. 空队列尝试获取队头：" << endl;
    q.getfront();

    cout << "\n===== 测试结束 =====" << endl;
    return 0;

}