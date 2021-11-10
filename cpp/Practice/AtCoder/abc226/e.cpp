#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 500010;
const int MOD = 998244353;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

struct Edge {int u, v, nxt;} e[N];

int ecnt(1), head[N], d[N], n, m, vis[N], p_num, e_num, ans;

inline void add_edge(int u, int v) {
    e[ecnt].u = u, e[ecnt].v = v, ++ d[u];
    e[ecnt].nxt = head[u], head[u] = ecnt ++;
}

void dfs(int x) {
    vis[x] = 1; e_num += d[x]; ++ p_num;
    for (int i = head[x]; i; i = e[i].nxt)
      if (!vis[e[i].v]) dfs(e[i].v);
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(m); ans = 1;
    for (int i = 1; i <= m; ++ i) {
        int u, v; read(u), read(v);
        add_edge(u, v), add_edge(v, u);
    }
    for (int i = 1; i <= n; ++ i) if (!vis[i]) {
        p_num = 0, e_num = 0; dfs(i);
        if (e_num == (p_num << 1)) (ans *= 2) %= MOD;
        else {ans = 0; break;}
    }
    printf("%d", ans); return 0;
}
