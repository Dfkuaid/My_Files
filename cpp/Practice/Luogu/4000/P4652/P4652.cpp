#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

struct Edge {int u, v, w, nxt;} ge[N], te[N];

int ghead[N], gecnt(1), thead[N], tecnt(1), scnt, dif[N], ans[N];
int n, m, p, stk[N], stp, dfn[N], low[N], T, instk[N], bel[N], vis[N];

inline void add_edge_g(int u, int v, int w, int id) {
    ge[gecnt].u = u, ge[gecnt].v = v, ge[gecnt].w = w, ge[gecnt].id = id;
    ge[gecnt].nxt = ghead[u], ghead[u] = gecnt ++;
}

inline void add_edge_t(int u, int v, int w, int id) {
    te[tecnt].u = u, te[tecnt].v = v, te[tecnt].w = w, te[tecnt].id = id;
    te[tecnt].nxt = thead[u], thead[u] = tecnt ++;
}

void tarjan(int x, int fa) {
    dfn[x] = low[x] = ++ T;
    stk[++ stp] = x, instk[x] = 1;
    for (int i = ghead[x]; i; i = ge[i].nxt) {
        if (ge[i].v == fa) continue;
        if (!dfn[x]) {
            tarjan(ge[i].v, x);
            low[x] = min(low[x], low[ge[i].v]);
        } else if (instk[ge[i].v])
          low[x] = min(low[x], dfn[ge[i].v]);
    }
    if (low[x] == dfn[x]) {
        int y; ++ scnt;
        do {
            y = stk[stp ++];
            bel[y] = scnt;
        } while (y != x);
    }
}

void dfs(int x, int fa, int id, int w) {
    for (int i = thead[x]; i; i = te[i].nxt) {
        if (te[i].v == fa) continue;
        vis[te[i].v] = 1, dif[x] += dif[e[i].v];
        dfs(te[i].v, x, te[i].id, te[i].w);
    }
    if (dif[x]) ans[id] = (dif[x] * w < 0 ? 1 : -1);
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(m);
    for (int i = 1; i <= m; ++ i) {
        int u, v; reasd(u), read(v);
        add_edge_g(u, v, 1, i), add_edge_g(v, u, -1, i);
    }
    for (int i = 1; i <= n; ++ i) if (!dfn[i]) tarjan(i, 0);
    for (int i = 1; i <= n; ++ i)
      for (int j = ghead[i]; j; j = ge[j].nxt)
        if (bel[ge[i].v] != bel[i])
          add_edge_t(bel[i], bel[ge[i].v], ge[i].w, ge[i].id);
    read(p);
    for (int i = 1; i <= p; ++ i) {
        int u, v; read(u), read(v);
        ++ dif[bel[u]], -- dif[bel[v]];
    }
    for (int i = 1; i <= scnt; ++ i) if (!vis[i]) dfs(i, 0, 0, 0);
    for (int i = 1; i <= m; ++ i) putchar(ans[i] ? (ans[i] == 1 ? 'R' : 'L') : 'B');
    return 0;
}