#include<bits/stdc++.h>
using namespace std;
const int N=1e4+10;
int idx=1,h;
int e[N];
int ne[N];

void add(double x){
    e[idx]=x;
    ne[idx]=h;
    h=idx++;
}


int merge(int a, int b) {
    if (!a) return b;
    if (!b) return a;
    int head;
    if (e[a] < e[b]) {
        head = a;
        ne[head] = merge(ne[a], b);
    } else {
        head = b;
        ne[head] = merge(a, ne[b]);
    }
    return head;
}


int mergeSort(int head) {
    if (!head || !ne[head]) return head;

 
    int slow = head, fast = ne[head];
    while (fast && ne[fast]) {
        slow = ne[slow];
        fast = ne[ne[fast]];
    }

    int mid = slow;
    int r = ne[mid];
    ne[mid] = 0; 

    int l = mergeSort(head);
    r = mergeSort(r);
    return merge(l, r);
}

int main() {
    int n;
    int a;
   
    scanf("%d", &n);
    srand(time(0));
    for (int i=1; i<=n; i++) {
        
         a=rand()%10000;
        add(a);
    }

    h = mergeSort(h); 

    for (int i=h; i!=0; i=ne[i]) {
        printf("%d\t", e[i]);
    }
    return 0;
}