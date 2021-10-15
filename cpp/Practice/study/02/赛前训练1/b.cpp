#define LOCAL
#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 50010;
const ll INF = 1e17;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

struct Edge {int u, v, nxt; ll w;} e[N << 1];

int t, n, m, head[N], ecnt(1), alist[N], acnt;
ll tag[N], g[N], f[N], sum, ans = INF;

inline void reset() {
    mset(head, 0); mset(tag, 0); ecnt = 1, acnt = 0;
}

inline void add_edge(int u, int v, ll w) {
    e[ecnt].u = u, e[ecnt].v = v, e[ecnt].w = w;
    e[ecnt].nxt = head[u], head[u] = ecnt ++;
}

void get_init(int x, int fa) {
    g[x] = tag[x], f[x] = 0;
    for (int i = head[x]; i; i = e[i].nxt) {
        if (e[i].v == fa) continue;
        get_init(e[i].v, x); g[x] += g[e[i].v];
        f[x] += f[e[i].v] + e[i].w * g[e[i].v];
    }
}

void dp(int x, int fa) {
    for (int i = head[x]; i; i = e[i].nxt) {
        if (e[i].v == fa) continue;
        f[e[i].v] = f[x] - 2 * e[i].w * g[e[i].v] + e[i].w * sum;
        dp(e[i].v, x);
    }
}

signed main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(t);
    while (t --) {
        read(n); reset(); ans = INF;
        for (int i = 1; i < n; ++ i) {
            int u, v; ll w; read(u); read(v); read(w);
            add_edge(u, v, w); add_edge(v, u, w);
        }
        read(m);
        for (int i = 1; i <= m; ++ i) {
            int x; read(x); read(tag[x]); tag[x] <<= 1;
        }
        get_init(1, 0); sum = g[1]; dp(1, 0);
        for (int i = 1; i <= n; ++ i)
          ans = min(ans, f[i]);
        printf("%lld\n", ans);
        for (int i = 1; i <= n; ++ i)
          if (f[i] == ans) alist[++ acnt] = i;
        for (int i = 1; i <= acnt; ++ i) {
            printf("%d", alist[i]);
            if (i < acnt) printf(" ");
        }
        printf("\n");
    }
    return 0;
}
