# #0.0 序

由于月初集训的缘故，本月偏重于 DP

# #1.0 启

> $\mathfrak{2021.5.10\sim2021.5.19}$

## #1.1 [P4170 [CQOI2007]涂色](https://www.luogu.com.cn/problem/P4170)

区间 DP 水题，按照一般的区间 DP 框架进行，同时注意到：如果一个区间左右两边字符相等，那么这两个字符显然可以被白嫖掉。

**转移方程**：
$$
f_{l,r}=\begin{cases}\min\limits_{l\leq k<r}\{f_{l,k}+f_{k+1,r}\},\\f_{l+1,r-1},\quad s_l=s_r\end{cases}
$$

## #1.2 [CF1132F Clear the String](https://www.luogu.com.cn/problem/CF1132F)

可以看做是上一题的反向操作，也可以用另一种思路：

``` cpp
for (int i = 2;i <= n;i ++)
  for (int l = 0;l + i - 1 < n;l ++){
      int r = l + i - 1;
      for (int k = l;k < r;k ++)
        f[l][r] = min(f[l][r],f[l][k] + f[k + 1][r]);
      if (s[l] == s[r]) f[l][r] --; //同样是白嫖掉
  }
```

## #1.3 [P2051 [AHOI2009]中国象棋](https://www.luogu.com.cn/problem/P2051)

简化题面：每行每列最多 $2$ 个炮。

按行为阶段转移，考虑有 $0,1,2$ 个炮的列数。

``` cpp
f[1][m][0] = 1,f[1][m - 2][2] = m * (m - 1) / 2,f[1][m - 1][1] = m;
    for (int i = 1;i < n;i ++)
      for (int j = 0;j <= m;j ++)
        for (int k = 0;k <= m;k ++){
            if (!f[i][j][k]) continue;
            f[i + 1][j][k] += f[i][j][k];
            if (j >= 1) (f[i + 1][j - 1][k + 1] += f[i][j][k] * j % MOD) %= MOD;
            if (k >= 1) (f[i + 1][j][k - 1] += f[i][j][k] * k % MOD) %= MOD;
            if (j >= 1) (f[i + 1][j - 1][k] += f[i][j][k] * j * k % MOD) %= MOD;
            if (j >= 2) (f[i + 1][j - 2][k + 2] += f[i][j][k] * j * (j - 1) / 2 % MOD) %= MOD;
            if (k >= 2) (f[i + 1][j][k - 2] += f[i][j][k] * k * (k - 1) / 2 % MOD) %= MOD;
        }
```

## #1.4 [AT2567 [ARC074C] RGB Sequence](https://www.luogu.com.cn/problem/AT2567)

**如何记录区间内不同颜色的数量：分别保存各种颜色最后一次出现的位置。**

设 $f_{i,j,k,l}$ 表示当前考虑到了第 $i$ 个格子，红绿 蓝三种颜色最后一次出现的位置分别是 $j,k,l$ 的方案数。

依然考虑去除冗余状态，发现 $i=\max\{j,k,l\}$，于是可简化为：设 $f_{i,j,k}$ 表示当前考虑到了第 $\max\{i,j,k\}$ 个格子，红绿蓝三种颜色最后一次出现的位置分别是 $i,j,k$ 的方案数。

``` cpp
f[1][0][0] = 1;
for (int i = 1;i <= n;i ++)
  for (int j = 0;j < i;j ++)
    for (int k = 0;k <= Max(0,j - 1);k ++){
        if (!check(i,j,k)) continue;
        (f[i + 1][j][k] += f[i][j][k]) %= MOD;
        (f[i + 1][i][j] += f[i][j][k]) %= MOD;
        (f[i + 1][i][k] += f[i][j][k]) %= MOD;
        if (i == n) (ans += f[i][j][k]) %= MOD;
    }
```

## #1.5 [P1758 [NOI2009] 管道取珠](https://www.luogu.com.cn/problem/P1758)

直接处理式子不好处理，考虑组合意义，发现该式与 “两个人分别取，有多少种取法可得到相同的序列”，然后分别讨论当前取到的来自那个位置，转移即可。

