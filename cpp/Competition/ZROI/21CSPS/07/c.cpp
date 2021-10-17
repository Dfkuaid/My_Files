#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 810;
const int M = 500000;
const ll MOD = 1e9 + 7;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T Max(T a, T b) {return a > b ? a : b;}
template <typename T> inline T Min(T a, T b) {return a < b ? a : b;}

struct Edge {
    int u, v, w;
    inline bool operator < (const Edge b) const {return w < b.w;}
} e[N], ne[M];

struct TEdge {int u, v, w, nxt;} te[N];

int n, m, fa[N], siz[N], nowans, c[N][N], ncnt;
int ecnt(1), head[N], dep[N], f[21][N], mx[21][N];

int find(int x) {while (x != fa[x]) x = fa[x] = fa[fa[x]]; return x;}

void connect(int u, int v) {
    u = find(u), v = find(v);
    ll tmp = siz[u] * (siz[u] - 1) / 2;
    tmp += siz[v] * (siz[v] - 1) / 2;
    if (siz[u] > siz[v]) swap(u, v);
    fa[u] = v; siz[v] += siz[u]; nowans -= tmp;
    nowans += siz[v] * (siz[v] - 1) / 2;
}

inline void add_edge(int u, int v, int w) {
    te[ecnt].u = u, te[ecnt].v = v, te[ecnt].w = w;
    te[ecnt].nxt = head[u], head[u] = ecnt ++;
}

void dfs(int x, int fa) {
    f[0][x] = fa, dep[x] = dep[fa] + 1;
    for (int i = 1; i <= 20; ++ i)
      f[i][x] = f[i - 1][f[i - 1][x]];
    for (int i = 1; i <= 20; ++ i)
      mx[i][x] = Max(mx[i - 1][x], mx[i - 1][f[i - 1][x]]);
    for (int i = head[x]; i; i = te[i].nxt)
      if (te[i].v != fa) {
          mx[0][te[i].v] = te[i].w; dfs(te[i].v, x);
      }
}

int get_limit(int u, int v) {
    int res = -INF;
    if (dep[u] < dep[v]) swap(u, v);
    for (int i = 20; ~i; -- i)
      if (dep[f[i][u]] >= dep[v])
        res = Max(res, mx[i][u]), u = f[i][u];
    if (u == v) return res;
    for (int i = 20; ~i; -- i)
      if (f[i][u] != f[i][v]) {
          res = Max(res, mx[i][u]), u = f[i][u];
          res = Max(res, mx[i][v]), v = f[i][v];
      }
    res = Max(res, Max(mx[0][u], mx[0][v]));
    return res;
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n); m = (n - 1) * n / 2;
    for (int i = 1; i < n; ++ i) {
        read(e[i].u), read(e[i].v), read(e[i].w);
        add_edge(e[i].u, e[i].v, e[i].w);
        add_edge(e[i].v, e[i].u, e[i].w);
        c[e[i].u][e[i].v] = e[i].w;
        c[e[i].v][e[i].u] = e[i].w;
    }  
    sort(e + 1, e + n); int nowedge = 1;
    for (int i = 1; i <= n; ++ i) fa[i] = i;
    for (int i = 1; i <= n; ++ i) siz[i] = 1;
    ll ans = 1;
    for (int i = 1; i <= m; ++ i) {
        if (nowedge < n && e[nowedge].w == i) {
            connect(e[nowedge].u, e[nowedge].v);
            ++ nowedge; continue;
        }
        (ans *= (nowans - i + 1)) %= MOD;
    }
    printf("%lld\n", ans); nowedge = 1;
    if (!ans) return 0; dfs(1, 0);
    for (int i = 1; i <= n; ++ i)
      for (int j = 1; j < i; ++ j)
        if (!c[i][j])  {
            ne[++ ncnt].u = i, ne[ncnt].v = j;
            ne[ncnt].w = get_limit(i, j);
        }
    sort(ne + 1, ne + ncnt + 1); int necnt = 1;
    for (int i = 1; i <= m; ++ i) {
        if (nowedge < n && e[nowedge].w == i) {++ nowedge; continue;}
        c[ne[necnt].u][ne[necnt].v] = i; c[ne[necnt].v][ne[necnt].u] = i; ++ necnt;
    }
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= n; ++ j) printf("%d ", c[i][j]);
        printf("\n");
    }
    return 0;
}
