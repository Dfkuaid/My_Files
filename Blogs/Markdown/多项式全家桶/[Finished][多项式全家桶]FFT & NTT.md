# #1.0 多项式

## #1.1 环和域

> 这一节没啥卵用...

### #1.1.1 环

如果一个非空集合 $R$ 上定义了两个二元运算 $+,\cdot$（分别称为加法和乘法），满足：

1. $(R,+)$ 构成 $\text{Abel}$ 群（满足交换律的群）；
2. **乘法结合律**：$(a\cdot b)\cdot c=a\cdot(b\cdot c),\forall\ a,b,c\in R;$
3. **分配率**：$(a+b)\cdot c=a\cdot c+b\cdot c,\ c\cdot(a+b)=c\cdot a+c\cdot b,\forall\ a,b,c\in R,$

则称 $R$ 关于运算 $+,\cdot$ 构成一个**环**，记为 $(R;+,\cdot)$，或简记为 $R.$

若环 $R$ 中成立

4. **乘法交换律**：$a\cdot b=b\cdot a,\forall\ a,b\in R,$

则称 $R$ 为**交换环**。

环 $R$ 中若存在乘法幺元，即存在 $e\in R$，使得对任意的 $a\in R$，恒有

$$
e\cdot a=a\cdot e=a,
$$

则称 $R$ 为**幺环**。

设 $R$ 为幺环，$a\in R$，如果存在 $b\in R$ 使得 $b\cdot a=e$，则称 $b$ 为 $a$ 的一个**左逆元**。类似的，如果存在 $c\in R$ 使得 $a\cdot c=e$，则称 $c$ 是 $a$ 的一个**右逆元**。如果 $b\in R$ 使得 $ba=ab=e$，则称 $b$ 为 $a$ 的**逆元**，记为 $a^{-1}$。同时称 $a$ 为**可逆元**或**单位元**。

### #1.1.2 域

设 $D$ 是含有至少两个元素的幺环。如果 $D$ 的每个非零元素都可逆，则称 $D$ 是一个**体**。具有乘法交换律的体称为 **域**。

**设 $p$ 是一个质数，那么模 $p$ 意义下的集合 ${0,1,\cdots,p−1}$ 是一个域，记为 $F_p$。**

下文的多项式都在域上。

## #1.2 多项式

### #1.2.1 定义

设 $R$ 是一个环，$a_0,a_1,\cdots,a_n$ 为 $R$ 中的元素且 $a_n\ne0,x_0$ 始终表示 $1$，则

$$
f(x)=\sum\limits_{k=0}^na_kx^k
$$

称为 $R$ 上次数为 $n$ 的多项式。

### #1.2.2 卷积

对于数组 $a,b$，令

$$
c_k=\sum\limits_{i+j=k}a_ib_j=\sum\limits_{i=0}^ka_ib_{k-i}=\sum\limits_{j=0}^ka_{k-j}b_j,
$$

则称 $c$ 为 $a$ 和 $b$ 的卷积。

### #1.2.3 多项式乘法

设 $f(x)=\sum\limits_{k=0}^na_kx^k$ 和 $g(x)=\sum\limits_{k=0}^mb_kx^k$，利用分配率可得

$$
f(x)g(x)=\sum\limits_{k=0}^{n+m}c_kx^k.
$$

其中 $c$ 是 $a$ 和 $b$ 的卷积。

### #1.2.4 多项式的点值表示

设 $f(x)=\sum\limits_{k=0}^na_kx^k$ 为次数不大于 $n$ 的多项式，对于 $n+1$ 个点 $x_0,x_1,\cdots,x_n$，有

$$
\begin{pmatrix}f(x_0)\\f(x_1)\\f(x_1)\\\vdots\\f(x_n)\end{pmatrix}=\begin{pmatrix}1&x_0&x_0^2&\cdots&x_0^n\\1&x_1&x_1^2&\cdots&x_1^n\\1&x_2&x_2^2&\cdots&x_2^n\\\vdots&\vdots&\vdots&\ddots&\vdots\\1&x_n&x_n^2&\cdots&x_n^n\end{pmatrix}\begin{pmatrix}a_0\\a_1\\a_2\\\vdots\\a_n\end{pmatrix}
$$

若 $x_0,x_1,\cdots,x_n$ 互不相同，则等式右边的矩阵可逆，那么

$$
\begin{pmatrix}a_0\\a_1\\a_2\\\vdots\\a_n\end{pmatrix}=\begin{pmatrix}1&x_0&x_0^2&\cdots&x_0^n\\1&x_1&x_1^2&\cdots&x_1^n\\1&x_2&x_2^2&\cdots&x_2^n\\\vdots&\vdots&\vdots&\ddots&\vdots\\1&x_n&x_n^2&\cdots&x_n^n\end{pmatrix}^{-1}\begin{pmatrix}f(x_0)\\f(x_1)\\f(x_1)\\\vdots\\f(x_n)\end{pmatrix}
$$

**即 $n+1$ 个点值对 $(x_k,f(x_k))$ 可以唯一确定 $f(x).$**

