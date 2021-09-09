[TOC]

# #0.0 前言
本篇文章为笔者的学习笔记及部分思考，如有错误还请不吝赐教
参考书籍为 《高等数学 上册 同济·第七版》[<sup>[1]</sup>](#refer-author)


<div id="difinition"></div>

# #1.0 定义

## #2.0 冰 冷 无 情 的式子
**设函数 $f(x)$ 在 $[a,b]$ 上有界，在 $[a,b]$ 中任意插入若干个分点**

$$
a=x_0<x_1<x_2<\cdots<x_{n-1}<x_n=b,
$$

**把区间 $[a,b]$ 分成 $n$ 个小区间**

$$
[x_0,x_1],[x_1,x_2],\cdots,[x_{n-1},x_n],
$$

**各个小区间的长度依次为**

$$
\Delta x_1=x_1-x_0,\Delta x_2=x_2-x_1,\cdots,\Delta x_n=x_{n}-x_{n-1}.
$$

**在每个小区间 $[x_{i-1},x_i]$ 上任取一点 $\xi_i\ (x_{i-1}\leqslant\xi_i\leqslant x_i)$，作函数值 $f(\xi_i)$ 与小区间长度 $\Delta x_i$ 的乘积 $f(\xi_i)\Delta x_i(i=1,2,\cdots,n)$，并作出和**

$$
S=\sum\limits_{i=1}^nf(\xi_i)\Delta x_i.
$$

**记 $\lambda=\max\{\Delta x_1,\Delta x_2,\cdots,\Delta x_n\}$，如果当 $\lambda\to0$ 时，这和的极限总存在，且与闭区间 $[a,b]$ 的分法及点 $\xi_i$ 的取法无关，那么称这个极限 $I$ 为函数 $f(x)$ 在区间 $[a,b]$ 上的<u>定积分</u>（简称<u>积分</u>），记作 $\int_a^bf(x)dx$，即**

$$
\int_a^bf(x)dx=I=\lim\limits_{\lambda\to0}\sum\limits_{i=1}^nf(\xi_i)\Delta x_i,
$$

**其中 $f(x)$ 叫做<u>被积函数</u>，$f(x)dx$ 叫做<u>被积表达式</u>，$x$ 叫做<u>积分变量</u>，$a$ 叫做<u>积分下限</u>，$b$ 叫做<u>积分上限</u>,$[a,b]$ 叫做<u>积分区间</u>.**

以上，就是定积分的定义，那么只有冰冷的式子显然是不够的，我们再来看一下定积分在几何上有什么意义

<div id="define-JH"></div>

## #1.2 生 动 有 趣 的图像

设 $f(x) = \dfrac{(x-4)^2}{5}$，我们来看一下 $\int_0^6f(x)dx$ ，我们先取

$$
n=6,x_0=0,x_1=1,x_2=2,x_3=3,\cdots,x_6=6,\\
\Delta x_i=1,i=1,2,\cdots,6,\\
\xi_i=x_{i-1},i=1,2,\cdots,6,
$$

$\sum\limits_{i=1}^nf(\xi_i)\Delta x_i$ 对应下图阴影部分

![](https://img.imgdb.cn/item/6067c68c8322e6675caa42eb.png)

那么如果我们让 $\lambda\to0,n\to\infty$，我们就会得到这样的图:

![](https://img.imgdb.cn/item/6067c7b48322e6675cab2e96.png)

这正对应着 $f(x)$ 与 $x$ 轴、直线 $x=a$ 、$x=b$ 所围成的图形面积，而当在该区间内有部分在 $x$ 轴下方，有部分在 $x$ 轴上方时，它等于上方图像面积减去下方图形面积所得的差

# #2.0 定积分的近似计算

> 你将看到一个无知而为无畏的傻瓜（指笔者）坚持不懈地推一堆没用的 ~~柿子~~ 式子

## #2.1 矩形法
就像我们上面探究定积分的几何意义时一样，将区间 $[a,b]$ 采取等分的方法，即 $a=x_0,x_1,x_2,\cdots,x_n=b$ 将 $[a,b]$ 分作 $n$ 个长度相等的小区间，每个小区间的长为

$$
\Delta x=\dfrac{b-a}{n},
$$

在 $[x_{i-1},x_i]$ 上，取 $\xi_i=x_{i-1}$，应有

$$
\int_a^bf(x)dx = \lim\limits_{n\to\infty}\dfrac{b-a}{n}\sum\limits_{i=1}^nf(x_{i-1}),
$$

对于唯一确定的正整数 $n$，应有

$$
\int_a^bf(x)dx\approx\dfrac{b-a}{n}\sum\limits_{i=1}^nf(x_{i-1}),
$$

记 $f(x_i)=y_i\ (i=0,1,2,\cdots,n)$，上式可记作

$$
\int_a^bf(x)dx\approx\dfrac{b-a}{n}(y_0+y_1+\cdots+y_{n-1}),
$$

若取 $\xi_i=x_i$，那么有

$$
\int_a^bf(x)dx\approx\dfrac{b-a}{n}(y_1+y_2+\cdots+y_{n}),
$$

以上两个式子便是 **矩形法公式**

## #2.1 梯形法
上面显然存在误差，考虑在做实验时我们减小误差常做的一件事：取平均值，那么假如我们将上面两个柿子相加取平均会得到什么呢？

$$
\begin{aligned}
\int_a^bf(x)dx&\approx\dfrac{b-a}{n}(\dfrac{y_0+y_1}{2}+\dfrac{y_1+y_2}{2}+\cdots+\dfrac{y_{n-1}+y_{n}}{2})\\
&=\dfrac{b-a}{n}(\dfrac{y_0+y_n}{2}+y_1+y_2+\cdots+y_{n-1})
\end{aligned}
$$

这个柿子~（爷饿了）~可以作为定积分的估计值嘛？我们来简单分析一下。

$$
\begin{aligned}
\int_a^bf(x)dx&\approx\dfrac{b-a}{n}(\dfrac{y_0+y_1}{2}+\dfrac{y_1+y_2}{2}+\cdots+\dfrac{y_{n-1}+y_{n}}{2})\\
&=\dfrac{1}{2}\cdot\dfrac{b-a}{n}(y_0+y_1)+\dfrac{1}{2}\cdot\dfrac{b-a}{n}(y_1+y_2)+\cdots+\dfrac{1}{2}\cdot\dfrac{b-a}{n}(y_{n-1}+y_n)\\
\end{aligned}
$$

上面式子的样子让我们想起了一个我们在幼儿园二年级就会的柿子：

$$
S_{梯形}=\dfrac{(l_{上底}+l_{下底})\cdot h}{2}
$$

那我们是不是就可以把上面的式子这样理解：
我们将一个个以 $y_{i-1}$ 为上底，$y_i$ 为下底，$\dfrac{b-a}{n}$ （即 $\Delta x$）为高的梯形面积累加，近似等于 $\int_a^bf(x)dx$ 的值，这样来看，我们就是用一条条线段 $\overline{M_{i-1}M_i}$ 来代替弧 $\widehat{M_{i-1}M_i}$,如下图：我们用线段 $\overline{GE}$ 来近似表示弧 $ \widehat{GE}$

> 笔者属实不知 $\text{Markdown}$ 环境下的 $\LaTeX$ 如何表示出合适的上弧线,于是使用 $\widehat{AB}$ 表示弧 $AB.$

![](https://img.imgdb.cn/item/6067d3018322e6675cb43920.png)

梯形法的思想只比矩形法复杂那么一点点，对吧？那我们来看下一个：**抛物线法。**

## #2.3 抛物线法
关于抛物线法，书[<sup>[2]</sup>](#refer-author)上是这样说的：

抛物线法的原理是将曲线 $y=f(x)$ 上的两个小弧段 $\widehat{M_{i-1}M_i}$ 和 $\widehat{M_iM_{i+1}}$ 合起来，用过 $M_{i-1},M_i,M_{i+1}$ 三点的抛物线 $y=px^2+qx+r$ 代替。**经推导可得**，以此抛物线为曲边、以 $[x_{i-1},x_{i+1}]$ 为底的曲边梯形面积为

$$
\dfrac{1}{6}(y_{i-1}+4y_i+y_{i+1})\cdot2\Delta x=\dfrac{b-a}{3n}(y_{i-1}+4y_i+y_{i+1}).
$$

取 $n$ 为偶数，得到定积分的近似值为

$$
\begin{align*}
\int_a^bf(x)dx&\approx\dfrac{b-a}{3n}[(y_0+4y_1+y_2)+(y_2+4y_3+y_4)+\cdots+(y_{n-2}+4y_{n-1}+y_n)]\\
&=\dfrac{b-a}{3n}[y_0+y_n+4(y_1+y_3+\cdots+y_{n-1})+2(y_{2}+y_{4}+\cdots+y_{n-2})].
\end{align*}
$$

上面的推导十分严谨，所以这里。。。等等，什么叫 **“经推导可得”**？这就勾起了我的好奇心，让我们看看能不能根据已有的知识将这个柿子推导出来。

首先，我们先来看 <sub>~~圆柿子~~</sub> 原式子：

$$
\dfrac{1}{6}(y_{i-1}+4y_i+y_{i+1})\cdot2\Delta x=\dfrac{x_{i+1}-x_{i-1}}{6}(y_{i-1}+4y_i+y_{i+1})
$$

而我们根据[定积分的定义](#difinition)可知，以抛物线 $f(x)=ax^2+bx+c$ 为曲边，以 $[s,t]$ 为底的曲边梯形的面积就是 

$$
\int_s^tf(x)dx,f(x)=ax^2+bx+c.
$$

所以，我们只需要证明对于 $f(x)=ax^2+bx+c$

$$
\int_s^tf(x)dx=\dfrac{t-x}{6}(f(s)+f(\dfrac{s+t}{2})+f(t))
$$

# #3.0 定积分的性质

> 下面颓柿子的过程中用到了诸如 $\sum_{i=1}^ni=\dfrac{n(n+1)}{2},\sum_{i=1}^ni^2=\dfrac{n(n+1)(2n+1)}{6}$ 这样的结论，证明请见[补充证明](#supplement)

## #3.1 颓柿子·一

> --WARING!--前方大量柿子出没--WARING!--

根据上面的定义，我们考虑按照定积分的定义来证明这个式子
**证：**
$$
\begin{align*}
\int_s^tf(x)dx&=\lim\limits_{\lambda\to0}\sum\limits_{i=1}^nf(\xi_i)\Delta x_i=\lim\limits_{n\to \infty}\sum\limits_{i=1}^n(a\xi_i^2+b\xi_i+c)\Delta x_i\\
&=\lim\limits_{n\to \infty}\sum\limits_{i=1}^n(a\xi_i^2\Delta x_i+b\xi_i\Delta x_i+c\Delta x_i)\\
&=\lim\limits_{n\to \infty}(a\sum\limits_{i=1}^n\xi_i^2\Delta x_i+b\sum\limits_{i=1}^n\xi_i\Delta x_i+c\sum\limits_{i=1}^n\Delta x_i)\\
&=a\lim\limits_{n\to \infty}\sum\limits_{i=1}^n\xi_i^2\Delta x_i+b\lim\limits_{n\to \infty}\sum\limits_{i=1}^n\xi_i\Delta x_i+c\lim\limits_{n\to \infty}\sum\limits_{i=1}^n\Delta x_i\\
\end{align*}\\
$$
$$
取x_i=\dfrac{(t-s)i}{n}+s,i=1,2,\cdots,n-1,\Delta x_i=\dfrac{t-s}{n},\xi_i=x_i,i=1,2,\cdots,n.\\
$$
$$
\begin{align*}
\sum\limits_{i=1}^n\xi_i^2\Delta x_i&=\sum\limits_{i=1}^n(\dfrac{(t-s)i}{n}+s)^2\dfrac{t-s}{n}=\sum\limits_{i=1}^n(\dfrac{(t-s)^2}{n^2}i^2+2\dfrac{(t-s)s}{n}i+s^2)\dfrac{t-s}{n}\\
&=\dfrac{t-s}{n}(\sum\limits_{i=1}^n\dfrac{(t-s)^2}{n^2}i^2+\sum\limits_{i=1}^n2\dfrac{(t-s)s}{n}i+\sum\limits_{i=1}^ns^2)\\
&=\dfrac{t-s}{n}(\dfrac{(t-s)^2}{n^2}\sum\limits_{i=1}^ni^2+2\dfrac{(t-s)s}{n}\sum\limits_{i=1}^ni+ns^2)\\
&=\dfrac{t-s}{n}(\dfrac{(t-s)^2}{n^2}\cdot\dfrac{1}{6}n(n+1)(2n+1)+2\dfrac{(t-s)s}{n}\cdot\dfrac{1}{2}n(n+1)+ns^2)\\
&=\dfrac{t-s}{n}(\dfrac{(t-s)^2}{n^2}\cdot\dfrac{1}{6}n(n+1)(2n+1)+\dfrac{(t-s)s}{n}n(n+1)+ns^2)\\
&=(t-s)(\dfrac{(t-s)^2}{6}(1+\dfrac{1}{n})(2+\dfrac{1}{n})+(t-s)s(1+\dfrac{1}{n})+s^2)\\
&=\dfrac{(t-s)^3}{6}(1+\dfrac{1}{n})(2+\dfrac{1}{n})+(t-s)^2s(1+\dfrac{1}{n})+(s-t)s^2\\
\end{align*}\\
$$
$$
\begin{align*}
a\lim\limits_{n\to \infty}\sum\limits_{i=1}^n\xi_i^2\Delta x_i&=a\lim\limits_{n\to \infty}(\dfrac{(t-s)^3}{6}(1+\dfrac{1}{n})(2+\dfrac{1}{n})+(t-s)^2s(1+\dfrac{1}{n})+(s-t)s^2)\\
&=a(t-s)\lim\limits_{n\to \infty}(\dfrac{(t-s)^2}{6}(1+\dfrac{1}{n})(2+\dfrac{1}{n})+(t-s)s(1+\dfrac{1}{n})+s^2)\\
&=a(t-s)(\dfrac{(t-s)^2}{3}+(t-s)s+s^2)\\
\end{align*}\\
$$
$$
\begin{align*}
\sum\limits_{i=1}^n\xi_i\Delta x_i&=\sum\limits_{i=1}^n(\dfrac{t-s}{n}i+s)\dfrac{t-s}{n}=\dfrac{t-s}{n}(\sum\limits_{i=1}^n\dfrac{t-s}{n}i+\sum\limits_{i=1}^ns)=\dfrac{t-s}{n}(\dfrac{t-s}{n}\sum\limits_{i=1}^ni+ns)\\
&=\dfrac{(t-s)^2}{n^2}\sum\limits_{i=1}^ni+(t-s)s=\dfrac{(t-s)^2}{n^2}\cdot\dfrac{1}{2}n(n+1)+(t-s)s\\
&=\dfrac{(t-s)^2}{2}(1+\dfrac{1}{n})+(t-s)s\\
\end{align*}\\
$$
$$
\begin{align*}
b\lim\limits_{n\to \infty}\sum\limits_{i=1}^n\xi_i\Delta x_i&=b\lim\limits_{n\to\infty}(\dfrac{(t-s)^2}{2}(1+\dfrac{1}{n})+(t-s)s)=b(\dfrac{(t-s)^2}{2}+(t-s)s)\\
&=b(t-s)(\dfrac{t-s}{2}+s)=b(t-s)(\dfrac{t+s}{2})=\dfrac{b}{2}(t-s)(t+s)
\end{align*}\\
$$
$$
\begin{align*}
c\lim\limits_{n\to \infty}\sum\limits_{i=1}^n\Delta x_i&=c\lim\limits_{n\to \infty}\sum\limits_{i=1}^n\dfrac{t-s}{n}=c(t-s)\\
\int_s^tf(x)dx&=a(t-s)(\dfrac{(t-s)^2}{3}+(t-s)s+s^2)+\dfrac{b}{2}(t-s)(t+s)+c(t-s)\\
&=\dfrac{1}{6}(a(t-s)(2(t-s)^2+6(t-s)s+6s^2)+3b(t-s)(t+s)+6c(t-s))\\
&=\dfrac{t-s}{6}(a(2(t-s)^2+6(t-s)s+6s^2)+3b((t+s)+6c)\\
&=\dfrac{t-s}{6}(a(2t^2-4ts+2s^2+6ts-6s^2+6s^2)+3b((t+s)+6c)\\
&=\dfrac{t-s}{6}(a(2t^2+2ts+2s^2)+3b((t+s)+6c)\\
&=\dfrac{t-s}{6}(a(t^2+s^2+(t+s)^2)+3b((t+s)+6c)\\
&=a(t+s)^2+2b(t+s)+4c+at^2+bt+c+as^2+bs+c\\
&=4(a\dfrac{(t+s)^2}{4}+b\dfrac{t+s}{2}+c)+f(t)+f(s)=4f(\dfrac{s+t}{2})+f(t)+f(s)
\end{align*}\\
$$
$$
故\int_s^tf(x)dx=f(s)+4f(\dfrac{s+t}{2})+f(t).
$$
<div align="right"><b>证毕.</b></div>

经历了一番磨难,我们最终推出了我们想要的柿子，而当我兴致勃勃的拿着我推出的柿子去找旁边的大佬 $\text{hyl}$ 时，他微笑着写下了一个我不认识的公式，说到：“这么麻烦干什么，用[牛顿-莱布尼茨公式](https://baike.baidu.com/item/%E7%89%9B%E9%A1%BF-%E8%8E%B1%E5%B8%83%E5%B0%BC%E8%8C%A8%E5%85%AC%E5%BC%8F)不就好了”

好吧，但凡我再往后翻十页，我就可以看到这个伟大的公式，这是什么暂且不谈，以后会更详细地讲。那么，我们颓出的这么长的柿子是不是没用了？并不是，我们似乎可以从中看出一些有趣的性质。

我们看这里：

$$
\begin{align*}
\int_s^tf(x)dx&=\lim\limits_{\lambda\to0}\sum\limits_{i=1}^nf(\xi_i)\Delta x_i=\lim\limits_{n\to \infty}\sum\limits_{i=1}^n(a\xi_i^2+b\xi_i+c)\Delta x_i\\
&=\lim\limits_{n\to \infty}\sum\limits_{i=1}^n(a\xi_i^2\Delta x_i+b\xi_i\Delta x_i+c\Delta x_i)\\
&=\lim\limits_{n\to \infty}(a\sum\limits_{i=1}^n\xi_i^2\Delta x_i+b\sum\limits_{i=1}^n\xi_i\Delta x_i+c\sum\limits_{i=1}^n\Delta x_i)\\
&=a\lim\limits_{n\to \infty}\sum\limits_{i=1}^n\xi_i^2\Delta x_i+b\lim\limits_{n\to \infty}\sum\limits_{i=1}^n\xi_i\Delta x_i+c\lim\limits_{n\to \infty}\sum\limits_{i=1}^n\Delta x_i\\
\end{align*}
$$

可以发现

$$
\begin{align*}
\int_a^b(ax^2+bx+c)dx &= \lim\limits_{n\to \infty}\sum\limits_{i=1}^n(a\xi_i^2+b\xi_i+c)\Delta x_i\\
&=a\lim\limits_{n\to \infty}\sum\limits_{i=1}^n\xi_i^2\Delta x_i+b\lim\limits_{n\to \infty}\sum\limits_{i=1}^n\xi_i\Delta x_i+c\lim\limits_{n\to \infty}\sum\limits_{i=1}^n\Delta x_i\\
&=a\int_a^bx^2dx+b\int_a^bxdx+c\int_a^bdx
\end{align*}
$$

于是，我们可以合理猜测，定积分具有以下性质：

### 定积分性质一

$$
\int_a^b[\alpha f(x)+\beta g(x)]dx=\alpha \int_a^bf(x)dx+\beta \int_a^bf(x)
$$

**证明：**

$$
\begin{align*}
\int_a^b[\alpha f(x)+\beta g(x)]dx&=\lim\limits_{n\to\infty}\sum\limits_{i=1}^n[\alpha f(\xi_i)+\beta g(\xi_i)]\Delta x_i\\
&=\lim\limits_{n\to\infty}[\alpha\sum\limits_{i=1}^nf(\xi_i)\Delta x_i+\beta\sum\limits_{i=1}^ng(\xi_i)\Delta x_i]\\
&=\alpha\lim\limits_{n\to\infty}\sum\limits_{i=1}^nf(\xi_i)\Delta x_i+\beta\lim\limits_{n\to\infty}\sum\limits_{i=1}^ng(\xi_i)\Delta x_i\\
&=\alpha \int_a^bf(x)dx+\beta \int_a^bf(x)\\
\end{align*}
$$
<div align="right"><b>证毕.</b></div>

## #3.2 颓柿子·二

同样是上面想推的柿子，这是我的另一个思路。我们知道，定积分 $\int_a^bf(x)dx$ 的[几何意义](#define-JH)是 $f(x)$ 与 $x$ 轴、直线 $x=a$ 、$x=b$ 所围成的图形面积，那么，运用前缀和的思想，可不可以有

$$
\int_a^bf(x)dx=\int_0^bf(x)dx-\int_0^af(x)dx
$$

似乎可以有...等等，这里是不是将原本的区间 $[a,b]$ 变成了 $(a,b]$，需不需要再加上 $\int_a^af(x)dx$？这一条线有没有面积？似乎陷入了奇怪的问题...

为此，我们引出

### 定积分的补充规定

如下
 - $\int_a^af(x)dx=0$
 - $\int_a^bf(x)dx=-\int_b^af(x)dx$

这样一来，上面的想法就合理了，上面的想法通过推导 $\int_0^af(x)dx$ 可以得到想要的结果，这里限于篇幅<sub>（~~我懒得再打小100行的 LaTeX~~）</sub>不多赘述

这样来看，综合上面的思路，定积分似乎可以有以下的性质

### 定积分性质二

设 $a<c<b$，有
$$
\int_a^bf(x)dx=\int_a^cf(x)dx+\int_c^bf(x)dx
$$

**证明：**
设 $x_k=c$
$$
\begin{align*}
\int_a^bf(x)dx&=\lim\limits_{n\to\infty}\sum\limits_{i=1}^nf(\xi_i)\Delta x_i\\
&=\lim\limits_{n\to\infty}\sum\limits_{i=1}^kf(\xi_i)\Delta x_i+\lim\limits_{n\to\infty}\sum\limits_{i=k}^nf(\xi_i)\Delta x_i-\lim\limits_{\lambda\to0}\sum\limits_{i=k}^kf(\xi_i)\Delta x_i\\
&=\int_a^cf(x)dx+\int_c^bf(x)dx-\int_c^cf(x)dx\\
&=\int_a^cf(x)dx+\int_c^bf(x)dx
\end{align*}
$$
<div align="right"><b>证毕.</b></div>

## #3.3 定积分的其他性质

> 下面大部分性质都很显然，或借助它前面的性质都可以轻松得证，这里不多赘述

### 定积分的性质三

**如果在区间 $[a,b]$ 上 $f(x)\equiv1$，那么**

$$
\int_a^b1dx=\int_a^bdx=b-a.
$$

### 定积分的性质四

**如果在区间 $[a,b]$ 上 $f(x)\geqslant0$，那么**

$$
\int_a^bf(X)dx\geqslant0\quad(a<b).
$$

#### 推论1

**如果在区间 $[a,b]$ 上 $f(x)\leqslant g(x)$**，那么

$$
\int_a^bf(x)dx\leqslant\int_a^bg(x)dx\quad(a<b).
$$

#### 推论2

$$
\left|\int_a^bf(x)dx\right|\leqslant\int_a^b\left|f(x)\right|dx\quad(a<b).
$$

<div id="nature-5"></div>

### 定积分的性质五

**设 $M$ 及 $m$ 分别是区间 $[a,b]$ 上的最小值和最大值，则**

$$
m(b-a)\leqslant\int_a^bf(x)dx\leqslant M(b-a)\quad(a<b).
$$

### 定积分中值定理

**如果 $f(x)$ 在积分区间 $[a,b]$ 上连续，那么在 $[a,b]$ 上至少存在一个点 $\xi$，使下式成立：**

$$
\int_a^bf(x)dx=f(\xi)(b-a)\quad (a\leqslant\xi\leqslant b).
$$

**证明：**
将[性质5](#nature-5)中的不等式左右同除以 $(b-a)$，得

$$
m\leqslant\dfrac{1}{b-a}\int_a^bf(x)dx\leqslant M.
$$

根据[介值定理](https://baike.baidu.com/item/%E4%BB%8B%E5%80%BC%E5%AE%9A%E7%90%86)可知，应有一点 $\xi\in[a,b]$ 满足

$$
\dfrac{1}{b-a}\int_a^bf(x)dx=f(\xi)\quad(a\leqslant\xi\leqslant b).
$$

即

$$
\int_a^bf(x)dx=f(\xi)(b-a)\quad (a\leqslant\xi\leqslant b).
$$
<div align="right"><b>证毕.</b></div>

<div id = "supplement"></div>

# #4.0 补充证明

## #4.1 证明·一

证明 $\sum_{i=1}^ni=\dfrac{n(n+1)}{2}$
**证：**
$$
\begin{align*}
\sum\limits_{i=1}^{n}i^2+(n+1)^2&=1+\sum\limits_{i=2}^{n+1}i^2=1+\sum\limits_{i=1}^n(i+1)^2\\
&=1+\sum\limits_{i=1}^n(i^2+2i+1)=\sum\limits_{i=1}^ni^2+2\sum_{i=1}^ni+n+1\\
\sum\limits_{i=1}^{n}i^2+(n+1)^2&=\sum\limits_{i=1}^ni^2+2\sum_{i=1}^ni+n+1\\
2\sum\limits_{i=1}^ni&=(n+1)^2-(n+1)=n(n+1)\\
\sum\limits_{i=1}^ni&=\dfrac{n(n+1)}{2}\\
\end{align*}
$$

## #4.2 证明·二

证明 $\sum_{i=1}^ni^2=\dfrac{n(n+1)(2n+1)}{6}$
**证：**
$$
\begin{align*}
\sum\limits_{i=1}^{n}i^3+(n+1)^3&=1+\sum\limits_{i=2}^{n+1}i^3=1+\sum\limits_{i=1}^n(i+1)^3\\
&=1+\sum\limits_{i=1}^n(i^3+3i^2+3i+1)\\
&=\sum\limits_{i=1}^ni^3+3\sum_{i=1}^ni^2+3\sum_{i=1}^ni+n+1\\
&=\sum\limits_{i=1}^ni^3+3\sum_{i=1}^ni^2+\dfrac{3}{2}n(n+1)+n+1\\
(n+1)^3&=\sum\limits_{i=1}^ni^2+2\sum_{i=1}^ni^2+n+1\\
(n+1)^3&=3\sum_{i=1}^ni^2+\dfrac{3}{2}n(n+1)+n+1\\
6\sum_{i=1}^ni^2&=2(n+1)^3-3n(n+1)-2(n+1)\\
&=(n+1)[2(n+1)^2-3n-2]\\
&=n(n+1)(2n+1)\\
\sum_{i=1}^ni^2&=\dfrac{n(n+1)(2n+1)}{6}
\end{align*}
$$

> 以上两个证明均使用了**扰动法**，关于扰动法的讲解具体参见《具体数学》[<sup>[3]</sup>](#refer-author)

<div id="refer-author"></div>

-----------

# 参考及更新日志

## 参考文章/书籍
 [1] [2]《高等数学 上册 同济·第七版》
 [3]《具体数学》

## 更新

> - 初次完成编辑 - $2021.4.3$
