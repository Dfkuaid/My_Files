[TOC]

# #1.0 LIS...LCS...LCIS!

 ~看这个标题总有种“Los！Los！Los！”的错觉...~

- **最长上升子序列**（Longest Increasing Subsequence ,LIS）问题

- **最长公共子序列**（Longest Common Subsequence,LCS）问题

以上两个问题是解决 LCIS（最长公共上升子序列，Longest Common Increasing Subsequence） 问题的前置问题，建议先把以上两问题搞懂，再学习 LCIS。

下面只简单回顾上面两个问题，不展开讨论。

## #1.1 LIS 最长上升子序列

**概述：**有一个序列 $\{a_i\}$，求序列中数值单调递增的子序列最长长度。

**设计状态：** $f_i$ 表示以 $a_i$ 为结尾的LIS的长度

**转移方程：**
$$
\begin{aligned}
f_i = \max_{0\leq j < i,a_j<a_i}\{f_j+1\}
\end{aligned}
$$
**伪代码：**
$$
\begin{aligned}
&f_0 \leftarrow 0\\
&for\ i \leftarrow 1\ to\ n:\\
&\quad\quad do\ for\ j \leftarrow 0\ to\ i-1:\\
&\quad\quad\quad\quad do\ if\ a_j < a_i:\\
&\quad\quad\quad\quad\quad\quad then\ f_i \leftarrow \max\{f_i,f_j+1\}
\end{aligned}
$$
当然以上 $O(n^2)$ 算法是可以通过**二分查找**或**线段树**优化到 $O(n\log n)$ 的，不过这里不多赘述，了解啥意思就行



## #1.2 LCS 最长公共子序列

**概述：**有两个序列 $\{a_i\},\{b_j\}$，求既是 $a$ 的子序列又是 $b$ 的子序列的子序列最长长度。

**设计状态：** $f_{i,j}$ 表示 $a_1 \sim a_i$ 与 $b_i \sim b_j$ 的LCS的长度

**转移方程：**
$$
\begin{aligned}
f_{i,j} = \max\begin{cases}f_{i-1,j}\\f_{i,j-1}\\f_{i-1,j-1}+1\quad a_i=b_i\end{cases}
\end{aligned}
$$
**伪代码：**
$$
\begin{aligned}
&f_{0,0} \leftarrow 0\\
&for\ i \leftarrow 1\ to\ n\\
&\quad\quad do\ for\ j \leftarrow 0\ to\ m\\
&\quad\quad\quad\quad do\ if\ a_j = b_i\\
&\quad\quad\quad\quad\quad\quad then\ f_{i,j} = f_{i-1,j-1}+1\\
&\quad\quad\quad\quad\quad\quad else\ f_{i,j} \leftarrow \max\{f_{i-1,j},f_{i,j - 1}\}\\
\end{aligned}
$$
当然以上 $O(n^2)$ 算法改变设计的状态，同样可以通过**二分查找**或**线段树**优化到 $O(n\log n)$ 的，不过这里不多赘述，了解最朴素的啥意思就行



# #2.0 LCIS 最长公共上升子序列

简单回顾了 LIS 和 LCS，我们终于可以看今天的主角——**LCIS**了

## #2.1 状态设计 & 转移方程

### #2.1.1 设计一个优美的状态

~优美的状态：指暴力美学~

结合 LIS 和 LCS 的状态设计，我们可以强行融合升级出这样一个状态：

**$f_{i,j}$ 表示 $a_1 \sim a_i$ 和 $b_1 \sim b_j$ 中以 $b_{j}$ 为结尾的 LCIS 的长度**

非常的简洁明了，而且，这样设计状态是符合动态规划的“三个基本条件”的。

### #2.1.2 写出一个优美的方程

那么，重要问题就来了：**如何转移状态**？

假设，我们已经转移到了 $a_i$和 $b_j.$ 显然，我们只有以下两种情况：

- $a_i\ne b_j$
- $a_i=b_j$