**状态设计**：$f_{k,i,j}$ 表示当前取了 $k$ 个珠子，第一个人在上面取了 $i$ 个，第二个人在上面取了 $j$ 个，有多少种方法可以得到相同的序列。

直接使用上面的状态会 $\text{MLE}$，观察转移，发现可以 $k$ 这一维可以滚动数组优化，但 $i,j$ 两维的枚举顺序应当为从大到小。

``` cpp
/*无优化，40pts*/
f[0][0][0] = 1;
for (int k = 1;k <= n + m;k ++)
  for (int i = 0;i <= k;i ++)
    for (int j = 0;j <= k;j ++){
        if (i && j && u[i - 1] == u[j - 1])
            (f[k][i][j] += f[k - 1][i - 1][j - 1]) %= MOD;
        if (i && (k - j) && u[i - 1] == d[k - j - 1])
            (f[k][i][j] += f[k - 1][i - 1][j]) %= MOD;
        if ((k - i) && j && d[k - i - 1] == u[j - 1])
            (f[k][i][j] += f[k - 1][i][j - 1]) %= MOD;
        if ((k - i) && (k - j) && d[k - i - 1] == d[k - j - 1])
            (f[k][i][j] += f[k - 1][i][j]) %= MOD;
    }

/*滚动数组优化，但状态设计不够优，必须吸氧才能过*/
f[0][0] = 1;
for (int k = 1;k <= n + m;k ++)
    for (int i = k;i >= 0;i --)
    for (int j = k;j >= 0;j --){
        if (!(k - i) || !(k - j) || d[k - i - 1] != d[k - j - 1])
            f[i][j] = 0;
        if (i && j && u[i - 1] == u[j - 1])
            (f[i][j] += f[i - 1][j - 1]) %= MOD;
        if (i && (k - j) && u[i - 1] == d[k - j - 1])
            (f[i][j] += f[i - 1][j]) %= MOD;
        if ((k - i) && j && d[k - i - 1] == u[j - 1])
            (f[i][j] += f[i][j - 1]) %= MOD;
    }
```

## #1.6 [P5957 [POI2017]Flappy Bird](https://www.luogu.com.cn/problem/P5957)

坐标系转化，如下图：

