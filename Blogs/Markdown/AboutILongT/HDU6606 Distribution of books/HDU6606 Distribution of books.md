## #1.0 题意简述

给定一个长度为 $n$ 的数列 $\{a_i\}$，可以任意去掉尾部一段连续的数，将剩下数列分为 $k$ 段非空连续子段，问分成的子段中的子段和最大值最小是多少。**多组数据**。

其中数据组数 $1\le T\le 10$，$\sum n\le2\times10^5$，$1\le k\le n$，$-10^9\le a_i\le10^9$.

## #2.0 大致思路

首先看到“最大值最小”立刻想到二分答案，那么现在问题转化为对于 $x$，是否存在一种分法使得最大的子段和小于等于 $x$，再考虑转变一下这个问题，因为尾部可以丢掉任意长度的一段，于是考虑是否存在一种分法得到至少 $k$ 段子段和小于等于 $x$ 的子段。

考虑 DP，设 $f_i$ 表示前 $i$ 个数可以分成的最多的子段个数，不难得到转移方程：
$$
f_i=\max\limits_{0\leq j<i}\{[sum_i-sum_j\leq x]\cdot(f_j+1)\},
$$
其中，$sum_i$ 表示到 $i$ 的前缀和，显然直接处理上面的柿子的时间复杂度是 $O(n^2)$，不能接受，考虑优化，将其中的艾弗森约定简单处理一下得到
$$
f_i=\max\limits_{0\leq j<i\ and\ sum_i-x\leq sum_j}\{f_j+1\},
$$
于是我们可以将 $sum$ 作为下标，进行线段树优化。即将每一个处理得到的 $f_j$ 插入线段树下标为 $sum_j$ 的位置，查询时查询下标大于等于 $sum_i-x$ 的最大值即可，由于 $sum$ 可能很大，而空间限制很紧，于是可以将前缀和数组进行离散化处理。总体时间复杂度为 $O(n\log^2n)$.

## #3.0 Code

``` cpp
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
```

