> [题目链接](https://acm.hdu.edu.cn/showproblem.php?pid=6315)

## #1.0 题意简述

给定两个数列 $\{a_i\}$ 和 $\{b_i\}$，其中 $\{a_i\}$ 初始全为 $0$，有如下操作：

- 给 $a_i(i\in[l,r])$ 加上 $1$；
- 求 $\sum_{i=l}^r\left\lfloor\frac{a_i}{b_i}\right\rfloor$；

**多组数据**。

## #2.0 大致思路

注意到每给 $a_i$ 加 $b_i$ 次答案才会增加一，而对于一个区间，当且仅当该区间内存在一个数被加了 $b_i$ 的倍数次才会对区间的答案作出贡献，于是可以直接记录当前区间内的区间加标记和至少还要加多少次才会更新，当次数变为 $0$ 时，递归地进行更新即可。

~~时间复杂度为 $O(能过)$。~~，考虑最多只会对答案造成 $O(n\log n)$ 级别的变化次数，每次更新答案均摊只有 $O(\log n)$ 的时间复杂度，于是总体时间复杂度为 $O(n\log^2n)$。

## #3.0 Code

``` cpp
const int N = 500010;
const int INF = 0x3fffffff;

template <typename T>
inline T Min(const T a, const T b) {return a < b ? a : b;}

struct Node {
    int ls, rs, mn, lz, sum;
    inline Node() {ls = rs = mn = lz = sum = 0;}
    inline void del() {ls = rs = mn = lz = sum = 0;}
} p[N];

int n, q, cnt, rt, b[N];

inline void Reset() {
    for (int i = 1; i <= cnt; ++ i) p[i].del();
    cnt = rt = 0;
}

inline void pushup(int k) {
    if (!p[k].ls || !p[k].rs) return;
    p[k].mn = Min(p[p[k].ls].mn, p[p[k].rs].mn);
    p[k].sum = p[p[k].ls].sum + p[p[k].rs].sum;
}

inline void pushdown(int k) {
    int ls = p[k].ls, rs = p[k].rs;
    if (p[k].lz) {
        if (ls) p[ls].lz += p[k].lz, p[ls].mn -= p[k].lz;
        if (rs) p[rs].lz += p[k].lz, p[rs].mn -= p[k].lz;
        p[k].lz = 0;
    }
}

void update(int k, int l, int r) {
    if (l == r) {++ p[k].sum, p[k].mn = b[l]; return;}
    pushdown(k); int mid = (l + r) >> 1;
    if (!p[p[k].ls].mn) update(p[k].ls, l, mid);
    if (!p[p[k].rs].mn) update(p[k].rs, mid + 1, r);
    pushup(k);
}

inline void add(int k, int l, int r, int c) {
    p[k].lz += c, p[k].mn -= c;
    if (!p[k].mn) pushdown(k), update(k, l, r), pushup(k);
}

void build(int &k, int l, int r) {
    if (!k) k = ++ cnt;
    if (l == r) {p[k].mn = b[l]; return;}
    int mid = (l + r) >> 1; build(p[k].ls, l, mid);
    build(p[k].rs, mid + 1, r); pushup(k);
}

void modify(int k, int l, int r, int x, int y, int c) {
    if (x <= l && r <= y) {add(k, l, r, c); return;}
    int mid = (l + r) >> 1; pushdown(k);
    if (x <= mid) modify(p[k].ls, l, mid, x, y, c);
    if (mid < y) modify(p[k].rs, mid + 1, r, x, y, c);
    pushup(k);
}

int query(int k, int l, int r, int x, int y) {
    if (x <= l && r <= y) return p[k].sum;
    int mid = (l + r) >> 1, res = 0; pushdown(k);
    if (x <= mid) res += query(p[k].ls, l, mid, x, y);
    if (mid < y) res += query(p[k].rs, mid + 1, r, x, y);
    return res;
}

int main() {
    while (~scanf("%d%d", &n, &q)) {
        for (int i = 1; i <= n; ++ i) scanf("%d", &b[i]);
        Reset(); build(rt, 1, n); char s[10]; int l, r;
        while (q --) {
            scanf("%s%d%d", s, &l, &r);
            if (s[0] == 'a') modify(rt, 1, n, l, r, 1);
            else printf("%d\n", query(rt, 1, n, l, r));
        }
    }
    return 0;
}
```

