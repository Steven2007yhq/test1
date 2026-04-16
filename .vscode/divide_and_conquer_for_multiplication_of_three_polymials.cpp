#include<bits/stdc++.h>
using namespace std;

string a,b,c;
const int N=1e3;
vector<int> array1, array2, array3;
vector<int> temp1;

vector<int> add(vector<int>& a, vector<int>& b) {
    vector<int> res(max(a.size(), b.size()));
    for (int i = 0; i < res.size(); i++) {
        int va = i < a.size() ? a[i] : 0;
        int vb = i < b.size() ? b[i] : 0;
        res[i] = va + vb;
    }
    return res;
}

vector<int> sub(vector<int> x, vector<int> y, vector<int> z) {
    int len = max({x.size(), y.size(), z.size()});
    vector<int> ans(len, 0);
    for (int i = 0; i < len; i++) {
        int xv = (i < x.size()) ? x[i] : 0;
        int yv = (i < y.size()) ? y[i] : 0;
        int zv = (i < z.size()) ? z[i] : 0;
        ans[i] = xv - yv - zv;
    }
    return ans;
}


vector<int> times(vector<int> x, vector<int> y) {
    int n = x.size();
    int m = y.size();
    if (n == 0 || m == 0) return {0};

    if (n <= 1 || m <= 1) {
        vector<int> res(n + m - 1, 0);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                res[i + j] += x[i] * y[j];
        return res;
    }

    int mid = max(n, m) / 2;
    vector<int> A0, A1, B0, B1;

    for (int i = 0; i < min(mid, n); i++) A0.push_back(x[i]);
    for (int i = mid; i < n; i++) A1.push_back(x[i]);
    for (int i = 0; i < min(mid, m); i++) B0.push_back(y[i]);
    for (int i = mid; i < m; i++) B1.push_back(y[i]);

    auto s1 = times(A0, B0);
    auto s2 = times(A1, B1);
    auto C = add(A0, A1);
    auto D = add(B0, B1);
    auto s3 = times(C, D);
    auto mid_term = sub(s3, s1, s2);

    int shift = mid;
    vector<int> ans(n + m - 1, 0);

    for (int i = 0; i < s1.size(); i++) ans[i] += s1[i];
    for (int i = 0; i < mid_term.size(); i++) ans[i + shift] += mid_term[i];
    for (int i = 0; i < s2.size(); i++) ans[i + 2 * shift] += s2[i];

    return ans;
}

void font(vector<int> x){
    bool first = 1;
    for(int i=0;i<x.size();i++){
        if(x[i]==0) continue;
        if(!first) cout<<"+";
        first=0;
        cout<<x[i]<<"x^"<<i;
    }
    cout<<endl;
}


void parse(string &s, vector<int> &arr) {
    arr.clear();
    vector<int> coeff(N, 0);
    int i = 0, n = s.size();
    while (i < n) {
        int sign = 1;
        if (s[i] == '+') i++;
        else if (s[i] == '-') sign = -1, i++;

        int num = 0;
        while (i < n && isdigit(s[i])) {
            num = num * 10 + s[i] - '0';
            i++;
        }

        int exp = 0;
        if (i < n && s[i] == 'x') {
            i++;
            if (i < n && s[i] == '^') i++;
            while (i < n && isdigit(s[i])) {
                exp = exp * 10 + s[i] - '0';
                i++;
            }
        }

        if (exp < N) coeff[exp] += sign * num;
    }

    int max_e = 0;
    for (int i = 0; i < N; i++) if (coeff[i] != 0) max_e = i;
    for (int i = 0; i <= max_e; i++) arr.push_back(coeff[i]);
}

int main(){
    getline(cin, a);
    getline(cin, b);
    getline(cin, c);

    parse(a, array1);
    parse(b, array2);
    parse(c, array3);

    vector<int> ab = times(array1, array2);
    vector<int> abc = times(ab, array3);

    font(abc);
    return 0;
}