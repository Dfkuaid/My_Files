#define LOCAL
#include <bits/stdc++.h>
using namespace std;

const int N = 200010;
const int INF = 0x3fffffff;

struct Edge {int u, v, nxt;} e[N];

int n, head[N], ecnt(2), vis[N], siz[N], pos, siz2, rt, ans = INF;

int g(int x) {return x < 0 ? -x : x;}

inline void add_edge(int u, int v) {
    e[ecnt].u = u, e[ecnt].v = v;
    e[ecnt].nxt = head[u], head[u] = ecnt ++;
}

void dfs(int x, int f) {
    siz[x] = 1;
    for (int i = head[x]; i; i = e[i].nxt)
      if (e[i].v != f) {
          dfs(e[i].v, x);
          if (!vis[i]) siz[x] += siz[e[i].v];
          else pos = e[i].v;
      }
    // printf("%d %d\n", x, siz[x]);
}

void divide(int x, int f) {
    // printf("IN: %d  %d %d\n", x, siz[x], siz2);
    for (int i = head[x]; i; i = e[i].nxt) {
        if (e[i].v == f || vis[i]) continue;
        divide(e[i].v, x);
    }
    // printf("%d %d %d\n", x, siz[x], siz2);
    if (g(siz[rt] - 2 * siz[x]) < g(siz[rt] - 2 * siz2))
      siz2 = siz[x];
}

int calc(int a, int b, int c) {
    int mx = max(a, max(b, c));
    int mn = min(a, min(b, c));
    return mx - mn;
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    scanf("%d", &n);
    for (int i = 1; i < n; ++ i) {
        int a, b; scanf("%d%d", &a, &b);
        add_edge(a, b); add_edge(b, a);
    }
    for (int i = 2; i < ecnt; i += 2) {
        vis[i] = 1, vis[i ^ 1] = 1; dfs(1, 0);
        // printf("%d\n", pos);
        if (siz[1] <= siz[pos]) {
            rt = pos, siz2 = 1; divide(pos, 0);
            ans = min(ans, calc(siz[1], siz2, siz[pos] - siz2));
            // printf("c1: %d %d %d %d\n", siz[1], siz2, siz[pos] - siz2, ans);
        } else {
            rt = 1, siz2 = 1; divide(1, 0);
            ans = min(ans, calc(siz[pos], siz2, siz[1] - siz2));
            // printf("c2: %d %d %d %d\n", siz[pos], siz2, siz[1] - siz2, ans);
        }
        vis[i] = 0, vis[i ^ 1] = 0;
    }
    printf("%d", ans); return 0;
}
