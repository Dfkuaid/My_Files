#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 1010;
const int M = 4e7;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

bitset <30> p[N];

int n, m, cnt[N], f[M], pos[M];

#define lowbit(x) -(x)&(x)

int main() {
#ifdef LOCAL
    freopen("ex_A2.in", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(m);
    for (int i = 0; i < n; ++ i)
      pos[(1 << i)] = i + 1;
    for (int i = 1; i <= m; ++ i) {
        int u, v; read(u), read(v);
        p[u][v] = 1, p[v][u] = 1;
    }
    for (int i = 1; i <= n; ++ i) p[i] >>= 1;
    f[0] = 0; cnt[0] = 1;
    for (int i = 1; i < (1 << n); ++ i) {
        int t = i, lt = pos[lowbit(i)];
        bitset <30> bt(t);
        bt &= p[lt]; t -= (lowbit(i));
        f[i] = f[t] + bt.count(); ++ cnt[f[i]];
    }
    for (int i = 0; i <= m; ++ i)
      printf("%d ", cnt[i]);
    return 0;
}