那么，我们来看如何用点值来处理多项式乘法。

设 $f(x)=\sum\limits_{i=0}^na_ix^i,g(x)=\sum\limits_{i=0}^mb_ix^i$，设 $h(x)$ 为 $f(x)$ 和 $g(x)$ 的乘积，于是有

$$
h(x)=f(x)g(x)=\sum\limits_{i=0}^{n+m}c_ix^i,
$$

其中 $c$ 是 $a$ 和 $b$ 的卷积。

那么，我们只需要 $n+m+1$ 个互不相同的点 $x_0,x_1,x_2,\cdots,x_{n+m}$，若已知所有的 $f(x_k)$ 和 $g(x_k)$，只需计算所有的 $h(x_k)$，即 $f(x_k)g(x_k)$ 的值便可唯一确定 $h(x)$，即 $f(x)g(x).$

当然，对于 $f(x)+g(x)$ 也是类似的。

### #1.2.5 多项式的根

设 $F,k$ 是域且 $F\subseteq K$，$f(x)$ 是 $F$ 上的多项式， $\alpha$ 是 $K$ 中的元素。若 $f(\alpha)=0$，则称 $\alpha$ 为 $f(x)$ 的一个根。

**$f(x)$ 的根不一定在 $F$ 中。**

### #1.2.6 单位根

对于复数，C++ 有专门的库 ```complex``` 可供使用，声明方式：

``` cpp
#include <complex>

complex <double> a;
complex <double> b(1,0);
complex <double> c;
c.real(1),c.imag(0);
```

多项式 $x^n-1$ 的根称为 $n$ 次单位根。

- 设 $\omega_n=e^{\frac{2\pi i}{n}}$ 为复数，由欧拉公式

$$
e^{ix}=\cos x+i\sin x
$$
容易验证 $\omega_n^n=1$。$1,\omega_n,\omega_n^2,\cdots,\omega_n^{n-1}$ 为 $n$ 个互不相同的 $n$ 次单位根。

<div id='nature'></div>

### #1.2.7 单位根 の 性质

1. $\omega_{2n}^{2k}=\omega_{n}^k.$

对应的点/向量是相同的。

$$
(\cos\dfrac{4k\pi}{2n},\sin\dfrac{4k\pi}{2n})=(\cos\dfrac{2k\pi}{n},\sin\dfrac{2k\pi}{n})
$$

2. $1,\omega_n,\omega_n^2,\cdots,\omega_n^{n-1}$ 互不相等。
3. $\omega_{n}^{k+\frac{n}{2}}=-\omega_n^k.$

$$
\omega_n^{k+\frac n 2}=\omega_n^k\cdot\omega_n^\frac n 2
$$

我们只需证明 $\omega_n^\frac n 2=-1$ 即可。不难发现在坐标系上，$\omega_n^n$ 是绕了一圈，坐标为 $(1,0)$，$\omega_n^\frac n 2$ 就是绕半圈，坐标为 $(-1,0)$，所以 $\omega_n^\frac n 2=-1.$

4. $\sum\limits_{i=0}^{n-1}(\omega_n^k)^i=n[k=0].$

显然当 $k=0$ 时上式等于 $1$，下面来证当 $k\ne0$ 时上式等于 $0.$

设

$$
S(k)=\sum\limits_{i=0}^{n-1}(\omega_n^k)^i=1+\omega_n^k+\omega_n^{2k}+\cdots+\omega_n^{(n-1)k},
$$

则

$$
\begin{aligned}
S(k)=&1+\omega_n^k+\omega_n^{2k}+\cdots+\omega_n^{(n-1)k}\\
\omega_n^kS(k)=&\omega_n^k+\omega_n^{2k}+\omega_n^{3k}\cdots+\omega_n^{nk}\\
\end{aligned}
$$

于是有

$$
(\omega_n^k-1)S(k)=\omega_n^{nk}-1\\
$$

$$
\begin{aligned}
S(k)=&\dfrac{\omega_n^{nk}-1}{\omega_n^k-1}=\dfrac{(\omega_n^n)^k-1}{\omega_n^k-1}\\
=&\dfrac{1-1}{\omega_n^k-1}=0
\end{aligned}
$$

# #2.0 快速傅里叶变换（FFT）

## #2.1 离散傅里叶变换（DFT）

### #2.1.1 定义

设 $a$ 为大小为 $n$ 的数组，$f(x)=\sum\limits_{k=0}^{n-1}a_kx^k$，定义

$$
\text{DFT}(a)=(f(1),f(\omega_n),f(\omega_n^2),\cdots,f(\omega_n^{n-1})),
$$

称为 $a$ 的离散傅里叶变换，或 $a$ 的 $\texttt{DFT}.$

$\texttt{DFT}$ 将 $f(x)$ 的系数数组 $a$ 变换成 $f(x)$ 在每个 $\omega_n^k$ 处的值，从而得到了 $f(x)$ 的一个点值表示。

### #2.1.2 IDFT

$\texttt{DFT}$ 的逆变换称为 $\texttt{IDFT}$，也记作 $\texttt{DFT}^{−1}$。$\texttt{IDFT}$ 将 $f(x)$ 在 $n$ 个 $n$ 次单位根处的点值表示变换为其系数表示。