对于第一种情况，由于状态的设计，$j$ 显然是不能变的，所以转移方程式为：
$$
\begin{aligned}
f_{i,j}=f_{i-1,j}
\end{aligned}
$$
对于相等的情况，我们要从前面的某个 $b_k(b_k < b_j)$ 转移到 $b_j$ ，所以有

$$
\begin{aligned}
f_{i,j} = \max_{0 \leq k < j \and b_k < b_j} \{f_{i-1,k}\} +1
\end{aligned}
$$

综上状态转移方程为
$$
\begin{aligned}
f_{i,j}=\begin{cases}f_{i-1,j}&a_i\ne b_j\\\max_{0 \leq k < j \and b_k < b_j} \{f_{i-1,k}\} +1&a_i=b_j\end{cases}
\end{aligned}
$$


#### #2.1.2.1 关于上面方程的部分解释

1. **为什么是从 $f_{i-1,k}$，而不是 $f_{i-2,k},f_{i-3,k},\dots$ 之中转移？** 

观察上面的式子，显然对于任意的 $f_{p-1,q}$ 来说，一定有过从 $f_{p-2,t}(0\leq t\leq q)$ 转移而来的选择

- 若 $f_{p-1,q}$ 是从 $f_{p-2,t}$ 转移而来，那么显然 $f_{p-1,q} \geq f_{p-2,t}$，即 $f_{p-1,q}$ 一定不会比 $f_{p-2,t}$ 差
- 若 $f_{p-1,q}$ 不是从 $f_{p-2,t}$ 转移而来，那么显然 $\exists f_{p-2,s} > f_{p-2,t},f_{p-1,q}=f_{p-2,s}+1$，故有 $f_{p-1,q}>f_{p-2,t}$， 即 $f_{p-1,q}$ 一定比 $f_{p-2,t}$ 更优
- 以上情况对于 $f_{p-2,t}$ 的转移同样适用

以上，可见， $f_{p,k}$ 从 $f_{p-1,q}$ 转移而来一定不会比从 $f_{s,t}(0\leq s<p-1,0\leq t\leq q)$ 差

2. **按 1. 中的证明思路，是不是直接找满足 $b_k<b_j$ 的最大的 $k$ 即可？**

**显然不是**，因为可能 $\exists b_r>b_k,b_r < b_j,f_{x,r}>f_{y,k}$，显然 $f_{y,k}$ 不会从 $f_{x,r}$ 转移，所以选择 $f_{x,r}$ 要比选 $f_{y,k}$ 更优

## #2.2 码代码

### #2.2.1 伪代码

$$
\begin{aligned}
&for\ i \leftarrow 1\ to\ n\\
&\quad\quad do\ for\ j \leftarrow 1\ to\ m\\
&\quad\quad\quad\quad do\ if\ a_i\ne b_j\\
&\quad\quad\quad\quad\quad\quad then\ f_{i,j}\leftarrow f_{i-1,j}\\
&\quad\quad\quad\quad\quad\quad else\ for\ k\leftarrow0\ to\ j-1\\
&\quad\quad\quad\quad\quad\quad\quad\quad do\ f_{i,j}\leftarrow \max\{f_{i,j},f_{i-1,k}+1\}\\
\end{aligned}
$$

 

### #2.2.2 **代码**~所以我为啥要写伪代码~

``` cpp
for (int i = 1;i <= n;i ++)
  for (int j = 1;j <= m;j ++)
    if (a[i] == b[i])
      for (int k = 0;k < j;k ++)
        f[i][j] = max(f[i][j],f[i - 1][k] + 1);
    else
      f[i][j] = f[i-1][j];

```

# #3.0 优化！优化！优化！

上面的时间复杂度大约是 $O(n^3)$ 的，显然不尽人意，那么有什么可以优化的吗？

## #3.1 从转移方程下手

