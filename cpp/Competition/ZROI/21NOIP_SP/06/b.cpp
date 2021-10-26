#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 2000010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

struct Edge {int u, v, nxt;} e[N];

int n, head[N], ecnt(1), vis[N], col[N];

inline void add_edge(int u, int v) {
    e[ecnt].u = u, e[ecnt].v = v;
    e[ecnt].nxt = head[u], head[u] = ecnt ++;
}

void mark(int x, int c) {
    col[x] = c, vis[x] = 1;
    for (int i = head[x]; i; i = e[i].nxt)
      if (!vis[e[i].v]) mark(e[i].v, c ^ 1);
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n);
    for (int i = 1; i <= n; ++ i) {
        int u, v; read(u), read(v);
        add_edge(u, v); add_edge(v, u);
    }
    for (int i = 1; i <= n; ++ i) {
        add_edge((i << 1) - 1, i << 1);
        add_edge(i << 1, (i << 1) - 1);
    }
    for (int i = 1; i <= n << 1; ++ i)
      if (!vis[i]) mark(i, 0);
    for (int i = 1; i <= n << 1; ++ i)
      if (col[i]) putchar('X'); else putchar('Y');
    return 0;
}
