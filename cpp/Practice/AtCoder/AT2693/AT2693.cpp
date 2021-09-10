#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

struct Edge {int u, v, nxt; ll w;} e[N << 1];

ll n, q, k, cnt(1), head[N], lg2[N], d[N];

inline void add(int u, int v, ll w) {
    e[cnt].u = u, e[cnt].v = v, e[cnt].w = w;
    e[cnt].nxt = head[u], head[u] = cnt ++;
}

void dfs(int x, int fa) {
    for (int i = head[x]; i; i = e[i].nxt)
      if (e[i].v != fa) {
          d[e[i].v] = d[x] + e[i].w;
          dfs(e[i].v, x);
      }
}

int main() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++ i)
      lg2[i] = lg2[i >> 1] + 1;
    for (int i = 1; i < n; ++ i) {
        int u, v; ll w; scanf("%d%d%lld", &u, &v, &w);
        add(u, v, w); add(v, u, w);
    }
    scanf("%lld%lld", &q, &k); dfs(k, 0);
    while (q --) {
        int a, b; scanf("%d%d", &a, &b);
        printf("%lld\n", d[a] + d[b]);
    }
    return 0;
}