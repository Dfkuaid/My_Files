#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 5010;
const int INF = 0x3f3f3f3f;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int t, n, d, lg[N], sum[15], f[N], dep[N];

inline void prework() {
    for (int i = 2; i <= 5000; ++ i) lg[i] = lg[i >> 1] + 1;
    for (int i = 0; i <= 12; ++ i) sum[i + 1] = sum[i] + (1 << i) * i;
}

inline void MAIN() {
    read(n); read(d);
    int mn = sum[lg[n]] + (n - (1 << lg[n]) + 1) * lg[n];
    if (d < mn) {puts("NO"); return;}
    for (int i = 1; i <= n; ++ i) f[i] = i >> 1;
    for (int i = 2; i <= n; ++ i) dep[i] = dep[f[i]] + 1;
    int rst = d - mn, q = 1 << lg[n];
    if (!rst) {
        puts("YES");
        for (int i = 2; i <= n; ++ i) printf("%d ", f[i]);
        puts(""); return;
    }
    for (int p = n; p >= 1 && rst; -- p) {
        if (!(p & (p - 1))) continue;
        rst -= dep[q] - dep[p] + 1;
        if (rst < 0) {
            while (rst) q = f[q], ++ rst;
            f[p] = q; break;
        }
        f[p] = q, dep[p] = dep[q] + 1, q = p;
    }
    if (rst) {puts("NO"); return;} else puts("YES");
    for (int i = 2; i <= n; ++ i) printf("%d ", f[i]); puts("");
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    prework(); read(t); while (t --) MAIN(); return (0 - 0);
}
