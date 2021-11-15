#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 10010;
const int M = 1000010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

struct Edge {int u, v, nxt;} e[M];

int t, n, m, head[N], ecnt(1), ans, bel[N];

bitset <N> G[N], grp[N], adj, tmp;

inline void reset() {
    for (int i = 1; i <= n; ++ i) G[i].reset();
    ecnt = 1, ans = 0; memset(head, 0, sizeof head);
}

inline void add_edge(int u, int v) {
    e[ecnt].u = u, e[ecnt].v = v;
    e[ecnt].nxt = head[u], head[u] = ecnt ++;
}

bool check(int x) {
    int tot = 0; adj.reset();
    for (int i = head[x]; i; i = e[i].nxt) {
        int v = e[i].v; tmp = adj & G[v];
        if (!tmp.any()) {
            grp[++ tot].reset();
            grp[tot][v] = 1, bel[v] = tot;
        } else {
            int p = tmp._Find_first(), now = bel[p];
            if (((~G[v]) & grp[now]).any()) return true;
            if ((G[v] & (adj ^ grp[now])).any()) return true;
            grp[now][v] = 1, bel[v] = now;
        }
        adj[v] = 1;
    }
    return false;
}

void MAIN() {
    read(n), read(m); reset();
    for (int i = 1; i <= m; ++ i) {
        int u, v; read(u), read(v);
        G[u][v] = 1, G[v][u] = 1;
        add_edge(u, v); add_edge(v, u);
    }
    for (int i = 1; i <= n; ++ i) ans |= check(i);
    printf("%s\n", ans ? "YES" : "NO");
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(t); while (t --) MAIN(); return 0;
}
