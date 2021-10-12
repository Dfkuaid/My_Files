#include<bits/stdc++.h>
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T Min(T a, T b) {return a < b ? a : b;}
template <typename T> inline T Max(T a, T b) {return a < b ? b : a;}

int t, n, a[N], b[N], bt, c[N], ct, d[N];

vector <int> v[N];

inline int gcd(int a, int b) {return b == 0 ? a : gcd(b, a % b);}

inline bool Solve(int l,int r) {
    vector <int> Len; Len.push_back(-INF);
    int len = r - l + 1; ct = 0;
    for (int i = l; i <= r; ++ i) {
        if (v[a[i]].empty()) c[++ ct] = a[i];
        v[a[i]].push_back(i);
    }
    int g = -1; bool flag = 1;
    for (int i = 1; i <= ct && flag; ++ i) {
        if (v[c[i]].size() == 1) continue;
        int tole = v[c[i]][1] - v[c[i]][0]; flag = 1;
        for (int j = 2; j < v[c[i]].size(); ++ j)
          if (tole != v[c[i]][j] - v[c[i]][j - 1]) {flag = 0; break;}
        if (!flag) break; if (g == -1) g = tole; else g = gcd(g, tole);
    }
    for (int i = 1; i <= ct; ++ i) v[c[i]].clear();
    if (!flag) return 0; if (g == 1 && ct > 1) return 0;
    if (g == 1 && ct == 1) return 1; if (g == -1) return 1;
    int last = l;
    for (int i = 1; i <= g; ++ i) {
        bt = 0;
        for (int j = 0; j * g + i <= len; ++ j) {
            int now = j * g + i + l - 1; b[++ bt] = a[now];
        }
        for (int j = last; j <= last + bt - 1; ++ j) d[j] = b[j-last+1];
        Len.push_back(bt); last = last + bt;
    }
    for (int i = l; i <= r; ++ i) a[i] = d[i];
    int now = l;
    for(int i = 1; i <= g; ++ i){
        if (!Solve(now, Min(now + Len[i] - 1, r))) return 0;
        now += Len[i];
    }
    return 1;
}

int main(){
    read(t);
    while(t--){
        read(n); for (int i = 1; i <= n; ++ i) read(a[i]);
        if(Solve(1,n)) puts("Yes"); else puts("No");
    }
    return 0;
}
