#include<bits/stdc++.h>
#define maxValue 1000000
using namespace std;

// 1. 补充缺失的Edge类定义（Prim/Kruskal算法必需）
struct Edge {
    int from;   // 边的起点
    int to;     // 边的终点
    int weight; // 边的权重
};

// 提前声明cmp函数（解决编译错误）
int cmp(const void* a, const void* b);

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
        // 无向图需要同时设置to->from（Prim/Kruskal算法通常处理无向图）
        AdjMatrix[to][from] = weight;
        indegree[from]++; // 无向图入度同步增加
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
        // 无向图同步删除反向边
        AdjMatrix[to][from] = 0;
        indegree[from]--;
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

    void DFS(int v){
        visited[v]=true;
        cout<<v<<"\t";
        for(int w=firstadj(v);w!=-1;w=nextadj(v,w)){
            if(visited[w]==false){
                DFS(w);
            }
        }
    }

    void BFS(int v){
        queue<int> Q;
        visited[v]=true;
        cout<<v<<"\t";
        Q.push(v);
        while(!Q.empty()){
            int curr=Q.front();
            Q.pop();
            for(int w=firstadj(curr);w!=-1;w=nextadj(curr,w)){
                if(visited[w]==false){
                    visited[w]=true;
                    cout<<w<<"\t";
                    Q.push(w);
                }
            }
        }
    }

    void resetVisited() {
        for(int i=0; i<numvertex; i++){
            visited[i] = false;
        }
    }

    void midnode(int i,int j,int** path){
        if(path[i][j]!=-1&&i!=path[i][j]){
            midnode(i,path[i][j],path);
            cout<<path[i][j]<<"->";
            midnode(path[i][j],j,path);
        }
    }

    void output_AIIPaths(int n,int** path, int** dist){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(i!=j){
                    if(dist[i][j] >= maxValue){
                        cout<<i<<"->"<<j<<"之间无路径可达！"<<endl;
                    } else {
                        cout<<i<<"->";
                        midnode(i,j,path);
                        cout<<j<<"  (最短路径长度："<<dist[i][j]<<")"<<endl;
                    }
                }
            }
        }
    }

    void Floyd(Graph& G,int **dist,int **path){
        int i,j,k,n=G.verticesnum();
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                if(i!=j&&G.weight(i,j)==0){
                    dist[i][j]=maxValue;
                } else {
                    dist[i][j]=G.weight(i,j);
                }
                if(i!=j&&dist[i][j]<maxValue){
                    path[i][j]=i;
                } else {
                    path[i][j]=-1;
                }
            }
        }
        for(k=0;k<n;k++){
            for(i=0;i<n;i++){
                for(j=0;j<n;j++){
                    if(dist[i][k] < maxValue && dist[k][j] < maxValue && dist[i][k]+dist[k][j]<dist[i][j]){
                        dist[i][j]=dist[i][k]+dist[k][j];
                        path[i][j]=k;
                    }
                }
            }
        }
        output_AIIPaths(n, path, dist); // 修复：传入dist数组用于判断无路径
    }

    void Prim(Graph& G,int s,Edge * MST){
        int i,j,n=G.verticesnum();
        Edge *MST_Edge=new Edge[n];
        // 初始化：所有顶点到起点s的边
        for(int i=0;i<n;i++){
            MST_Edge[i].from=i;
            MST_Edge[i].to=s;
            if(i!=s&&G.weight(i,s)==0){
                MST_Edge[i].weight=maxValue;
            } else {
                MST_Edge[i].weight=G.weight(i,s);
            }
        }
        int v,Min;
        // 选n-1条边构成最小生成树
        for(int i=0;i<n-1;i++){
            Min=maxValue;
            v=0;
            // 找到未加入生成树的、权重最小的顶点v
            for(j=0;j<n;j++){
                if(MST_Edge[j].weight!=0&&MST_Edge[j].weight<Min){
                    Min=MST_Edge[j].weight;
                    v=j;
                }
            }
            // 将选中的边加入MST
            MST[i].from=v;
            MST[i].to=MST_Edge[v].to;
            MST[i].weight=Min;
            // 标记v已加入生成树（权重置0）
            MST_Edge[v].weight=0;
            // 更新其他顶点到生成树的最小边
            for(j=0;j<n;j++){
                if(G.weight(v,j)!=0&&G.weight(v,j)<MST_Edge[j].weight){
                    MST_Edge[j].to=v;
                    MST_Edge[j].weight=G.weight(v,j);
                }
            }
        }
        // 修复：释放动态内存，避免内存泄漏
        delete[] MST_Edge;
    }

    void Kruskal(Graph& G, Edge* MST) {
        int n = G.verticesnum();       // 顶点数
        int m = G.edgesnum();          // 边数
        int* vset = new int[n];        // 顶点集合（用于并查集，判断是否成环）
        Edge* E = new Edge[m];         // 存储所有边
        int edgecnt = 0;               // 实际收集的边数

        // 步骤1：收集所有无向边（i<j避免重复收集）
        for (int i = 0; i < n; i++) {
            vset[i] = i; // 初始化并查集：每个顶点自成一个集合
            for (int j = G.firstadj(i); j != -1; j = G.nextadj(i, j)) {
                if (i < j) { // 无向图只存一次边（i->j，避免j->i重复）
                    E[edgecnt].from = i;
                    E[edgecnt].to = j;
                    E[edgecnt].weight = G.weight(i, j);
                    edgecnt++; // 修复：边计数自增，否则E数组为空
                }
            }
        }

        // 步骤2：按边的权重升序排序
        qsort(E, edgecnt, sizeof(E[0]), cmp);

        // 步骤3：贪心选边，构建最小生成树
        int cnt = 0; // 已选入生成树的边数
        int i = 0;   // 当前遍历的边索引
        while (cnt < n - 1 && i < edgecnt) {
            int x = vset[E[i].from]; // 起点所在集合
            int y = vset[E[i].to];   // 终点所在集合

            // 如果起点和终点不在同一集合（选这条边不会成环）
            if (x != y) {
                MST[cnt++] = E[i];  // 将这条边加入生成树
                // 合并两个集合：将y集合的所有顶点归属到x集合
                for (int j = 0; j < n; j++) {
                    if (vset[j] == y) {
                        vset[j] = x;
                    }
                }
            }
            i++; // 遍历下一条边
        }

        // 异常处理：非连通图，无法生成最小生成树
        if (cnt < n - 1) {
            cout << "警告：图是非连通图，无法生成完整的最小生成树！" << endl;
        }

        // 修复：释放动态内存，避免内存泄漏
        delete[] vset;
        delete[] E;
    }
};

