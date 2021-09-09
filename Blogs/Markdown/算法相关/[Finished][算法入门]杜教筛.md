# #1.0 基础知识

## #1.1 积性函数

### #1.1.1 定义

设 $f$ 是数论函数，若对**任意互质的**正整数 $a,b$，都有 $f(ab)=f(a)f(b)$，则称 $f$ 是**积性函数**。若对**任意的**正整数 $a,b$，都有 $f(ab)=f(a)f(b)$，则称 $f$ 是**完全积性的**。

### #1.1.2 性质

若 $f$ 是积性函数，且 $n=p_1^{\alpha_1}p_2^{\alpha_2}···p_s^{\alpha_s}$ 是 $n$ 的标准分解，则有 $f(n)=f(p_1^{\alpha_1})f(p_2^{\alpha_2})···f(p_s^{\alpha_s})$。因此研究积性函数 $f$ 可以转化为研究 $f(p^\alpha)$，即 $f$ 在素数和素数的幂上的取值。

### #1.1.3 一些常见的积性函数

1. **单位函数**

单位函数 $\epsilon(n)$ 定义为：

$$
\epsilon(n)=[n=1] =\begin{cases}1,\quad n=1,\\0,\quad n\ne1.\end{cases}
$$

其中 $[\text{condition}]$ 表示当 $\text{condition}$ 为真时取值为 $1$，否则为 $0$ 的函数。单位函数是**完全积性函数**。

2. **除数函数**

除数函数 $\sigma_k(n)$ 用来表示 $n$ 的因子的 $k$ 次方和：

$$
\sigma_k(n)=\sum\limits_{d|n}d^k.
$$

约数个数 $\sigma_0(n)$ 常记为 $d(n)$，约数和 $\sigma_1(n)$ 常记为 $\sigma(n).$

除数函数都是**积性函数**。

3. **$\text{Euler}$ 函数**

$\text{Euler}$ 函数 $\varphi(n)$ 表示不超过 $n$ 且与 $n$ 互质的正整数的个数。由 $n$ 的标准分解并结合容斥原理，我们可以得到 $\text{Euler}$ 函数的显示表达式：

$$
\varphi(n)=n\cdot\prod\limits_{i=1}^s(1−\dfrac{1}{p_i}),
$$

其中 $n=p_1^{\alpha_1}p_2^{\alpha_2}···p_s^{\alpha_s}$ 是 $n$ 的标准分解。由此易见 $\text{Euler}$ 函数是**积性函数**。

对于任意 $n$，$\text{Euler}$ 函数有如下性质：

$$
n=\sum\limits_{d|n}\varphi(d).
$$

**证明**：

若 $\gcd(n,i)=d$，那么 $\gcd(\dfrac{n}{d},\dfrac{i}{d})=1$。而 $\dfrac{i}{d}\leq\dfrac{n}{d},\dfrac{i}{d}\in\Z$，故这样的 $i$ 有 $φ(\dfrac{n}{d})$ 个。考虑所有 $d|n$，我们也就考虑到了所有 $1$ 到 $n$ 之间的 $n$ 个整数，因此有

$$
n=\sum\limits_{d|n}\varphi(\dfrac{n}{d})=\sum\limits_{d|n}\varphi(d).
$$

<div align=right>证毕.</div>

4. **幂函数** $id_k(n)$， $id_k(n)=n^k,id=id_1.$

5. **恒等函数** $I(n)$，这个函数的值恒为 $1.$

6. **$\text{Mobius}$ 函数**

$$
\mu(n)=\begin{cases}1,&n=1,\\(-1)^s,&n=p_1p_2\cdots p_s\\0,&otherwise.\end{cases}
$$

其中 $p_1,\cdots,p_s$ 是不同素数。可以看出，$\mu(n)$ 恰在 $n$ 无平方因子时非零。易见 $\mu$ 是积性函数。

$\text{Mobius}$ 函数具有以下性质：

$$
\sum\limits_{d|n}\mu(d)=\epsilon(n).
$$

**证明**：

当 $n = 1$ 时显然成立，下面证 $n>1$ 时结论成立。

当根据 $\text{Mobius}$ 函数的定义，当且仅当 $n$ 无平方因子时非零，故能对答案造成贡献的 $d$ 中每个素因子的次数只能为 $0$ 或 $1$，设 $n$ 的唯一分解式为 $n=p_1^{\alpha_1}p_2^{\alpha_2}\cdots p_s^{\alpha_s}$,于是有：

$$
\sum\limits_{d|n}\mu(d)=\sum\limits_{k=0}^s(-1)^k\dbinom{s}{k}=(1-1)^s=0.
$$

<div align=right>证毕.</div>

