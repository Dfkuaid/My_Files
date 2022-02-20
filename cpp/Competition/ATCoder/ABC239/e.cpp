#define LOCAL
#include <bits/stdc++.h>
#define ll long long 
using namespace std;

const int N = 1000100;
const int INF = 0x3fffffff;

struct Edge {int u, v, nxt;} e[N << 2];
struct Node {int ls, rs, sum;} p[N << 2];

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int n, m, a[N], cnt, t[N], tot, rt[N], ans[N], val[N];
int head[N], ecnt(1), T, dfn[N], lmt[N][2], q[N], s[N];

inline void add_edge(int u, int v) {
    e[ecnt].u = u, e[ecnt].v = v;
    e[ecnt].nxt = head[u], head[u] = ecnt ++;
}

void dfs(int x, int fa) {
    lmt[x][0] = dfn[x] = ++ T;
    for (int i = head[x]; i; i = e[i].nxt)
      if (e[i].v != fa) dfs(e[i].v, x);
    lmt[x][1] = T;
}

inline void pushup(int k) {
    p[k].sum = p[p[k].ls].sum + p[p[k].rs].sum;
}

void build(int &k, int l, int r) {
    if (!k) k = ++ cnt;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(p[k].ls, l, mid);
    build(p[k].rs, mid + 1, r);
}

void modify(int lt, int &k, int l, int r, int x) {
    if (!k) k = ++ cnt;
    p[k].sum = p[lt].sum + 1;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (x <= mid) {
        p[k].rs = p[lt].rs;
        modify(p[lt].ls, p[k].ls, l, mid, x);
    } else {
        p[k].ls = p[lt].ls;
        modify(p[lt].rs, p[k].rs, mid + 1, r, x);
    }
}

int query(int lt, int k, int l, int r, int x) {
    if (l == r) return l;
    int mid = (l + r) >> 1;
    int sum_l = p[p[k].ls].sum - p[p[lt].ls].sum;
    if (sum_l >= x) return query(p[lt].ls, p[k].ls, l, mid, x);
    else return query(p[lt].rs, p[k].rs, mid + 1, r, x - sum_l);
}

inline bool cmp(int x, int y) {return dfn[x] < dfn[y];}

#define lb(l, len, x) lower_bound(l + 1, l + len + 1, x)

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i) read(val[i]), s[i] = val[i];
    for (int i = 1, u, v; i < n; ++ i)
      read(u), read(v), add_edge(u, v), add_edge(v, u);
    for (int i = 1; i <= n; ++ i) q[i] = i;
    sort(s + 1, s + n + 1); tot = unique(s + 1, s + n + 1) - s - 1;
    for (int i = 1; i <= n; ++ i) val[i] = lb(s, tot, val[i]) - s;
    dfs(1, 0); sort(q + 1, q + n + 1, cmp); build(rt[0], 1, tot);
    for (int i = 1; i <= n; ++ i)
      modify(rt[i - 1], rt[i], 1, tot, val[q[i]]);
    while (m --) {
        int x = 0, y = 0; read(x), read(y); y = lmt[x][1] - lmt[x][0] + 1 - y + 1;
        printf("%d\n", s[query(rt[lmt[x][0] - 1], rt[lmt[x][1]], 1, tot, y)]);
    }
    return 0;
}
