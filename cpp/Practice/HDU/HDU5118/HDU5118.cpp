#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 100010;
const int M = 100000010;
const int LIMIT = 1e8;

struct Edge {
    int u, v, w;
    Edge (int _u, int _v, int _w) {u = _u, v = _v, w = _w;}
    inline bool operator < (const Edge x) const {return w < x.w;}
};

vector<Edge> G[N];

int s[N], n, m, q, sum, ans[M];
int tot[N], fv[N], fvd[N];

inline void add_edge(int u, int v, int w) {G[u].push_back(Edge(u, v, w));}

void dfs(int u, int dep) {
    if (sum >= LIMIT) return;
    if (~tot[u]) {
        for (int i = 1; i <= tot[u]; ++ i) {
            if (sum >= LIMIT) return;
            ans[++ sum] = ans[fv[u] + i] + dep - fvd[u];
        } return;
    }
    fv[u] = sum, fvd[u] = dep;
    if (s[u]) ans[++ sum] = dep;
    for (unsigned int i = 0; i < G[u].size(); ++ i)
      dfs(G[u][i].v, dep + 1);
    tot[u] = sum - fv[u];
}

int main() {
    int T; scanf("%d", &T);
    for (int t = 1; t <= T; ++ t) {
        scanf("%d%d%d", &n, &m, &q); s[1] = sum = 0;
        for (int i = 1; i <= n; ++ i) G[i].clear();
        for (int i = 2; i <= n; ++ i) scanf("%d", &s[i]);
        for (int i = 1; i <= m; ++ i) {
            int u, v, w; scanf("%d%d%d", &u, &v, &w);
            add_edge(u, v, w);
        }
        for (int i = 1; i <= n; ++ i)
          sort(G[i].begin(), G[i].end());
        mset(tot, -1); dfs(1,0);
        printf("Case #%d:\n", t);
        for (int i = 1; i <= q; ++ i) {
            int x; scanf("%d", &x);
            if (x <= sum) printf("%d\n", ans[x]);
            else printf("-1\n");
        }
    }
    return 0;
}