**只要将 $\text{DFT}$ 中的 $\omega_n$ 换成 $\omega_n^{-1}$ 并将结果除以 $n$，就可以得到 $\text{IDFT}$。**

更形式化地说，设 $g(x)=\sum\limits_{k=0}^{n-1}f(\omega_n^k)x^k$，则有

$$
\begin{aligned}
a=&\text{DFT}^{-1}(\text{DFT(a)})\\
=&\dfrac{1}{n}(g(1),g(\omega_n^{-1}),g(\omega_n^{-2}),\cdots,g(\omega_n^{-(n-1)})).
\end{aligned}
$$

**证明**：

设 $(y_0,y_1,y_2,\cdots,y_{n−1})$ 为多项式 $A(x)=\sum\limits_{i=0}^{n-1}a_ix^i$ 的 $\texttt{DFT}$。

现在我们再设一个多项式 $B(x)=\sum\limits_{i=0}^{n-1}b_ix^i$，现在我们把上面的 $n$ 个单位根的倒数，即 $\omega^0_n,\omega^{−1}_n,\omega^{−2}_n,\cdots,\omega^{−(n−1)}_n$ 作为 $x$ 代入 $B(x)$，得到一个新的离散傅里叶变换 $(z_0,z_1,z_2,\cdots,z_{n−1})$。

$$
\begin{align*}  
z_k &= \sum_{i = 0}^{n - 1} y_i(\omega_n^{-k})^i \\  
&= \sum_{i = 0}^{n - 1}(\sum_{j = 0}^{n - 1} a_j(\omega_n^i)^j)(\omega_n^{-k})^i  \\
&= \sum_{j = 0}^{n - 1}a_j(\sum_{i = 0}^{n - 1}(\omega_n^{j - k})^i)
\end{align*}
$$

这个 $\sum_{i = 0}^{n - 1}(\omega_n^{j - k})^i$ 是可求的：当 $j−k=0$ 时，它等于 $n$; 其余时候，通过等比数列求和可知它等于

$$
\frac{(\omega_n^{j-k})^n-1}{\omega_n^{j-k}-1}=\frac{(\omega_n^n)^{j-k}-1}{\omega_n^{j-k}-1}=\frac{1^{j-k}-1}{\omega_n^{j-k}-1}=0
$$

那么，$z_k$ 就等于 $na_k$, 即：

$$
a_i = \frac{z_i}{n}
$$

## #2.2 卷积

### #2.2.1 循环卷积

对于大小为 $n$ 的数组 $a,b$，令

$$
c_k=\sum\limits_{(i+j)\bmod\ n=k}a_ib_j=\sum\limits_{i+j=k}a_ib_j+\sum\limits_{i+j=n+k}a_ib_j
$$

则称 $c$ 为 $a$ 和 $b$ 的循环卷积，用 $a\otimes b$ 表示。

### #2.2.2 卷积定理

设 $f(x)=\sum\limits_{k=0}^{n-1}a_kx^k,g(x)=\sum\limits_{k=0}^{n-1}b_kx^k,h(x)=\sum\limits_{k=0}^{n-1}c_kx^k$。对于任意正数 $s$ 由于 $(\omega_n^s)^n=1$，有

$$
\begin{aligned}
f(\omega_n^s)g(\omega_n^s)=&\sum\limits_{k=0}^{n-1}\left(\sum\limits_{i+j=k}a_ib_j(\omega_n^s)^k+\sum\limits_{i+j=n+k}a_ib_j(\omega_n^s)^{n+k}\right)\\
=&\sum\limits_{k=0}^{n-1}\left(\sum\limits_{i+j=k}a_ib_j(\omega_n^s)^k+\sum\limits_{i+j=n+k}a_ib_j(\omega_n^s)^{k}(\omega_n^s)^n\right)\\
=&\sum\limits_{k=0}^{n-1}\left(\sum\limits_{i+j=k}a_ib_j+\sum\limits_{i+j=n+k}a_ib_j\right)(\omega_n^s)^k\\
=&h(\omega_n^s)
\end{aligned}
$$

注意这里 $c=a\otimes b.$

由于 $h(x)$ 是次数不大于 $n-1$ 的多项式，由点值表示的唯一性得

$$
\text{DFT}^{-1}(\text{DFT}(a)\circ\text{DFT}(b))=a\otimes b.
$$

其中 $\circ$ 为逐元素相乘的运算。

狭义的 $\texttt{DFT}$ 仅指代复数域上的 $\texttt{DFT}$，因此常把 $F_p$ 上的 $\texttt{DFT}$ 称为数论变换，或 $\texttt{NTT}$。当然，这两种形式的 $\texttt{DFT}$ 的原理是相同的。

## #2.3 FFT 综述

快速傅里叶变换，或 $\texttt{FFT}$，是快速计算 $\texttt{DFT}$ 的方法，其时间复杂度仅为 $O(n\log n)$。

