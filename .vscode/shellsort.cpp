#include<bits/stdc++.h>
using namespace std;
const int N=1e3;
int a[N];  // 数组

// 希尔排序
void shell_sort(int n) {
    // 步长 gap 初始为 n/2，每次减半，直到 gap=1
    for (int gap = n / 2; gap > 0; gap /= 2) {
        
        // 对每个分组做插入排序
        for (int i = gap; i < n; i++) {
            int temp = a[i];  // 待插入的数
            int j;
            
            // 分组内向前比较、移动
            for (j = i; j >= gap && a[j - gap] > temp; j -= gap) {
                a[j] = a[j - gap];
            }
            
            a[j] = temp;  // 插入正确位置
        }
    }
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    shell_sort(n);  // 排序
    
    // 输出
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    return 0;
}