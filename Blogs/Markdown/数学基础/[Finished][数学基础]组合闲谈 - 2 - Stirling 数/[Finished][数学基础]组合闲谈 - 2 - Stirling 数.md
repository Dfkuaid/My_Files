# #1.0 第一类 Stirling 数

<div id='definition-1'></div>

## #1.1 定义

对于正整数 $n,k$，定义 $c(n,k)$ 为 $n$ 元对称群 $S_n$ 中恰含 $k$ 个轮换（即可恰写成 $k$ 个不交轮换的乘积）的置换个数（注意，不动点也看做一个轮换）。称 $s(n,k)=(-1)^{n-k}c(n,k)$ 为第一类 $\text{Stirling}$ 数，也常常称 $c(n,k)$ 为无符号的第一类 $\text{Stirling}$ 数。

置 $c(0,0)=1$，以及当 $n\geqslant1$ 时，$c(n,0)=c(0,n)=0.$

## #1.2 补充点抽代

上面的定义涉及到了亿点点抽象代数的知识，这里简单讲讲。

### #1.2.1 群

如果一个非空集合 $G$ 上定义了一个二元运算 $\circ$，满足：

1. **结合律**：$(a\circ b)\circ c=a\circ(b\circ c)\ (\forall\ a,b,c\in G)$；
2. 存在 **幺元**：存在 $e\in G$ 使得

$$
e\circ a=a\circ e=a\ (\forall\ a\in G)
$$

（$e$ 称为 $G$ 的幺元）；

3. 存在 **逆元**：对任意的 $a\in G$，存在 $b\in G$ 使得

$$
a\circ b=b\circ a=e
$$

（$b$ 称为 $a$ 的逆元）；

则称 $G$ 关于运算 $\circ$ 构成一个**群**，记为 $(G,\circ)$，或简记为 $G.$

注意，群 $G$ 中不一定满足交换律，如果群 $G$ 满足交换律：

$$
a\circ b=b\circ a\ (\forall\ a,b\in G),
$$

则称 $G$ 为**交换群**或 **$\text{Abel}$ 群**。

### #1.2.2 全变换群

> 这里的部分可以结合下面的 [对称群]() 进行理解。

设 $M$ 是一个非空集合，$M$ 到自身的双射的全体对于映射的乘法（即复合）构成一个群，叫做 $M$ 的全变换群，记为 $S(M).$

### #1.2.3 对称群

设 $M$ 是含有 $n$ 个元素的集合，$M$ 的全变换群 $S(M)$ 称为 $n$ 级**对称群**，记为 $S_n.$

$S_n$ 的元素称为 **$n$ 元置换**。

举个例子，我们设 $M=\{1,2,\cdots,n\}$，任一置换 $\sigma$ 可以用列表的方式表示，即：如果 $\sigma(j)=\sigma_j$，则记

$$
\sigma=\begin{pmatrix}1&2&\cdots&n\\\sigma_1&\sigma_2&\cdots&\sigma_n\end{pmatrix}.
$$

可以看出，$\sigma_1,\sigma_2,\cdots,\sigma_n$ 是 $1,2,\cdots,n$ 的一个排列。

来考虑一种特殊的置换：设 $\sigma\in S_n,i_1,i_2,\cdots,i_t\in\{1,2,\cdots,n\}$，如果 $\sigma(i_1)=i_2,\sigma(i_2)=i_3,\cdots,\sigma(i_{t-1})=i_t,\sigma(i_t)=i_1$，且 $i_1,i_2,\cdots,i_t$ 之外的元素在 $\sigma$ 下都保持不变，则称 $\sigma$ 为 $i_1,i_2,\cdots,i_t$ 的轮换，记为 $(i_1,i_2,\cdots,i_t)$，$t$ 称为轮换 $\sigma$ 的长度。

看一张形象的图：

