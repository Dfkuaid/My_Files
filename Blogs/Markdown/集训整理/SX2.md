## 亿些性质

对于任意的 $x$ 与正整数 $a,b$，我们均有：$\left\lfloor\dfrac{\left\lfloor\dfrac{x}{a}\right\rfloor}{b}\right\rfloor=\left\lfloor\dfrac{x}{ab}\right\rfloor.$

对于正整数 $n$，考虑当 $1\leq d\leq n$ 时，$\left\lfloor\dfrac{n}{d}\right\rfloor$的不同的取值个数。

- 若 $d\leq\sqrt{n}$，则能得到的 $\left\lfloor\dfrac{n}{d}\right\rfloor$ 只有不超过 $\sqrt{n}$ 种。
- 若 $d>\sqrt{n}$，则 $\left\lfloor\dfrac{n}{d}\right\rfloor\leq\dfrac{n}{d}<\sqrt{n}$，又因为 $\left\lfloor\dfrac{n}{d}\right\rfloor$ 是正整数，故此时可能的取值也不超过 $\sqrt{n}$ 种。

综上，$\left\lfloor\dfrac{n}{d}\right\rfloor$ 可能的取值不超过 $2\sqrt{n}$ 种。

## 调和数

调和数的定义： $H_n=\sum\limits_{k=1}^n\dfrac{1}{k}.$

### 性质

1. $H_n = \ln n+\gamma+o(1).$

由此可以推出时间复杂度：$\sum\limits_{k=1}^n\left\lfloor\dfrac{n}{k}\right\rfloor=O(n\log n).$

## 素数

### 性质

1. 定义 $\pi(n)$ 表示不超过 $n$ 的素数个数，有$\pi(n)\sim\dfrac{n}{\ln n}.$

由此可得推论：

- $n$ 附近的素数密度近似是 $\dfrac{1}{\ln n}.$
- 第 $n$ 个素数 $p_n\sim n\ln n.$

## 积性函数

### 定义

设 $f$ 是数论函数，若对**任意互质的**正整数 $a,b$，都有 $f(ab)=f(a)f(b)$，则称 $f$ 是**积性函数**。若对**任意的**正整数 $a,b$，都有 $f(ab)=f(a)f(b)$，则称 $f$ 是**完全积性的**。

### 性质

若 $f$ 是积性函数，且 $n=p_1^{\alpha_1}p_2^{\alpha_2}···p_s^{\alpha_s}$ 是 $n$ 的标准分解，则有 $f(n)=f(p_1^{\alpha_1})f(p_2^{\alpha_2})···f(p_s^{\alpha_s})$ 因此研究积性函数 $f$ 可以转化为研究 $f(p^\alpha)$，即 $f$ 在素数和素数的幂上的取值。

### 积性函数的求法

设 $f$ 是积性函数，为求 $f(n)$，可以对 $n$ 分解素因子，然后计算所有的 $f(p^\alpha)$ 乘起来。如果要对 $1$ 到 $n$ 之间的所有数求出 $f$，注意到 $\text{Euler}$ 筛法的过程中可以求出每个数的最小素因子和最小素因子的幂次，利用此就能在线性时间内计算出所需的f的值。

### 单位函数

单位函数 $\epsilon(n)$ 定义为：

$$
\epsilon(n)=[n=1] =\begin{cases}1,\quad n=1,\\0,\quad n\ne1.\end{cases}
$$

其中 $[\text{condition}]$ 表示当 $\text{condition}$ 为真时取值为 $1$，否则为 $0$ 的函数。单位函数是**完全积性函数**。

有 $[n=1]=\epsilon(n).$

### 除数函数

除数函数 $\sigma_k(n)$ 用来表示 $n$ 的因子的 $k$ 次方和：

$$
\sigma_k(n)=\sum\limits_{d|n}d^k.
$$

约数个数 $\sigma_0(n)$ 常记为 $d(n)$，约数和 $\sigma_1(n)$ 常记为 $\sigma(n).$

除数函数都是**积性函数**。

### $\text{Euler}$ 函数

$\text{Euler}$ 函数 $\varphi(n)$ 表示不超过 $n$ 且与 $n$ 互质的正整数的个数。由 $n$ 的标准分解并结合容斥原理，我们可以得到 $\text{Euler}$ 函数的显示表达式：

$$
\varphi(n)=n\cdot\prod\limits_{i=1}^s(1−\dfrac{1}{p_i}),
$$