在 OI 中，通常只实现要求 $n$ 为 $2$ 的幂的 $\texttt{FFT}$。如果要计算 $a$和 $b$ 的卷积 $c$，可以取 $n$ 为不小于 $c$ 的大小的最小的 $2$ 的幂，将$a$ 和 $b$ 的大小均扩充为 $n$ 后再计算。如果要计算循环卷积，可以先计算普通卷积，再将第 $k+n$ 项加到第 $k$ 项上。

## #2.4 FFT の 实现

设 $n$ 为 $2$ 的幂。对于 $f(x)=\sum\limits_{k=0}^{n-1}a_kx^k$，设

$$
\begin{aligned}
f_0(x)=&\sum\limits_{k=0}^{n/2-1}a_{2k}x^k\\
f_1(x)=&\sum\limits_{k=0}^{n/2-1}a_{2k+1}x^k
\end{aligned}
$$

那么有 $f_(x)=f_0(x^2)+xf_1(x^2).$

当 $0\leq s<\dfrac{n}{2}$ 时，有

$$
\begin{aligned}
f(\omega_n^s)&=f_0(\omega_n^{2s})+\omega_n^sf_1(\omega_n^{2s})\\
&=f_0(\omega_{\frac{n}{2}}^{s})+\omega_n^sf_1(\omega_{\frac{n}{2}}^{s})
\end{aligned}
$$

显然有 $\omega_n^{\frac{n}{2}}=-1$，于是当 $\dfrac{n}{2}\leq s<n$ 时，有

$$
\begin{aligned}
f(\omega_n^s)=&f_0((\omega_n^s)^2)+\omega_n^sf_1((\omega_n^s)^2)\\
=&f_0((\omega_n^{s-\frac{n}{2}})^2)-\omega_n^{s-\frac{n}{2}}f_1((\omega_n^{s-\frac n 2})^2)\\
=&f_0(\omega_n^{2s-n})-\omega_n^{s-\frac{n}{2}}f_1(\omega_n^{2s-n})\\
=&f_0(\omega_{\frac n 2}^{s-\frac n 2})-\omega_n^{s-\frac n 2}f_1(\omega_\frac n 2^{s-\frac n 2})
\end{aligned}
$$

也就是说，对于 $0\leq s<\dfrac{n}{2}$，有

$$
\begin{aligned}
f(\omega_n^s)&=f_0(\omega_{\frac{n}{2}}^{s})+\omega_n^sf_1(\omega_{\frac{n}{2}}^{s})\\
f(\omega_n^{s+\frac n 2})&=f_0(\omega_\frac n 2^s)-\omega_n^sf_1(\omega_\frac n 2^s)
\end{aligned}
$$

那么只要递归地算出 $f_0(x)$ 和 $f_1(x)$ 的 $\texttt{DFT}$，就可以以 $O(n)$ 的时间复杂度计算 $f(x)$ 的 $\texttt{DFT}$，总时间复杂度为 $O(n\log n)$。

对于 $n=2^k$，可以将所有下标视为 $k$ 位二进制数。将下标根据是否小于 $\dfrac{n}{2}$ 划分成两部分是根据最高位进行划分，而根据奇偶性划分成两部分是根据最低位进行划分。对于前者，可以自然地将递归树展开。而对于后者，只要将所有下标的二进制位翻转，就可以转化为前者的情况。

展开递归树不仅会减少递归的开销，还会去除冗余的操作，并且优化了内存访问效率。

# #3.0 FFT の 应用

- **直接运算（构造卷积）**
  两个数列卷积可以看做两个多项式相乘。
- **多项式运算**
- **字符串匹配**

## #3.1 [P3803 【模板】多项式乘法（FFT）](https://www.luogu.com.cn/problem/P3803)

板子题。

``` cpp
const int N = 10000010;
const int INF = 0x3fffffff;
const double PI = acos(-1);

typedef complex <double> cp;

int n,m,t = 1,res[N],ta[N],tb[N],lim,r[N];
cp ca[N],cb[N];

inline void fft(cp *a,int type){
    for (int i = 0;i < t;i ++)
      if (i < r[i]) swap(a[i],a[r[i]]);
    for (int mid = 1;mid < t;mid <<= 1){
        cp OMG(cos(PI / mid),type *sin(PI / mid));
        for (int R = mid << 1,j = 0;j < t;j += R){
            cp omg(1,0);
            for (int k = 0;k < mid;k ++,omg = omg * OMG){
                cp tmp1 = a[j + k],tmp2 = omg * a[j + mid + k];
                a[j + k] = tmp1 + tmp2;
                a[j + mid + k] = tmp1 - tmp2;
            }
        }
    }
}

int main(){
    scanf("%d%d",&n,&m);
    while (t <= n + m) t <<= 1,lim ++;
    for (int i = 0;i <= n;i ++){
        scanf("%d",&ta[i]);
        ca[i].real(ta[i]);
    }
    for (int i = 0;i <= m;i ++){
        scanf("%d",&tb[i]);
        cb[i].real(tb[i]);
    }
    for (int i = 0;i < t;i ++)
      r[i] = (r[i >> 1] >> 1) | ((i & 1) << (lim - 1));
    fft(ca,1);fft(cb,1);
    for (int i = 0;i < t;i ++)
      ca[i] *= cb[i];
    fft(ca,-1);
    for (int i = 0;i < t;i ++)
      res[i] = floor(ca[i].real() / t + 0.5);
    for (int i = 0;i <= n + m;i ++)
      cout << res[i] << " ";
    return 0;
}
```

