#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 400010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T Max(T a, T b) {return a > b ? a : b;}
template <typename T> inline T Min(T a, T b) {return a < b ? a : b;}

struct Edge {int u, v, nxt;} ge[N], te[N];
struct Node {int ls, rs, val;};
struct SegmentTree {
    Node p[N]; int cnt, rt;

    inline SegmentTree() {rt = cnt = 0;}
    inline void pushup(int k) {
        p[k].val = Min(p[p[k].ls].val, p[p[k].rs].val);
    }

    void insert(int &k, int l, int r, int x, int c) {
        if (!k) k = ++ cnt; int mid = l + r >> 1;
        if (l == r) {p[k].val = c; return;}
        if (x <= mid) insert(p[k].ls, l, mid, x, c);
        else insert(p[k].rs, mid + 1, r, x, c);
        pushup(k);
    }

    int query(int k, int l, int r, int x, int y) {
        if (!k) return INF; if (x <= l && r <= y) return p[k].val;
        int mid = l + r >> 1, res = INF;
        if (x <= mid) res = Min(res, query(p[k].ls, l, mid, x, y));
        if (mid < y) res = Min(res, query(p[k].rs, mid + 1, r, x, y));
        return res;
    }
} t;

int gecnt(1), tecnt(1), ghead[N], thead[N], n, m, q, w[N];
int bel[N], low[N], dfn[N], top[N], id[N], bcnt, T, stk[N], stp;
int f[N], siz[N], d[N], rk[N], son[N];

multiset <int> s[N];

inline void add_edge_g(int u, int v) {
    ge[gecnt].u = u, ge[gecnt].v = v;
    ge[gecnt].nxt = ghead[u], ghead[u] = gecnt ++;
}

inline void add_edge_t(int u, int v) {
    te[tecnt].u = u, te[tecnt].v = v;
    te[tecnt].nxt = thead[u], thead[u] = tecnt ++;
}

void biconnect(int x) {
    dfn[x] = low[x] = ++ T; stk[++ stp] = x;
    for (int i = ghead[x]; i; i = ge[i].nxt)
      if (!dfn[ge[i].v]) {
          biconnect(ge[i].v);
          low[x] = Min(low[x], low[ge[i].v]);
          if (low[ge[i].v] == dfn[x]) {
              int y; ++ bcnt;
              do {
                  y = stk[stp --];
                  bel[y] = bcnt;
                  add_edge_t(bcnt, y);
                  s[bcnt].insert(w[y]);
              } while (y != ge[i].v);
              add_edge_t(x, bcnt);
          }
      } else low[x] = Min(low[x], dfn[ge[i].v]);
}

void dfs1(int x, int fa, int dep) {
    f[x] = fa, siz[x] = 1, d[x] = dep;
    for (int i = thead[x]; i; i = te[i].nxt) {
        if (te[i].v == fa) continue;
        dfs1(te[i].v, x, dep + 1);
        siz[x] += siz[te[i].v];
        if (siz[te[i].v] > siz[son[x]])
          son[x] = te[i].v;
    }
}

void dfs2(int x, int t) {
    top[x] = t; id[x] = ++ T, rk[T] = x;
    if (!son[x]) return; else dfs2(son[x], t);
    for (int i = thead[x]; i; i = te[i].nxt)
      if (te[i].v != f[x] && te[i].v != son[x])
        dfs2(te[i].v, te[i].v);
}

void modify(int x, int c) {
    t.insert(t.rt, 1, bcnt, id[x], c);
    if (bel[x]) {
        s[bel[x]].erase(s[bel[x]].find(w[x]));
        s[bel[x]].insert(c);
        t.insert(t.rt, 1, bcnt, id[bel[x]], *s[bel[x]].begin());
    }
    w[x] = c;
}

int query(int x, int y) {
    int res = INF;
    while (top[x] != top[y]) {
        if (d[top[x]] < d[top[y]]) swap(x, y);
        res = Min(res, t.query(t.rt, 1, bcnt, id[top[x]], id[x]));
        x = f[top[x]];
    }
    if (id[x] < id[y]) swap(x, y);
    res = Min(res, t.query(t.rt, 1, bcnt, id[y], id[x]));
    if (y > n) res = Min(res, w[f[y]]); return res;
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(m), read(q);
    for (int i = 1; i <= n; ++ i) read(w[i]);
    for (int i = 1; i <= m; ++ i) {
        int u, v; read(u), read(v);
        add_edge_g(u, v); add_edge_g(v, u);
    }
    bcnt = n; biconnect(1);
    T = 0; dfs1(1, 0, 1); dfs2(1, 1);
    for (int i = 1; i <= n; ++ i)
      t.insert(t.rt, 1, bcnt, id[i], w[i]);
    for (int i = n + 1; i <= bcnt; ++ i)
      t.insert(t.rt, 1, bcnt, id[i], *s[i].begin());
    while (q --) {
        char opt; int x, y;
        cin >> opt; read(x), read(y);
        if (opt == 'C') modify(x, y);
        else printf("%d\n", query(x, y));
    }
    return 0;
}