其中 $n=p_1^{\alpha_1}p_2^{\alpha_2}···p_s^{\alpha_s}$ 是 $n$ 的标准分解。由此易见 $\text{Euler}$ 函数是**积性函数**。

对于任意 $n$，$\text{Euler}$ 函数有如下性质：

$$
n=\sum\limits_{d|n}\varphi(d).
$$

证明：

若 $\gcd(n,i)=d$，那么 $\gcd(\dfrac{n}{d},\dfrac{i}{d})=1$。而 $\dfrac{i}{d}\leq\dfrac{n}{d},\dfrac{i}{d}\in\Z$，故这样的 $i$ 有 $φ(\dfrac{n}{d})$ 个。考虑所有 $d|n$，我们也就考虑到了所有 $1$ 到 $n$ 之间的 $n$ 个整数，因此有

$$
n=\sum\limits_{d|n}\varphi(\dfrac{n}{d})=\sum\limits_{d|n}\varphi(d).
$$

## $\text{Dirichlet}$ 卷积

### 定义

设 $f,g$ 是数论函数，考虑数论函数 $h$ 满足

$$
h(n)=\sum\limits_{d|n}f(d)g(\dfrac{n}{d}),
$$

则称 $h$ 为 $f$ 和 $g$ 的 $\text{Dirichlet}$ 卷积，记作 $h=f*g.$

### 性质

单位函数 $\epsilon$ 是 $\text{Dirichlet}$ 卷积的单位元，即对于任意函数 $f$，有 $\epsilon∗f=f∗\epsilon=f$。$\text{Dirichlet}$ 卷积满足**交换律**和**结合律**。

如果 $f,g$ 都是积性函数，那么 $f∗g$ 也是积性函数。

### 计算 $\text{Dirichlet}$ 卷积

设 $f,g$ 是数论函数，计算 $f$ 和 $g$ 的 $\text{Dirichlet}$ 卷积在 $n$ 处的值需要枚举 $n$ 的所有约数。

如果要计算 $f$ 和 $g$ 的 $\text{Dirichlet}$ 卷积的前 $n$ 项，可以枚举 $1$ 到 $n$ 中每个数的倍数，根据调和数的相关结论，这样做的复杂度是 $O(n\log n)$。

如果 $f,g$ 是积性函数，则可以用线性筛达到（近似？） $O(n)$ 的时间复杂度。

定义幂函数 $Id_k(n) =n^k,Id=Id_1.$

## $\text{Mobius}$ 函数

### 定义

$$
\mu(n)=\begin{cases}1,&n=1,\\(-1)^s,&n=p_1p_2\cdots p_s\\0,&otherwise.\end{cases}
$$

其中 $p_1,\cdots,p_s$ 是不同素数。可以看出，$\mu(n)$ 恰在 $n$ 无平方因子时非零。易见 $\mu$ 是积性函数。

### 性质

$$
\sum\limits_{d|n}\mu(d)=\epsilon(n).
$$

用 $\text{Dirichlet}$ 卷积表示，即

$$
\mu*1=\epsilon.
$$

**证明**：

当 $n = 1$ 时显然成立，下面郑 $n>1$ 时结论成立。

当根据 $\text{Mobius}$ 函数的定义，当且仅当 $n$ 无平方因子时非零，故能对答案造成贡献的 $d$ 中每个素因子的次数只能为 $0$ 或 $1$，设 $n$ 的唯一分解式为 $n=p_1^{\alpha_1}p_2^{\alpha_2}\cdots p_s^{\alpha_s}$,于是有：

$$
\sum\limits_{d|n}\mu(d)=\sum\limits_{k=0}^s(-1)^k\dbinom{s}{k}=(1-1)^s=0.
$$

<div align=right>证毕.</div>

### $\text{Mobius}$ 变换

对于数论函数 $f$，定义函数 $g$ 满足

$$
g(n)=\sum\limits_{d|n}f(d).\tag1
$$

用 $\text{Dirichlet}$ 卷积表示即 $g=f*1.$

称 $g$ 是 $f$ 的 $\text{Mobius}$ 变换，$f$ 是 $g$ 的 $\text{Mobius}$ 逆变换。

### $\text{Mobius}$ 反演

$\text{Mobius}$ 反演指出，$(1)$ 的充要条件为

$$
f(n)=\sum\limits_{d|n}g(d)\mu(\dfrac{n}{d}).\tag2
$$

**证明**：

$$
g=f*1\Leftrightarrow f=f*\epsilon=f*1*\mu=g*\mu.
$$

<div align=right>证毕.</div>

### 应用

