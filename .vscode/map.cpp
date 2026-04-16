#include<bits/stdc++.h>
using namespace std;

// 图的抽象基类
class Graph{
public:
    int numvertex;  // 顶点数
    int numedge;    // 边数
    bool * visited; // 访问标记数组（用于遍历）
    int * indegree; // 入度数组（用于拓扑排序等）

    // 构造函数：初始化顶点数，并为辅助数组分配内存
    Graph(int numvert){
        numvertex = numvert;
        numedge = 0;
        // 修复：为visited和indegree分配内存（原代码未分配，直接用会崩溃）
        visited = new bool[numvertex]{false}; // 初始化为未访问
        indegree = new int[numvertex]{0};     // 初始入度为0
    }

    // 析构函数：释放辅助数组内存
    ~Graph(){
        delete[] visited;
        delete[] indegree;
    }

    // 纯虚函数：获取指定顶点的第一个邻接点
    virtual int firstadj(int onevertex) = 0;
    // 纯虚函数：获取指定顶点在prevertex之后的下一个邻接点
    virtual int nextadj(int onevertex, int prevertex) = 0;

    // 获取顶点数/边数
    int verticesnum(){ return numvertex; }
    int edgesnum(){ return numedge; }

    // 纯虚函数：获取边(from, to)的权重
    virtual int weight(int from, int to) = 0;
    // 虚函数：设置边(from, to)的权重
    virtual void setedge(int from, int to, int weight);
    // 纯虚函数：删除边(from, to)
    virtual void deledge(int from, int to) = 0;
};

// 基类虚函数的空实现（也可以留空，由子类重写）
void Graph::setedge(int from, int to, int weight) {}

// 邻接矩阵实现的图类（继承Graph抽象类）
class Graphm : public Graph{
private:
    int **AdjMatrix; // 邻接矩阵：AdjMatrix[i][j]表示i到j的边的权重（0表示无边）
public:
    // 构造函数：初始化邻接矩阵
    Graphm(int numvert) : Graph(numvert) { // 先调用基类构造函数
        // 为邻接矩阵分配二维数组内存
        AdjMatrix = new int*[numvertex];
        for(int i=0; i<numvertex; i++){
            AdjMatrix[i] = new int[numvertex];
        }
        // 初始化邻接矩阵：所有边初始为0（无边）
        for(int i=0; i<numvertex; i++){
            for(int j=0; j<numvertex; j++){
                AdjMatrix[i][j] = 0;
            }
        }
    }

    // 析构函数：释放邻接矩阵内存
    ~Graphm(){
        for(int i=0; i<numvertex; i++){
            delete[] AdjMatrix[i]; // 释放每行的内存
        }
        delete[] AdjMatrix;       // 释放行指针数组
    }

    // 重写：获取边(from, to)的权重
    int weight(int from, int to) override {
        // 边界检查：防止越界访问
        if(from < 0 || from >= numvertex || to < 0 || to >= numvertex){
            return 0; // 越界视为无边
        }
        return AdjMatrix[from][to];
    }

    // 重写：设置边(from, to)的权重
    void setedge(int from, int to, int weight) override {
        // 边界检查
        if(from < 0 || from >= numvertex || to < 0 || to >= numvertex){
            cout << "顶点编号越界！" << endl;
            return;
        }
        // 如果原本无边，则边数+1，目标顶点入度+1
        if(AdjMatrix[from][to] == 0){
            numedge++;
            indegree[to]++;
        }
        // 更新边的权重
        AdjMatrix[from][to] = weight;
    }

    // 重写：删除边(from, to)
    void deledge(int from, int to) override {
        // 边界检查
        if(from < 0 || from >= numvertex || to < 0 || to >= numvertex){
            cout << "顶点编号越界！" << endl;
            return;
        }
        // 如果原本有边，则边数-1，目标顶点入度-1
        if(AdjMatrix[from][to] != 0){
            numedge--;
            indegree[to]--;
        }
        // 置为0表示无边
        AdjMatrix[from][to] = 0;
    }

    // 重写：获取onevertex的第一个邻接点
    int firstadj(int onevertex) override {
        if(onevertex < 0 || onevertex >= numvertex){
            return -1; // 越界返回-1（无邻接点）
        }
        // 遍历所有顶点，找到第一个有边的顶点
        for(int i=0; i<numvertex; i++){
            if(AdjMatrix[onevertex][i] != 0){
                return i;
            }
        }
        return -1; // 无邻接点
    }

    // 重写：获取onevertex在prevertex之后的下一个邻接点
    int nextadj(int onevertex, int prevertex) override {
        if(onevertex < 0 || onevertex >= numvertex || prevertex < 0 || prevertex >= numvertex){
            return -1;
        }
        // 从prevertex+1开始遍历，找到下一个有边的顶点
        for(int i=prevertex+1; i<numvertex; i++){
            if(AdjMatrix[onevertex][i] != 0){
                return i;
            }
        }
        return -1; // 无下一个邻接点
    }
};

// 测试用例：验证图的基本操作
int main(){
    // 创建一个5个顶点的邻接矩阵图
    Graphm g(5);

    // 设置边：0->1（权重10）、0->2（权重20）、1->3（权重15）、2->3（权重5）
    g.setedge(0, 1, 10);
    g.setedge(0, 2, 20);
    g.setedge(1, 3, 15);
    g.setedge(2, 3, 5);

    // 输出基本信息
    cout << "顶点数：" << g.verticesnum() << endl; // 输出5
    cout << "边数：" << g.edgesnum() << endl;     // 输出4
    cout << "顶点0的第一个邻接点：" << g.firstadj(0) << endl; // 输出1
    cout << "顶点0在1之后的下一个邻接点：" << g.nextadj(0, 1) << endl; // 输出2
    cout << "边0->2的权重：" << g.weight(0, 2) << endl; // 输出20
    cout << "顶点3的入度：" << g.indegree[3] << endl; // 输出2（1->3和2->3）

    // 删除边0->2
    g.deledge(0, 2);
    cout << "删除边0->2后的边数：" << g.edgesnum() << endl; // 输出3
    cout << "顶点3的入度：" << g.indegree[3] << endl; // 仍为2（删除的是0->2，不影响3的入度）

    return 0;
}