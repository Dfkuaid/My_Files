TODO: Finish this Blog.

[TOC]

# #1.0 全排列和对换

## #1.1 排列及逆序数

把 $n$ 个不同的元素排成一列，叫做这 $n$ 个元素的**全排列**（简称**排列**）

$n$ 个不同元素的所有排列的种数，用 $P_n$ 表示
$$
\begin{aligned}
p_n = n \cdot (n-1)\cdot (n-2)\cdot\ \cdots\ \cdot 2\cdot 1=n!
\end{aligned}
$$
对于 $n$ 个不同的元素，先规定各元素之间有一个**标准次序**，于是在这 $n$ 个元素的任意排列中，当某一对元素的先后次序与标准次序不同时，就说它构成一个**逆序**，一个排列中所有逆序的总数叫做这个排列的**逆序数**

逆序数为奇数的排列叫**奇排列**，为偶数的叫**偶排列**

## #2.1 对换

- **一个排列中的任意两个元素对换，排列改变奇偶性**

- **奇排列变换为标准排列的对换次数为奇数，偶排列变换为标准排列的对换次数为偶数**

# #2.0 n阶行列式

## #2.1 定义

设有 $n^2$ 个数，排成 $n$ 行 $n$ 列的数表
$$
\begin{aligned}
&a_{11}\quad a_{12}\quad\cdots\quad a_{1n}\\\\
&a_{21}\quad a_{22}\quad\cdots\quad a_{2n}\\\\
&\quad\;\cdots\cdots\cdots\cdots\\\\
&a_{n1}\quad a_{n2}\quad\cdots\quad a_{nn}\\
\end{aligned}
$$
作出表中位于不同行不同列的 $n$ 个数的乘积，并冠以符号 $(-1)^t$，得到形如
$$
(-1)^ta_{1p_1}a_{2p_2}\cdots a_{np_n}
$$
的项，其中 $p_1p_2p_3\cdots p_n$ 为自然数 $1,2,3,\cdots,n$ 的一个排列，$t$ 为这个排列的逆序数，形如 $(1)$ 的项有 $n!$ 个，所有这 $n!$ 项的代数和
$$
\begin{aligned}
\Sigma(-1)^ta_{1p_1}a_{2p_2}\cdots a_{np_n}
\end{aligned}
$$
称为 $n$ 阶行列式，记作
$$
\begin{aligned}
D=\begin{vmatrix}a_{11}&a_{12}&\cdots&a_{1n}\\a_{21}&a_{22}&\cdots&a_{2n}\\\vdots&\vdots&&\vdots\\a_{n1}&a_{n2}&\cdots&a_{nn}\end{vmatrix},
\end{aligned}
$$


简记作 $det(a_{ij})$，其中数 $a_{ij}$ 为行列式 $D$ 的 $(i,j)$ 元

## #2.2 上（下）三角行列式 & 对角线行列式

### #2.2.1 定义

- **主对角线以下（上）的元素都为 $0$ 的行列式叫做上（下）三角行列式**

- **主对角线以上和以下的元素都为 $0$ 的行列式叫对角线行列式**

### #2.2.2 简单性质及证明

:newspaper: 下三角形行列式
$$
\begin{aligned}
D_1=\begin{vmatrix}a_{11}&&&\\a_{21}&a_{22}&&0\\\vdots&\vdots&\ddots&\\a_{n1}&a_{n2}&\cdots&a_{nn}\end{vmatrix}=a_{11}a_{22}\cdots a_{nn};
\end{aligned}
$$
**证明：**

由于当 $i<j$ 时，$a_{ij}=0$，故对于 $D_1$ 中不为 $0$ 的元素 $a_{ip_i}$，其下标应有 $p_i \leq i,1\leq i \leq n$，故应有 $p_1\leq1,p_2\leq2,\cdots,p_n\leq n$，又因为 $p_1+p_2+\cdots+p_n=1+2+\cdots+n$，于是有 $p_1=1,p_2=2,\cdots,p_n=n$，故 $D$ 中不为 $0$ 的项只有 $(-1)^ta_{11}a_{22}\cdots a_{nn}$，此项的符号 $(-1)^t=(-1)^0=1$，故 $D_1=a_{11}a_{22}\cdots a_{nn}.$

<div align="right">证毕.</div>

:newspaper: 上三角形行列式
$$
\begin{aligned}
D_2=\begin{vmatrix}a_{11}&a_{12}&\cdots&a_{1n}\\&a_{22}&\cdots&a_{2n}\\0&&\ddots&\vdots\\&&&a_{nn}\end{vmatrix}=a_{11}a_{22}\cdots a_{nn};
\end{aligned}
$$
与下三角形行列式证明相同

:newspaper: 对角线行列式
$$
\begin{aligned}
D_3=\begin{vmatrix}a_{11}&&&\\&a_{22}&&\\&&\ddots&\\&&&a_{nn}\end{vmatrix}=a_{11}a_{22}\cdots a_{nn};
\end{aligned}
$$
由下三角形行列式结论即得

# #3.0 行列式的性质

## #3.1 定义

记
$$
\begin{aligned}
D=\begin{vmatrix}a_{11}&a_{12}&\cdots&a_{1n}\\a_{21}&a_{22}&\cdots&a_{2n}\\\vdots&\vdots&&\vdots\\a_{n1}&a_{n2}&\cdots&a_{nn}\end{vmatrix},
D^T=\begin{vmatrix}a_{11}&a_{21}&\cdots&a_{n1}\\a_{12}&a_{22}&\cdots&a_{n2}\\\vdots&\vdots&&\vdots\\a_{1n}&a_{2n}&\cdots&a_{nn}\end{vmatrix},
\end{aligned}
$$
行列式 $D^T$ 为行列式 $D$ 的**转置行列式**

## #3.2 性质

**性质1   行列式与它的转置行列式相等**

证明：

记行列式 $D=det(a_{ij})$ 的转置行列式为 $D^T=det(b_{ji})$