## #3.2 [P1919 【模板】A*B Problem升级版](https://www.luogu.com.cn/problem/P1919)

也是板子题。将数 $A$ 看做多项式

$$
A(x)=\sum\limits_{k=0}^{n}a_k10^k
$$

即可。

注意要将读入的数据反向存储，因为是由低位影响高位。

``` cpp
const int N = 3e6 + 10;
const double PI = acos(-1);
const int INF = 0x3fffffff;

typedef complex <double> cp;

string sa,sb;
int lena,lenb,t = 1,lt,r[N],res[N];
cp a[N],b[N];

void fft(cp *A,int opt){
    /*...总之就是 FFT...*/
}

int main(){
    cin >> sa >> sb;
    lena = sa.length();lenb = sb.length();
    while (t <= lena + lenb) t <<= 1,lt ++;
    for (int i = 0;i < lena;i ++)
      a[i].real((double)(sa[lena - i - 1] - '0'));
    for (int i = 0;i < lenb;i ++)
      b[i].real((double)(sb[lenb - i - 1] - '0'));
    for (int i = 0;i < t;i ++)
      r[i] = (r[i >> 1] >> 1) | ((i & 1) << (lt - 1));
    fft(a,1);fft(b,1);
    for (int i = 0;i < t;i ++) a[i] *= b[i];
    fft(a,-1);
    for (int i = 0;i < t;i ++){
        res[i] += floor(a[i].real() / t + 0.5);
        res[i + 1] += res[i] / 10;
        res[i] %= 10;
    }
    while (!res[t] && t >= 1) t --;
    t ++;
    for (int i = t - 1;i >= 0;i --)
      cout << res[i];
    return 0;
}

```

## #3.3 [CF993E Nikita and Order Statistics](https://www.luogu.com.cn/problem/CF993E)

由于 $x$ 固定，直接把 $a$ 中小于 $x$ 数的设为 $1$，其余数设为 $0$，只需要求有多少个区间的和为 $k$。设 $s$ 为 $a$ 的前缀和，则只需要求有多少个数对 $(s_i,s_j)$ 满足 $s_j−s_i=k$，或 $s_j−k=s_i$。

设 $f_{s_i}$ 为 $s_i$ 的出现次数，则 $k$ 的答案为

$$
\begin{aligned}
\sum\limits_{i=k}^nf_if_{i-k}=&\sum\limits_{i=k}^nf_if_{n-(n+k-i)}=\sum\limits_{i+j=n+k}f_if_{n-j},\\
\end{aligned}
$$

令 $g_j=f_{n-j}$，于是有

$$
\begin{aligned}
\sum\limits_{i+j=n+k}f_if_{n-j}=\sum\limits_{i+j=n+k}f_ig_j,\\
\end{aligned}
$$

于是求 $f*g$ 即可。

不过要注意，上面的式子只适用于 $k>0$ 的情况。

那么对于 $k=0$ 的情况，我们注意到，只有前缀和数组中一串相同的数才会对答案造成贡献，但同时注意到，这一串数的第一个数不会造成贡献，因为这是前缀和改变的第一个数，此位置上必定为 $1$，于是一串长度为 $l$ 的相同的数的贡献为 $\sum\limits_{i=1}^{l-1}i=\dfrac{l(l-1)}{2}.$

``` cpp
const int N = 700010;
const double PI = acos(-1);
const int INF = 0x3fffffff;

typedef complex <double> cp;

ll a[N],n,sum[N];
ll r[N],x,ans;
ll t = 1,lt,cnt;
cp f[N],g[N];

inline void fft(cp *A,int opt){
    /*...总之就是 FFT...*/
}

inline ll RS(int x){
    return (ll)(1 + x) * x / 2;
}

int main(){
    scanf("%lld%lld",&n,&x);
    for (int i = 1;i <= n;i ++){
        scanf("%lld",&a[i]);
        if (a[i] < x) a[i] = 1;
        else a[i] = 0;
    }
    f[0].real(1);g[n].real(1);
    for (int i = 1;i <= n;i ++){
        sum[i] = sum[i - 1] + a[i];
        f[sum[i]].real(f[sum[i]].real() + 1);
        g[n - sum[i]].real(g[n - sum[i]].real() + 1);
    }
    while (t <= 2 * n + 2) t <<= 1,lt ++;
    for (int i = 0;i < t;i ++)
      r[i] = (r[i >> 1] >> 1) | ((i & 1) << (lt - 1));
    fft(f,1);fft(g,1);
    for (int i = 0;i < t;i ++) f[i] *= g[i];
    fft(f,-1);
    for (int i = 1;i <= n;i ++)
      if (sum[i] != sum[i - 1])
        ans += RS(cnt),cnt = 0;
      else cnt ++;
    ans += RS(cnt);
    printf("%lld ",ans);
    for (int i = n + 1;i <  2 * n + 1;i ++)
     printf("%lld ",(ll)(f[i].real() / t + 0.5));
    return 0;
}
```

