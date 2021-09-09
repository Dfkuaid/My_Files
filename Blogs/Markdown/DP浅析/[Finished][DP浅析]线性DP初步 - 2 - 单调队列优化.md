[TOC]

# #0.0 前置知识

本文为**单调队列优化dp**，请确保你已熟练掌握以下知识：

---

<div style="width=10px;line_height: 1px;">
<a href=https://www.cnblogs.com/Dfkuaid-210/p/13184367.html style="text-decoration:none;">
      <font face="黑体" size=6>
            <b>[算法入门]单调队列</b>
      </font>
      <font face="黑体" size=2>
            <br>&nbsp;&nbsp;发表于 2020-6-24 14:40&nbsp;Dfkuaid<br>
      </font>
      <font face="黑体" size=6>   </font>
      <font face="FangSong" size=4>
            摘要：&nbsp;单调队列简单介绍&nbsp;<br>
      </font>
    <p align="right">
      <font face="黑体" size=4>
          阅读全文&nbsp;&nbsp;&nbsp;<br>
          <u>&nbsp;&nbsp;&nbsp;>>&nbsp;&nbsp;&nbsp;</u>&nbsp;&nbsp;&nbsp;<br>
      </font>
    </p>
</a>
</div>

---

---

# #1.0 简单介绍

## #1.1 本质 & 适用范围

运用单调队列优化dp，本质是利用**单调性**，及时**排除不可能的决策**，以保持候选集合的有效性和秩序性。

单调队列非常适合优化决策取值范围的**上、下界均单调变化**，每个决策在候选集合中**插入或删除至多一次**

## #1.2 适用方程 & 条件

可以使用单调队列的状态转移方程大多可归为如下形式：
$$
\begin{aligned}
f_i=\min_{L(i)\leq j\leq R(i)}\{f_j+val(i,j)\}
\end{aligned}
$$
其中 $L(i)$ 和 $R(i)$ 是两个关于 $i$ 的一次函数，限制了 $j$ 的取值范围，$val(i,j)$ 是一个关于 $i,j$ 的多项式函数。

**条件：**

- 多项式 $val(i,j)$ 的每一项仅与 $i$ 和 $j$ 中的一个有关

直接上例题

# #2.0 例题讲解

## #2.1 [P3572 [POI2014]PTA-Little Bird](https://www.luogu.com.cn/problem/P3572)

### #2.1.1 关于题面

题面的翻译少给了很重要的一句：

**小鸟从第一棵树开始跳跃** (**On top of the first one**, there is a little bird who ...)

### #2.1.2 朴素算法

相信不难写出本题的状态转移方程：
$$
\begin{aligned}
f_i = \min_{i-k\leq j<i}\{f_j+[a_j\leq a_i]\}
\end{aligned}
$$
**伪代码**：
$$
\begin{aligned}
&f_1 \leftarrow 0\\
&\text{For }i \leftarrow2\text{ to }n\\
&\quad\quad \text{do For }j\leftarrow i-k\text{ to }i-1\text{ by }1\text{ do}\\
&\quad\quad\quad\quad f_i\leftarrow\min\{f_i,f_j+(a_j<=a_i)\ ?\ 1:0\}\\
&\quad\quad \text{End}
\end{aligned}
$$

### #2.1.3 单调性分析

观察 $j$ 的取值范围：
$$
\begin{aligned}
i-k\leq j<i
\end{aligned}
$$
当 $i$ 增加 $1$ 时，$j$ 的范围的上界与下界均增加 $1$，也就意味着每次只有一个新的决策 $f_i$ 加入候选集合，最多一个旧的决策 $f_{i-k}$ 被排除候选集合，显然，候选集合中下标应是**单调递增**的，这一点无需格外关注

显然，我们希望每一次得到的决策 $f_j$ 应该是候选集合中**最小的**，也就是说，如果有决策 $f_p,f_q,p<q<i,f_p>f_q$ ，显然 $f_q$ 比 $f_p$ 更优，因为 $f_q$ 比 $f_p$ 在候选集合中可持续的时间更长，且贡献的 $f$ 值更小，那么 $f_p$ 显然是无用的，可以直接放弃，因此，我们应该维护候选集合中 $f_j$ **单调递增**

