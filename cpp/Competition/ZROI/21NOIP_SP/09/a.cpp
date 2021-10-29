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
template <typename T> inline T Min(T a, T b) {return a < b ? a : b;}

struct Edge {int u, v, nxt;} e[N], ne[N];
struct DSU {
    int fa[N], siz[N], num;

    inline void init(int x) {
        num = x;
        for (int i = 1; i <= num; ++ i)
          fa[i] = i, siz[i] = 1;
    }
    
    inline int find(int x) {
        while (x != fa[x]) x = fa[x] = fa[fa[x]]; return x;
    }

    inline void merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        if (siz[x] > siz[y]) swap(x, y);
        siz[y] += siz[x], fa[x] = y;
    }
} dsu;

int n, col[N], head[N], ecnt(1), ncnt(1), nhead[N], vis[N], d[N];

inline void add_edge(int u, int v) {
    e[ecnt].u = u, e[ecnt].v = v;
    e[ecnt].nxt = head[u], head[u] = ecnt ++;
}

inline void connect(int u, int v) {
    ne[ncnt].u = u, ne[ncnt].v = v;
    ne[ncnt].nxt = nhead[u], nhead[u] = ncnt ++;

    ne[ncnt].u = v, ne[ncnt].v = u;
    ne[ncnt].nxt = nhead[v], nhead[v] = ncnt ++;
}

void combine(int x, int fa) {
    vis[x] = 1;
    for (int i = head[x]; i; i = e[i].nxt) {
        if (e[i].v == fa) continue;
        if (col[e[i].v] == col[x])
          dsu.merge(e[i].v, x), combine(e[i].v, x);
    }
}

void build(int x, int fa) {
    for (int i = head[x]; i; i = e[i].nxt) {
        if (e[i].v == fa) continue;
        if (col[e[i].v] != col[x])
          connect(dsu.find(x), dsu.find(e[i].v));
        build(e[i].v, x);
    }
}

int res;

void dfs(int x, int fa) {
    d[x] = d[fa] + 1;
    for (int i = nhead[x]; i; i = ne[i].nxt) {
        if (ne[i].v == fa) continue;
        dfs(ne[i].v, x);
    }
    if (d[x] > d[res]) res = x;
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n); dsu.init(n);
    for (int i = 1; i <= n; ++ i) {
        char c; cin >> c; 
        if (c == 'R') col[i] = 1;
        else col[i] = 0;
    }
    for (int i = 1; i < n; ++ i) {
        int u, v; read(u), read(v);
        add_edge(u, v); add_edge(v, u);
    }
    for (int i = 1; i <= n; ++ i)
      if (!vis[i]) combine(i, 0);
    int st = 0, ed = 0;
    build(1, 0); dfs(dsu.find(1), 0);
    mset(d, 0); st = res; res = 0;
    dfs(dsu.find(st), 0); ed = res;
    printf("%d", d[ed] / 2);
    return 0;
}