## #3.4 [P3723 [AH2017/HNOI2017] 礼物](https://www.luogu.com.cn/problem/P3723)

简化题意，$a,b$ 是两个循环节长度为 $n$ 的数组，让我们求

$$
\min\limits_{c,k}\left\{\sum\limits_{i=1}^n(c+a_{i+k}-b_i)^2\right\},
$$

将上式展开得

$$
\begin{aligned}
&\sum\limits_{i=1}^n(c+a_{i+b}-b_i)^2\\
=&\sum\limits_{i=1}^n(c^2+a_{i+k}^2+b_i^2+2ca_{i+k}-2cb_i-2a_{i+k}b_i)\\
=&\sum\limits_{i=1}^n(c^2+a_i^2+b_i^2+2ca_i-2cb_i-2a_{i+k}b_i)\\
=&nc^2+\sum\limits_{i=1}^n(a_i^2+b_i^2)+2c\sum\limits_{i=1}^n(a_i-b_i)-2\sum\limits_{i=1}^na_{i+k}b_i.
\end{aligned}
$$

注意到 $\sum\limits_{i=1}^n(a_i^2+b_i^2)$ 和 $\sum\limits_{i=1}^n(a_i-b_i)$ 是对于给定数据的两个定值，所以式

$$
nc^2+2c\sum\limits_{i=1}^n(a_i-b_i)+\sum\limits_{i=1}^n(a_i^2+b_i^2)\tag1
$$

可看做关于 $c$ 的二次函数。由于 $n>0$，所以 $(1)$ 在

$$
c=-\dfrac{2\sum\limits_{i=1}^n(a_i-b_i)}{2n}=-\dfrac{\sum\limits_{i=1}^n(a_i-b_i)}{n}
$$

时取最小值（要考虑不能整除的情况）。我们还需要求 $\sum\limits_{i=1}^na_{i+k}b_i$ 的最大值，令 $t_i=b_{n-i}$，有

$$
\sum\limits_{i=1}^na_{i+k}b_i=\sum\limits_{i=1}^na_{i+k}t_{n-i}=d_{n+k}.
$$

于是 $k$ 对应的值便是 $a*t$ 中第 $n+k$ 项，取最大值即可。

这里要注意，因为要处理环的问题，所以需要将 $a$ 复制一遍。

``` cpp
const int N = 500010;
const double PI = acos(-1);
const int INF = 0x3fffffff;

typedef complex <double> cp;

ll t = 1,lt,r[N];
ll n,m,a[N],b[N],FV1,FV2,c,ans1,ans2;
cp f[N],g[N];

inline void fft(cp *A,int opt){
    /*...总之就是 FFT...*/
}

int main(){
    scanf("%lld%lld",&n,&m);
    for (int i = 1;i <= n;i ++){
        scanf("%lld",&a[i]);
        f[n - i + 1].real(a[i]);
        FV1 += a[i] * a[i];
        FV2 += a[i];
    }
    for (int i = 1;i <= n;i ++){
        scanf("%lld",&b[i]);
        g[i].real(b[i]);
        g[i + n].real(b[i]);
        FV1 += b[i] * b[i];
        FV2 -= b[i];
    }
    c = - FV2 / n;
    ans1 = min(min(n * c * c + 2 * c * FV2 + FV1,
        n * (c - 1) * (c - 1) + 2 * (c - 1) * FV2 + FV1),
        n * (c + 1) * (c + 1) + 2 * (c + 1) * FV2 + FV1);
    while (t <= 3 * n) t <<= 1,lt ++;
    for (int i = 0;i < t;i ++)
      r[i] = (r[i >> 1] >> 1) | ((i & 1) << (lt - 1));
    fft(f,1),fft(g,1);
    for (int i = 0;i < t;i ++) f[i] *= g[i];
    fft(f,-1);
    for (int i = 1;i <= n;i ++)
      ans2 = max(ans2,(ll)(f[n + i].real() / t + 0.5));
    printf("%lld",ans1 - 2 * ans2);
    return 0;
}
```

## #3.5 字符串匹配

### #3.5.1 基础

设有两个文本串 $S,T$，要求 $S$ 在 $T$ 中的匹配，可以用 $\texttt{FFT}$ 解决。设两个串在 $x$ 处匹配成功（$x$ 为结尾），那么应当有

$$
\sum\limits_{i=0}^{|s|-1}(s_i-t_{x-|s|+i+1})^2=0,
$$

令 $a_i=s_{|s|-i-1}$，即将 $s$ 翻转，有

$$
\begin{aligned}
&\sum\limits_{i=0}^{|s|-1}(s_i-t_{x-|s|+i+1})^2\\
=&\sum\limits_{i=0}^{|s|-1}(a_{s|-i-1|}-t_{x-|s|+i+1})^2=\sum\limits_{i=0}^{|s|-1}(a_i-t_{x-i})^2\\
=&\sum\limits_{i=0}^{|s|-1}(a_i^2+t_{x-i}^2)-2\sum\limits_{i=0}^{|s|-1}a_it_{x-i}\\
\end{aligned}
$$

