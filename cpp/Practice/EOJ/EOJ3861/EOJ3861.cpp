#define LOCAL
#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 2000010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T Max(T a, T b) {return a > b ? a : b;}

struct Edge {int u, v, nxt;} e[N];

int head[N], ecnt(1), icnt[N];

inline void add_edge(int u, int v) {
    e[ecnt].u = u, e[ecnt].v = v; ++ icnt[v];
    e[ecnt].nxt = head[u], head[u] = ecnt ++;
}

int n, m, a[N], mx, f[N], frt, tal, q[N], vis[N], tcnt[N];

inline int calc(int id, int val) {return a[id] >= val ? 1 : -1;}

bool check(int x) {
    fill(f + 1, f + n + 1, -INF); mset(vis, 0);
    frt = 0, tal = -1, vis[1] = 1, f[1] = calc(1, x);
    for (int i = 1; i <= n; ++ i) {
        tcnt[i] = icnt[i];
        if (!icnt[i]) q[++ tal] = i;
    }
    while (frt <= tal) {
        int now = q[frt ++]; // printf("%d %d\n", now, f[now]);
        for (int i = head[now]; i; i = e[i].nxt) {
            vis[e[i].v] |= vis[now];
            if (vis[e[i].v]) f[e[i].v] = Max(f[e[i].v], f[now] + calc(e[i].v, x));
            if (!(-- tcnt[e[i].v])) q[++ tal] = e[i].v;
        }
    }
    return f[n] >= 0;
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n); read(m);
    for (int i = 1; i <= n; ++ i)
      read(a[i]), mx = Max(mx, a[i]);
    for (int i = 1; i <= m; ++ i) {
        int u, v; read(u), read(v);
        add_edge(u, v);
    }
    check(-1); if (f[n] < 0) {puts("-1"); return 0;}
    int l = -1, r = mx, ans = 0;
    while (l <= r) {
        int mid = l + r >> 1;
        if (check(mid))
          ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    printf("%d", ans); return 0;
}
