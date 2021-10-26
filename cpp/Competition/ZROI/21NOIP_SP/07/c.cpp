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

template <typename T> inline T Max(T a, T b) {return a > b ? a : b;}

struct Edge {int u, v, nxt;} e[N], te[N];

int n, head[N], ecnt(2), vis[N], endpos, pre[N], spc[N], nxt[N];
int ring[N], rcnt, ve[N], f[N], g[N], ans, pos[N];

inline void add_edge(int u, int v) {
    e[ecnt].u = u, e[ecnt].v = v;
    e[ecnt].nxt = head[u], head[u] = ecnt ++;
}

bool get_ring(int x, int fa) {
    vis[x] = 1;
    for (int i = head[x]; i; i = e[i].nxt) {
        if (e[i].v == fa) continue; pre[e[i].v] = i;
        if (vis[e[i].v]) {endpos = e[i].v; return true;}
        if (get_ring(e[i].v, x)) return true; 
    }
    return false;
}

void get_ring_list() {
    int now = endpos;
    do {
        ring[++ rcnt] = now;
        ve[pre[now]] = ve[pre[now] ^ 1] = 1;
        nxt[e[pre[now]].u] = pre[now] / 2;
        now = e[pre[now]].u;
    } while (now != endpos);
    for (int i = 1; i <= rcnt; ++ i)
      ring[i + rcnt] = ring[i];
}

void dp_on_tree(int x, int fa) {
    g[x] = 0, f[x] = 0;
    for (int i = head[x]; i; i = e[i].nxt) {
        if (e[i].v == fa || ve[i] || ve[i ^ 1]) continue;
        dp_on_tree(e[i].v, x);
        f[x] = Max(f[x], f[e[i].v]);
        f[x] = Max(f[x], g[x] + g[e[i].v] + 1);
        g[x] = Max(g[x], g[e[i].v] + 1);
    }
}

int q1[N], q2[N], frt1 = 0, tal1 = -1, frt2 = 0, tal2 = -1;

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n);
    for (int i = 1; i <= n; ++ i) {
        read(te[i].u), read(te[i].v);
        add_edge(te[i].u, te[i].v);
        add_edge(te[i].v, te[i].u);
    }
    get_ring(1, 0); get_ring_list(); reverse(ring + 1, ring + rcnt * 2 + 1);
    for (int i = 1; i <= rcnt; ++ i) dp_on_tree(ring[i], 0), ans = Max(ans, f[ring[i]]);
    for (int i = 1; i <= rcnt; ++ i) spc[nxt[ring[i]]] = ans;
    for (int i = 1; i <= rcnt; ++ i) {
        while (frt1 <= tal1 && g[ring[q1[tal1]]] - q1[tal1] < g[ring[i]] - i) -- tal1;
        while (frt2 <= tal2 && g[ring[q2[tal2]]] + q2[tal2] < g[ring[i]] + i) -- tal2;
        q1[++ tal1] = i, q2[++ tal2] = i;
    }
    for (int i = rcnt + 1; i <= rcnt << 1; ++ i) {
        while (frt1 <= tal1 && q1[frt1] <= i - rcnt) ++ frt1;
        while (frt2 <= tal2 && q2[frt2] <= q1[frt1]) ++ frt2;
        while (frt2 <= tal2 && g[ring[q2[tal2]]] + q2[tal2] < g[ring[i]] + i) -- tal2; q2[++ tal2] = i;
        spc[nxt[ring[i]]] = Max(spc[nxt[ring[i]]], g[ring[q1[frt1]]] - q1[frt1] + g[ring[q2[frt2]]] + q2[frt2]);
        while (frt1 <= tal1 && g[ring[q1[tal1]]] - q1[tal1] < g[ring[i]] - i) -- tal1; q1[++ tal1] = i;
    }
    for (int i = 1; i <= n; ++ i)
      if (ve[i << 1]) printf("%d\n", spc[i]);
      else printf("-1\n");
     return 0;
}
