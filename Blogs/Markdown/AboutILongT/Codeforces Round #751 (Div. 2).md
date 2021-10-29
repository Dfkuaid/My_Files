## A. Two Subsequences

> Time Limit: 2s | Memory Limit: 256MB

### #题意简述

给定一个字符串 $S(|S|\leq100)$，从中取出一个子序列 $a$，剩下的部分合为 $b$，要求 $a$ 的字典序最小，输出 $a$ 和 $b$。

有 $t(t\leq1000)$ 次询问。

### #大体思路

直接找字典序最小的单个字符作为 $a$ 即可。

### #Code

``` cpp
const int N = 100010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

char s[N]; int t, pos, n;

int main() {
    read(t);
    while (t --) {
        scanf("%s", s + 1); pos = 1; n = strlen(s + 1);
        for (int i = 2; i <= n; ++ i)
          if (s[pos] > s[i]) pos = i;
        putchar(s[pos]); putchar(' ');
        for (int i = 1; i <= n; ++ i)
          if (i != pos) putchar(s[i]);
        putchar('\n');
    }
    return 0;
}

```



## B. Divine Array

> Time Limit: 2s | Memory Limit: 256MB

### #题意简述

给定 $n(n\leq2000)$ 个正整数的序列，每次该序列按照如下规则变化：$a_i$ 变为 $cnt_{a_i}$；现有 $q(q\leq10^5)$ 个询问，每次询问位置 $i$ 在第 $t(t\leq10^9)$ 次变换后的值是多少。

有 $t(t\leq 1000)$，保证数据满足 $\sum n\leq2000,\sum q\leq10^5$.

### #大体思路

显然一个数列的变化次数不可能超过 $n$ 次，于是直接预处理即可，赛时为了保证正确，直接预处理了 $2000$ 次变化/qd

时间复杂度 $O(n^2+q)$.

### #Code

``` cpp
const int N = 4010;
const int INF = 0x3fffffff;
 
template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}
 
int t, n, a[N], q, b[N][N], tot[N];
 
int main() {
    read(t);
    while (t --) {
        read(n);
        for (int i = 1; i <= n; ++ i) read(b[i][0]);
        for (int i = 1; i <= n; ++ i) tot[i] = 0;
        for (int i = 1; i <= n; ++ i) ++ tot[b[i][0]];
        for (int i = 1; i <= 2000; ++ i) {
            for (int j = 1; j <= n; ++ j) b[j][i] = tot[b[j][i - 1]];
            for (int j = 1; j <= n; ++ j) tot[j] = 0;
            for (int j = 1; j <= n; ++ j) ++ tot[b[j][i]];
        }
        read(q);
        while (q --) {
            int x, k; read(x), read(k);
            if (k >= 2000) printf("%d\n", b[x][2000]);
            else printf("%d\n", b[x][k]);
        }
    }
    return 0;
}

```



## C. Array Elimination

> Time Limit: 2s | Memory Limit: 512MB

### #题意简述

给定一个有 $n(n\leq2\times10^5)$ 个非负整数的序列 $a_i(a_i\leq2^{30})$，我们可以选定一个 $k(1\leq k\leq n)$ 进行如下操作：

- 在 $a_i$ 中选出 $k$ 个数；
- 令 $x=a_{i_1}\&a_{i_2}\&\cdots\&a_{i_k}$；
- 将 $a_{i_1},a_{i_2},\dots,a_{i_k}$ 减去 $x$；

最终将所有 $a_i$ 变为 $0$.

问可以选出多少个 $k$，并给出所有可能的 $k$.

最多 $t(t\leq10^4)$ 组数据，满足 $\sum n\leq2\times10^5$.

### #大体思路

注意到对于二进制下第 $j$ 位，显然当我们选出的 $k$ 个数的第 $j$ 位都是 $1$，$x$ 的第 $j$ 位才能是 $1$，于是显然如果要将第 $j$ 位的 $1$ 全部消除，选定的 $k$ 必须是第 $j$ 位 $1$ 的出现次数的因数，所以如果我们要将所有位上的 $1$ 都消除，那么我们选定的 $k$ 显然必须是所有位上的 $1$ 的出现次数的公因数。

于是我们求出最大公因数后 $O(\sqrt n)$ 枚举因数即可。时间复杂度 $O(n\log^2 n+n\sqrt n)$.

### #Code

