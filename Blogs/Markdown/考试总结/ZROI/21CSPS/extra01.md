## #T1 Str

### #题意简述

定义两个字符串相似为各个字符数相等；给定一个长度为 $n(n\leq10^5)$ 的字符串 $s$，求一个尽可能短的前缀 $t$ 满足可以将 $s$ 分为大于等于 $2$ 段，要求每段长度相同，除第一段与 $t$ 相等外，其余段与 $t$ 相似。

### #大体思路

$n$ 的因数最多只有 $O(\sqrt n)$ 个，可以暴力枚举 $n$ 的小于等于 $\dfrac n 2$ 的因数，直接进行判断，一个极为宽松的时间复杂度为 $O(n\sqrt n)$，或者也可以看作循环 $n$ 次，每个循环里 $O(\dfrac{1}k)$，整体为 $O(n\log n)$.

### #Code

``` cpp
const int N = 100010;
const int INF = 0x3fffffff;

char s[N]; int n, cnt[N][26], standard[26];

inline bool check(int l, int r) {
    for (int i = 0; i < 26; ++ i)
      if (cnt[r][i] - cnt[l - 1][i] != standard[i])
        return false;
    return true;
}

int main() {
    scanf("%s", s); n = strlen(s);
    for (int i = 0; i < n; ++ i)
      ++ cnt[i + 1][s[i] - 'a'];
    for (int i = 1; i <= n; ++ i)
      for (int j = 0; j < 26; ++ j)
        cnt[i][j] += cnt[i - 1][j];
    for (int l = 1; l <= n >> 1; ++ l) if (!(n % l)) {
        int is_answer = true;
        for (int i = 0; i < 26; ++ i)
          standard[i] = cnt[l][i];
        for (int i = l + 1; i <= n; i += l)
          if (!check(i, i + l - 1)) {
              is_answer = false; break;
          }
        if (is_answer) {
            for (int i = 0; i < l; ++ i)
              putchar(s[i]);
            return 0;
        }
    }
    puts("-1"); return 0;
}
```

## #T2 Subset

### #题意简述

给出一个长度为 $n(1\leq n\leq10^5)$ 的序列 $A$ ，求 $A$ 的所有长度为 $k(1\leq k\leq50)$ 的子序列的最大值之和 $\bmod 10^9+7$。

### #大体思路

我们来直接考虑元素 $x$ 造成的贡献，显然只有当子序列中的数 $b_i(1\leq i\leq k)$ 都小于等于 $x$ 时才会造成 $x$ 的贡献，于是不难想到将序列自小到大排序，于是 $a_i(1\leq i\leq n)$ 的贡献为 $\dbinom{i-1}{k-1}\cdot a_i$。时间复杂度为 $O(nk)$，瓶颈为预处理组合数，当然也可以采用线性求阶乘、逆元的方式优化到 $O(n\log n)$，此时时间复杂度瓶颈为快速排序。

### #Code

``` cpp
#define ll long long

const int N = 100010;
const ll MOD = 1e9 + 7;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int n, k; ll C[N][55], a[N], ans;

inline void init_C(int x, int y) {
    for (int i = 0; i <= x; ++ i) C[i][0] = 1;
    for (int i = 1; i <= x; ++ i)
      for (int j = 1; j <= i && j <= y; ++ j) {
          if (j == i) {C[i][j] = 1; break;}
          C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
      }
}

int main() {
    read(n); read(k); init_C(n, k);
    for (int i = 1; i <= n; ++ i) read(a[i]);
    sort(a + 1, a + n + 1);
    for (int i = k; i <= n; ++ i)
      (ans += C[i - 1][k - 1] * a[i] % MOD) %= MOD;
    printf("%lld", ans); return 0;
}
```

## #T3 Pair

### #题意简述

给出一个整数 $n(n\leq20)$ ，求满足 $\forall(a,b)\in S,1\leq a<b\leq n$ 且 $\gcd(a,b)=1$ ，并且**不存在**一个划分的集合 $S$ 的数量 $\bmod 10^9$.

定义一个集合 $S$ 存在划分为 $\exists x\in[2,n]$，$\forall(a,b)\in S$ 要么满足 $a<x\text{ and }b<x$，要么满足 $a\geq x\text{ and }b\geq x$.

### #大体思路

首先不难发现这样的数对最多有 $n^2$ 个，于是显然可以预处理得到。

发现一个集合不存在划分，即意味着对于集合 $S=\{(a_1,b_1),(a_2,b_2),\dots,(a_k,b_k)\}$，应当有
$$
\bigcup\limits_{i=1}^k[a_i,b_i]=[1,n],
$$
考虑设计 DP 解决计数问题。假设我们已经得到了所有 $m$ 个可行的数对（按先 $a$ 后 $b$ 的顺序从小到大排序），设 $f_{i,j}$ 表示考虑了前 $i$ 个二元组，并集为 $[1,j]$ 的方案数，最终答案为 $f_{m,n}$.

来考虑如何转移，如果不选新加入的二元组，那么方案数为 $f_{i-1,j}$，即具有转移 $f_{i-1,j}\to f_{i,j}$，如果新加入的二元组 $(a,b)$ 满足 $a\leq j$，意味着将其并入得到的集合不会存在划分，新得到的并集应当为 $[1,\max\{j,b\}]$，于是具有转移 $f_{i-1,j}\to f_{i,\max\{j,b\}}$。一个极为宽松的时间复杂度上界为 $O(n^3)$.

