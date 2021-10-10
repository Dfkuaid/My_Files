## #T1 有趣的数

### #题意简述

定义一个整数 $N$ 是有趣的，当且仅当 $N$ 满足：

- $0\leq N\leq10^{18}$；
- 在 $B_1$ 进制下有 $K_1$ 位，在 $B_2$ 进制下有 $K_2$ 位；

其中 $2\leq B_1,B_2\leq100$，$1\leq K_1,K_2\leq20$。

### #大体思路

不难发现在 $B_1,K_1$ 给定的情况下，可能的有趣的数是一个区间，上下界可以用快速幂得到，$B_2,K_2$ 同理，于是求区间交即可。

### #Code

``` cpp
#define ll long long

const ll LMT = 1e18;

ll b1, d1, b2, d2;

inline ll get_limit(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res *= a;
        if (res >= LMT + 1 || res <= 0) return LMT + 1;
        b >>= 1; if (b) a *= a;
        if (a >= LMT + 1 || a <= 0) return LMT + 1;
    }
    return res;
}

int main() {
    scanf("%lld%lld%lld%lld", &b1, &d1, &b2, &d2);
    ll ul1 = get_limit(b1, d1);
    ll ll1 = get_limit(b1, d1 - 1);
    ll ul2 = get_limit(b2, d2);
    ll ll2 = get_limit(b2, d2 - 1);
    ll ul = min(ul1, ul2), lo = max(ll1, ll2);
    printf("%lld", ul > lo ? ul - lo : 0);
    return 0;
}
```

## #T2 木棒

### #题意简述

给定十二根木棒的长度 $l_i(l_i\leq10^9)$，问最多能同时得到多少个三角形。

多组数据，数组组数 $t$ 满足 $1\leq t\leq6000.$

### #大体思路

发现选择状态数极少，可以考虑状压 DP，但是直接转移颇具难度，考虑用更加容易理解的记忆化搜索。

每次找到一个最短的、未被考虑的木棍，他只有两种选择：

- 丢掉；
- 再找两根与其配对；

进行记忆化搜索即可。

### #Code

``` cpp
const int N = 12;
const int init_S = (1 << N) - 1;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T Max(T &a, T &b) {return a > b ? a : b;}

int t, T, l[N], f[(1 << N) + 10], vis[(1 << N) + 10];

int dfs(int S) {
    if (vis[S] == T || !S) return f[S];
    int now; f[S] = 0, vis[S] = T;
    for (int i = 0; i < N; ++ i)
      if ((S >> i) & 1) {now = i; break;}
    f[S] = dfs(S ^ (1 << now));
    for (int i = now + 1; i < N; ++ i) if ((S >> i) & 1)
      for (int j = i + 1; j < N; ++ j) if ((S >> j) & 1 && l[now] + l[i] > l[j])
        f[S] = max(f[S], dfs(S ^ (1 << now) ^ (1 << i) ^ (1 << j)) + 1);
    return f[S];
}

int main() {
    read(t);
    for (T = 1; T <= t; ++ T) {
       for (int i = 0; i < N; ++ i) read(l[i]);
        sort(l, l + N); printf("%d\n", dfs(init_S));
    }
    return 0;
}
```

## #T3 装饰

### #题意简述

一棵 $n(n\leq10^5)$ 个节点、以 $1$ 为根的树，每个节点上有两个参数 $c_i,t_i$，分别表示以 $i$ 为根的子树中至少被选择 $c_i(1\leq c_i\leq10^7)$ 次，节点 $i$ 被选一次的代价是 $t_i(1\leq t_i\leq100)$，求最小总代价。

### #大体思路

考虑如果一棵子树上当前所选的数量不足，为了代价最小，应当选择整棵子树上代价最小的节点，按此思路进行树上 DP（树上贪心？）即可。

### #Code

