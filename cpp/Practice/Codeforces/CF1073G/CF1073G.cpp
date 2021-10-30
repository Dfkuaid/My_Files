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

struct Node {
    int ls, rs; ll sum; int mn, mx, cov;

    inline Node() {ls = rs = sum = mn = mx = 0, cov = -1;}
    inline void reset() {ls = rs = sum = mn = mx = 0, cov = -1;}
};

struct SegmentTree {
    Node p[N << 1]; int rt, cnt;
    
    inline SegmentTree() {rt = cnt = 0;}
    inline void reset() {while (cnt) p[cnt].reset(), -- cnt; rt = 0;}
    
    inline void cover(int k, int l, int r, int x) {
        p[k].cov = x; p[k].mn = p[k].mx = x;
        p[k].sum = 1ll * (r - l + 1) * x;
    }
    
    inline void pushup(int k) {
        int ls = p[k].ls, rs = p[k].rs;
        p[k].sum = p[ls].sum + p[rs].sum;
        p[k].mn = Min(p[ls].mn, p[rs].mn);
        p[k].mx = Max(p[ls].mx, p[rs].mx);
    }

    inline void pushdown(int k, int l, int r) {
        int ls = p[k].ls, rs = p[k].rs;
        if (~p[k].cov) {
            int mid = l + r >> 1;
            if (ls) cover(ls, l, mid, p[k].cov);
            if (rs) cover(rs, mid + 1, r, p[k].cov);
            p[k].cov = -1;
        }
    }

    void build(int &k, int l, int r) {
        if (!k) k = ++ cnt; if (l == r) return; int mid = l + r >> 1;
        build(p[k].ls, l, mid); build(p[k].rs, mid + 1, r);
    }

    void modify(int k, int l, int r, int x, int c) {
        if (l == r) {cover(k, l, r, c); return;}
        int mid = l + r >> 1; pushdown(k, l, r);
        if (x <= mid) modify(p[k].ls, l, mid, x, c);
        else modify(p[k].rs, mid + 1, r, x, c);
        pushup(k);
    }

    void recover(int k, int l, int r, int x) {
        if (p[k].mx < x) return; if (p[k].mn >= x) {cover(k, l, r, x); return;}
        int mid = l + r >> 1; pushdown(k, l, r);
        recover(p[k].ls, l, mid, x); recover(p[k].rs, mid + 1, r, x); pushup(k);
    }
} seg;

char s[N];
int sa[N], rk[N], oldrk[N], px[N], id[N], cnt[N], n;

bool comp(int x, int y, int w) {
    return oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w];
}

inline void build_sa(int m) {
    int i, p, w;
    for (i = 1; i <= n; ++ i) ++ cnt[rk[i] = s[i]];
    for (i = 1; i <= m; ++ i) cnt[i] += cnt[i - 1];
    for (i = n; i >= 1; -- i) sa[cnt[rk[i]] --] = i;
    for (w = 1;; w <<= 1, m = p) {
        for (p = 0, i = n; i > n - w; --i) id[++ p] = i;
        for (i = 1; i <= n; ++ i) if (sa[i] > w) id[++ p] = sa[i] - w;
        memset(cnt, 0, sizeof(cnt));
        for (i = 1; i <= n; ++ i) ++ cnt[px[i] = rk[id[i]]];
        for (i = 1; i <= m; ++ i) cnt[i] += cnt[i - 1];
        for (i = n; i >= 1; -- i) sa[cnt[px[i]] --] = id[i];
        memcpy(oldrk, rk, sizeof(rk));
        for (p = 0, i = 1; i <= n; ++ i)
          rk[sa[i]] = comp(sa[i], sa[i - 1], w) ? p : ++ p;
        if (p == n) {for (int i = 1; i <= n; ++ i) sa[rk[i]] = i; break;}
    }
}

int ht[N], h[30][N], lg[N];

inline void get_rk_height() {
    for (int i = 1, k = 0; i <= n; ++ i) {
        if (rk[i] == 1) {ht[rk[i]] = k = 0; continue;}
        if (k) k --; assert(rk[i]);
        while (s[i + k] == s[sa[rk[i] - 1] + k]) ++ k;
        ht[rk[i]] = k;
    }
    for (int i = 1; i <= n; ++ i) lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i <= n; ++ i) h[0][i] = ht[i];
    for (int i = 1; i <= lg[n]; ++ i) 
      for (int j = 1; j + (1 << i) - 1 <= n; ++ j)
        h[i][j] = Min(h[i - 1][j], h[i - 1][j + (1 << i - 1)]);
}

int q, a[N], b[N];

inline bool cmp(int x, int y) {return rk[x] < rk[y];}

inline int query(int l, int r) {
    int k = lg[r - l + 1];
    return Min(h[k][l], h[k][r - (1 << k) + 1]);
}

inline int lcp(int x, int y) {
    if (x == y) return n - x + 1;
    if (rk[x] > rk[y]) swap(x, y);
    return query(rk[x] + 1, rk[y]);
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n); read(q); scanf("%s", s + 1); lg[0] = -1;
    build_sa(256); get_rk_height();
    while (q --) {
        int k, l; ll ans  = 0; read(k), read(l);
        for (int i = 1; i <= k; ++ i) read(a[i]);
        for (int i = 1; i <= l; ++ i) read(b[i]);
        sort(a + 1, a + k + 1, cmp);
        sort(b + 1, b + l + 1, cmp);
        seg.reset(); seg.build(seg.rt, 1, k);
        for (int i = 1, j = 1; i <= l; ++ i) {
            seg.recover(seg.rt, 1, k, lcp(b[i], b[i - 1])); 
            while (j <= k && rk[a[j]] <= rk[b[i]])
              seg.modify(seg.rt, 1, k, j, lcp(b[i], a[j])), ++ j;
            ans += seg.p[seg.rt].sum;
        }
        seg.reset(); seg.build(seg.rt, 1, k);
        for (int i = l, j = k; i >= 1; -- i) {
            seg.recover(seg.rt, 1, k, lcp(b[i], b[i + 1]));
            while (j >= 1 && rk[a[j]] > rk[b[i]])
              seg.modify(seg.rt, 1, k, j, lcp(b[i], a[j])), j --;
            ans += seg.p[seg.rt].sum;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
