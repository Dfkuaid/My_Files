#define LOCAL
#include <bits/stdc++.h>
#define ll long long
#define plli pair <long long, int>
#define mp(a, b) make_pair(a, b)
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 1000010;
const int M = 2000010;
const ll INF = 1e17;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T Max(T a, T b) {return a > b ? a : b;}
template <typename T> inline T Min(T a, T b) {return a < b ? a : b;}

struct Edge {int u, v, nxt, tag; ll w, val;} e[M << 1], et[M << 1];

int n, m, head[N], ecnt(2), ect2(1);

inline void add_edge(int u, int v, ll w) {
    e[ecnt].u = u, e[ecnt].v = v, e[ecnt].w = w;
    e[ecnt].nxt = head[u], head[u] = ecnt ++;
}

priority_queue <plli > q;

int vis[N]; ll dis[N];

void dijkstra(int u) {
    mset(vis, 0); mset(dis, 0x3f);
    dis[u] = 0; q.push(mp(0, u));
    while (q.size()) {
        int x = q.top().second; q.pop();
        if (vis[x]) continue; vis[x] = true;
        for (int i = head[x]; i; i = e[i].nxt)
          if (dis[e[i].v] > dis[x] + e[i].w) {
              dis[e[i].v] = dis[x] + e[i].w;
              q.push(mp(-dis[e[i].v], e[i].v));
          }
    }
}

int fath[N], dep[N], fa[N]; ll val[N], f[N];

inline int find(int x) {while (x != fa[x]) x = fa[x] = fa[fa[x]]; return x;}

void get_info(int x, int father) {
    fath[x] = father, dep[x] = dep[father] + 1, vis[x] = 1;
    for (int i = head[x]; i; i = e[i].nxt) {
        if (vis[e[i].v] || dis[e[i].v] != dis[x] + e[i].w) continue;
        e[i].tag = 1; get_info(e[i].v, x);
    }
}

inline ll calc(int k) {return dis[e[k].u] + dis[e[k].v] + e[k].w;}

void mark(int k) {
    int u = et[k].u, v = et[k].v; ll w = et[k].val;
    if (!dep[u] || !dep[v]) return;
    u = find(u), v = find(v);
    while (u != v) {
        if (dep[u] < dep[v]) swap(u, v);
        val[u] = w, fa[u] = fath[u]; u = find(u);
    }
}

void get_ans(int u) {
    while (q.size()) q.pop();
    mset(vis, 0); mset(f, 0x3f);
    f[u] = 0; q.push(mp(0, u));
    while (q.size()) {
        int x = q.top().second; q.pop();
        if (vis[x]) continue; vis[x] = true;
        for (int i = head[x]; i; i = e[i].nxt) if (!vis[e[i].v])
          if (f[e[i].v] > Max(val[e[i].v], f[x] + e[i].w)) {
              f[e[i].v] = Max(val[e[i].v], f[x] + e[i].w);
              q.push(mp(-f[e[i].v], e[i].v));
          }
    }
}

signed main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int st; read(n), read(m), read(st);
    for (int i = 1; i <= m; ++ i) {
        int u, v; ll w; read(u), read(v), read(w);
        add_edge(u, v, w), add_edge(v, u, w);
    }
    dijkstra(st); mset(vis, 0); get_info(st, 0);
    for (int i = 2; i < ecnt; i += 2) {
        if (e[i].tag || e[i ^ 1].tag) continue;
        et[ect2] = e[i]; et[ect2 ++].val = calc(i);
    }
    auto cmp = [](Edge x, Edge y){return x.val < y.val;};
    sort(et + 1, et + ect2, cmp); mset(val, 0x3f); 
    for (int i = 1; i <= n; ++ i) fa[i] = i;
    for (int i = 1; i < ect2; ++ i) mark(i);
    for (int i = 1; i <= n; ++ i) val[i] -= dis[i];
    get_ans(st);
    for (int i = 1; i <= n; ++ i)
      printf("%lld ", f[i] > INF / 10 ? -1 : f[i]);
    return 0;
}