利用 $\text{Dirichlet}$ 卷积可以解决一系列求和问题。常见做法是使用一个 $\text{Dirichlet}$ 卷积替换求和式中的一部分，然后调换求和顺序，最终降低时间复杂度。

经常利用的卷积有 $\mu∗1=\epsilon$ 和 $Id=\varphi∗1$。

$\text{Mobius}$ 反演本身可以看成对整除关系的容斥。

## 杜教筛

------

<div style="width=10px;line_height: 1px;">
<a href=https://www.cnblogs.com/Dfkuaid-210/p/DU-JIAO-SHAI.html style="text-decoration:none;">
      <font face="黑体" size=6>
            <b>[算法入门]杜教筛</b>
      </font>
      <font face="黑体" size=2>
            <br>&nbsp;&nbsp;发表于 2021-06-1 18:52&nbsp;Dfkuaid<br>
      </font>
      <font face="黑体" size=6>   </font>
      <font face="FangSong" size=4>
            摘要：&nbsp;积性函数，Dirichlet 卷积，杜教筛的简单讲解&nbsp;<br>
      </font>
    <p align="right">
      <font face="黑体" size=4>
          阅读全文&nbsp;&nbsp;&nbsp;<br>
          <u>&nbsp;&nbsp;&nbsp;>>&nbsp;&nbsp;&nbsp;</u>&nbsp;&nbsp;&nbsp;<br>
      </font>
    </p>
</a>
</div>

------

## 杂项

### $\text{Euler}$ 定理

对于正整数 $n$ 以及与 $n$ 互质的正整数 $a$，有

$$
a^\varphi(n)\equiv1(\bmod\ n)
$$

**引申而来的结论：**

对于正整数 $n$ 与正整数 $a$，$\text{Euler}$ 定理说明如果 $a⊥n$，那么对于任意的 $m$，有

$$
a^m\equiv a^{m\bmod\ \varphi(n)}(\bmod\ n).
$$

如果 $a$ 与 $n$ 不一定互质，若 $m \geq \varphi(n)$，我们也有以下结论：

$$
a^m\equiv a^{m\bmod\ \varphi(n)+\varphi(n)}(\bmod\ n).
$$

### 阶

给定正整数 $n$，对于 $a$ 满足 $a⊥n$，定义 $a$ 模 $n$ 的阶为最小的正整数 $d$ 使得下式成立：

$$
a^d\equiv1(\bmod\ n).
$$

$a$ 模 $n$ 的阶为 $\delta_n(a)$，由 $\text{Euler}$ 定理知有 $\delta_n(a)|\varphi(n).$

### 原根

若 $\delta_n(a)=\varphi(n)$，则称 $a$ 是模 $n$ 的原根。

可以看出，$a$ 是模 $n$ 的原根当且仅当 $a_0,a_1,\cdots,a^{\varphi(n)−1} $在 $\bmod\ n$ 意义下两两不同。这也是原根重要的性质和等价定义。

模 $n$ 存在原根当且仅当 $n=1,2,4,p^k,2p^k$，其中 $p$ 为奇素数，$k$ 为正整数。

### 离散对数

设 $g$ 是模 $n$ 的原根。那么对于任意 $a$ 满足 $a⊥n$，均存在 $k$ 使得

$$
g^k\equiv a(\bmod\ n).
$$

这样的关系有助于把 $\bmod\ n$ 的乘法转化为 $\bmod\ varphi(n)$ 的加法，与对数的作用有相似之处。

### $\text{Lucas}$ 定理

> 在 []() 里证过了，这里就复制过来。

设 $p$ 是一个质数，$n$ 用 $p$ 进制表示为 $a_0+a_1p^1+a_2p^2+\cdots+a_kp^k$，$m$ 用 $p$ 进制表示为 $b_0+b_1p^1+b_2p^2+\cdots+b_kp^k$，那么有：
$$
\dbinom{n}{m}\equiv\prod\limits_{i=0}^k\dbinom{a_i}{b_i}(\text{mod }p).
$$
**证明：**

