#define DEBUG
#include <bits/stdc++.h>
#define ll long long
#define pii pair <int, int>
#define mp(a, b) make_pair(a, b)
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int M = 1000010;
const int N = 20000010;
const int INF = 0x3fffffff;

template <typename T>
inline T Min(const T a, const T b) {return a < b ? a : b;}

struct Node {int ls, rs, fa, dep, mdis;} p[N];
struct Edge {
    int u, v, w, h, nxt;
    inline bool operator < (const Edge b) const {return h > b.h;}
} e[M], ne[M];

int cnt, ecnt(1), head[M], rt[M], n;
int d[M], vis[M], ht[M], lsta, m, T;

inline int clone(int k) {p[++ cnt] = p[k]; return cnt;}

inline void clear() {
    mset(head, 0); mset(rt, 0);
    for (int i = 0; i <= cnt; ++ i)
      p[i].dep = p[i].fa = p[i].ls = p[i].rs = p[i].mdis = 0;
    lsta = 0, cnt = 0, ecnt = 1;
}

inline void add(int u, int v, int w) {
    e[ecnt].u = u, e[ecnt].v = v, e[ecnt].w = w;
    e[ecnt].nxt = head[u], head[u] = ecnt ++;
}

int get_ind(int k, int l, int r, int x) {
    int mid = (l + r) >> 1; if (l == r) return k;
    if (x <= mid) return get_ind(p[k].ls, l, mid, x);
    else return get_ind(p[k].rs, mid + 1, r, x);
}

inline int find(int r, int x) {
    int idx = get_ind(r, 1, n, x);
    while (p[idx].fa != x)
      x = p[idx].fa, idx = get_ind(r, 1, n, x);
    return idx;
}

void build(int &k, int l, int r) {
    if (!k) {k = ++ cnt;}; int mid = (l + r) >> 1;
    if (l == r) {
        p[k].dep = 1, p[k].fa = l;
        p[k].mdis = d[l]; return;
    }
    build(p[k].ls, l, mid); build(p[k].rs, mid + 1, r);
}

int modify(int k, int l, int r, int x, int c, int w) {
    k = clone(k); int mid = (l + r) >> 1;
    if (l == r) {
        p[k].mdis = Min(p[k].mdis, w);
        p[k].dep += c; return k;
    }
    if (x <= mid) p[k].ls = modify(p[k].ls, l, mid, x, c, w);
    else p[k].rs = modify(p[k].rs, mid + 1, r, x, c, w);
    return k;
}

int merge(int k, int l, int r, int x, int y) {
    k = clone(k); int mid = (l + r) >> 1;
    if (l == r) {p[k].fa = y; return k;}
    if (x <= mid) p[k].ls = merge(p[k].ls, l, mid, x, y);
    else p[k].rs = merge(p[k].rs, mid + 1, r, x, y);
    return k;
}

inline void dijkstra(int s) {
    mset(d, 0x3f); mset(vis, 0); d[s] = 0;
    priority_queue <pii> q; q.push(mp(0, s));
    while (q.size()) {
        int now = q.top().second; q.pop();
        if (vis[now]) {continue;} vis[now] = 1;
        for (int i = head[now]; i; i = e[i].nxt)
          if (d[e[i].v] > d[now] + e[i].w) {
              d[e[i].v] = d[now] + e[i].w;
              q.push(mp(-d[e[i].v], e[i].v));
          }
    }
}

inline void connect(int &root, int x, int y) {
    int fx = find(root, x), fy = find(root, y);
    if (fx == fy) return;
    if (p[fx].dep > p[fy].dep) swap(fx, fy);
    root = merge(root, 1, n, p[fx].fa, p[fy].fa);
    int nedad = (p[fx].dep == p[fy].dep);
    root = modify(root, 1, n, p[fy].fa, nedad, p[fx].mdis);
}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    scanf("%d", &T);
    while (T --) {
        scanf("%d%d", &n, &m); clear();
        for (int i = 1; i <= m; ++ i) {
            scanf("%d%d%d%d", &ne[i].u, &ne[i].v, &ne[i].w, &ne[i].h);
            add(ne[i].u, ne[i].v, ne[i].w);
            add(ne[i].v, ne[i].u, ne[i].w);
        }
        sort(ne + 1, ne + m + 1); dijkstra(1);
        int hp = 0, rtp = 1; build(rt[0], 1, n);
        while (rtp <= m) {
            ++ hp; rt[hp] = clone(rt[hp - 1]); ht[hp] = ne[rtp].h;
            while (rtp <= m && ne[rtp].h == ht[hp])
              connect(rt[hp], ne[rtp].u, ne[rtp].v), ++ rtp;
        }
        int q, k, s; scanf("%d%d%d", &q, &k, &s); ht[0] = s + 1;
        while (q --) {
            int v0, p0; scanf("%d%d", &v0, &p0);
            v0 = (v0 + k * lsta - 1) % n + 1;
            p0 = (p0 + k * lsta) % (s + 1);
            int l = 0, r = hp, root = 0;
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (ht[mid] <= p0) r = mid - 1;
                else l = mid + 1, root = mid;
            }
            int fv = find(rt[root], v0);
            printf("%d\n", lsta = p[fv].mdis);
        }
    }
    return 0;
}