``` cpp
const int N = 200010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int t, n, tot[N], a[N], ans[N], cnt;

int gcd(int x, int y) {return y ? gcd(y, x % y) : x;}

int main() {
    read(t);
    while (t --) {
        read(n); memset(tot, 0, sizeof tot); cnt = 0;
        for (int i = 1; i <= n; ++ i) read(a[i]);
        for (int i = 1; i <= n; ++ i)
          for (int j = 0; j < 30; ++ j)
            tot[j] += (a[i] >> j) & 1;
        int g = 0;
        for (int i = 0; i < 30; ++ i)
          g = gcd(g, tot[i]);
        for (int i = 1; i * i <= g; ++ i) if (!(g % i)) {
            ans[++ cnt] = i;
            if (i * i != g) ans[++ cnt] = g / i;
        }
        sort(ans + 1, ans + cnt + 1);
        if (!g) for (int i = 1; i <= n; ++ i) printf("%d ", i);
        else for (int i = 1; i <= cnt; ++i) printf("%d ", ans[i]);
        putchar('\n');
    }
    return 0;
}

```



## D. Frog Traveler

> Time Limit: 2s | Memory Limit: 512MB

### #题意简述

有一只青蛙在一个高为 $n(1\leq n\leq10^5)$ 的井的井底，当青蛙处于 $i$ 高度时，可以向上跳 $[0,a_i]$ 高度，当它跳到 $i$ 高度时，会下滑 $b_i$，问最小跳跃次数，并输出路径。

### #大体思路

显然 DP 是不行的，于是考虑建图最短路，即将每个高度拆为两个点：入点和出点，入点到出点的距离为 $0$，其余边的距离为 $1$，然后跑 01 最短路。

发现这样建图边数过多，无法接受，考虑优化建图。发现每次都是单个点向一个区间连边，考虑用线段树优化建图，这样边数可以优化到 $O(n\log n)$ 级别，再进行 01 最短路即可。时间复杂度 $O(n\log n)$.

### #Code

``` cpp
#define mset(l, x) memset(l, x, sizeof(l))


const int N = 2000010;
const int INF = 0x3f3f3f3f;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

struct Node {int ls, rs;} p[N];
struct Edge {int u, v, w, nxt;} e[N << 2];

int n, a[N], b[N], head[N], ecnt(1), cnt;
int npos[N], id[N], rk[N], endpos, rt;

inline void add_edge(int u, int v, int w) {
    e[ecnt].u = u, e[ecnt].v = v, e[ecnt].w = w;
    e[ecnt].nxt = head[u], head[u] = ecnt ++;
}

void build(int &k, int l, int r) {
    if (!k) k = ++ cnt;
    if (l == r) {
        id[l] = cnt; rk[cnt] = l;
        if (!l) endpos = cnt; return;
    }
    int mid = l + r >> 1;
    build(p[k].ls, l, mid);
    build(p[k].rs, mid + 1, r);
    add_edge(k, p[k].ls, 0);
    add_edge(k, p[k].rs, 0);
}

void connect(int k, int l, int r, int x, int y, int c) {
    if (x <= l && r <= y) {add_edge(c, k, 1); return;}
    int mid = l + r >> 1;
    if (x <= mid) connect(p[k].ls, l, mid, x, y, c);
    if (mid < y) connect(p[k].rs, mid + 1, r, x, y, c);
}

void mapping() {
    for (int i = 1; i <= n; ++ i) npos[i] = ++ cnt;
    for (int i = 1; i <= n; ++ i) add_edge(id[i], npos[i + b[i]], 0);
    for (int i = 1; i <= n; ++ i) connect(rt, 0, n, i - a[i], i, npos[i]);
}

deque <int> q; int d[N], vis[N], pre[N];

inline void shortest_path(int u) {
    mset(d, 0x3f); mset(vis, 0);
    d[u] = 0; q.push_back(u);
    while (q.size()) {
        int x = q.front(); q.pop_front();
        if (vis[x]) continue; vis[x] = 1;
        for (int i = head[x]; i; i = e[i].nxt)
          if (d[e[i].v] > d[x] + e[i].w) {
              d[e[i].v] = d[x] + e[i].w;
              pre[e[i].v] = i;
              if (e[i].w) q.push_back(e[i].v);
              else q.push_front(e[i].v);
          }
    }
}

int ans[N], acnt;

inline void print() {
    if (d[id[0]] >= INF) {puts("-1"); return;}
    printf("%d\n", d[id[0]]); int now = id[0];
    while (now) {
        ans[++ acnt] = pre[now];
        now = e[pre[now]].u;
    }
    reverse(ans + 1, ans + acnt + 1);
    for (int i = 1; i <= acnt; ++ i)
      if (rk[e[ans[i]].v] || e[ans[i]].v == endpos)
        printf("%d ", rk[e[ans[i]].v]);
}

int main() {
    read(n); build(rt, 0, n);
    for (int i = 1; i <= n; ++ i) read(a[i]);
    for (int i = 1; i <= n; ++ i) read(b[i]);
    mapping(); shortest_path(id[n]); print(); return 0;
}

```