``` cpp
#define ll long long

const int N = 100010;

template <typename T> inline T Min(T a, T b) {return a < b ? a : b;}

struct Edge {int u, v, nxt;} e[N];

int n,ecnt(1), head[N], siz[N];
ll c[N], t[N], mn[N], f[N], tot[N];

inline void add_edge(int u, int v) {
    e[ecnt].u = u, e[ecnt].v = v;
    e[ecnt].nxt = head[u], head[u] = ecnt ++;
}

void solve(int x) {
    int nowtot = 0; siz[x] = 1, mn[x] = t[x];
    for (int i = head[x]; i; i = e[i].nxt) {
        solve(e[i].v); siz[x] += siz[e[i].v];
        tot[x] += tot[e[i].v]; f[x] += f[e[i].v];
        mn[x] = Min(mn[x], mn[e[i].v]);
    }
    if (tot[x] < c[x]) {f[x] += mn[x] * (c[x] - tot[x]), tot[x] = c[x];}
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) {
        int x; scanf("%d%lld%lld", &x, &c[i], &t[i]);
        if (x > 0) add_edge(x, i);
    }
    solve(1); printf("%lld", f[1]); return 0;
}
```

## #T4 翻转硬币

### #题意简述

一个长度为 $n(n\leq300)$ 的 01 串 $s$，给定参数 $m(1\leq m\leq n)$，要求通过以下两种操作：

- 将一个位置取反；
- 将前 $k\cdot m(k\in Z)$ 位取反（若 $k\cdot m>n$ 则整体取反）；

使得 $s$ 最终满足 $s_1=s_{m+1},s_2=s_{m+2},\dots,s_{n-m}=s_{n}$，问最小操作数。

### #大体思路

注意到一个位置单个、整体各最多被取反一次，否则没有意义。

通过简单画图不难发现，最终状态满足将原串从头开始划分为长度为 $m$ 的 $\left\lceil\dfrac n m\right\rceil$ 小段（最后一段长度可能小于 $m$），其中前 $\left\lfloor\dfrac {n - m} m\right\rfloor$ 段的每一段都相等，最后一点不足 $m$ 的小段也与完整的小段的前部对应相等。

当 $m>\sqrt n$ 时，段数极少，极限数据下不超过 $17$ 段，于是可以考虑枚举每一段是否被翻转，然后贪心地考虑每一位选什么直接统计。

否则，考虑枚举每一段是什么样子，然后 DP 即可，每次转移的时候贪心地选择这一段是否要翻转即可。

### #Code

``` cpp
const int N = 310;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

char ca[N];
int n, m, a[N], id[N], sub[N][2], bcnt, f[N][2];

inline void divide() {
    for (int i = 1; i <= n; ++ i) id[i] = (i - 1) / m + 1;
    for (int i = 1; i <= id[n]; ++ i)
      sub[i][0] = (i - 1) * m + 1, sub[i][1] = i * m;
    sub[id[n]][1] = min(sub[id[n]][1], n); bcnt = id[n];
}

inline int bitcnt(int x) {
    int cnt = 0; while (x) x -= x & (-x), ++ cnt; return cnt;
}

int solve_1() {
    int res = INF;
    for (int s = 0; s < 1 << bcnt; ++ s) {
        int cnt = 0, lst = 0;
        for (int i = bcnt; i >= 1; -- i)
          if ((s >> (i - 1)) & 1 != lst) ++ cnt, lst ^= 1;
        for (int i = 1; i <= m; ++ i) {
            int c[2]; c[0] = c[1] = 0;
            for (int j = i; j <= n; j += m)
              ++ c[a[j] ^ (s >> (id[j] - 1)) & 1];
            cnt += min(c[0], c[1]);
        }
        res = min(res, cnt);
    }
    return res;
}

int solve_2() {
    int res = INF;
    for (int s = 0; s < 1 << m; ++ s) {
        for (int i = 1; i <= bcnt; ++ i) {
            int cnt[2]; cnt[0] = cnt[1] = 0;
            for (int j = sub[i][0]; j <= sub[i][1]; ++ j)
              ++ cnt[a[j] ^ (s >> (j - sub[i][0]) & 1)];
            f[i][0] = min(f[i - 1][0] + cnt[1], f[i - 1][1] + cnt[1] + 1);
            f[i][1] = min(f[i - 1][1] + cnt[0], f[i - 1][0] + cnt[0] + 1);
        }
        res = min(res, min(f[bcnt][0], f[bcnt][1] + 1));
    }
    return res;
}

int main() {
    scanf("%s", ca); n = strlen(ca); read(m);
    for (int i = 0; i < n; ++ i) a[i + 1] = ca[i] - '0';
    divide(); printf("%d", m > sqrt(n) ? solve_1() : solve_2());
    return 0;
}
```

