> [题目链接](https://acm.hdu.edu.cn/showproblem.php?pid=5756)

## #1.0 题意简述

给定一棵以 $1$ 为根的 $n$ 个点的树，$q$ 次询问，每次给定一个集合 $\{a_1,a_2,\dots,a_k\}$，定义“可行点”为不属于给定集合中的任意一点的子树的点，给定点 $p$，有以下三种询问：

- 问 $p$ 到所有可行点的距离之和；
- 问 $p$ 到所有可行点的距离最小值；
- 问 $p$ 到所有可行点的距离最大值；

定义树上每条边的长度为 $1$，每个点到自己的距离为 $0$，如果不存在可行点，则输出 `-1`。

本题**强制在线**，记上一次的答案为 $lastans$，每次询问给出 $p'$，询问真正的 $p$ 为

$$
p=(p'+lastans)\bmod n+1.
$$

若为第一个询问或上个询问答案为 $-1$，则令 $lastans=0.$

有**多组数据**，直至读入文件结束符（EOF）程序停止。

## #2.0 大体思路

看到一个点被选中的影响是整棵子树，我们便考虑通过 dfn 序将树上的问题变成序列上的问题。如果我们当前序列保存的是 dfn 序为 $i$ 的点与 $p$ 的距离，那么问题变为了给定 $k$ 个区间，询问在 $[1,n]$ 中去掉这 $k$ 个区间后，剩下所有区间的权值和/最小值/最大值。

那么现在来考虑对于每个点如何维护距离序列。

考虑从一个父节点进入其的一个儿子，发现该儿子的子树中的点的距离全部减少 $1$，其余的点的距离全部增加 $1$。因为整棵树以 $1$ 为根，所以可以通过一次 dfs 得到 $p=1$ 时的序列，之后的所有修改都可以从这个序列的基础上得到，不难想到此过程可以用可持久化线段树维护。

于是我们的具体实现流程为

- 通过一次 dfs 得到 $p=1$ 时的序列和其他必要信息；
- 利用 dfs 得到的信息建出初始线段树，按 dfn 序通过区间修改得到各版本的序列；
- 处理每个询问，得到在 $[1,n]$ 中去掉这 $k$ 个区间后，剩下所有区间的答案；

对于每个询问，最多会要查询 $k+1$ 个区间，于是时间复杂度为 $O(\left(n+\sum k\right)\log n).$

## #3.0 一些细节

### #3.1 如何得到询问区间

因为序列是按 dfn 序排列，所以不难得到这条性质：任意两个子树代表的区间要么为包含关系，要么毫不相关；

于是我们可以对选定点代表的区间按左端点进行排序，如果当前处理到的询问右端点 $r$ 比上一个右端点 $R$ 大，就询问 $[R+1,l-1]$ 这个区间，注意要特殊处理 $R+1=l$ 的情况；最后需要判断是否要查询 $[R+1,n]$ 这个区间。

直接采用 `sort()` 不会影响时间复杂度。

### #3.2 关于区间修改

因为涉及到区间修改，所以会涉及到区间标记，如果这里采用标记下传，下传标记时为保证不对历史版本的节点进行修改，便需要新建节点，空间复杂度大致约为 $O(n\log^2n)$，而我们只有 $128M$ 空间，无法接受，而区间加法的标记具有可加性，故应当采用标记永久化，这样空间复杂度便为 $O(n\log n).$

## #4.0 Code

``` cpp
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
```