![](https://pic.imgdb.cn/item/60b039c508f74bc159ba912a.png)

然后就随便做了。

``` cpp
const int N = 100010;
const int INF = 0x3fffffff;

int n,X,x,a,b;
int L,R,now;

int main(){
    scanf("%d%d",&n,&X);
    while (n --){
        scanf("%d%d%d",&x,&a,&b);
        if (R + (x - now) >= b)
          R = (R - (x - now) - b) & 1 ? b - 1 : b - 2;
        else R += x - now;
        if (L - (x - now) <= a)
          L = (a - L + (x - now)) & 1 ? a + 1 : a + 2;
        else L -= (x - now);
        if (R < L){puts("NIE");return 0;}
        now = x;
    }
    printf("%d",(x + L) >> 1);
    return 0;
}

```

# #2.0 升

> $\mathfrak{2021.5.20\sim2021.5.31}$

## #2.1 [P2516 [HAOI2010]最长公共子序列](https://www.luogu.com.cn/problem/P2516)

**状态设计**：
 - $f_{i,j}$ 表示 $S$ 在 $1∼i$，$T$ 在 $1∼j$ 中的 LCS 长度,
 - $g_{i,j}$ 表示 $S$ 在 $1∼i$，$T$ 在 $1∼j$ 中的 LCS 个数.

讨论较为复杂，见代码。可滚动数组优化第一维。

``` cpp
const int N = 5010;
const int MOD = 1e8;
const int INF = 0x3fffffff;

char a[N],b[N];
int f[3][N],g[3][N],lena,lenb;

inline int Max(const int &x,const int &y){
    return x > y ? x : y;
}

int main(){
    scanf("%s%s",a,b);
    lena = strlen(a);lenb = strlen(b);
    for (int i = 0;i < 3;i ++) g[i][0] = 1;
    for (int i = 0;i < lenb;i ++) g[0][i] = 1;
    for (int i = 1;i < lena;i ++)
      for (int j = 1;j < lenb;j ++){
        int now = i & 1,lst = (i - 1) & 1;
          if (a[i - 1] == b[j - 1]){
              f[now][j] = f[lst][j - 1] + 1;g[now][j] = g[lst][j - 1];
              if (f[now][j] == f[lst][j]) (g[now][j] += g[lst][j]) %= MOD;
              if (f[now][j] == f[now][j - 1]) (g[now][j] += g[now][j - 1]) %= MOD;
          }
          else{
              f[now][j] = Max(f[lst][j],f[now][j - 1]);
              if (f[lst][j] > f[now][j - 1]) g[now][j] = g[lst][j];
              else if (f[lst][j] < f[now][j - 1]) g[now][j] = g[now][j - 1];
              else if (f[now][j] != f[lst][j - 1]) g[now][j] = (g[lst][j] + g[now][j - 1]) % MOD;
              else g[now][j] = (g[lst][j] + g[now][j - 1] - g[lst][j - 1]) % MOD;
          }
      }
    printf("%d\n%d",f[(lena - 1) & 1][lenb - 1],g[(lena - 1) & 1][lenb - 1]);
    return 0;
}
```

## #2.2 [P1450 [HAOI2008]硬币购物](https://www.luogu.com.cn/problem/P1450)

**状态压缩** + **容斥原理**。先不考虑限制，做完全背包，之后对于每个询问，我们枚举至少多少种硬币的数量超过限制了。数量超过限制的意思是，这种硬币至少用了$d_{i+1}$ 个，假设 $x$ 为所有你枚举出来的、钦定超过数量限制的硬币的 $(d_i+1)\cdot c_i$ 的和，那么贡献就是容斥系数乘以 ```f[s−x]``` 即可。

``` cpp
const int N = 100010;
const int INF = 0x3fffffff;

int f[N],w[5],n,ms = -INF;
int Q[N][5],A[N];

inline int Max(const int &a,const int &b){
    return a > b ? a : b;
}

signed main(){
    scanf("%lld%lld%lld%lld%lld",&w[1],&w[2],&w[3],&w[4],&n);
    for (int i = 1;i <= n;i ++){
        scanf("%lld%lld%lld%lld%lld",&Q[i][1],&Q[i][2],&Q[i][3],&Q[i][4],&Q[i][0]);
        ms = Max(ms,Q[i][0]);
    }
    f[0] = 1;
    for (int i = 1;i <= 4;i ++)
      for (int j = w[i];j <= ms;j ++)
        f[j] += f[j - w[i]];
    for (int i = 1;i <= n;i ++)
      for (int k = 0;k < 16;k ++){
          int opt = __builtin_parity(k) ? -1 : 1,x = 0;
          for (int j = 1;j <= 4;j ++)
            x += ((k >> (j - 1)) & 1) * w[j] * (Q[i][j] + 1);
          if (x > Q[i][0]) continue;
          A[i] += opt * f[Q[i][0] - x];
      }
    for (int i = 1;i <= n;i ++)
      printf("%lld\n",A[i]);
    return 0;
}
```

## #2.3 [CF864E Fire](https://www.luogu.com.cn/problem/CF864E)

-------

<div style="width=10px;line_height: 1px;">
<a href=https://www.cnblogs.com/Dfkuaid-210/p/CF864E.html style="text-decoration:none;">
      <font face="黑体" size=6>
            <b>[题解]CF864E Fire</b>
      </font>
      <font face="黑体" size=2>
            <br>&nbsp;&nbsp;发表于 2021-5-25 20:09&nbsp;Dfkuaid<br>
      </font>
      <font face="黑体" size=6>   </font>
      <font face="FangSong" size=4>
            摘要：&nbsp;CF864E 题解&nbsp;<br>
      </font>
    <p align="right">
      <font face="黑体" size=4>
          阅读全文&nbsp;&nbsp;&nbsp;<br>
          <u>&nbsp;&nbsp;&nbsp;>>&nbsp;&nbsp;&nbsp;</u>&nbsp;&nbsp;&nbsp;<br>
      </font>
    </p>
</a>
</div>

-------

## #2.4 [P4141 消失之物](https://www.luogu.com.cn/problem/P4141)

经典老题，思路明晰。

``` cpp
const int N = 2010;
const int INF = 0x3fffffff;

int n,m,w[N];
int f[N],g[N];

int main(){
    scanf("%d%d",&n,&m);
    for (int i = 1;i <= n;i ++)
      scanf("%d",&w[i]);
    f[0] = 1,g[0] = 1;
    for (int i = 1;i <= n;i ++)
      for (int j = m;j >= w[i];j --)
        (f[j] += f[j - w[i]]) %= 10;
    for (int i = 1;i <= n;i ++){
        for (int j = 1;j <= m;j ++){
            if (j < w[i]) g[j] = f[j] % 10;
            else g[j] = (f[j] - g[j - w[i]] + 10) % 10;
            printf("%d",g[j]);
        }
        putchar('\n');
    }
    return 0;
}
```

## #2.5 [P3478 [POI2008]STA-Station](https://www.luogu.com.cn/problem/P3478)

换根 DP，

**状态设计**： $g_x$ 表示以 $x$ 为根的深度之和。

我们先任选一点为根，以此为基础算出各点的父亲和子树大小，不难发现，有

$$
g_x=g_{fa_x} + N-2\cdot size_x,
$$

$N$ 为节点数，$size_x$ 表示以 $x$ 为根的子树大小。可 $\text{DFS}$ 实现。

``` cpp
#define ll long long
#define int long long
#define mset(l,x) memset(l,x,sizeof(l))

const int N = 1000010;
const int INF = 0x3fffffff;

struct Edge{
    int u,v;
    int nxt;
};
Edge e[N << 1];

int n,cnt,head[N],size[N],fa[N],h[N],f[N],rt,g[N],ans[2];

inline void add(int u,int v){
    e[cnt].u = u;
    e[cnt].v = v;
    e[cnt].nxt = head[u];
    head[u] = cnt ++;
}

inline void dfs1(int k,int p){
    size[k] = 1;fa[k] = p;h[k] = h[p] + 1;
    for (int i = head[k];i != -1;i = e[i].nxt){
        if (e[i].v == p) continue;
        dfs1(e[i].v,k);
        size[k] += size[e[i].v];
        f[k] += size[e[i].v] + f[e[i].v];
    }
}

inline void dfs2(int k){
    for (int i = head[k];i != -1;i = e[i].nxt){
        if (e[i].v == fa[k]) continue;
        g[e[i].v] = g[k] + n - 2 * size[e[i].v];
        dfs2(e[i].v);
    }
    if (ans[0] < g[k]) ans[0] = g[k],ans[1] = k;
}

signed main(){
    mset(head,-1);
    scanf("%lld",&n);
    for (int i = 1;i < n;i ++){
        int u,v;
        scanf("%lld%lld",&u,&v);
        add(u,v);add(v,u);
    }
    dfs1(rt = 1,1);
    
    g[rt] = f[rt];
    dfs2(rt);
    printf("%lld",ans[1]);
    return 0;
}
```

## #2.6 [P1879 [USACO06NOV]Corn Fields G](https://www.luogu.com.cn/problem/P1879)

基础状压。

``` cpp
#define ll long long
#define int long long
#define mset(l,x) memset(l,x,sizeof(l))

const int N = 10010;
const int MOD = 1e8;
const int INF = 0x3fffffff;

int n,m,f[20][N],line[N],ans,check[N];

signed main(){
    scanf("%lld%lld",&n,&m);
    for (int i = 1;i <= n;i ++){
        int t = 0;
        for (int j = 1;j <= m;j ++){
            scanf("%lld",&t);
            line[i] = (line[i] << 1) + (!t);
        }
    }
    for (int i = 0;i < (1 << m);i ++)
      check[i] = (i & (i >> 1)) ? 0 : 1;
    f[0][0] = 1;
    for (int i = 1;i <= n;i ++)
      for (int j = 0;j <= (1 << m) - 1;j ++){
          if (j & line[i] || !check[j]) continue;
          for (int k = 0;k <= (1 << m) - 1;k ++){
              if (k & line[i - 1] || k & j || !check[k]) continue;
              (f[i][j] += f[i - 1][k]) %= MOD;
          }
      }
    for (int i = 0;i <= (1 << m) - 1;i ++)
      (ans += f[n][i]) %= MOD;
    printf("%lld",ans);
    return 0;
}
```

## #2.7 [P2704 [NOI2001] 炮兵阵地](https://www.luogu.com.cn/problem/P2704)

基础状压。

``` cpp
const int N = 2050;
const int M = 110;
const int INF = 0x3fffffff;

int n,m,check[N],f[N][N][2],line[M],ans,T,S[N],cnt,cnt1,cnt2;

inline int Max(const int &a,const int &b){
    return a > b ? a : b;
}

int main(){
    cin >> n >> m;T = (1 << m);
    for (int i = 1;i <= n;i ++){
        char c;
        for (int j = 1;j <= m;j ++){
            cin >> c;
            line[i] = (line[i] << 1) + (c == 'H');
        }
    }
    for (int i = 0;i < (1 << m);i ++)
      S[i] = __builtin_popcount(i);
    for (int i = 0;i < (1 << m);i ++){
        check[i] = ((i & (i << 1)) || (i & (i << 2))) ? 0 : 1;
        if (!check[i] || i & line[1]) continue;
        f[0][i][1] = S[i];
    }
    for (int i = 2;i <= n;i ++)
      for (int j = 0;j < (1 << m);j ++){
          if (!check[j] || j & line[i - 1]) continue;
          for (int k = 0;k < (1 << m);k ++){
              if (!check[k] || k & line[i] || j & k) continue;
              for (int l = 0;l < (1 << m);l ++){
                  if (!check[l] || l & line[i - 2] || j & l || l & k) continue;
                  f[j][k][i % 2] = Max(f[j][k][i % 2],f[l][j][(i - 1) % 2] + S[k]);
              }
          }
      }
    for (int i = 0;i < (1 << m);i ++)
      for (int j = 0;j < (1 << m);j ++)
        ans = Max(ans,f[j][i][n % 2]);
    cout << ans;
    return 0;
}
```

## #2.8 [CF607B Zuma](https://www.luogu.com.cn/problem/CF607B)

> 贼简单的区间DP，能上蓝题纯属恶评。

**状态设计**： $f_{i,j}$ 表示删去区间 $[l,r]$ 所需的最小次数。

提前预处理每个区间是否是回文串，如果是，那么 $f_{l,r}=1.$

否则有

$$
f_{l,r} = \begin{cases}f_{l+1,r-1},\quad a_l=a_r\ 且\ r-l>1,\\\min\limits_{l\leq k< r}\{f_{l,k}+f_{k+1,r}\}.\end{cases}
$$

``` cpp
const int N = 510;
const int INF = 0x3fffffff;

int n,a[N],f[N][N],check[N][N];

inline int Min(const int &a,const int &b){
    return a < b ? a : b;
}

int main(){
    mset(f,0x3f);
    scanf("%d",&n);
    for (int i = 1;i <= n;i ++)
      scanf("%d",&a[i]);
    for (int l = 1;l <= n;l ++)
      for (int r = l + 1;r <= n;r ++)
        for (int i = 0;i <= (r - l + 1) / 2;i ++)
          if (a[l + i] != a[r - i]){check[l][r] = 1;break;}
    for (int len = 1;len <= n;len ++)
      for (int l = 1;l + len - 1 <= n;l ++){
          int r = l + len - 1;
          if (!check[l][r]){f[l][r] = 1;continue;}
          if (a[l] == a[r] && r - l > 1) f[l][r] = f[l + 1][r - 1];
          for (int k = l;k < r;k ++)
            f[l][r] = Min(f[l][r],f[l][k] + f[k + 1][r]);
      }
    printf("%d",f[1][n]);
    return 0;
}
```

# #3.0 落

五月就这样结束了，推荐生的压力已经过去，正是学 OI 的大好时光!