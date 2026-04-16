#include <iostream>
#include <list>
#include <vector>
using namespace std;

// 获取数字n的第i位（i=1：个位，i=2：十位，i=3：百位...）
int get_nth_digit(int n, int i) {
    // 处理负数（基数排序通常针对非负数，这里转为正数）
    n = abs(n);
    for (int j = 1; j < i; j++) {
        n /= 10;
    }
    return n % 10;
}

// 分配：将数组元素按当前位数分配到对应的桶中
void distribute(int rec[], int n, int radix, int digit, int current_bit, list<int> buckets[]) {
    // 清空上一轮的桶，避免残留数据
    for (int j = 0; j < radix; j++) {
        buckets[j].clear();
    }
    // 遍历数组，按当前位分配到对应桶
    for (int j = 0; j < n; j++) {
        int bucket_idx = get_nth_digit(rec[j], current_bit);
        buckets[bucket_idx].push_back(rec[j]);
    }
}

// 收集：将桶中的元素按顺序放回原数组
void collect(int rec[], int n, int radix, int digit, int current_bit, list<int> buckets[]) {
    int k = 0; // 原数组的索引
    // 按桶的顺序（0~radix-1）收集元素
    for (int j = 0; j < radix; j++) {
        // 遍历当前桶的所有元素，放入原数组
        while (!buckets[j].empty()) {
            rec[k++] = buckets[j].front(); // 取桶首元素
            buckets[j].pop_front();        // 删除桶首元素
        }
    }
}

// 基数排序主函数
// rec：待排序数组，n：数组长度，radix：基数（通常为10），digit：数组中最大数的位数
void radix_sort(int rec[], int n, int radix, int digit) {
    // 动态创建radix个桶（每个桶是一个链表）
    list<int>* buckets = new list<int>[radix];
    
    // 从第1位（个位）到第digit位（最高位）依次排序
    for (int i = 1; i <= digit; i++) {
        distribute(rec, n, radix, digit, i, buckets); // 分配
        collect(rec, n, radix, digit, i, buckets);    // 收集
    }
    
    // 释放动态内存
    delete[] buckets;
}

// 测试代码
int main() {
    int arr[] = {329, 457, 657, 839, 436, 720, 355};
    int n = sizeof(arr) / sizeof(arr[0]);
    int radix = 10;    // 十进制基数
    int max_digit = 3; // 数组中最大数是3位数（839）
    
    cout << "排序前：";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    radix_sort(arr, n, radix, max_digit);
    
    cout << "排序后：";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    return 0;
}