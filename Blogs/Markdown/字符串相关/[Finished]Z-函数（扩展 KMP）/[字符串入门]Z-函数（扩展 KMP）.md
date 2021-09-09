> 一个小约定：下文中的所有字符串下标都从 $0$ 开始。

# #1.0 什么是 Z-函数

对于一个长度为 $n$ 的字符串 $S$，定义函数 $z(i)$ 表示 $S[i,n-1]$，即以 $S[i]$ 开头的后缀，与 $S$ 的最长相同前缀（$\texttt{Longest Common Prefix, LCP}$）的长度，特别地，我们定义 $z(0)=0$。$z$ 被称为 $S$ 的 **Z-函数**。

别看它还有另一个名字**扩展 KMP**，但是实际上 [$\texttt{KMP}$](https://www.cnblogs.com/Dfkuaid-210/p/KMP.html) 算法与 $\tt{Z}$-函数除了*看起来*思想上很像，$\tt{Z}$-函数比 $\tt{KMP}$ 能实现的功能好像多一点外，没有任何联系。

# #2.0 求解 Z-函数

## #2.1 朴素算法

$$
\begin{aligned}
&\text{Procedure}\ Brute\_Force(s:string)\\
1.\ &\quad len\gets length(s)\\
2.\ &\quad\text{Set all elements in }z\text{ to }0\\
3.\ &\quad\textbf{For }i\text{ to }len-1\\
4.\ &\quad\qquad\textbf{While }i+z[i]<n\text{ and }s[z[i]]=s[i+z[i]]\\
5.\ &\quad\qquad\qquad z[i]\gets z[i]+1\\
\end{aligned}
$$

很显然，上面的做法是 $O(n^2)$ 的。

## #2.2 线性算法

这里有一个思想与 $\tt{KMP}$ 有些类似：**运用之前已有的状态加速计算当前状态。**这种思想在 [$\tt{Manacher}$](https://www.cnblogs.com/Dfkuaid-210/p/manacher.html) 算法等许多字符串算法中同样有体现。

我们假设当前已经计算出了 $z(0),z(1),\cdots,z(i-1)$ ，现在来考虑如何计算 $z(i).$

先来定义几个概念：

- **匹配段（Z-Box）**：对于 $x$，我们称 $[x,x+z(x)-1]$ 为 $x$ 的匹配段；
- 记当前右端点最靠右的匹配段为 $[l,r].$

在计算 $z(i)$ 过程中，保证 $l\leq i$。初始时 $l=r=0$。

如果当前 $i\leq r$，那么根据 $z$ 的定义有 $S[l,r]=S[0,r-l]$，所以有 $S[i,r]=S[i-l,r-l]$，那么 $S[i,n-1]$ 与 $S$ 的 $\tt{LCP}$ 长度 $z(i)$ 只有以下可能：

1. 当 $z(i-l)<r-i+1$ 时，$z(i)=z(i-l)$。

   来看下面这张图，我们知道根据 $z$ 的定义，应当有 $S[i-l,i-l+z(i-l)-1]=S[0,z[i-l]-1]$，而又有 $S[i,r]=S[i-l,r-l]$，所以如果 $z(i-l)<r-i+1$，意味着相同前缀的长度不可能超过 $z(i-l)$，否则与 $z(i-l)$ 的定义相悖。

![](https://pic.imgdb.cn/item/60e118c85132923bf82d7baf.png)

2. 当 $z(i-l)\geq r-i+1$ 时，应当先令 $z(i)=r-i+1$，再尽可能地向后扩展。

   如同下面这张图，我们只能确定 $S[i,r]=S[i-l,r-l]$ 相同，后面的无法确定。

![](https://pic.imgdb.cn/item/60e11c1e5132923bf843fb20.png)

当 $i>r$ 时，我们无法用已知状态进行转移，只能暴力向后扩展。

结束当前计算后，我们检查是否有 $i+z(i)-1>r$，如果是，那么更新 $[l,r].$

于是得到代码：

``` cpp
inline void z_func() {
    for (int i = 1, l = 0, r = 0; i < lenb; ++ i) {
        if (i <= r && z[i - l] < r - i + 1)
          z[i] = z[i - l];
        else {
            /*注意进入 else 的可能时 r < i 的情况，
            所以下面的 z[i] 应当取 Max(0, r - i + 1)*/
            z[i] = Max(0, r - i + 1);
            while (i + z[i] < lenb && b[z[i]] == b[i + z[i]])
              ++ z[i]; //尽可能向后扩展。
        }
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
        /*更新 [l,r] 的范围*/
    }
}
```

# #3.0 Z-函数的应用

## #3.1 [LG P5410 扩展 KMP（Z 函数）](https://www.luogu.com.cn/problem/P5410)

~~并不知道该给这种应用起什么名字。~~

- 操作一就是基础的 $\tt{Z}$-函数，只不过要注意需要单独处理 $z(0)$，显然是 $b$ 的长度。

- 操作二与 $\tt Z$-函数的定义十分相似，所以依旧考虑使用已经求出的 $z$ 进行加速求解。

整体的讨论与上面没有任何区别，这里略去不写。注意仍需单独处理。

``` cpp
const int N = 20000100;
const int INF = 0x3fffffff;

int lena, lenb, z[N], p[N];
ll ans1, ans2;
string a, b;

template <typename T>
inline T Max(const T a, const T b) {
    return a > b ? a : b;
}

template <typename T>
inline T Min(const T a, const T b) {
    return a < b ? a : b;
}

inline void z_func() {
    for (int i = 1, l = 0, r = 0; i < lenb; ++ i) {
        if (i <= r && z[i - l] < r - i + 1)
          z[i] = z[i - l];
        else {
            z[i] = Max(0, r - i + 1);
            while (i + z[i] < lenb && b[z[i]] == b[i + z[i]])
              ++ z[i];
        }
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
}

inline void p_func() {
    for (int i = 1, l = 0, r = 0; i < lena; ++ i) {
        if (i <= r && z[i - l] < r - i + 1)
          p[i] = z[i - l];
        else {
            p[i] = Max(0, r - i + 1);
            while (i + p[i] < lena && b[p[i]] == a[i + p[i]])
              ++ p[i];
        }
        if (i + p[i] - 1 > r) l = i, r = i + p[i] - 1;
    }
    while (p[0] < Min(lena, lenb) && b[p[0]] == a[p[0]]) p[0] ++;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cin >> a >> b;
    lena = a.length(), lenb = b.length();
    z_func(); z[0] = lenb; p_func();
    for (int i = 0; i < lenb; i ++)
      ans1 ^= ((ll)(i + 1) * (z[i] + 1));
    for (int i = 0; i < lena; i ++)
      ans2 ^= ((ll)(i + 1) * (p[i] + 1));
    printf("%lld\n%lld", ans1, ans2);
    return 0;
}
```

## #3.2 模式串匹配

用 $\tt Z$ 函数做模式串匹配很简单，将要寻找的串凭借在文本串前，两者中间用 `#` 等不会在两个串中出现的字符连接，求出新串的 $\tt Z$ 函数，枚举每个位置上的 $z$，如果 $z[i]$ 等于模式串的长度，那么该位置存在我们要找的模式串。

中间的 `#` 是为了保证匹配的最大长度不会超过模式串的长度。

正确性显然。



# 参考资料

[1] [Z 函数（扩展 KMP） - OI Wiki](https://oi-wiki.net/string/z-func/)

[2] [Z函数(扩展KMP)&前缀函数的总结~ - NuoCarter](https://www.cnblogs.com/NuoCarter/p/14470033.html)