当 $a_i\ne b_j$ 时的转移方程显然已经无法优化了，我们来看当 $a_i=b_j$ 时：
$$
\begin{aligned}
f_{i,j}=\max_{0\leq k<j\and b_k<b_j}\{f_{i-1,k}\}+1=\max_{0\leq k<j且b_k<a_i}\{f_{i-1,k}\}+1
\end{aligned}
$$
不难发现， 
$$
\begin{aligned}
f_{i,j}=\boxed{\max_{0\leq k<j\and b_k<a_i}\{f_{i-1,k}\}}+1
\end{aligned}
$$
加框的部分无非是为了找 $f_{i-1,k}(1\leq k<j)$ 中满足 $b_k<a_i$的最大值，那么考虑，每次当 $j$ 增加一时，$k$ 可选的范围由 $0\leq k<j$ 变为 $0\leq k<j+1$，那么仅有 $f_{i-1,j}$ 加入了待选集合，而在仅考虑 $j$ 的变化时，$i$ 可以看作是不变的量，那么我们只需要每次更新完 $f_{i,j}$ 后，检查 $f_{i-1,j}$ 能否用来更新 $f_{i,j+1}$ 即可

## #3.2 码代码

### #3.2.1 伪代码

$$
\begin{aligned}
&for\ i \leftarrow 1\ to\ n\\
&\quad\quad do\ val\leftarrow 0\\
&\quad\quad for\ j \leftarrow 1\ to\ m\\
&\quad\quad\quad\quad do\ if\ a_i=b_j\\
&\quad\quad\quad\quad\quad\quad then\ f_{i,j}\leftarrow val+1\\
&\quad\quad\quad\quad\quad\quad else\ f_{i,j}\leftarrow f_{i-1,j}\\
&\quad\quad\quad\quad if\ b_j<a_i\\
&\quad\quad\quad\quad\quad\quad then\ val\leftarrow \max\{val,f_{i-1,j}\}
\end{aligned}
$$

### #3.2.2 代码

``` cpp
for (int i = 1;i <= n;i ++){
    int val = 0;
    for (int j = 1;j <= m;j ++){
        if (a[i] == b[j])
            f[i][j] = val + 1;
        else
            f[i][j] = f[i - 1][j];
        if (b[j] < a[i])
            val = max(val,f[i - 1][j]);
    }
}
```

# #4.0 拓展

## #4.1 输出路径

惯用的手法，多采用一个数组```pre[N][M][2]```记录每一步的前驱

``` cpp
inline void path(int i,inr j){
    if (pre[i][j][0] != -1)
      path(pre[i][j][0],pre[i][j][1]);
    printf("%d ",b[j]);
}
```

但是，这样做可能会爆空间，仔细看看是不是可以优化掉一维空间

显然对于每一步，我们真正需要的不过是 ```j``` 的具体数值，因为 ```i``` 一定是依次递减的，所以并不需要存下 ```i``` 的值

```cpp
inline void path(int i,int j){
    if (pre[i][j] != -1)
      path(i - 1,pre[i][j]);
    printf("%d ",b[j]);
}

inline void solve(){
    for (int i = 1;i <= n;i ++){
        int val = 0,tmp = -1;
        for (int j = 1;j <= m;j ++){
            if (a[i] != b[j]){
                pre[i][j] = pre[i - 1][j]; //注意因为此时j相同，所以需要再找前驱
                f[i][j] = f[i - 1][j];
            }
            else{
                f[i][j] = val + 1;
                pre[i][j] = tmp;
            }
            if (b[j] < a[i]){
                if (val < f[i - 1][j]){
                    val = f[i - 1][j];
                    tmp = j;
                }
            }
        }
    }
}
```

-------

# 更新日志及说明

## 更新

> - 初次完成编辑 - $\mathfrak{2021.3.3}$

## 个人主页

欢迎到以下地址支持作者！
**Github**：[戳这里](https://github.com/Dfkuaid/)
**Bilibili**：[戳这里](https://space.bilibili.com/312728987)
**Luogu**：[戳这里](https://www.luogu.com.cn/user/162191)