## E. Optimal Insertion

> Time Limit: 3s | Memory Limit: 512MB

### #题意简述

给定一个长度为 $n(n\leq10^6)$ 的序列 $a_i$ 和长度为 $m(m\leq10^6)$ 的序列 $b_i$，现在要将 $b_i$ 中的元素全部插入 $a_i$ 中，要求 $a_i$ 的顺序不变，$b_i$ 顺序不限，问得到序列的最小逆序对数。

共有 $t(t\leq10^4)$ 组询问，满足 $\sum n\leq10^6,\sum m\leq10^6$.

### #大体思路

注意到最终答案序列中的逆序对数一共有两种来源：$a_i$ 自有的和插入 $b_i$ 得到的。

显然 $b_i$ 的考虑顺序不会影响答案，不妨将 $b_i$ 自小到大排序，设 $p_i$ 为 $b_i$ 在 $a_i$ 的插入位置，如 $p_1=1$ 则表示 $b_1$ 插在 $a_1$ 前面，于是 $p_i=n+1$ 表示插在 $a_i$ 尾部。

对于排序后的 $b_i$，显然有 $p_1\leq p_2\leq p_3\leq\cdots\leq p_m$，可以用交换法证明这个贪心。

然后考虑分治，每次考虑位于中间的 $b_{mid}$，找到目标区间中贡献最小的位置作为 $p_{mid}$，然后将区间分为两部分继续分治即可。这个分治的正确性同样可以采用交换法并结合上面的贪心进行证明。

显然这样的分治不会超过 $O(\log(n+m))$ 层，每层将 $n$ 个位置遍历一次，于是时间复杂度为 $O(n\log(n+m))$.

经过上述操作后我们得到了答案序列，然后用树状数组维护求得逆序对即可。

（当然用线段树应当也可以，不过笔者用线段树被卡常了 QnQ）

> 有意思的是卡常的点的输出全是 $0$，当时测试不是分治挂了的时候，~~人工智能~~让他在 test 5 不对答案序列计算答案，然后突然就 Accepted 了/cy
>
> 当然还是老老实实换了树状数组/kk

### #Code

``` cpp
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))

const int N = 2000010;
const int LIMIT = 1e9;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

struct BIT {
    int val[N], len;
    
    inline BIT() {len = 0;};
    inline void init(int x) {len = x;}
    inline void reset() {while (len) val[len --] = 0;}
    inline void add(int x, int c) {while (x <= len) val[x] += c, x += (x & -x);}
    inline ll query(int x) {
        ll res = 0; while (x) res += val[x], x -= (x & -x); return res;
    }
} bit;

#define lb(l, len, x) lower_bound(l + 1, l + len + 1, x)
#define ub(l, len, x) upper_bound(l + 1, l + len + 1, x)

int t, n, m, a[N], b[N], c[N], p[N], upper[N], lower[N], dct[N]; ll ans;

inline void reset() {bit.reset(); ans = 0;}

inline void discretize() {
    for (int i = 1; i <= n; ++ i) dct[i] = a[i];
    for (int i = 1; i <= m; ++ i) dct[n + i] = b[i];
    sort(dct + 1, dct + n + m + 1);
    int len = unique(dct + 1, dct + n + m + 1) - dct - 1;
    for (int i = 1; i <= n; ++ i) a[i] = lb(dct, len, a[i]) - dct;
    for (int i = 1; i <= m; ++ i) b[i] = lb(dct, len, b[i]) - dct;
}

void solve(int l, int r, int pl, int pr) {
    if (l > r) return; int mid = l + r >> 1, res = INF;
    upper[pl - 1] = 0, upper[pl] = (a[pl] > b[mid]);
    lower[pr + 1] = 0, lower[pr] = (a[pr] < b[mid]);
    for (int i = pl; i < pr; ++ i) upper[i + 1] = upper[i] + (a[i + 1] > b[mid]);
    for (int i = pr; i > pl; -- i) lower[i - 1] = lower[i] + (a[i - 1] < b[mid]);
    for (int i = pl; i <= pr; ++ i) if (upper[i - 1] + lower[i] < res)
      res = upper[i - 1] + lower[i], p[mid] = i;
    if (pl == pr) p[mid] = pl;
    solve(l, mid - 1, pl, p[mid]); solve(mid + 1, r, p[mid], pr);
}

inline void get_list() {
    int ap = 1, lp = 1;
    for (int i = 1; i <= m; ++ i) {
        while (ap <= n && ap < p[i]) c[lp ++] = a[ap], ++ ap;
        c[lp ++] = b[i];
    }
    while (ap <= n) c[lp ++] = a[ap], ++ ap;
}

inline void calculate() {
    for (int i = n + m; i >= 1; -- i) {
        ans += bit.query(c[i] - 1);
        bit.add(c[i], 1);
    }
}

void MAIN() {
    read(n), read(m); reset(); bit.init(n + m + 1);
    for (int i = 1; i <= n; ++ i) read(a[i]);
    for (int i = 1; i <= m; ++ i) read(b[i]);
    discretize(); sort(b + 1, b + m + 1); a[n + 1] = INF;
    solve(1, m, 1, n + 1); get_list();
    calculate(); printf("%lld\n", ans);
}

int main() {
    read(t); while (t --) MAIN(); return 0;
}

```