## #1.2 $\text{Dirichlet}$ 卷积

### #1.2.1 定义

设 $f,g$ 是数论函数，考虑数论函数 $h$ 满足

$$
h(n)=\sum\limits_{d|n}f(d)g(\dfrac{n}{d}),
$$

则称 $h$ 为 $f$ 和 $g$ 的 $\text{Dirichlet}$ 卷积，记作 $h=f*g.$

### #1.2.2 性质

单位函数 $\epsilon$ 是 $\text{Dirichlet}$ 卷积的单位元，即对于任意函数 $f$，有 $\epsilon∗f=f∗\epsilon=f$。$\text{Dirichlet}$ 卷积满足**交换律**和**结合律**。

如果 $f,g$ 都是积性函数，那么 $f∗g$ 也是积性函数。

### #1.2.3 一些关系

通过观察，不难发现有些积性函数可以用 $\text{Dirichlet}$ 卷积的形式联系起来，比如：

- $\mu*I=\epsilon.$
- $\varphi*I=id.$

以上两个是较为常用的转换关系。

<div id='divide'></div>

## #1.3 整除分块

定理：$\left\lfloor\tfrac{n}{d}\right\rfloor$ 的值不超过 $2\sqrt n$ 个。很显然，不证。

假设我们要求 $\sum_{i=1}^n\left\lfloor\frac{n}{i}\right\rfloor.$

通过打表（以 $n=10$ 为例），我们得到：

