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

vector<int> times(vector<int> x,vector<int> y,int l1,int r1,int l2,int r2)
{
    if(x.empty() || y.empty()) return {0};
    if(l1 > r1 || l2 > r2) return {0};

    if(l1 == r1 || l2 == r2){
        vector<int> res(r1-l1+r2-l2+1, 0);
        for(int i=l1; i<=r1; i++){
            for(int j=l2; j<=r2; j++){
                res[i-l1 + j-l2] += x[i] * y[j];
            }
        }
        return res;
    }

    int mid1 = (l1 + r1) / 2;
    int mid2 = (l2 + r2) / 2;
    vector<int> A0,B0,A1,B1;

    for(int i=l1;i<=mid1;i++) A0.push_back(x[i]);
    for(int i=mid1+1;i<=r1;i++) A1.push_back(x[i]);
    for(int i=l2;i<=mid2;i++) B0.push_back(y[i]);
    for(int i=mid2+1;i<=r2;i++) B1.push_back(y[i]);

    vector<int> s1 = times(A0,B0,0,A0.size()-1,0,B0.size()-1);
    vector<int> s2 = times(A1,B1,0,A1.size()-1,0,B1.size()-1);
    vector<int> C = add(A0,A1);
    vector<int> D = add(B0,B1);
    vector<int> s3 = times(C,D,0,C.size()-1,0,D.size()-1);
    vector<int> mid_term = sub(s3,s1,s2);

    int shift = mid1 - l1 + 1;
    int total_len = (r1-l1+1)+(r2-l2+1)-1;
    vector<int> ans(total_len, 0);

    for(int i=0; i<s1.size(); i++) ans[i] += s1[i];
    for(int i=0; i<mid_term.size(); i++) ans[i+shift] += mid_term[i];
    for(int i=0; i<s2.size(); i++) ans[i+2*shift] += s2[i];

    return ans;
}

void font(vector<int> x){
    bool first = 1;
    for(int i=0;i<x.size();i++){
        if(x[i]==0) continue;
        if(!first) cout << "+";
        first = 0;
        cout << x[i] << "x^" << i;
    }
    cout << endl;
}

vector<int> times2(vector<int> x,vector<int> y,vector<int> a,vector<int> b){
    vector<int> t = times(x,y,0,x.size()-1,0,y.size()-1);
    return sub(t,a,b);
}

int main(){
    getline(cin,a);
    getline(cin,b);
    getline(cin,c);

    auto parse = [&](string &s, vector<int> &arr){
        arr.clear();
        int n = s.size(), i=0;
        vector<int> coeff(N, 0);
        while(i < n){
            int sign = 1;
            if(s[i] == '-') sign = -1, i++;
            else if(s[i] == '+') i++;
            int num = 0;
            while(i < n && isdigit(s[i])){
                num = num*10 + s[i]-'0';
                i++;
            }
            int exp = 0;
            if(i < n && s[i] == 'x'){
                i++;
                if(i < n && s[i] == '^') i++;
                while(i < n && isdigit(s[i])){
                    exp = exp*10 + s[i]-'0';
                    i++;
                }
            }
            if(exp < N) coeff[exp] += sign * num;
        }
        int mx = 0;
        for(int i=0; i<N; i++) if(coeff[i]) mx = i;
        for(int i=0; i<=mx; i++) arr.push_back(coeff[i]);
    };

    parse(a, array1);
    parse(b, array2);
    parse(c, array3);

    vector<int> ab = times(array1, array2, 0, array1.size()-1, 0, array2.size()-1);
    vector<int> abc = times(ab, array3, 0, ab.size()-1, 0, array3.size()-1);

    font(abc);
    return 0;
}