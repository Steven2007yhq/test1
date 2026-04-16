#include<bits/stdc++.h>
using namespace std;

template<class T>
class Maxheap{
private:
    T * Heap;      // 堆的数组指针（外部传入，堆类不管理内存）
    int n;         // 当前堆中元素个数
    int maxsize;   // 堆的最大容量

    // 新增：向上滤（用于插入/移除指定元素后调整堆）
    void siftup(int pos) {
        T temp = Heap[pos];
        // 有父节点且父节点值小于当前节点（最大堆特性）
        while (pos > 0 && Heap[parent(pos)] < temp) {
            Heap[pos] = Heap[parent(pos)]; // 父节点下移
            pos = parent(pos);             // 移动到父节点位置
        }
        Heap[pos] = temp; // 插入到正确位置
    }

public:
    // 构造函数：初始化堆并构建最大堆
    Maxheap(T* h, int num, int max) {
        Heap = h;
        n = num;
        maxsize = max;
        buildheap();
    }

    // 修复：析构函数不释放Heap（Heap由外部传入，避免双重释放）
    ~Maxheap() {};

    // 获取当前堆大小
    int heapsize() {
        return n;
    }

    // 修复：判断叶子节点应基于当前堆大小n，而非最大容量maxsize
    bool isleaf(int pos) {
        return (pos * 2 + 1) >= n; // 无左孩子则为叶子节点
    }

    // 获取左孩子索引
    int leftchild(int pos) {
        return pos * 2 + 1;
    }

    // 获取右孩子索引
    int rightchild(int pos) {
        return pos * 2 + 2;
    }

    // 获取父节点索引
    int parent(int pos) {
        return (pos - 1) / 2;
    }

    // 修复：构建堆的循环范围（i从n/2-1到0，而非i>0）
    void buildheap() {
        // 从最后一个非叶子节点开始下滤，确保所有节点满足最大堆特性
        for (int i = n / 2 - 1; i >= 0; i--) {
            siftdown(i);
        }
    }

    // 向下滤：调整指定位置节点，使其满足最大堆特性
    void siftdown(int pos) {
        if (pos < 0 || pos >= n) {
            cout << "Invalid position!" << endl;
            return;
        }
        T temp = Heap[pos];
        while (!isleaf(pos)) { // 非叶子节点才需要调整
            int lc = leftchild(pos);
            // 选择左右孩子中较大的那个
            if (lc + 1 < n && Heap[lc] < Heap[lc + 1]) {
                lc++; // 右孩子更大，切换到右孩子
            }
            // 当前节点值大于等于最大孩子，无需调整
            if (temp >= Heap[lc]) break;
            // 孩子节点上移
            Heap[pos] = Heap[lc];
            pos = lc; // 移动到孩子节点位置
        }
        Heap[pos] = temp; // 插入到正确位置
    }

    // 修复：插入元素的循环条件（避免越界，逻辑更严谨）
    bool insert(const T& newkey) {
        if (n == maxsize) { // 堆已满，插入失败
            cout << "Heap is full!" << endl;
            return false;
        }
        int curr = n++; // 新元素放在最后，堆大小+1
        Heap[curr] = newkey;
        siftup(curr); // 向上滤调整堆结构
        return true;
    }

    // 修复：返回值改为值类型（避免返回局部变量引用导致未定义行为）
    T removemax() {
        if (n == 0) { // 堆空，抛出异常或提示
            cerr << "Remove from empty Heap!" << endl;
            throw runtime_error("Heap is empty");
        }
        T temp = Heap[0]; // 保存堆顶（最大值）
        n--;              // 堆大小-1
        Heap[0] = Heap[n]; // 最后一个元素移到堆顶
        siftdown(0);      // 向下滤调整堆结构
        return temp;
    }

    // 补全：移除指定位置的元素，将移除的元素存入node，返回是否成功
    bool remove(int pos, T & node) {
        if (pos < 0 || pos >= n) { // 位置无效
            cout << "Invalid position!" << endl;
            return false;
        }
        node = Heap[pos]; // 保存要移除的元素
        n--;              // 堆大小-1
        Heap[pos] = Heap[n]; // 最后一个元素移到当前位置

        // 判断需要向上滤还是向下滤：
        // 1. 若当前节点大于父节点 → 向上滤
        // 2. 否则 → 向下滤
        if (pos > 0 && Heap[pos] > Heap[parent(pos)]) {
            siftup(pos);
        } else {
            siftdown(pos);
        }
        return true;
    }

