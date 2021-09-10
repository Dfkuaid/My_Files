#define DEBUG
#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int M = 40010;
const int N = 20000010;
const int INF = 0x3fffffff;

template <typename T>
inline T Max(const T a, const T b) {return a > b ? a : b;}

template <typename T>
inline T Min(const T a, const T b) {return a < b ? a : b;}

struct Node {int ls, rs, mx, mn, tag;} p[N];

int a[M], tx[M], lst, ql[4];
int n, cnt, rt[M], id[M], tp = 1, q;

inline bool cmp(const int x, const int y) {return tx[x] < tx[y];}

inline int clone(int k) {p[++ cnt] = p[k]; return cnt;} 

inline void pushup(int k) {
    p[k].mx = Max(p[p[k].ls].mx, p[p[k].rs].mx);
    p[k].mn = Min(p[p[k].ls].mn, p[p[k].rs].mn);
}

inline void add(int k, int x) {
    p[k].mn += x, p[k].mx += x, p[k].tag += x;
}

inline void pushdown(int k) {
    if (p[k].tag) {
        if (p[k].ls) p[k].ls = clone(p[k].ls); add(p[k].ls, p[k].tag);
        if (p[k].rs) p[k].rs = clone(p[k].rs); add(p[k].rs, p[k].tag);
        p[k].tag = 0;
    }
}

void build(int &k, int l, int r) {
    if (!k) {k = ++ cnt;} int mid = l + r >> 1;
    if (l == r) {p[k].mn = p[k].mx = l; return;}
    build(p[k].ls, l, mid);
    build(p[k].rs, mid + 1, r); pushup(k);
}

int modify(int k, int l, int r, int x, int y, int c) {
    k = clone(k);
    if (x <= l && r <= y) {add(k, c); return k;}
    int mid = l + r >> 1; pushdown(k);
    if (x <= mid) p[k].ls = modify(p[k].ls, l, mid, x, y, c);
    if (mid < y) p[k].rs = modify(p[k].rs, mid + 1, r, x, y, c);
    pushup(k); return k;
}

int query_min(int k, int l, int r, int x, int y) {
    if (x <= l && r <= y) return p[k].mn;
    int mid = l + r >> 1, res = INF; pushdown(k);
    if (x <= mid) res = Min(res, query_min(p[k].ls, l, mid, x, y));
    if (mid < y) res = Min(res, query_min(p[k].rs, mid + 1, r, x, y));
    return res;
}

int query_max(int k, int l, int r, int x, int y) {
    if (x <= l && r <= y) return p[k].mx;
    int mid = l + r >> 1, res = -INF; pushdown(k);
    if (x <= mid) res = Max(res, query_max(p[k].ls, l, mid, x, y));
    if (mid < y) res = Max(res, query_max(p[k].rs, mid + 1, r, x, y));
    return res;
}

inline bool check(int x, int i, int j, int k, int l) {
    int res1 = query_min(rt[x], 0, n, i - 1, j - 1);
    int res2 = query_max(rt[x], 0, n, k, l);
    return res2 >= res1;
}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) scanf("%d", &a[i]), tx[i] = a[i];
    sort(a + 1, a + n + 1); int _n = unique(a + 1, a + n + 1) - a - 1;
    for (int i = 1; i <= n; ++ i)
      tx[i] = lower_bound(a + 1, a + _n + 1, tx[i]) - a;
    for (int i = 1; i <= n; ++ i) id[i] = i;
    sort(id + 1, id + n + 1, cmp); build(rt[0], 0, n);
    for (int i = 1; i <= n; ++ i)  {
        rt[i] = clone(rt[i - 1]);
        while (tp <= n && tx[id[tp]] < i)
          rt[i] = modify(rt[i], 0, n, id[tp ++], n, -2);
    }
    scanf("%d", &q);
    while (q --) {
        scanf("%d%d%d%d", &ql[0], &ql[1], &ql[2], &ql[3]);
        ql[0] = (ql[0] + lst) % (ll)n, ql[1] = (ql[1] + lst) % (ll)n;
        ql[2] = (ql[2] + lst) % (ll)n, ql[3] = (ql[3] + lst) % (ll)n;
        ++ ql[0], ++ ql[1], ++ ql[2], ++ ql[3];
        sort(ql, ql + 4);
        int L = 1, R = n, ans = 0;
        while (L <= R) {
            int mid = L + R >> 1;
            if (check(mid, ql[0], ql[1], ql[2], ql[3])) {
                ans = mid, L = mid + 1;
            } else R = mid - 1;
        }
        printf("%lld\n", lst = a[ans]);
    }
    return 0;
}