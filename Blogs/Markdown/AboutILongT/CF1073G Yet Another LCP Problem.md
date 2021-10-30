> 这题从早上调到下午，伴随着 $3$ 杯茶的离去，SA、线段树、st 表各挂了 $2$ 次/kk

## #1.0 题意简述

> Time Limit: 2s | Memory Limit: 256MB

记 $lcp(i,j)$ 表示 $i$ 这个后缀和 $j$ 这个后缀的最长公共前缀长度，

给定一个字符串 $S(|S|\leq2\cdot10^5)$ ，$q(q\leq2\cdot10^5)$ 次询问，每次询问的时候给出两个正整数集合 $A$ 和 $B$，求 $\sum_{i \in A,j \in B}lcp(i,j)$ 的值

保证数据满足 $\sum|A|,\sum|B|\leq2\cdot 10^5$.

## #2.0 大体思路

求后缀之间的 LCP 的和，很容易（~~并不~~）想到使用**后缀数组**来解决问题，于是我们先求出后缀数组及对应的 $height$ 数组。

这里需要提前说明一个将要使用的定理：
$$
LCP(i,j)=\min_{i+1\leq k\leq j}\{height_k\}
$$
于是可以用 st 表 $O(n\log n)$ 预处理，$O(1)$ 查询。

### #2.1 分块

考虑对于集合 $B$ 中的每一个元素向集合 $A$ 统计答案，于是我们把 $A$ 按 $rank$ 排序后，分成 $\sqrt n$ 大小的块，然后再考虑如何对于 $b_i$ 计算对于 $A$  的所有答案。

于是我们对于 $b_i$ 将所有情况分为三种，分别讨论：

1. 当前块左端点的 $rank\leq rank_{b_i}\leq$ 当前块的右端点的 $rank$，如下图

   ![](https://pic.imgdb.cn/item/617cfd412ab3f51d9147bfbc.jpg)

   这种情况暴力扫一遍统计答案即可。

2. $rand_{b_i}<$ 当前块左端点，如下图

   ![](https://pic.imgdb.cn/item/617cfdab2ab3f51d914827c6.jpg)

   根据上面给出的定理，我们可以很容易得到 $b_i$ 与这一段的 LCP 一定是（非严格）递减的， 于是当我们求出 $b_i$ 与左端点的 LCP 为 $x$，然后鹅分最后一个 LCP$\geq x$ 的位置，然后显然这个位置及之前的所有的贡献都是 $x$，剩下的部分可以提前维护出来做后缀和得到。

3. 当前块右端点 $<rand_{b_i}$，与上种情况基本一致。

于是时间复杂度为 $O(n\sqrt n\log\sqrt n)$，很遗憾**不能通过本题**。

### #2.2 线段树

我们尝试对以上分块的做法进行一些优化。上面的方法之所以要分块，是因为要统计 LCP 的前缀和。那么我们尝试动态维护这个东西。

不妨把 $B$ 中的元素也**按 $rank$ 排序**。对于 $B$ 排序后的第 $i$ 个元素，设它与 $A$ 中 $rank$ 小于等于它的元素 $a_j$ 的 LCP 为 $d_{i,j}$ ，那么，根据上文提到的定理，从 $d_i$ 转移到 $d_{i+1}$ 时，只需要把 $d_i$ 中所有大于 $LCP(b_i,b_{i+1})$ 的都改成 $LCP(b_i,b_{i+1})$，再将 $A$ 中所有满足 $rank_{b_i}<rank_{a_j}\leq rank_{b_{i+1}}$ 的元素加入 $d_{i+1}$ 即可；

我们发现以上维护 $d_i$ 的过程，需要支持两个操作：

1. 把所有大于 $k$ 的数改为 $k$ ；
2. 单点修改一个元素。

容易发现，$d_i$ 其实是一个非严格递增的数组（直接考虑 SA 的定义不难证明），于是所有大于 $k$ 的数都会连在一起，可以将其转化为区间覆盖操作；

$b_i$ 的答案就是 $d_i$ 的和，因此还需要支持一个区间求和的操作；

综上，我们发现可以用线段树维护整个 $d_i$ 转移的操作即可。

以上过程统计了 $b_i$ 与 $a_j(rank_{a_j}\leq rank_{b_i})$ 的答案，再反向做一遍，即可类似地统计 $b_i$ 与 $a_j(rank_{a_j}>rank_{b_i})$ 的答案。这两部分的答案相加，就是最终的答案。

时间复杂度为 $O(n\log n)$.

## #3.0 Code

``` cpp
#define ll long long

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

```

