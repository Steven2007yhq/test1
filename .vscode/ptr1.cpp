#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
struct node{
    int value;
    struct node*next;
  
}a[N];

int main() {
    // 请在此处编写代码...
    int n,m;
    scanf("%d%d",&n,&m);
    
    for(int i=1;i<=n-1;i++){
        a[i].value=i;
        a[i].next=&a[i+1];
    }
    a[n].value=n;
    a[n].next=NULL;
    struct node*head=&a[1];
    int a;
    int p,q;
    for(int i=1;i<=m;i++){
        scanf("%d",&a);
        if(a==1){
            scanf("%d",&p);
            a[p-1].next=a[p].next;
            a[p].next=head;
        }
        else if(a==2){
            scanf("%d",&p);
            a[p-1].next=a[p].next;
            a[n].next=&a[p];
            a[p].next=NULL;
        }
        else{
            scanf("%d%d",&p,&q);
            a[p-1].next=a[p].next;
            a[q].next=&a[p];
            a[p].next=&a[q+1];
        }
    }
    struct node*head=&a[1];
    for(int i=1;i<=n;i++){
        printf("%d ",head->value);
        head=head->next;
    }
    return 0;
}