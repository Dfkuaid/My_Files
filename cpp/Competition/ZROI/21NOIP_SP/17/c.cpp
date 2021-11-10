#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 10000010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T Max(T a, T b) {return a > b ? a : b;}

int t, n, c, d[N], dv[N], dcnt;

bool solve(int x, int lmt, int rst) {
    if (rst == 1) {for (int i = 1; i <= x; ++ i) d[i] = 1; return true;}
    if (!x) return false; int mx = 0;
    if (rst <= lmt) {d[x] = rst; for (int i = 1; i < x; ++ i) d[i] = 1; return true;}
    for (int i = 2; i * i <= rst && i <= lmt; ++ i) if (!(rst % i)) {
        mx = Max(mx, i); 
        if (rst / i <= lmt) {d[x] = rst / i; return solve(x - 1, d[x] + 1, i);}
    }
    if (!mx) return false; else d[x] = mx;
    return solve(x - 1, d[x] + 1, rst / mx);
}

void MAIN() {
    read(n), read(c); dcnt = 0; bool flg = 0;
    for (int i = 1; i <= n; ++ i) d[i] = 1;
    for (int i = 1; i * i <= c && !flg; ++ i) if (!(c % i)) {
        dv[++ dcnt] = c / i; d[n] = i;
        if (solve(n - 1, d[n] + 1, c / i)) flg = 1;
    }
    if (!flg) for (int i = dcnt; i >= 1; -- i) {
        d[n] = dv[i];
        if (solve(n - 1, d[n] + 1, c / dv[i])) break;
    }
    for (int i = 1; i <= n; ++ i) printf("%d ", d[i] + i - 1); puts("");
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(t); while (t --) MAIN(); return 0;
}
