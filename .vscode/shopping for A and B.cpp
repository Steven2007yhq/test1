#include <bits/stdc++.h>
using namespace std;

const int N = 105;
int price[N], happy[N], type[N];
int dp[N][N][5005];
int pre_a[N][N][5005], pre_j[N][N][5005];
bool sel[N];

int n, money;

int main() {
    cin >> n >> money;
    for (int i = 1; i <= n; i++) cin >> price[i];
    for (int i = 1; i <= n; i++) cin >> happy[i];
    for (int i = 1; i <= n; i++) {
        char t; cin >> t;
        type[i] = (t == 'A');
    }

    memset(dp, -0x3f, sizeof(dp));
    dp[0][0][0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int a = 0; a <= n/2; a++) {
            for (int j = 0; j <= money; j++) {

                if (type[i] == 1) { 
                    if (a >= 1 && j >= price[i]) {
                        int no = dp[i-1][a][j];
                        int yes = dp[i-1][a-1][j-price[i]] + happy[i];
                        if (yes > no) {
                            dp[i][a][j] = yes;
                            pre_a[i][a][j] = a-1;
                            pre_j[i][a][j] = j-price[i];
                        } else {
                            dp[i][a][j] = no;
                            pre_a[i][a][j] = a;
                            pre_j[i][a][j] = j;
                        }
                    } else {
                        dp[i][a][j] = dp[i-1][a][j];
                        pre_a[i][a][j] = a;
                        pre_j[i][a][j] = j;
                    }
                } else { 
                    if (j >= price[i]) {
                        int no = dp[i-1][a][j];
                        int yes = dp[i-1][a][j-price[i]] + happy[i];
                        if (yes > no) {
                            dp[i][a][j] = yes;
                            pre_a[i][a][j] = a;
                            pre_j[i][a][j] = j-price[i];
                        } else {
                            dp[i][a][j] = no;
                            pre_a[i][a][j] = a;
                            pre_j[i][a][j] = j;
                        }
                    } else {
                        dp[i][a][j] = dp[i-1][a][j];
                        pre_a[i][a][j] = a;
                        pre_j[i][a][j] = j;
                    }
                }

            }
        }
    }
    int max_hap = 0, best_a = 0, best_j = money;
    for (int a = 0; a <= n/2; a++) {
        for (int j = 0; j <= money; j++) {
            if (dp[n][a][j] < 0) continue;

            int ta = a, tj = j, cnt = 0;
            for (int p = n; p >= 1; p--) {
                int pa = pre_a[p][ta][tj];
                int pj = pre_j[p][ta][tj];
                if (dp[p-1][pa][pj] != dp[p][ta][tj]) cnt++;
                ta = pa; tj = pj;
            }

            int b = cnt - a;
            if (a <= b && dp[n][a][j] > max_hap) {
                max_hap = dp[n][a][j];
                best_a = a;
                best_j = j;
            }
        }
    }

    if (max_hap == 0) {
        cout << 0 << endl;
        return 0;
    }

    int now_i = n, now_a = best_a, now_j = best_j;
    while (now_i > 0) {
        int pa = pre_a[now_i][now_a][now_j];
        int pj = pre_j[now_i][now_a][now_j];
        if (dp[now_i-1][pa][pj] != dp[now_i][now_a][now_j]) {
            sel[now_i] = 1;
        }
        now_i--;
        now_a = pa;
        now_j = pj;
    }

    for (int i = 1; i <= n; i++)
        if (sel[i]) cout << i << " ";
    cout << endl << max_hap << endl;

    return 0;
}