    // 新增：打印堆（用于测试）
    void printHeap() {
        for (int i = 0; i < n; i++) {
            cout << Heap[i] << " ";
        }
        cout << endl;
    }
    void filterdown(int i,int EndOfHeap){
        int current=i;
        int child=2*i+1;
        T temp=Heap[i];
        while(child<=EndOfHeap){
            if(child+1<=EndOfHeap&&Heap[child]<Heap[child+1]){
                child=child+1;
            }
            if(temp>=Heap[child]){
                break;
            }
            else{
                Heap[current]=Heap[child];
                current=child;
                child=child*2+1;
            }
        }
        Heap[current]=temp;
    }
    void Heapsort(){
        for(int i=(n-2)/2;i>=0;i--)filterdown(i,n-1);
        for(int i=n-1;i>=1;i--){
            swap(Heap[0],Heap[i]);
            filterdown(0,i-1);
        }
    }
};
void printArray(int a[],int n){
    for(int i=0;i<=n-1;i++){
        cout<<a[i]<<" ";
    }
}
int main() {
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6};
    int maxsize = 10;
    int n = sizeof(arr) / sizeof(arr[0]);

    // 初始化最大堆
    Maxheap<int> heap(arr, n, maxsize);
    cout << "初始堆：";
    heap.printHeap(); // 输出：9 6 4 1 5 3 2 1

    // 插入元素7
    heap.insert(7);
    cout << "插入7后：";
    heap.printHeap(); // 输出：9 7 4 6 5 3 2 1 1

    // 移除堆顶（最大值9）
    int maxVal = heap.removemax();
    cout << "移除最大值：" << maxVal << "，堆变为：";
    heap.printHeap(); // 输出：7 6 4 1 5 3 2 1

    // 移除位置3的元素
    int removedVal;
    heap.remove(3, removedVal);
    cout << "移除位置3的元素：" << removedVal << "，堆变为：";
    heap.printHeap(); // 输出：7 6 4 1 5 3 2
    cout << "===== 堆排序测试程序 =====" << endl;

    // 测试用例1：普通无序数组（含不同数值）
    cout << "\n【测试用例1】普通无序数组" << endl;
    int arr1[] = {3, 1, 4, 1, 5, 9, 2, 6};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int maxsize1 = n1; // 堆容量等于数组长度即可
    cout << "排序前：";
    printArray(arr1, n1);
    Maxheap<int> heap1(arr1, n1, maxsize1);
    heap1.Heapsort(); // 执行堆排序
    cout << "排序后：";
    printArray(arr1, n1); // 输出升序数组

    // 测试用例2：含重复元素的数组
    cout << "\n【测试用例2】含重复元素的数组" << endl;
    int arr2[] = {5, 2, 8, 2, 9, 5, 1, 5};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int maxsize2 = n2;
    cout << "排序前：";
    printArray(arr2, n2);
    Maxheap<int> heap2(arr2, n2, maxsize2);
    heap2.Heapsort();
    cout << "排序后：";
    printArray(arr2, n2);

    // 测试用例3：单元素数组（边界情况）
    cout << "\n【测试用例3】单元素数组" << endl;
    int arr3[] = {10};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int maxsize3 = n3;
    cout << "排序前：";
    printArray(arr3, n3);
    Maxheap<int> heap3(arr3, n3, maxsize3);
    heap3.Heapsort();
    cout << "排序后：";
    printArray(arr3, n3);

    // 测试用例4：空数组（边界情况，需处理）
    cout << "\n【测试用例4】空数组" << endl;
    int* arr4 = new int[0]; // 空数组
    int n4 = 0;
    int maxsize4 = 0;
    cout << "排序前：(空数组)" << endl;
    if (n4 == 0) {
        cout << "排序后：(空数组，无需排序)" << endl;
    } else {
        Maxheap<int> heap4(arr4, n4, maxsize4);
        heap4.Heapsort();
        printArray(arr4, n4);
    }
    delete[] arr4; // 释放空数组内存

    
    return 0;
}