注意到等式前半部分是定值，后半部分可看作 $a * t$ 的第 $x$ 项。只需判断每个位置 $x$ 是否符合即可。

### #3.5.2 带通配符的匹配

**通配符**指的是可以匹配任意字符的符号。

设有两个文本串 $S,T$，$S,T$ 中存在通配符，要求 $S$ 在 $T$ 中的匹配，可以用 $\texttt{FFT}$ 解决。设两个串在 $x$ 处匹配成功（$x$ 为结尾），令通配符的值为 $0$，那么应当有

$$
\sum\limits_{i=0}^{|s|-1}s_it_{x-|s|+i+1}(s_i-t_{x-|s|+i+1})^2=0,
$$

令 $s_i=s_{|s|-i-1}$，即将 $s$ 翻转，有

$$
\begin{aligned}
&\sum\limits_{i=0}^{|s|-1}s_it_{x-|s|+i+1}(s_i-t_{x-|s|+i+1})^2\\
=&\sum\limits_{i=0}^{|s|-1}s_{|s|-i-1}t_{x-|s|+i+1}(s_{|s|-i-1}-t_{x-|s|+i+1})^2\\
=&\sum\limits_{i=0}^{|s|-1}s_it_{x-i}(s_i-t_{x-i})^2\\
=&\sum\limits_{i=0}^{|s|-1}s_it_{x-i}(s_i^2+t_{x-i}^2-2s_it_{x-i})\\
=&\sum\limits_{i=0}^{|s|-1}(s_i^3t_{x-i}+s_it_{x-i}^3-2s_i^2t_{x-i}^2)\\
=&\sum\limits_{i=0}^{|s|-1}s_i^3t_{x-i}+\sum\limits_{i=0}^{|s|-1}s_it_{x-i}^3-2\sum\limits_{i=0}^{|s|-1}s_i^2t_{x-i}^2
\end{aligned}
$$

注意这里 $s_i^3$ 只是某一项的三次方，不是我卷我自己。做 $\texttt{FFT}$，只需判断每个位置 $x$ 是否符合即可。

# #4.0 数论变换（NTT）

> $\texttt{NTT}$ 其实就是在域 $F_p$ 上做 $\texttt{DFT}$。

我们发现，因为 $\texttt{FFT}$ 用的是实数计算，必然会产生精度误差，那怎么办？—— $\texttt{NTT}$ 应运而生！

## #4.1 原根

先来简单介绍下接下来的主角——**原根**

### #4.1.1 阶

给定正整数 $n$，对于 $a$ 满足 $a⊥n$，定义 $a$ 模 $n$ 的阶为最小的正整数 $d$ 使得下式成立：

$$
a^d\equiv1(\bmod n).
$$

$a$ 模 $n$ 的阶为 $\delta_n(a)$，由 $\text{Euler}$ 定理知有 $\delta_n(a)|\varphi(n).$

### #4.1.2 原根

若 $\delta_n(a)=\varphi(n)$，则称 $a$ 是模 $n$ 的原根。形象点说，也就是 $\varphi(n)$ 是最小的 $d$ 满足

$$
a^d\equiv1(\bmod n)
$$

可以看出，$a$ 是模 $n$ 的原根当且仅当 $a^0,a^1,\cdots,a^{\varphi(n)−1}$ 在 $\bmod\ n$ 意义下两两不同。这也是原根重要的性质和等价定义。

模 $n$ 存在原根当且仅当 $n=1,2,4,p^k,2p^k$，其中 $p$ 为奇素数，$k$ 为正整数。

## #4.2 推翻单位根！！1

为啥有精度误差？因为我们用的是复数域上的单位根，那能不能找个整数顶着？可以，用 $F_p$ 上的**原根**。

现在，假设我们**在 $\bmod p$ 的意义下**，$p$ 是一个素数，设 $g$ 为 $p$ 的原根。

