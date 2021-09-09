TODO: Finish this Blog.
# #1.0 整除
## #1.1 定义
设 $a,b$ 是整数，$b\ne0.$ 如果有整数 $q$ ，使得 $a=qb$，则称 $b$ 整除 $a$，记作 $b\mid a.$ 并称 $b$ 是 $a$ 的约数（或因数）， $a$ 是 $b$ 的倍数，否则称 $b$ 不能整除 $a$，记作 $b \nmid a.$

## #1.2 简单性质

### #1.2.1 概述

以下是整除的几个简单性质：

- 若 $b \mid a,c\mid b$，则 $c\mid a.$
- 若 $c \mid a,c\mid b$，则对任意整数 $x,y$ ，必有 $c \mid (ax+by).$
- 若 $b\mid a,a\ne 0$，则 $\left\vert b \right\vert \leqslant \left\vert a \right\vert.$
- 若 $b\mid a,a \ne 0$，则 $\dfrac{a}{b}\mid a.$

### #1.2.2 简单证明

**1.若 $b \mid a,c\mid b$，则 $c\mid a.$**
$$
\begin{align*}
证明&：\\
&\because b \mid a,c\mid b\\
&\therefore a = q\cdot b,b = p\cdot c\\
&\therefore a= q \cdot p \cdot c\\
&\because p,q \in Z\\
&\therefore c \mid a
\end{align*}
$$


**2.若 $c \mid a,c\mid b$，则对任意整数 $x,y$ ，必有 $c \mid (ax+by).$**
$$
\begin{align*}
证明&：\\
&\because c \mid a,c\mid b\\
&\therefore a = qc,b=pc\\
&\therefore ax + by=qcx + pcy=(qx+py)c\\
&\because a,b,x,y\in Z\\
&\therefore c \mid (ax+by)
\end{align*}
$$