那如果 $f_p=f_q$ 呢？显然我们选**高度更高的**，即 $a$ 更大的更优

- 因为假设 $a_p<a_q$
  - 如果 $a_p<a_q\leq a_i$ ，两者都需要加一，所以两者的贡献是相同的，而 $p<q$，这意味着 $q$ 可以在队列中保存更长时间，那么选 $p$ 显然就可以直接丢弃
  - 若 $a_p\leq a_i<a_q$，显然选择 $a_q$ 得到的结果更优
  - 若 $a_i<a_p<a_q$，无论选 $p$ 还是 $q$ 得到的结果都相同，而 $p<q$，这意味着 $q$ 可以在队列中保存更长时间，那么选 $p$ 显然就可以直接丢弃
- 若 $a_p=a_q$，显然无论如何 $p$ 与 $q$ 的贡献都是相同的， $p<q$，这意味着 $q$ 可以在队列中保存更长时间，那么选 $p$ 显然就可以直接丢弃
- **但是**，如果 $a_p>a_q$，$a_q$ 仍然**有可能是后面转移的最优决策**（当 $p$ 已经超出范围时，$q$ 仍然有可能在范围内且是最优决策）

所以应维护候选集合中**当 $f_j$ 相等时， $a_j$ 单调递减**

综合以上的结论，决策的选择是存在单调性的，我们可以维护一个如下的单调队列 

-  $f_j$ **单调递增**
- **当 $f_j$ 相等时， $a_j$ 单调递减**

### #2.1.4 码代码

``` cpp
const int N = 1000010;
const int INF = 0x3fffffff;

int n,k,t,a[N],f[N],q[N];

int main(){
    scanf("%d",&n);
    for (int i = 1;i <= n;i ++)
      scanf("%d",&a[i]);
    scanf("%d",&t);
    while (t --){
        scanf("%d",&k);
        int frt = 0,tal = -1; //清空队列
        q[++ tal] = 1; //加入初始候选决策
        for (int i = 2;i <= n;i ++){
            while (frt <= tal && q[frt] + k < i)
              frt ++; //去掉超出范围的
            f[i] = f[q[frt]] + (a[q[frt]] <= a[i]); //转移
            while (frt <= tal && ((f[q[tal]] > f[i]) || (f[q[tal]] == f[i] && a[q[tal]] <= a[i])))
              tal --; //从队尾维护单调性,将新决策入队
            q[++ tal] = i; 
        }
        cout << f[n] << endl;
    }
    return 0;
}
```

## #2.2 [P3089 [USACO13NOV]Pogo-Cow S](https://www.luogu.com.cn/problem/P3089)

### #2.2.1 朴素算法

首先，不难想到，最大得分一定是从一端开始，一直向一个方向跳跃，所以我们上来就需要一个 ```sort()``` 对数据进行排序，又因为有两个方向，所以要进行两次DP

设 $f_{i,j}$ 表示最后一步从 $j$ 到 $i$ 的最大得分

不难写出转移方程：
$$
\begin{aligned}
f_{i,j} = \max_{k<j<i\and x_j-x_k\leq x_i-x_j}\{f_{j,k}\}+p_i
\end{aligned}
$$
**代码：**

``` cpp
const int N = 1010;
const int INF = 0x3fffffff;

struct Node{
    int p;
    int a;
};
Node s[N];

int n,sum[N],f[N][N],ans;

int cmp(const Node x,const Node y){
    return x.p < y.p;
}

int main(){
    scanf("%d",&n);
    for (int i = 1;i <= n;i ++)
      scanf("%d%d",&s[i].p,&s[i].a);
    sort(s + 1,s + n + 1,cmp);
    for (int i = 1;i <= n;i ++)
      f[i][i] = s[i].a;
    for (int i = 1;i <= n;i ++)
      for (int j = 1;j < i;j ++){
          for (int k = 1;k <= j;k ++)
            if (s[j].p - s[k].p <= s[i].p - s[j].p)
              f[i][j] = max(f[i][j],f[j][k] + s[i].a);
          ans = max(ans,f[i][j]);
      }
    mset(f,0);
    for (int i = 1;i <= n;i ++)
      f[i][i] = s[i].a;
    for (int i = n;i >= 1;i --)
      for (int j = n;j > i;j --){
          for (int k = n;k >= j;k --)
            if (s[k].p - s[j].p <= s[j].p - s[i].p)
              f[i][j] = max(f[i][j],f[j][k] + s[i].a);
          ans = max(ans,f[i][j]);
      }
    cout << ans;
    return 0;
}
```

