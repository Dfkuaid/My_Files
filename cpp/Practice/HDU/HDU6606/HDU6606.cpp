#define DEBUG
#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 200010;
const int M = 2000010;
const ll INF = 0x3f3f3f3f3f3f;

template <typename T>
inline T Min(const T a, const T b) {return a < b ? a : b;}

template <typename T>
inline T Max(const T a, const T b) {return a > b ? a : b;}

struct Node {
    int ls, rs, mx;
    inline Node() {ls = rs = mx = 0;}
    inline void del() {ls = rs = mx = 0;}
};

struct SegmentTree {
    Node p[M]; int cnt, rt;
    
    inline SegmentTree() {cnt = rt = 0;}
    inline void reset() {
        while (cnt) p[cnt --].del();
        cnt = rt = 0;
    }

    inline void pushup(int k) {
        p[k].mx = Max(p[p[k].ls].mx, p[p[k].rs].mx);
    }

    void insert(int &k, int l, int r, int pos, int x) {
        int mid = (l + r) >> 1; if (!k) k = ++ cnt;
        if (l == r) {p[k].mx = Max(p[k].mx, x); return;}
        if (pos <= mid) insert(p[k].ls, l, mid, pos, x);
        else insert(p[k].rs, mid + 1, r, pos, x);
        pushup(k);
    }
    
    int query(int k, int l, int r, int x, int y) {
        if (!k) return -1;
        if (x <= l && r <= y) return p[k].mx;
        int mid = (l + r) >> 1, res = -1;
        if (x <= mid) res = Max(res, query(p[k].ls, l, mid, x, y));
        if (mid < y) res = Max(res, query(p[k].rs, mid + 1, r, x, y));
        return res;
    }
} t;

int T, n, k, f[N], zero_pos, dcnt;
ll mint, maxt, s[N], dis[N];

inline int get_pos(ll x) {
    return lower_bound(dis + 1, dis + dcnt + 1, x) - dis;
}

bool check(ll x) {
    mset(f, -1); t.reset(); int res = 0;
    t.insert(t.rt, 1, dcnt, zero_pos, 0);
    for (int i = 1; i <= n; ++ i) {
        int pos1 = get_pos(s[i] - x), pos2 = get_pos(s[i]);
        if (pos1 > dcnt) continue;
        f[i] = t.query(t.rt, 1, dcnt, pos1, dcnt) + 1;
        if (f[i] >= k) return true;
        if (f[i] > 0) t.insert(t.rt, 1, dcnt, pos2, f[i]);
    }
    return false;
}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    scanf("%d", &T);
    while (T --) {
        scanf("%d%d", &n, &k); dcnt = 0;
        for (int i = 1; i <= n; ++ i) {
            scanf("%lld", &s[i]);
            s[i] = s[i - 1] + s[i];
            dis[++ dcnt] = s[i];
        }
        dis[++ dcnt] = 0; sort(dis + 1, dis + dcnt + 1);
        dcnt = unique(dis + 1, dis + dcnt + 1) - dis - 1;
        zero_pos = get_pos(0);
        ll l = -INF, r = INF, ans = 0;
        while (l <= r) {
            ll mid = (l + r) >> 1;
            if (check(mid))
              ans = mid, r = mid - 1;
            else l = mid + 1;
        }
        printf("%lld\n", ans);
    }
    return 0;
}