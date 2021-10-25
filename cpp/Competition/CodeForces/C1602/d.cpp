#define LOCAL
#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 2000010;
const int INF = 0x3f3f3f3f;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

struct Node {int ls, rs;} p[N];
struct Edge {int u, v, w, nxt;} e[N << 2];

int n, a[N], b[N], head[N], ecnt(1), cnt;
int npos[N], id[N], rk[N], endpos, rt;

inline void add_edge(int u, int v, int w) {
    e[ecnt].u = u, e[ecnt].v = v, e[ecnt].w = w;
    e[ecnt].nxt = head[u], head[u] = ecnt ++;
}

void build(int &k, int l, int r) {
    if (!k) k = ++ cnt;
    if (l == r) {
        id[l] = cnt; rk[cnt] = l;
        if (!l) endpos = cnt; return;
    }
    int mid = l + r >> 1;
    build(p[k].ls, l, mid);
    build(p[k].rs, mid + 1, r);
    add_edge(k, p[k].ls, 0);
    add_edge(k, p[k].rs, 0);
}

void connect(int k, int l, int r, int x, int y, int c) {
    if (x <= l && r <= y) {add_edge(c, k, 1); return;}
    int mid = l + r >> 1;
    if (x <= mid) connect(p[k].ls, l, mid, x, y, c);
    if (mid < y) connect(p[k].rs, mid + 1, r, x, y, c);
}

void mapping() {
    for (int i = 1; i <= n; ++ i) npos[i] = ++ cnt;
    for (int i = 1; i <= n; ++ i) add_edge(id[i], npos[i + b[i]], 0);
    for (int i = 1; i <= n; ++ i) connect(rt, 0, n, i - a[i], i, npos[i]);
}

deque <int> q; int d[N], vis[N], pre[N];

inline void shortest_path(int u) {
    mset(d, 0x3f); mset(vis, 0);
    d[u] = 0; q.push_back(u);
    while (q.size()) {
        int x = q.front(); q.pop_front();
        if (vis[x]) continue; vis[x] = 1;
        for (int i = head[x]; i; i = e[i].nxt)
          if (d[e[i].v] > d[x] + e[i].w) {
              d[e[i].v] = d[x] + e[i].w;
              pre[e[i].v] = i;
              if (e[i].w) q.push_back(e[i].v);
              else q.push_front(e[i].v);
          }
    }
}

int ans[N], acnt;

inline void print() {
    if (d[id[0]] >= INF) {puts("-1"); return;}
    printf("%d\n", d[id[0]]); int now = id[0];
    while (now) {
        ans[++ acnt] = pre[now];
        now = e[pre[now]].u;
    }
    reverse(ans + 1, ans + acnt + 1);
    for (int i = 1; i <= acnt; ++ i)
      if (rk[e[ans[i]].v] || e[ans[i]].v == endpos)
        printf("%d ", rk[e[ans[i]].v]);
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n); build(rt, 0, n);
    for (int i = 1; i <= n; ++ i) read(a[i]);
    for (int i = 1; i <= n; ++ i) read(b[i]);
    mapping(); shortest_path(id[n]); print(); return 0;
}