易知，当 $1\leq j \leq p^i-1,i\geq1$ 时，$\tbinom{p^i}{j}$ 是 $j$ 的倍数，故
$$
(1+x)^{p^i}=1+x^{p^i}+\sum\limits_{j=1}^{p^i-1}\dbinom{p^i}{j}x^j\equiv1+x^{p^i}(\text{mod }p).
$$
所以有
$$
\begin{aligned}
(1+x)^n=&(1+x)^{\sum\limits_{i=0}^ka_ip^i}=\prod\limits_{i=0}^k[(1+x)^{p^i}]^{a_i}\equiv\prod\limits_{i=0}^k(1+x^{p^i})^{a_i}\\
=&\prod\limits_{i=0}^k\left[\sum\limits_{j_i=0}^{a_i}x^{j_ip^i}\dbinom{a_i}{j_i}\right]
\end{aligned}
$$
上式左端 $x^m$ 的系数为 $\tbinom{n}{m}$，考虑到 $m$ 表示成 $p$ 进制的唯一性，$m=b_0+b_1p^1+\cdots+b_kp^k$，故上式右端 $x^m$ 的系数应为
$$
\prod\limits_{i=0}^k\dbinom{a_i}{b_i}(\text{mod }p).
$$
故有 
$$
\begin{equation}
\dbinom{n}{m}\equiv\prod\limits_{i=0}^k\dbinom{a_i}{b_i}(\text{mod }p).\tag{3}
\end{equation}
$$

<div align="right">证毕.</div>

**$b_i$ 有可能大于 $a_i$，那么此时式 $(3)$ 仍成立吗？**

仍成立。

**证明：**

根据组合数的定义，我们知道，当 $a_i<b_i$ 时，$\tbinom{a_i}{b_i}=0$，所以式 $(3)$ 右端的柿子等于零；再来看左边的柿子：
$$
\begin{aligned}
(1+x)^n=&(1+x)^{\sum\limits_{i=0}^ka_ip^i}=\prod\limits_{i=0}^k[(1+x)^{p^i}]^{a_i}\\
=&\prod\limits_{i=0}^k[1+x^{p^i}+\sum\limits_{j_i=1}^{p^i-1}\dbinom{p^i}{j_i}x^{j_i}]^{a_i}
\end{aligned}
$$
所以得
$$
\begin{align}
(1+x)^n=\prod\limits_{i=0}^k[1+x^{p^i}+\sum\limits_{j_i=1}^{p^i-1}\dbinom{p^i}{j_i}x^{j_i}]^{a_i}\tag{4}
\end{align}
$$


不难发现，在式 $(4)$ 右边出现项 $x^{b_ip^i}$ 是有可能的，我们将 $[1+x^{p^i}+\sum\limits_{j_i=1}^{p^i-1}\dbinom{p^i}{j_i}x^{j_i}]^{a_i}$ 展开，得到：
$$
\underbrace{(1+x^{p^i}+\sum\limits_{j_i=1}^{p^i-1}\dbinom{p^i}{j_i}x^{j_i})(1+x^{p^i}+\sum\limits_{j_i=1}^{p^i-1}\dbinom{p^i}{j_i}x^{j_i})\cdots(1+x^{p^i}+\sum\limits_{j_i=1}^{p^i-1}\dbinom{p^i}{j_i}x^{j_i})}_{a_i\text{个}}
$$
显然有多种选取方法可以得到 $x^{b_ip^i}$，比如在第一个柿子中选 $x^{p^i}$，在第二个式子中选 $x^{b_i}$，其他的柿子都选 $1$，最终的结果即为 $x^{b_ip^i}$。但注意到，无论怎样选取，必然有至少一个因子是从 $\sum_{j_i=1}^{p^i-1}\tbinom{p^i}{j_i}x^{j_i}$ 中选取得到的，所以项 $x^{b_ip^i}$ 前的系数至少有一个为 $\tbinom{p^i}{j_i},1\leq j_i\leq p^i-1$，而我们知道 $p|\tbinom{p^i}{j_i},1\leq j_i\leq p^i-1$，故上式在模 $p$ 意义下时，设 $x^{b_ip^i}$ 的系数为 $\alpha$，必然有
$$
p|\alpha,\quad\alpha x^{b_ip^i}\equiv0(\text{mod }p).
$$
所以 $x^{b_ip^i}$ 的系数在模 $p$ 意义下为 $0.$ 

那么，在由相乘得到 $x^m=x^{b_0+b_1p^1+\cdots+b_kp^k}$ 时，自然项 $x^m$ 的系数也为 $0$，所以，式 $(4)$ 左边项 $x^m$ 的系数在模 $p$ 意义下为 $0$，而单独分析式 $(4)$ 左端柿子中 $x^m$ 的系数应为 $\tbinom{n}{m}$，所以可知
$$
\dbinom{n}{m}\equiv0\equiv\prod\limits_{i=0}^k\dbinom{a_i}{b_i}(\text{mod }p).
$$
即得式 $(3)$ 在 $\exists a_i<b_i$ 时仍成立。

<div align="right">证毕.</div>

###