### #Code

``` cpp
#define ll long long

const ll MOD = 1e9;
const int N = 2000010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int n, npr[N][2], cnt; ll f[N][21];

ll gcd(ll x, ll y) {return y ? gcd(y, x % y) : x;}

int main() {
    read(n);
    for (int i = 1; i < n; ++ i)
      for (int j = i + 1; j <= n; ++ j)
        if (gcd(i, j) == 1) npr[++ cnt][0] = i, npr[cnt][1] = j;
    f[0][1] = 1;
    for (int i = 1; i <= cnt; ++ i)
      for (int j = 1; j <= n; ++ j) {
          f[i][j] = (f[i][j] + f[i - 1][j]) % MOD;
          if (npr[i][0] <= j)
            (f[i][max(npr[i][1], j)] += f[i - 1][j]) %= MOD;
      }
    printf("%lld", f[cnt][n]);
    return 0;
}
```



## #T4 Match

### #题意简述

给定 $n(n\leq10^5)$ 个字符串 $S_i$，有 $m(m\leq10^5)$ 个询问，每次给出一个前缀 $T_1$ 和一个后缀 $T_2$，问有多少个串 $S_i$ 满足 $S_i=T_1RT_2(|R|\geq0)$。

数据范围满足 $\sum|S_i|+\sum|T|\leq10^6$.

### #大体思路

先考虑将所有字符串插入一棵 trie 中，先考虑前缀要求 $T_1$，假设得到 $T_1$ 的结束点为 $x$， 这限制了所有答案的 $T_2$ 的起始点一定在 $x$ 的子树中，于是我们现在的目标就是得到 $x$ 的子树中能作为 $T_2$ 的起始点的点的个数，发现不好进行解决，不妨将其转化为能作为 $T_2$ 的起始点的点中 dfn 大于等于 $dfn_x$ 小于等于 $end\_dfn_x$ 的点的个数。

于是我们可以这样解决：在插入每个串时，在每个经过的点上增加一个当前剩余的后缀（的 Hash 值），在递归求 dfn 时将每个点上的串与该点的 dfn 结合加入一个序列中，最后将该序列按照先 Hash 值后 dfn 的顺序进行排序，得到的序列中同样的串所在位置连续，于是用 `lower_bound()` 和 `upper_bound()` 结合即可得到答案。

由于不同字符串的数量可能很大，这里采用双 Hash 防止冲突。

### #Code

``` cpp
#define ll long long
#define pii pair <int, int>
#define mkp(a, b) make_pair(a, b)

const int N = 3000010;
const int BAS1 = 131;
const int BAS2 = 13331;
const int MOD1 = 998244353;
const int MOD2 = 1004535809;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int dfn[N], endp[N], ch[N][30], cnt = 1;
int hash_val1[N], hash_val2[N], T;

vector <pii > h[N]; /*the hash values of each string belong the node.*/
vector <pair <pii, int> > v; /*the list of all hash values with dfn.*/

/*Insert a new string, and add the hash values of 
the suffixes to the list of corresponding node.*/
void insert(char *s) {
    int len = strlen(s), p = 1;
    hash_val1[len] = hash_val2[len] = 0;
    /*Get the hash value of each suffix.*/
    for (int i = len - 1; ~i; -- i)
      hash_val1[i] = (1ll * hash_val1[i + 1] * BAS1 % MOD1 + s[i] - 96) % MOD1,
      hash_val2[i] = (1ll * hash_val2[i + 1] * BAS2 % MOD2 + s[i] - 96) % MOD2;
    h[p].push_back(mkp(hash_val1[0], hash_val2[0]));
    /*Insert string and add the hash values.*/
    for (int i = 0; i < len; ++ i) {
        int k = s[i] - 96;
        if (!ch[p][k]) {ch[p][k] = ++ cnt;} p = ch[p][k];
        h[p].push_back(mkp(hash_val1[i + 1], hash_val2[i + 1]));
    }
}


/*Get the dfn of each node, and add the hash
values with dfn to the list at the same time.*/
void dfs(int x) {
    dfn[x] = ++ T;
    for (auto i : h[x]) v.push_back(mkp(mkp(i.first, i.second), T));
    for (int i = 1; i <= 26; ++ i) if (ch[x][i]) dfs(ch[x][i]);
    endp[x] = T;
}

int n, m; char a[N];

int main() {
    read(n); read(m); 
    for (int i = 1; i <= n; ++ i)
      scanf("%s", a), insert(a);
    dfs(1); sort(v.begin(), v.end());
    while (m --) {
        scanf("%s", a); int l = strlen(a), p = 1, q = 0;
        /*Get into the end node of T1.*/
        while (q < l && a[q] != '*') p = ch[p][a[q] - 96], ++ q;
        /*Get the hash value of T_2.*/
        int hv1 = 0, hv2 = 0;
        for (int i = l - 1; i > q; -- i)
          hv1 = (1ll * hv1 * BAS1 % MOD1 + a[i] - 96) % MOD1,
          hv2 = (1ll * hv2 * BAS2 % MOD2 + a[i] - 96) % MOD2;
        printf("%d\n", ub(mkp(mkp(hv1, hv2), endp[p])) - lb(mkp(mkp(hv1, hv2), dfn[p])));
    }
    return 0;
}
```

> 囸，当时在被 whk 蹂躏，不知道有 extra Round...