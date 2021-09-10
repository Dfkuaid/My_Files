#define DEBUG
#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int M = 200010;
const int N = 2000010;
const int INF = 0x3fffffff;

struct Edge {int u, v, nxt;} e[N << 1];
struct DSU {
    int fa[M << 1], dep[M << 1], stk[N << 2][3], stp;

    inline DSU() {stp = 0;}
    inline void init(int n) {
        for (int i = 1; i <= n; ++ i) fa[i] = i, dep[i] = 1;
    }

    inline int find(int x) {
        while (x != fa[x]) x = fa[x]; return x;
    }

    inline void merge(int x, int y) {
        int fx = find(x), fy = find(y);
        if (dep[fx] > dep[fy]) swap(fx, fy);
        stk[++ stp][0] = (dep[fy] == dep[fx]);
        stk[stp][1] = fx; stk[stp][2] = fy;
        dep[fy] += stk[stp][0]; fa[fx] = fy;
    }

    inline void revoke() {
        int x = stk[stp][1], y = stk[stp][2];
        fa[x] = x, dep[y] = dep[y] - stk[stp --][0];
    }
} dsu;

int head[N << 2], rt = 1, cnt = 1, n, m, t, ans[M << 1];

inline void add(int k, int u, int v) {
    e[cnt].u = u, e[cnt].v = v;
    e[cnt].nxt = head[k], head[k] = cnt ++;
}

inline void modify(int k, int l, int r, int x, int y, int u, int v) {
    if (x <= l && r <= y) {add(k, u, v); return;}
    int mid = l + r >> 1;
    if (x <= mid) modify(k << 1, l, mid, x, y, u, v);
    if (mid < y) modify(k << 1 | 1, mid + 1, r, x, y, u, v);
}

void solve(int k, int l, int r) {
    int is_graph = true, top = dsu.stp;
    for (int i = head[k]; i; i = e[i].nxt) {
        int fu = dsu.find(e[i].u);
        int fv = dsu.find(e[i].v);
        if (fu == fv) {
            ++ ans[l], -- ans[r + 1];
            is_graph = false; break;
        }
        dsu.merge(e[i].u, e[i].v + n);
        dsu.merge(e[i].v, e[i].u + n);
    }
    if (is_graph && l != r) {
        int mid = l + r >> 1;
        solve(k << 1, l, mid);
        solve(k << 1 | 1, mid + 1, r);
    }
    while (top < dsu.stp) dsu.revoke();
}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    scanf("%d%d%d", &n, &m, &t);
    for (int i = 1; i <= m; ++ i) {
        int x, y, l, r;
        scanf("%d%d%d%d", &x, &y, &l, &r);
        if (l == r) continue;
        modify(rt, 1, t, l + 1, r, x, y);
    }
    dsu.init(n << 1); solve(rt, 1, t);
    for (int i = 1; i <= n; ++ i) {
        ans[i] += ans[i - 1];
        if (ans[i]) printf("No\n");
        else printf("Yes\n");
    }
    return 0;
}