![](https://pic.imgdb.cn/item/60c31652844ef46bb2c804c9.jpg)

不难发现，对于每一个值相同的块，它的起始点为 $i$，它的最后一个数就是 $n/(n/i).$

``` cpp
for (int l = 1,r;l <= n;l = r + 1){
    r = n / (n / l);
    ans += (r - l + 1) * (n / l);
}
```

再根据我们一开始得到的定理可知，上面程序的时间复杂度为 $O(\sqrt n).$

# #2.0 杜教筛（SUM）

## #2.1 有啥用？

杜教筛是一种利用 $\text{Dirichlet}$ 卷积来构造递推式，从而对积性函数进行快速求和的方法。

比如，我要求 $\sum\limits_{i=1}^n\varphi(i)$，当 $n$ 的规模在 $10^7$ 时，线性筛还可以勉强一战，再高一些，就需要更优的方法了。至于杜教筛为啥更优，后面再说。

## #2.2 怎么办？

假定我们要求 $S(n)=\sum\limits_{i=1}^nf(i)$，我们需要构造出这样两个积性函数 $h,g$，满足 $h=f*g$。

$$
\begin{aligned}
\sum\limits_{i=1}^nh(i)&=\sum\limits_{i=1}^n\sum\limits_{d|i}g(d)\cdot f(\dfrac{i}{d})\\
&=\sum\limits_{d=1}^ng(d)\cdot\sum\limits_{i=1}^{\left\lfloor\frac{n}{d}\right\rfloor}f(i)\\
&=\sum\limits_{d=1}^ng(d)\cdot S(\left\lfloor\dfrac{n}{d}\right\rfloor)\\
&=g(1)\cdot S(n)+\sum\limits_{d=2}^ng(d)\cdot S(\left\lfloor\dfrac{n}{d}\right\rfloor)\\
\end{aligned}
$$
于是有
$$
g(1)\cdot S(n)=\sum\limits_{i=1}^nh(i)-\sum\limits_{d=2}^ng(d)\cdot S(\left\lfloor\dfrac{n}{d}\right\rfloor).\tag1
$$
式 $(1)$ 便是杜教筛的一个常用形式。显然我们希望构造出的 $h$ 的前缀和要好求一些。

抛开右式前半部分不谈，我们来看后半部分 $\sum_{d=2}^xg(d)\cdot S(\left\lfloor\tfrac{n}{d}\right\rfloor).$

看到这个熟悉的形式，不由得让我们想起了 [整除分块](#divide)，然后我们可以递归地解决，并采用记忆化搜索。

当然，我们可以与线性筛结合，进一步降低时间复杂度。

## #2.3 时间复杂度分析

算法的总时间复杂度就是计算所有特殊点处的函数值的时间复杂度。

 回忆特殊点的结构，时间复杂度 $T(n)$ 可以估计为
$$
T(n)=\sum\limits_{i=1}^\sqrt nO\left(\sqrt i\right)+\sum\limits_{i=1}^\sqrt nO\left(\sqrt{\left\lfloor\dfrac{n}{i}\right\rfloor}\right).
$$
显然式中第一项渐进意义上小于第二项。

而对于式中第二项我们可以利用积分估计：
$$
\sum\limits_{i=1}^\sqrt nO\left(\sqrt{\left\lfloor\dfrac{n}{i}\right\rfloor}\right)=O\left(\int_1^{\sqrt n}\sqrt{\dfrac{n}{x}}dx\right)=O(n^{\frac{1}{2}}\cdot n^{\frac{1}{4}})=O(n^{\frac{3}{4}}).
$$


于是算法的时间复杂度为 $O(n^{\frac{3}{4}})$。

假设我们使用 $\text{Euler}$ 筛预先求出了 $\varphi$ 的前 $S$ 项，那么递归部分的时间复杂度变为：
$$
\sum\limits_{i=1}^{\frac{n}{S}}O\left(\sqrt{\left\lfloor\dfrac{n}{i}\right\rfloor}\right)=O\left(\int_1^{\frac{n}{S}}\sqrt{\dfrac{n}{x}}dx\right)=O\left(n^{\frac{1}{2}}\cdot\sqrt{\dfrac{n}{S}}\right)=O\left(\dfrac{n}{\sqrt{S}}\right).
$$
结合 $\text{Euler}$ 筛的时间复杂度为 $O(S)$，于是总体时间复杂度为 $O\left(S+\frac{n}{\sqrt{S}}\right).$

如果取 $S=n^{\frac{2}{3}}$，于是总体时间复杂度为 $O(n^{\frac{2}{3}})$.

## #2.4 例题

> 练习是必不可少的。

### #2.4.1 $\text{Euler}$ 函数

求 $\sum_{i=1}^n\varphi(i).$

熟知
$$
\varphi*I=id.
$$
令 $\phi(n)=\sum_{i=1}^n\varphi(i)$，于是有
$$
\begin{aligned}
\phi(n)=\sum\limits_{i=1}^ni-\sum\limits_{d=2}^n\phi(\left\lfloor\dfrac{n}{d}\right\rfloor).
\end{aligned}
$$

### #2.4.2 $\text{Mobius}$ 函数

求 $\sum_{i=1}^n\mu(i).$

同样考虑 
$$
\mu*I=\epsilon.
$$
令 $\Mu=\sum_{i=1}^n\mu(i)$，于是有
$$
\begin{aligned}
\Mu(n)=1-\sum\limits_{d=2}^n\Mu(\left\lfloor\dfrac{n}{d}\right\rfloor).
\end{aligned}
$$

## #2.5 代码实现

> [P4213 【模板】杜教筛（Sum）](https://www.luogu.com.cn/problem/P4213)

``` cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <tr1/unordered_map> //unordered_map 在 c++98 中需要该头文件
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;
using namespace tr1; //需要该名称空间

const int N = 6000010;
const int INF = 0x3fffffff;
const int L = 5000000;

bool vis[N];
int mu[N],phi[N],sum1[N],n,prim[N],cnt,t;
ll sum2[N];

unordered_map <int,int> w1;
unordered_map <ll,ll> w2;

inline void prework(int x){
    phi[1] = mu[1] = 1;
    for (int i = 2;i <= x;i ++){
        if (!vis[i]){
            prim[++ cnt] = i;
            phi[i] = i - 1;mu[i] = -1;
        }
        for (int j = 1;j <= cnt && prim[j] * i <= x;j ++){
            vis[prim[j] * i] = 1;
            if (i % prim[j] == 0){
                phi[prim[j] * i] = phi[i] * prim[j];
                break;
            }
            else {
                mu[i * prim[j]] = -mu[i];
                phi[i * prim[j]] = phi[i] * (prim[j] - 1);
            }
        }
    }
    for (int i = 1;i <= x;i ++)
      sum1[i] = sum1[i - 1] + mu[i],sum2[i] = sum2[i - 1] + phi[i];
}

inline int djsmu(int x){
    if (x <= L) return sum1[x];
    if (w1[x]) return w1[x];
    int ans = 1;
    for (ll l = 2,r;l <= x;l = r + 1){
        r = x / (x / l);
        ans -= (r - l + 1) * djsmu(x / l);
    }
    return w1[x] = ans;
}

inline ll djsphi(ll x){
    if (x <= L) return sum2[x];
    if (w2[x]) return w2[x];
    ll ans = x * (1 + x) / 2;
    for (ll l = 2,r;l <= x;l = r + 1){
        r = x / (x / l);
        ans -= (r - l + 1) * djsphi(x / l);
    }
    return w2[x] = ans;
}


int main(){
    scanf("%d",&t);
    prework(L);
    while (t --){
        scanf("%d",&n);
        printf("%lld %d\n",djsphi(n),djsmu(n));
    }
    return 0;
}
```

上面使用的 ```unordered_map``` 本身是冲着比 ```map``` 少个 $\log$ 才用的，但发现实际用时差的不多（而且似乎还容易被卡）。

