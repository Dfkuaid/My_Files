#define LOCAL
#include <bits/stdc++.h>
#define ll long long
#define plli pair <long long, int>
#define mp(a, b) make_pair(a, b)
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 5000010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

struct Magic {int a, b; ll c;} p[N];
struct Edge {int u, v, nxt; ll w;} e[N];

int n, m, v[N], head[N], ecnt(1), a[N];
ll d[N]; int vis[N];

inline void add_edge(int u, int v, int w) {
    e[ecnt].u = u, e[ecnt].v = v, e[ecnt].w = w;
    e[ecnt].nxt = head[u], head[u] = ecnt ++;
}

#define lb(l, len, x) lower_bound(l + 1, l + len + 1, x)

priority_queue <plli > q;

void solve(int s) {
    mset(d, 0x3f); mset(vis, 0);
    d[s] = 0; q.push(mp(0, s));
    while (q.size()) {
        int now = q.top().second; q.pop();
        if (vis[now]) continue; vis[now] = 1;
        for (int i = head[now]; i; i = e[i].nxt)
          if (d[e[i].v] > d[now] + e[i].w) {
              d[e[i].v] = d[now] + e[i].w;
              q.push(mp(-d[e[i].v], e[i].v));
          }
    }
}

int main() {
#ifdef LOCAL
    freopen("T2.in", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(m);
    for (int i = 1; i <= n; ++ i) read(v[i]);
    for (int i = 1; i <= m; ++ i) {
        read(p[i].a), read(p[i].b), read(p[i].c);
        a[i * 2 - 1] = p[i].a, a[i * 2] = p[i].b;
    }
    for (int i = 1; i <= n; ++ i) a[2 * m + i] = v[i];
    a[2 * m + n + 1] = 1; sort(a + 1, a + 2 * m + n + 2);
    int _m = unique(a + 1, a + 2 * m + n + 2) - a - 1;
    for (int i = 1; i <= m; ++ i) {
        int u = lb(a, _m, p[i].a) - a;
        int v = lb(a, _m, p[i].b) - a;
        add_edge(v, u, p[i].c);
    }
    for (int i = 1; i < _m; ++ i)
      add_edge(i, i + 1, a[i + 1] - a[i]);
    solve((lb(a, _m, 1) - a)); ll ans = 0;
    for (int i = 1; i <= n; ++ i) {
        int pos = lb(a, _m, v[i]) - a;
        ans += d[pos];
    }
    printf("%lld ", ans);
    return 0;
}