## F. Difficult Mountain

> Time Limit: 2s | Memory Limit: 512MB

### #题意简述

$n(n\leq5\times10^5)$ 个人依次爬一座难度为 $d(d\leq10^9)$ 的山，每个人有两个参数：$s_i$ 和 $a_i$，当且仅当当前山的难度不大于 $s_i$ 这个人才可以爬上去，同时会将山的难度变为 $\max(d,a_i)$，你可以安排他们爬山的顺序，问最多能有多少个人登顶。

### #大体思路

一个很是巧妙的贪心：按照 $\max(s,a)$ 排序，从小到大；然后再按照 $s$ 从小到大排序，最后按照 $a$。

考虑证明上面贪心策略：设 $\max(s_i,a_i)<\max(s_j,a_j)$

- $s_i\geq a_i,s_j\geq a_j$

  这种情况不难发现，如果我们先让 $i$ 爬，$j$ 一定可以爬，但是如果我们先让 $j
  $ 爬，$i$ 可能不能爬，所以我们先让 $i$ 爬，不会使答案变劣。

- $s_i\geq a_i,s_j<a_j$

  如果我们先让 $i$ 爬，然后 $j$ 一定可以爬，如果我们先让 $j$ 爬，$i$ 一定不能爬。我们先让 $i$ 爬，会使答案变优。

- $s_i<a_i,s_j\geq a_j$

  如果我们先让 $i$ 爬，然后 $j$ 一定可以爬，但是如果我们先让 $j$ 爬，$i$ 可能不能爬，所以我们先让 $i$ 爬不会使答案变劣。

- $s_i<a_i,s_j<a_j$

  如果我们先让 $i$ 爬，$j$ 可能能爬，如果 $j$ 先爬，则 $i$ 一定不能爬，让 $i$ 先爬，不会是答案变劣。

同理，经过同样的分析，我们可以得到当最值相等时我们让 $s$ 小的先爬不会使答案变劣。

排序直接跑就可以。

似乎是一个规律：如果一个贪心策略与两个元素的大小都有关系，不妨考虑其最小值或最大值，或者加减乘除运算。这个题就是一个典型的考虑最大值的贪心。

### #Code

``` cpp
const int N = 500010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T Max(T a, T b) {return a > b ? a : b;}

struct Alpinists {
    int s, a;
    inline bool operator < (const Alpinists b) const {
        int mx1 = Max(s, a), mx2 = Max(b.s, b.a);
        if (mx1 != mx2) return mx1 < mx2;
        else return s == b.s ? a < b.a : s < b.s;
    }
} p[N];

int n, d, ans;

int main() {
    read(n); read(d);
    for (int i = 1; i <= n; ++ i)
      read(p[i].s), read(p[i].a);
    sort(p + 1, p + n + 1);
    for (int i = 1; i <= n; ++ i)
      if (p[i].s >= d) ++ ans, d = Max(d, p[i].a);
    printf("%d", ans); return 0;
}

```