![](https://pic.imgdb.cn/item/60c45317844ef46bb21bd88c.png)

> 图中 $a\to b$ 表示 $\sigma(a)=b.$

上图中，$(1,3,4)$ 是一个长度为 $3$ 的轮换。

![](https://pic.imgdb.cn/item/60c45317844ef46bb21bd89e.png)

上图中的置换可看做是 $(1,3,4)$ 和 $(2,5)$ 这两个不交轮换的乘法（即复合）的结果。

## #1.3 性质

补充完这么多抽代的知识，相信再看上面的定义就不难理解了，下面来看它的几个性质。

### #1.3.1 递推关系

对于这种特殊的数列，我们首先想要知道的肯定是他的递推式以及通项公式，我们先来看递推式。

来看第 $n$ 个元素的归属。设 $\sigma$ 是 $S_n$ 中恰有 $k$ 个轮换的置换。

若 $\sigma(n)=n$，那么 $n$ 是一个单独的轮换，所以剩下的 $n-1$ 个元素应当恰好包含 $k-1$ 个轮换，所以这样的置换应当有 $c(n-1,k-1)$ 个。

若 $\sigma(n)=m\ (n\ne m)$，也就意味着 $n$ 不是一个单独的轮换，所以前 $n-1$ 个元素仍应恰好包含 $k$ 个轮换，也就是 $c(n-1,k)$。但这就够了吗？不够。因为 $\sigma(n)$ 显然还有 $n-1$ 种不同的可能，所以这样应当总共有 $(n-1)\cdot c(n-1,k)$ 种不同的置换。

综合上面两种情况的讨论，我们能得到：

**对任意 $n\geq1,\ k\geq1,\ c(n,k)$ 满足递推关系**

$$
c(n,k)=(n-1)c(n-1,k)+c(n-1,k-1).
$$

### #1.3.2 性质 1

$\{c(n,k)\}_{n=1}^\infty$ 满足如下的函数方程：

$$
\sum\limits_{k=1}^nc(n,k)x^k=x(x+1)\cdots(x+n-1).\tag1
$$

**证明**：

对 $n$ 用归纳法进行证明。当 $n=1$ 时，命题即 $x=x$，显然成立。

设 $n\geq2$，且命题对 $n-1$ 成立，则对 $n$，由归纳假设及 $c(n,k)$ 的递推性质知，对任意 $1\leq k\leq n$，有

$$
\begin{aligned}
&[x^k]x(x+1)\cdots(x+n-1)\\
=&[x^k]x(x+1)\cdots(x+n-2)x+(n-1)([x^k]x(x+1)\cdots(x+n-2))\\
=&[x^{k-1}]x(x+1)\cdots(x+n-2)+(n-1)([x^k]x(x+1)\cdots(x+n-2))\\
=&c(n-1,k-1)+(n-1)c(n-1,k)=c(n,k)
\end{aligned}
$$

从而

$$
\sum\limits_{k=1}^nc(n,k)x^k=x(x+1)\cdots(x+n-1),
$$

即命题对 $n$ 成立。

<div align=right>证毕.</div>

对上面证明的部分说明：

- $[x^k]$ 指的是取后面的多项式中 $x^k$ 项的系数。

### #1.3.3 性质 2

$\{s(n,k)\}_{n=1}^\infty$ 满足如下的函数方程：

$$
\sum\limits_{k=1}^ns(n,k)x^k=x^{\underline n}=x(x-1)\cdots(x-n+1).
$$

**证明**：

在 $(1)$ 中，用 $-x$ 代替 $x$，得

$$
\sum\limits_{k=1}^nc(n,k)(-x)^k=(-x)(-x+1)\cdots(-x+n-1),
$$

上式两端同乘 $(-1)^n$，得

$$
\sum\limits_{k=1}^n(-1)^nc(n,k)(-1)^k=x(x-1)\cdots(x-n+1),
$$

回顾 [第一类 Stirling 数的定义](#definition-1) 知上式即

$$
\sum\limits_{k=1}^ns(n,k)x^k=x(x-1)\cdots(x-n+1)=x^{\underline n}.
$$

<div align=right>证毕.</div>

# #2.0 第二类 Stirling 数

<div id='definition-2'></div>

## #2.1 定义

对于正整数 $n,k$，定义 $S(n,k)$ 为把 $[n]$（含有 $n$ 个元素的集合）分成 $k$ 个非空子集的划分个数，称之为**第二类 $\text{Stirling}$ 数**。

置 $S(n,0)=S(0,n)=0(n\geq1)$ 及 $S(0,0)=1.$

第二类 $Stirling$ 数的定义要简单很多，没有任何需要补充的知识，这很好 ~~（不用再多敲那么多东西）~~。

## #2.2 性质

比较一下 [第一类 Stirling 数的定义](#definition-1) 和 [第二类 Stirling 数的定义](#definition-2)，发现有着惊人的相似度，那么他们在性质上是不是也相似呢？是的，听我慢慢道来。

### #2.2.1 递推关系

> 把 $[n]$ 分成 $k$ 个非空子集的划分简称为 $k$-划分。

同样考虑第 $n$ 个元素的归属。设 $P$ 是 $[n]$ 的一个 $k$-划分。

若 $n$ 在 $P$ 中是一个单独的子集，所以剩下的 $n-1$ 个元素应当恰好被分成 $k-1$ 个子集，所以这样的划分应当有 $S(n-1,k-1)$ 个。

若 $n$ 不是一个单独的子集，所以前 $n-1$ 个元素仍应恰好被分成 $k$ 个子集，也就是 $S(n-1,k)$。但这就够了吗？不够。因为 $n$ 所处的集合显然还有 $k$ 种不同的可能，所以应当总共有 $k\cdot S(n-1,k)$ 种不同的划分。

综合上面两种情况的讨论，我们能得到：

**对任意 $n\geq1,\ k\geq1,\ S(n,k)$ 满足递推关系**

$$
S(n,k)=kS(n-1,k)+S(n-1,k-1).
$$

~~上面的过程不能说很像，只能说是一模一样。~~

### #2.2.2 性质 1

$\{S(n,k)\}_{n=1}^\infty$ 满足如下的函数方程：

$$
\sum\limits_{k=1}^nS(n,k)x^{\underline k}=x^n,
$$

这里 $x^{\underline k}=x(x-1)\cdots(x-k+1)$，叫做**下降幂**，也写作 $(x)_n.$

**证明**：

对 $n$ 用归纳法进行证明。当 $n=1$ 时，命题即 $x=x$，显然成立。

设 $n\geq2$，且命题对 $n-1$ 成立，则对 $n$，由归纳假设及 $S(n,k)$ 的递推性质知

$$
\begin{aligned}
x^n=&x^{n-1}x=\sum\limits_{k=1}^{n-1}S(n-1,k)x^{\underline k}x\\
=&\sum\limits_{k=1}^{n-1}S(n-1,k)x^{\underline k}(x-k+k)\\
=&\sum\limits_{k=1}^{n-1}S(n-1,k)x^{\underline{k+1}}+\sum\limits_{k=1}^{n-1}kS(n-1,k)x^{\underline k}\\
=&\sum\limits_{k=2}^{n}S(n-1,k-1)x^{\underline k}+\sum\limits_{k=1}^{n-1}kS(n-1,k)x^{\underline k}\\
=&\sum\limits_{k=1}^{n}S(n-1,k-1)x^{\underline k}+\sum\limits_{k=1}^{n}kS(n-1,k)x^{\underline k}\\
=&\sum\limits_{k=1}^nS(n,k)x^{\underline k}.
\end{aligned}
$$

即命题对 $n$ 成立。

<div align=right>证毕.</div>

### #2.2.3 显式公式

对任意正整数 $n,k$，有

$$
S(n,k)=\dfrac{1}{k!}\sum\limits_{j=0}^k\dbinom{k}{j}j^n(-1)^{k-j}.
$$

**证明**：

假设有 $k$ 个不同的篮子，将 $[n]$ 中的元素分到这 $k$ 个**不同的**篮子里，篮子中可以为空，用 $S$ 表示所有这样的分法组成的集合，显然 $|S|=k^n$，对任意 $1\leq i\leq k$，定义 $P_i$ 为性质 “第 $i$ 个篮子是空的”,$A_i$ 为 $S$ 中满足性质 $P_i$ 的分法组成的集合，$\mathcal P$ 为所有这些性质组成的集合，则

$$
\begin{aligned}
S(n,k)&=\dfrac{|\{A\in S\ |\ A\ 不满足\ \mathcal P\ 中的任何性质\}|}{k!}\\
&=\dfrac{|\overline{A_1}\cap\overline{A_2}\cap\cdots\cap\overline{A_k}|}{k!}
\end{aligned}
$$


先来讲讲上面的部分：

上面柿子中 $\overline{A_i}$ 表示 $A_i$ 在 $S$ 中的补集。

$k!$ 从哪来？注意到，我们这里构造的篮子是不同的，所以就导致统计出的是包含顺序的，但回顾 [第二类 Stirling 数的定义](#definition-2) 发现，第二类 $\text{Stirling}$ 数所划分的集合是不同的，因而不应有顺序，除以 $k!$。

注意到对于任意 $1\leq i_i<i_2<\cdots<i_s\leq k,\ A_{i_1}\cap A_{i_{2}}\cap\cdots\cap A_{i_{s}}$ 表示的意义是 $S$ 中满足性质 $P_{i_1},P_{i_2},\cdots,P_{i_s}$ 的分法组成的集合。在这些分法中，标号为 $i_1,i_2,\cdots,i_s$ 的篮子为空，所有的元素只能放进其余的 $k-s$ 个篮子中，从而 $|A_{i_1}\cap A_{i_{2}}\cap\cdots\cap A_{i_{s}}|=(k-s)^n$。考虑容斥，得

$$
\begin{aligned}
k!S(n,k)=&|S|-\sum\limits_i|A_i|+\sum\limits_{1\leq i<j\leq k}|A_i\cap A_j|\\
&-\sum\limits_{1\leq i<j<t \leq k}|A_i\cap A_j\cap A_t|\\
&+\cdots+(-1)^k|A_1\cap A_1\cap\cdots\cap A_k|\\
=&\sum\limits_{r=0}^k\dbinom{k}{r}(k-r)^n(-1)^r\\
=&\sum\limits_{j=0}^k\dbinom{k}{j}j^n(-1)^{k-j}.
\end{aligned}
$$

上面柿子的最后一步是令 $j=k-r$ 得到。

<div align=right>证毕.</div>

# #3.0 融合——

现在我们已经对第一类、第二类 $\text{Stirling}$ 数作了了解，现在让我们来找一找他们之间的联系，并发掘一些有趣的性质吧/se/se/se

## #3.1 二者联系

### #3.1.1 联系一

由两类 $\text{Stirling}$ 数，定义 $n$ 阶矩阵 $\bold A=(a_{ij})_{n\times n}:=(s(i,j))_{n\times n}$ 及 $\bold B=(b_{ij})_{n\times n}:=(D(i,j))_{n\times n}$，则

$$
\bold{AB=BA=I}.
$$

由此可得推论

$$
\sum\limits_{l=1}^ns(i,l)S(l,j)=\delta(i,j),\\
\sum\limits_{l=1}^nS(i,l)s(l,j)=\delta(i,j),\\
\\
\delta(i,j)=\begin{cases}1,\quad i=j,\\0,\quad i\ne j.\end{cases}
$$

<div id='connect-2'></div>

### #3.1.2 联系二

> 这一节需要先看 [#3.2.1 第二类的生成函数](#EGF-2)

令 $A(x),B(x)$ 分别表示数列 $\{a_n\}_{n=0}^\infty,\{b_n\}_{n=0}^\infty$ 的指数型生成函数，则下列三个命题等价：

1. 对任意 $n\geq0$，有 $b_n=\sum\limits_{i=0}^nS(n,i)a_i,$
2. 对任意 $n\geq0$，有 $a_n=\sum\limits_{i=0}^ns(n,i)b_i,$
3. $B(x)=A(e^x-1)$，也即 $A(x)=B(\ln(1+x)).$

**证明**：

若 2. 成立，则有

$$
\begin{aligned}
\sum\limits_{j=0}^nS(n,j)a_j=&\sum\limits_{j=0}^nS(n,j)\sum\limits_{i=0}^js(j,i)b_i=\sum\limits_{i=0}^nb_i\sum\limits_{j=i}^nS(n,j)s(j,i)\\
=&\sum\limits_{i=0}^nb_i\sum\limits_{j=1}^nS(n,j)s(j,i)=\sum\limits_{i=0}^nb_i\delta(n,i)=b_n,
\end{aligned}
$$

即 1. 也成立。同理，若 1. 成立，则可得 2. 成立，从而命题 1. 与 2. 等价。

若 1. 成立，则有

$$
\begin{aligned}
B(x)=&\sum\limits_{n=0}^\infty b_n\dfrac{x^n}{n!}=\sum\limits_{n=0}^\infty\sum\limits_{i=0}^nS(n,i)a_i\dfrac{x^n}{n!}=\sum\limits_{i=0}^\infty a_i\sum\limits_{n\geq i}S(n,i)\dfrac{x^n}{n!}\\
=&\sum\limits_{i=0}^\infty a_i\sum\limits_{n\geq0}S(n,i)\dfrac{x^n}{n!}=\sum\limits_{i=0}^\infty a_i\dfrac{(e^x-1)^i}{i!}=A(e^x-1),
\end{aligned}
$$

从而 3. 成立。易见推导过程可逆，故 1. 与 3. 等价。

综上，1. 2. 3. 相互等价。

<div align=right>证毕.</div>

## #3.2 生成函数

<div id='EGF-2'></div>

### #3.2.1 第二类的生成函数

$\{S(n,k)\}_{n=0}^\infty$ 的指数型生成函数为

$$
\sum\limits_{n=0}^\infty\dfrac{S(n,k)}{n!}x^n=\dfrac{(e^x-1)^k}{k!}.
$$

**证明**：

$$
\begin{aligned}
\sum\limits_{n=0}^\infty\dfrac{S(n,k)}{n!}x^n&=\sum\limits_{n=0}^\infty\dfrac{1}{k!}\sum\limits_{j=0}^k\dbinom{k}{j}j^n(-1)^{k-j}\dfrac{x^n}{n!}\\
&=\sum\limits_{j=0}^k(-1)^{k-j}\dfrac{1}{k!}\dbinom{k}{j}\sum\limits_{n=0}^\infty j^n\dfrac{x^n}{n!}\\
&=\sum\limits_{j=0}^k(-1)^{k-j}\dfrac{1}{k!}\dbinom{k}{j}\sum\limits_{n=0}^\infty\dfrac{(jx)^n}{n!}\\
&=\sum\limits_{j=0}^k(-1)^{k-j}\dfrac{1}{k!}\dbinom{k}{j}e^{jx}\\
&=\dfrac{1}{k!}\sum\limits_{j=0}^k\dbinom{k}{j}(e^x)^j(-1)^{k-j}=\dfrac{1}{k!}(e^x-1)^k.
\end{aligned}
$$

<div align=right>证毕.</div>

### #3.2.2 第一类的生成函数

结合 [第二类的生成函数](#EGF-2) 和 [联系二](#connect-2) 易得

$\{s(n,k)\}_{n=0}^\infty$ 的指数型生成函数为

$$
\sum\limits_{n=0}^\infty\dfrac{s(n,k)}{n!}x^n=\dfrac{(\ln(1+x))^k}{k!}.
$$

<div id='refer-auth'></div>

# 参考文献

[1]  冯荣权, 宋春伟. 组合数学. 北京: 北京大学出版社, 2015.

[2]  赵春来, 徐明曜. 抽象代数Ⅰ. 北京: 北京大学出版社, 2008.