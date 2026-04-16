#include <bits/stdc++.h>
using namespace std;
const int N=1e3+10;
int a[N][N];
int s[N][N];
int x1[N],x2[N],y3[N],y2[N];
int n,m,q;
int main() {
    // 请在此处编写代码...
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf("%d",&a[i][j]);
        }
    }
    for(int i=1;i<=q;i++){
       
        scanf("%d%d%d%d",&x1[i],&x2[i],&y3[i],&y2[i]);
        
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            s[i][j]=s[i][j-1]+s[i-1][j]-s[i-1][j-1]+a[i][j];
        }
    }
    for(int i=1;i<=q;i++){
        cout<<s[x2[i]][y2[i]]-s[x1[i]-1][y2[i]]-s[x2[i]][y3[i]-1]+s[x1[i]-1][y3[i]-1]<<endl;
    }
    
    return 0;
}