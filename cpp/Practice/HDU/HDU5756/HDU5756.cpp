/*采用了标记永久化*/
#define DEBUG
#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 200001;
const int M = 2000010;
const ll INF = 0x3fffffffffffffff;

template <typename T>
inline T Max(const T a, const T b) {return a > b ? a : b;}

template <typename T>
inline T Min(const T a, const T b) {return a < b ? a : b;}

struct Edge {int u, v, nxt;} e[N];
struct Node {
    int ls, rs; ll sum, mn, mx, lz;

    inline Node(int x) {sum = mn = mx = (ll)x; lz = ls = rs = 0;}
    inline Node() {ls = rs = sum = mn = mx = lz = 0;}

    inline void del() {ls = rs = sum = mn = mx = lz = 0;}
} p[M];

struct BAD_NODES {
    int l, r;
    inline bool operator < (const BAD_NODES b) const {return l < b.l;}
} bp[N << 1];

struct Answer {
    ll sum, mn, mx;

    inline Answer() {sum = 0, mn = INF, mx = -INF;}
    inline Answer(ll _sum, ll _mn, ll _mx) {
        sum = _sum, mn = _mn, mx = _mx;
    }

    inline Answer(Node P) {
        sum = P.sum, mn = P.mn, mx = P.mx;
    }
    
    inline void update(Answer b) {
        sum += b.sum, mn = Min(mn, b.mn), mx = Max(mx, b.mx);
    }

    inline Answer addtag(ll x, int l, int r) {
        sum += (r - l + 1) * x, mn += x, mx += x;
        return Answer(sum, mn, mx);
    }
};

int n, q, cnt, rt[N], head[N], ecnt = 1, f[N];
int T, dfn[N], d[N], lx[N], rx[N], id[N]; ll lsta;

inline void clear() {
    for (int i = 1; i <= cnt; ++ i) p[i].del();
    cnt = lsta = T = 0; d[0] = -1; ecnt = 1;
    mset(rt, 0); mset(head, 0);
}

inline int clone(int k) {p[++ cnt] = p[k]; return cnt;}

inline void add_edge(int u, int v) {
    e[ecnt].u = u, e[ecnt].v = v;
    e[ecnt].nxt = head[u], head[u] = ecnt ++;
}

inline void update(int k, int l, int r, ll x) {
    p[k].sum += (r - l + 1) * x;
    p[k].mn += x, p[k].mx += x, p[k].lz += x;
}

inline void pushup(int k, int l, int r) {
    int ls = p[k].ls, rs = p[k].rs;
    p[k].sum = p[ls].sum + p[rs].sum + (r - l + 1) * p[k].lz;
    p[k].mn = Min(p[ls].mn, p[rs].mn) + p[k].lz;
    p[k].mx = Max(p[ls].mx, p[rs].mx) + p[k].lz;
}

void build(int &k, int l, int r) {
    int mid = (l + r) >> 1; if (!k) k = ++ cnt;
    if (l == r) {p[k] = Node(d[id[l]]); return;}
    build(p[k].ls, l, mid);
    build(p[k].rs, mid + 1, r); pushup(k, l, r);
}

int modify(int k, int l, int r, int x, int y, ll c) {
    k = clone(k); int mid = (l + r) >> 1;
    if (x <= l && r <= y) {update(k, l, r, c); return k;}
    if (x <= mid) p[k].ls = modify(p[k].ls, l, mid, x, y, c);
    if (mid < y) p[k].rs = modify(p[k].rs, mid + 1, r, x, y, c);
    pushup(k, l, r);
    return k;
}

Answer query(int k, int l, int r, int x, int y, ll z) {
    if (x <= l && r <= y) return Answer(p[k]).addtag(z, l, r);
    int mid = (l + r) >> 1; Answer res;
    if (x <= mid) res.update(query(p[k].ls, l, mid, x, y, z + p[k].lz));
    if (mid < y) res.update(query(p[k].rs, mid + 1, r, x, y, z + p[k].lz));
    return res;
}

void get_dfn(int x, int fa) {
    dfn[x] = ++ T, lx[x] = T, id[T] = x;
    d[x] = d[fa] + 1, f[x] = fa;
    for (int i = head[x]; i; i = e[i].nxt)
      if (e[i].v != fa) get_dfn(e[i].v, x);
    rx[x] = T;
}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    while (~scanf("%d%d", &n, &q)) {
        clear(); int pt = 0, k = 0, t = 0;
        for (int i = 1; i < n; ++ i) {
            int u, v; scanf("%d%d", &u, &v);
            add_edge(u, v); add_edge(v, u);
        }
        get_dfn(1, 0); build(rt[1], 1, n);
        for (int i = 2; i <= n; ++ i) {
            rt[i] = modify(rt[dfn[f[id[i]]]], 1, n, 1, n, 1);
            rt[i] = modify(rt[i], 1, n, lx[id[i]], rx[id[i]], -2);
        }
        while (q --) {
            scanf("%d%d%d", &k, &pt, &t);
            pt = (pt + lsta) % n + 1;
            int r = 0; Answer res;
            if (k) {
                for (int i = 1; i <= k; ++ i) {
                    int x; scanf("%d", &x);
                    bp[i] = (BAD_NODES){lx[x], rx[x]};
                } sort(bp + 1, bp + k + 1);
                if (bp[1].l == 1) {lsta = 0; printf("-1\n"); continue;}
                for (int i = 1; i <= k; ++ i) {
                    if (bp[i].r <= r) continue;
                    if (bp[i].l == r + 1) {r = bp[i].r; continue;}
                    res.update(query(rt[dfn[pt]], 1, n, r + 1, bp[i].l - 1, 0));
                    r = bp[i].r;
                }
            }
            if (r < n) res.update(query(rt[dfn[pt]], 1, n, r + 1, n, 0));
            if (t == 1) printf("%lld\n", lsta = res.sum);
            else if (t == 2) printf("%lld\n", lsta = res.mn);
            else printf("%lld\n", lsta = res.mx);
        }
    }
    return 0;
}