设 $p-1=q\cdot2^r=q\cdot n$，我们令 $n$ 为多项式的项数，为了让原根推翻单位根，我们要看它是否满足单位根在 $\texttt{FFT}$ 过程中体现的[性质](#nature)。设 $\omega_n=g^q.$

1. $\omega_n^n=1.$

$$
\omega_n^n=g^{qn}=g^{p-1}=g^{\varphi(p)}\equiv1(\bmod p)
$$

2. $\omega_{2n}^{2k}=\omega_{n}^k.$

$$
p-1=q\cdot n=\dfrac q 2\cdot2n
$$

故

$$
\omega_{2n}^{2k}=g^{\frac q 2\cdot2k}=g^{qk}=\omega_{n}^k.
$$

3. $1,\omega_n,\omega_n^2,\cdots,\omega_n^{n-1}$ 互不相等。

假设存在 $\omega_n^i=\omega_n^j$，不妨设 $j<i$，于是有

$$
g^{qi}\equiv g^{qj}(\bmod p)\\
g^{q(i-j)}\equiv 1\equiv g^{qn}(\bmod p)
$$

但显然有 $i-j\ne n$ 且 $q(i-j)<qn=p-1=\varphi(p)$，这与原根的定义/性质相悖。

4. $\omega_{n}^{k+\frac{n}{2}}=-\omega_n^k.$

我们只需证明 $\omega_n^\frac n 2=-1.$

$$
\omega_n^n=(\omega_n^\frac n 2)^2\equiv1(\bmod p)
$$

由原根的定义知 $\omega_n^\frac n 2\ne1$，所以有 $\omega_n^\frac n 2=-1.$

5. $\sum\limits_{i=0}^{n-1}(\omega_n^k)^i=n[k=0].$

显然当 $k=0$ 时上式等于 $1$，下面来证当 $k\ne0$ 时上式等于 $0.$

设

$$
S(k)=\sum\limits_{i=0}^{n-1}(\omega_n^k)^i=1+\omega_n^k+\omega_n^{2k}+\cdots+\omega_n^{(n-1)k},
$$

则

$$
\begin{aligned}
S(k)=&1+\omega_n^k+\omega_n^{2k}+\cdots+\omega_n^{(n-1)k}\\
\omega_n^kS(k)=&\omega_n^k+\omega_n^{2k}+\omega_n^{3k}\cdots+\omega_n^{nk}\\
\end{aligned}
$$

于是有

$$
(\omega_n^k-1)S(k)=\omega_n^{nk}-1\\
$$

$$
\begin{aligned}
S(k)=&\dfrac{\omega_n^{nk}-1}{\omega_n^k-1}=\dfrac{(\omega_n^n)^k-1}{\omega_n^k-1}\\
=&\dfrac{1-1}{\omega_n^k-1}=0
\end{aligned}
$$

现在我们知道了，原根完全满足单位根在 $\texttt{FFT}$ 中所体现的性质，所以我们可以将 $\texttt{FFT}$ 中的单位根换成模数的原根，这样便得到了 $\texttt{NTT}.$

题目中常见的模数为 $998244353=2^{23}\times 7\times 17+1$，它的最小原根是 $3$。于是，只要多项式的长度不超过 $2^{23}$，便可以使用 $\texttt{NTT}$ 而非 $\texttt{FFT}.$

当然，在进行 $\texttt{IDFT}$ 时，我们应当采用所选最小原根在模 $p$ 意义下的逆元，这一步可以通过快速幂实现。

## #4.3 代码实现

``` cpp
const int G = 3;
const int N = 1e7 + 100;
const int MOD = 998244353;
const int INVG = 332748118;
const int INF = 0x3fffffff;

ll n,m,a[N],b[N],r[N],t = 1,lt;

inline ll ksm(ll q,ll k){
    ll res = 1;
    while (k){
        if (k & 1) (res *= q) %= MOD;
        k >>= 1;(q *= q) %= MOD;
    }
    return res % MOD;
}

inline void NTT(ll *A,int opt){
    for (int i = 0;i < t;i ++)
      if (i < r[i]) swap(A[i],A[r[i]]);
    for (int mid = 1;mid < t;mid <<= 1){
        ll OMG = ksm(opt == 1 ? G : INVG,(MOD - 1) / (mid << 1));
        for (int R = mid << 1,l = 0;l < t;l += R){
            ll omg = 1;
            for (int k = 0;k < mid;k ++,(omg *= OMG) %= MOD){
                ll tmp1 = A[l + k],tmp2 = A[l + mid + k] * omg % MOD;
                A[l + mid + k] = (tmp1 - tmp2 + MOD) % MOD;
                A[l + k] =(tmp1 + tmp2) % MOD;
            }
        }
    }
}


int main(){
    scanf("%lld%lld",&n,&m);
    for (int i = 0;i <= n;i ++)
      scanf("%lld",&a[i]);
    for (int i = 0;i <= m;i ++)
      scanf("%lld",&b[i]);
    while (t <= n + m) t <<= 1,lt ++;
    for (int i = 0;i < t;i ++)
      r[i] = (r[i >> 1] >> 1) | ((i & 1) << (lt - 1));
    NTT(a,1);NTT(b,1);
    for (int i = 0;i < t;i ++) (a[i] *= b[i]) %= MOD;
    NTT(a,-1);ll invn = ksm(t,MOD - 2);
    for (int i = 0;i <= n + m;i ++)
      printf("%lld ",(a[i] * invn) % MOD);
    return 0;
}
```

<div id='refer-auth'></div>

# 参考资料

[1] [多项式入门 - hyl天梦](https://www.cnblogs.com/TianMeng-hyl/p/14886109.html)

[2] [傅里叶变换(FFT)学习笔记 - command_block](https://www.luogu.com.cn/blog/command-block/fft-xue-xi-bi-ji)

[3] [快速数论变换超详解 - 星夜](https://zhuanlan.zhihu.com/p/347726949)

[4] [FFT 字符串匹配 - ghj1222](https://www.cnblogs.com/oier/p/10066781.html)