### #2.2.2 单调性分析

观察转移方程
$$
\begin{aligned}
f_{i,j} = \boxed{\max_{k<j<i\and x_j-x_k\leq x_i-x_j}\{f_{j,k}\}}+p_i
\end{aligned}
$$
加框的部分是在求 $f_{j,k}$ 的最大值，考虑可不可以采用单调性优化，不难发现，数列 $\{x_k\}$ 本身便是一个具有单调性的数列，当 $j$ 不变时，$i$ 增加一，转移方程为
$$
\begin{aligned}
f_{i+1,j} = \max_{k<j<i+1\and x_j-x_k\leq x_{i+1}-x_j}\{f_{j,k}\}+p_{i+1}
\end{aligned}
$$
$k$ 的取值范围 $1\leq k<j$ 没有变化，只是满足 $x_j-x_k\leq x_{i+1}-x_j$ 的 $k$ 可能增多了，而且，显然若 $x_j-x_p\nleq x_{i+1}-x_j$，对于 $q<p$ 则必然有 $x_j-x_q\nleq x_{i+1}-x_j$，这就相当于直接存在一个不需要出队的单调队列，因为数列 $\{x_k\}$ 本身便是一个具有单调性的数列，我们只需记录下当前满足 $x_j-x_k\leq x_{i+1}-x_j$ 的最小的 $k$，保存该区间内最大值，下一次从 $k+1$ 开始更新即可，**注意**，由于这里是 $i$ 增加一，$j$ 不变的情况，所以要将 $j$ 的变化放在外层循环，$i$ 在内层

### #2.2.3 码代码

``` cpp
const int N = 1010;
const int INF = 0x3fffffff;

struct Node{
    int p;
    int a;
};
Node s[N];

int n,sum[N],f[N][N];

int cmp(const Node x,const Node y){
    return x.p < y.p;
}

int main(){
    scanf("%d",&n);
    for (int i = 1;i <= n;i ++)
      scanf("%d%d",&s[i].p,&s[i].a);
    sort(s + 1,s + n + 1,cmp);
    int ans = 0;
    for (int j = 1;j < n;j ++){
        int k = j;
        f[j][j] = s[j].a;
        for (int i = j + 1;i <= n;i ++){
            f[i][j] = f[i - 1][j] - s[i - 1].a; //显然上一次转移的值必然是上个区间最大值
            while (k && s[j].p - s[k].p <= s[i].p - s[j].p)
              f[i][j] = max(f[i][j],f[j][k --]);
            f[i][j] += s[i].a;
            ans = max(ans,f[i][j]);
        }
    }
    mset(f,0);
    for (int j = n;j > 1;j --){ //别忘了求两次，顺序反过来
        int k = j;
        f[j][j] = s[j].a;
        for (int i = j - 1;i >= 1;i --){
            f[i][j] = f[i + 1][j] - s[i + 1].a;
            while (k <= n && s[k].p - s[j].p <= s[j].p - s[i].p)
              f[i][j] = max(f[i][j],f[j][k ++]);
            f[i][j] += s[i].a;
            ans = max(ans,f[i][j]);
        }
    }
    cout << ans;
    return 0;
}
```



# #3.0 单调队列优化多重背包

## #3.1 分析

我们先来考虑最朴素的多重背包问题解法