// 边的比较函数：按权重升序，权重相同按起点降序（qsort要求的C风格比较函数）
int cmp(const void* a, const void* b) {
    Edge* c = (Edge*)a;
    Edge* d = (Edge*)b;
    if (c->weight != d->weight) {
        return c->weight - d->weight; // 权重升序
    } else {
        return d->from - c->from;     // 权重相同，起点降序（可选）
    }
}

// 工具函数1：创建n*n的二维int数组，初始化所有元素为0
int** create2DArray(int n) {
    int** arr = new int*[n];
    for (int i = 0; i < n; i++) {
        arr[i] = new int[n](); // ()表示默认初始化值为0
    }
    return arr;
}

// 工具函数2：释放n*n的二维int数组内存
void free2DArray(int** arr, int n) {
    for (int i = 0; i < n; i++) {
        delete[] arr[i];
    }
    delete[] arr;
}

// 测试用例：验证DFS/BFS + Floyd + Prim + Kruskal全功能
int main() {
    // 创建一个5个顶点的无向图（顶点0,1,2,3,4）
    Graphm g(5);

    // 设置无向边：带权重
    g.setedge(0, 1, 10);
    g.setedge(0, 2, 20);
    g.setedge(1, 3, 15);
    g.setedge(2, 3, 5);
    g.setedge(3, 4, 8);
    g.setedge(1, 4, 20);

    // ********** 原有基础操作测试 **********
    cout << "===== 图的基本信息 =====" << endl;
    cout << "顶点数：" << g.verticesnum() << endl; // 输出5
    cout << "边数：" << g.edgesnum() << endl;     // 输出6（无向边，每条算1条）
    cout << "顶点0的第一个邻接点：" << g.firstadj(0) << endl; // 输出1
    cout << "顶点0在1之后的下一个邻接点：" << g.nextadj(0, 1) << endl; // 输出2
    cout << "边0->2的权重：" << g.weight(0, 2) << endl; // 输出20
    cout << "顶点3的入度：" << g.indegree[3] << endl; // 输出3（1->3、2->3、3->4的反向）
    cout << "顶点1的入度：" << g.indegree[1] << endl; // 输出2（0->1、1->4的反向）

    // 删除边0->2再恢复
    g.deledge(0, 2);
    cout << "删除边0->2后的边数：" << g.edgesnum() << endl; // 输出5
    g.setedge(0, 2, 20); // 恢复边
    cout << "恢复边0->2后的边数：" << g.edgesnum() << endl; // 输出6

    // ********** DFS和BFS测试 **********
    cout << "\n===== DFS和BFS遍历测试 =====" << endl;
    cout << "DFS(0)：";
    g.resetVisited();
    g.DFS(0); // 输出：0    1    3    2    4

    cout << "\nBFS(0)：";
    g.resetVisited();
    g.BFS(0); // 输出：0    1    2    3    4
    cout << endl;

    // ********** Floyd最短路径测试 **********
    cout << "\n===== Floyd所有顶点对最短路径 =====" << endl;
    int n = g.verticesnum();
    int** dist = create2DArray(n);
    int** path = create2DArray(n);
    g.Floyd(g, dist, path);
    free2DArray(dist, n);
    free2DArray(path, n);

    // ********** Prim最小生成树测试 **********
    cout << "\n===== Prim最小生成树测试（起点0） =====" << endl;
    Edge* MST_Prim = new Edge[n-1]; // 生成树有n-1条边
    g.Prim(g, 0, MST_Prim);
    // 输出最小生成树的边
    int totalWeight_Prim = 0;
    for(int i=0; i<n-1; i++){
        cout << "边(" << MST_Prim[i].from << "," << MST_Prim[i].to << ") 权重：" << MST_Prim[i].weight << endl;
        totalWeight_Prim += MST_Prim[i].weight;
    }
    cout << "Prim最小生成树总权重：" << totalWeight_Prim << endl; // 预期：43
    delete[] MST_Prim; // 释放MST内存

    // ********** Kruskal最小生成树测试 **********
    cout << "\n===== Kruskal最小生成树测试 =====" << endl;
    Edge* MST_Kruskal = new Edge[n-1]; // 生成树有n-1条边
    g.Kruskal(g, MST_Kruskal);
    // 输出最小生成树的边
    int totalWeight_Kruskal = 0;
    for(int i=0; i<n-1; i++){
        cout << "边(" << MST_Kruskal[i].from << "," << MST_Kruskal[i].to << ") 权重：" << MST_Kruskal[i].weight << endl;
        totalWeight_Kruskal += MST_Kruskal[i].weight;
    }
    cout << "Kruskal最小生成树总权重：" << totalWeight_Kruskal << endl; // 预期：43
    delete[] MST_Kruskal; // 释放MST内存

    return 0;
}