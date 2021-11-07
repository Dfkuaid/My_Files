> “我写了这么多 `memset`，绝不可能还因为多测没清空挂了！来，交一发……”
>
> ……
>
> “What's up! 到底为什么 WA 啊！拍不出来……哦拍出来了！让我康康……”
>
> “……不如把这个数据挑出来测吧……嗯？怎么过了？不会又是多测没清空吧？不可能啊！”
>
> ……
>
> “Watch out! 我用了两遍 `tot` 只清空了一遍……我是**！”

## #1.0 题意简述

> Time Limit: 5s | Memory Limit: 64MB

定义
$$
T(i,k)=T_iT_{i+1}T_{i+2}\dots T_{i+k-1},\ 1\leq i\leq i+k-1\leq|T|.\\
$$
给定两个字符串 $A,B(|A|,|B|\leq10^5)$ 和 $K$，求所有满足下列要求的三元组 $(i,j,k)$：
$$
\{(i,j,k)|k\geq K,A(i,k)=B(j,k)\}.
$$
**多组数据**，输入 $K=0$ 时停止。

## #2.0 大体思路

### #2.1 转化题意

首先不难发现，题目实际是要求公共前缀长度不小于 $K$ 的后缀对数，即：
$$
\sum_{i=1}^{|A|}\sum_{j=1}^{|B|}[LCP(i,j)\geq K](LCP(i,j)-K+1)
$$
于是首先想到采用**后缀数组**进行操作，但是由于后缀数组只能（我只会）对于单个字符串进行操作，于是考虑将两个串拼起来。中间用一个未出现过的符号连接（我用的 `$`），我们默认这个符号的优先级最小，对新串进行后缀排序。

### #2.2  暴力怎么做

于是我们可以直接求出 `height[]` 数组并直接使用 RMQ 做到 $O(n^2)$.

### #2.3 单调栈优化

考虑从上面的暴力入手进行优化，假设我们当前对于所有 $B_i$ 求他前面（后缀排序后）所有的 $A_j$ 与它的 LCP 之和，根据我们使用 `height[]` 求 LCP 的原理，注意到这个 LCP 序列一定是从后向前非严格递减的，于是我们可以考虑通过维护一个单调的数据结构来对这一段一段的相同的 `height[]` 进行维护。

那具体维护什么信息呢？当我们向后考虑当前这一位时，发现绝大部分都是可以直接继承的，但是显然之前 `height[]` 比当前后缀的 `height[]` 大的都需要修改，于是我们考虑维护一个 `height[]` 单调递增的单调栈，同时维护栈内所有对应 `height[]` 的贡献（所有 `height[]-k+1` 乘上以该 `height[]` 为 LCP 的 $A_j$ 的数量的和），当我们把所有不合法的都弹出之后，再将当前的加入栈中，由于 `height[]` 是当前与上一个的 LCP 长度，于是我们需要判断上一个是否有贡献，经过上面的过程，当前维护的栈内的和就是对于当前后缀的答案，累加即可。

同样的，对于 $A_i$ 考虑前面的每一个 $B_j$ 时是完全一致的过程。

### #时间复杂度分析

- 求解 SA 是 $O(n\log n)$；
- 求解 `height[]` 是 $O(n)$；
- 单调栈每个元素最多进栈、出栈各 $O(1)$ 级别次，于是均摊复杂度为 $O(n)$；

综上，时间复杂度为 $O(n\log n)$，瓶颈在于求解 SA.

## #3.0 Code

``` cpp
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))

const int N = 500010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int k; char a[N], b[N], s[N]; ll ans;
int sa[N], rk[N], oldrk[N], px[N], id[N], cnt[N], n, ht[N];

inline void reset() {
    mset(sa, 0), mset(rk, 0), mset(oldrk, 0), mset(ht, 0);
    mset(px, 0), mset(id, 0), mset(cnt, 0); ans = 0;
    for (int i = 1; i <= n; ++ i) s[i] = '\0';
}

inline bool comp(int x, int y, int w) {
    return oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w];
}

inline void get_sa(int m) {
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

inline void get_height() {
    for (int i = 1, k = 0; i <= n; ++ i) {
        if (k) -- k;
        while (s[i + k] == s[sa[rk[i] - 1] + k]) ++ k;
        ht[rk[i]] = k;
    }
}

int stk[N], stp, lena, lenb; ll sum, tot[N];

void solve() {
    mset(tot, 0);
    for (int i = 1; i <= n; ++ i) {
        if (ht[i] < k) {stp = 0, sum = 0; continue;}
        while (stp && ht[stk[stp]] >= ht[i]) {
            sum -= 1ll * tot[stk[stp]] * (ht[stk[stp]] - k + 1);
            sum += 1ll * tot[stk[stp]] * (ht[i] - k + 1);
            tot[i] += tot[stk[stp]]; -- stp;
        }
        if (sa[i - 1] <= lena) sum += 1ll * (ht[i] - k + 1), ++ tot[i];
        stk[++ stp] = i; if (sa[i] > lena + 1) ans += sum;
    }
    mset(tot, 0);
    for (int i = 1; i <= n; ++ i) {
        if (ht[i] < k) {stp = 0, sum = 0; continue;}
        while (stp && ht[stk[stp]] >= ht[i]) {
            sum -= 1ll * tot[stk[stp]] * (ht[stk[stp]] - k + 1);
            sum += 1ll * tot[stk[stp]] * (ht[i] - k + 1);
            tot[i] += tot[stk[stp]]; -- stp;
        }
        if (sa[i - 1] > lena + 1) sum += 1ll * (ht[i] - k + 1), ++ tot[i];
        stk[++ stp] = i; if (sa[i] <= lena) ans += sum;
    }
}

void MAIN() {
    scanf("%s%s", a + 1, b + 1); reset();
    lena = strlen(a + 1), lenb = strlen(b + 1);
    for (int i = 1; i <= lena; ++ i) s[i] = a[i];
    n = lena + 1 + lenb; s[lena + 1] = '$';
    for (int i = 1; i <= lenb; ++ i) s[lena + 1 + i] = b[i];
    get_sa(256); get_height(); solve(); printf("%lld\n", ans);
}

int main() {read(k); while (k) {MAIN(); read(k);} return 0;}

```