状态转移方程为
$$
\begin{aligned}
f_j=\max_{1\leq cnt \leq c_i}\{f_{j-cnt\times v_i}+cnt\times W_i\}
\end{aligned}
$$
伪代码：
$$
\begin{aligned}
&\text{For }i\leftarrow1\text{ to }n\\
&\quad\quad \text{do For }j\leftarrow M\text{ to }v_i\text{ by }-1\text{ do}\\
&\quad\quad\quad\quad \text{do For }cnt\leftarrow 1\text{ to }c_i\\
&\quad\quad\quad\quad\quad\quad \text{If }cnt\times v_i<j\\
&\quad\quad\quad\quad\quad\quad\quad\text{then }f_{j}\leftarrow\max\{f_j,f_{j-cnt\times v_i}+cnt\times w_i\}\\
&\quad\quad\quad\quad\quad\quad\quad\text{else }break\\
&\quad\quad\quad\quad\text{End}
\end{aligned}
$$

我们来看一下能够转移到状态 $j$ 的决策候选集合，为 $\{j-cnt\times v_i|1\leq cnt\leq c_i\}$

再看一下能够转移到 $j-1$ 的候选集合，为 $\{j-cnt\times v_i-1|1\leq cnt\leq c_i\}$

显然这两个集合没有交集，无法快速地从 $j$ 的决策集合转移到 $j-1$ 的决策集合

那么，我们从最内层循环向外一层，观察 $cnt$ 对 $j$ 的决策集合的影响

当 $cnt$ 加一时，状态 $j-v_i$ 的决策候选集合为 $\{j-(cnt+1)\times v_i|1\leq cnt+1\leq c_i\}$ 

如下图：

![](https://img.imgdb.cn/item/60461f83cef1ec5e6f9e6edd.png)

显然，如果我们把状态 $j$ 按照按照以模 $v_i$ 的余数 $u$ 分组，令 $p\in[0,\lfloor\dfrac{M-u}{v_i}\rfloor]$，倒序循环，每一组的决策候选集合是可以快速推出的，新的状态转移方程：
$$
\begin{aligned}
f_{u+p\times v_i}&=\max_{p-c_i\leq k\leq p-1}\{f_{u+k\times v_i}+(p-k)\times w_i\}\\
&=\max_{p-c_i\leq k\leq p-1}\{f_{u+k\times v_i}-k\times w_i+p\times w_i\}
\end{aligned}
$$
显然，如果我们想要得到的结果尽可能大，就需要决策 $k$ 的 $f_{u+k\times v_i}-k\times w_i$ 尽可能大

那么当 $p$ 减小一时，$k$ 的取值范围上下界均减小一，我们需要一个 $k$ 单调递减，$f_{u+k\times v_i}-k\times w_i$ **单调递减**的单调队列，每次按照单调队列的基本操作进行维护即可

## #3.2 码代码

``` cpp
const int N = 100010;
const int INF = 0x3fffffff;

int n,m;
int v[N],w[N],c[N];
int f[N],q[N];

inline int val(int i,int u,int k){
    return f[u + k * v[i]] - k * w[i];
}

int main(){
    scanf("%d%d",&n,&m);
    for (int i = 1;i <= n;i ++){
        scanf("%d%d%d",&w[i],&v[i],&c[i]);
        for (int u = 0;u < v[i];u ++){
            int l = 0,r = -1;
            int maxp = (m - u) / v[i];
            for (int k = maxp - 1;k >= max(maxp - c[i],0);k --){
                while (l <= r && val(i,u,q[r]) <= val(i,u,k))
                  r --;
                q[++ r] = k;
            }
            for (int p = maxp;p >= 0;p --){
                while (l <= r && q[l] > p - 1)
                  l ++;
                if (l <= r)
                  f[u + p * v[i]] = max(f[u + p * v[i]],val(i,u,q[l]) + p * w[i]);
                if (p - c[i] - 1 >= 0){
                    while (l <= r && val(i,u,q[r]) <= val(i,u,p - c[i] - 1))
                      r --;
                    q[++ r] = p - c[i] - 1;
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0;i <= m;i ++)
      ans = max(ans,f[i]);
    cout << ans;
    return 0;
}
```



