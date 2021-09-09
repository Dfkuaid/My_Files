[TOC]

# #0.0 前置知识

在学习本文之前，请确保你已学会以下知识：

- 线段树基本操作（区间修改，区间查询）
- 线段树动态开点
- 离散化

若并未学会，建议进入以下相应博文先行学习前置知识

----------------------------------------------------------------------------------------------

<div style="width=10px;line_height: 1px;">
<a href=https://www.cnblogs.com/Dfkuaid-210/p/11953598.html style="text-decoration:none;">
      <font face="黑体" size=6>
            <b>[数据结构入门]线段树</b>
      </font>
      <font face="黑体" size=2>
            <br>&nbsp;&nbsp;发表于 2019-11-28 20:39&nbsp;Dfkuaid<br>
      </font>
      <font face="黑体" size=6>   </font>
      <font face="FangSong" size=4>
            摘要：&nbsp;线段树的基本（建树、区间查询、单点修改）及进阶操作（区间修改 单点查询、区间修改 区间查询（标记下传、标记永久化））&nbsp;<br>
      </font>
    <p align="right">
      <font face="黑体" size=4>
          阅读全文&nbsp;&nbsp;&nbsp;<br>
          <u>&nbsp;&nbsp;&nbsp;>>&nbsp;&nbsp;&nbsp;</u>&nbsp;&nbsp;&nbsp;<br>
      </font>
    </p>
</a>
</div>
----------------------------------------------------------------------------------------------

<div style="width=10px;line_height: 1px;">
<a href=https://www.cnblogs.com/Dfkuaid-210/p/14365197.html style="text-decoration:none;">
      <font face="黑体" size=6>
            <b>[数据结构入门]线段树plus - 区间乘法 & 动态开点 </b>
      </font>
      <font face="黑体" size=2>
            <br>&nbsp;&nbsp;发表于 2021-02-05 21:52&nbsp;Dfkuaid<br>
      </font>
      <font face="黑体" size=6>   </font>
      <font face="FangSong" size=4>
            摘要：&nbsp;线段树区间乘法，动态开点及权值线段树简单介绍&nbsp;<br>
      </font>
    <p align="right">
      <font face="黑体" size=4>
          阅读全文&nbsp;&nbsp;&nbsp;<br>
          <u>&nbsp;&nbsp;&nbsp;>>&nbsp;&nbsp;&nbsp;</u>&nbsp;&nbsp;&nbsp;<br>
      </font>
    </p>
</a>
</div>

----------------------------------------------------------------------------------------------

<div style="width=10px;line_height: 1px;">
<a href=https://www.cnblogs.com/zythonc/p/13184668.html style="text-decoration:none;">
      <font face="黑体" size=6>
            <b>算法初探 - 离散化</b>
      </font>
      <font face="黑体" size=2>
            <br>&nbsp;&nbsp;发表于 2020-09-25 16:01&nbsp;zythonc<br>
      </font>
      <font face="黑体" size=6>   </font>
      <font face="FangSong" size=4>
            摘要：&nbsp;离散化的简单学习与相关例题&nbsp;<br>
      </font>
    <p align="right">
      <font face="黑体" size=4>
          阅读全文&nbsp;&nbsp;&nbsp;<br>
          <u>&nbsp;&nbsp;&nbsp;>>&nbsp;&nbsp;&nbsp;</u>&nbsp;&nbsp;&nbsp;<br>
      </font>
    </p>
</a>
</div>


----------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------

# #1.0 某些基本知识

## #1.1 啥是权值线段树？有啥区别？

权值线段树，毋庸置疑，还是建立在线段树之上的，只不过维护的东西略有不同

举个例子，有一个数列 $\{a_i\},(i \leq 10000,a < 10^9)$，

一般的线段树，结点代表的区间是 $i$ 的范围，叶结点维护的是 $a_{i}$ 的值，权值线段树代表的区间则是 $a_i$ 的范围，叶结点上维护 $a_i$ 这个数出现的次数（运用了“桶”的思想），做统计用

但是 $a_i$ 可以很大，$i$ 却不会很大，所以一般先对数据进行**离散化**，同时使用动态开点节约空间，再进行统计。

## #1.2 权值线段树の结构 & 思想

回到定义上，线段树维护的是某一个数出现的次数，那么，它的结构是这样的：

- 有一个左儿子叶结点 $P$，代表的数为 $a_i$，它上面记录的是 $a_i$ 出现的次数，它还有个兄弟结点，维护的是 $a_i+1$ （注意不是 $a_{i+1}$）出现的次数
- $P$ 的父结点维护的则是 $a_i$ 和 $a_i+1$ 出现的次数之和，以此类推

那么，举个例子，我们有下面这个数列：
$$
\begin{aligned}
A=\{5,2,1,3,2,3,4,7,8,4,5\}
\end{aligned}
$$
将他维护成权值线段树便是这样的：

![](https://img.imgdb.cn/item/601e91fa3ffa7d37b3832eab.png)

那么，问题来了，我们为什么要维护这样一个区间线段树？

是为了**动态地维护**区间的某一个数出现的次数，比如求动态第 $k$ 小值。

# #2.0 部分代码实现

## #2.1 数据处理

首先，因为权值线段树维护的是值域，而有些值域可能特别大，但数的数量可能不多，我们维护一个数出现的次数，显然只需要这个数相应的大小位置即可，不需要具体数值，那么就需要**离散化**

``` cpp
scanf("%d",&n); //输入数据
for (int i = 1;i <= n;i ++){
    scanf("%lld",&a[i]);
    b[i] = a[i]; //copy一份，查值输出可能会用到
}
/*下面是离散化的过程*/
sort(a + 1,a + n + 1); //排序
int size = unique(a + 1,a + n + 1) - a - 1; //去重
for (int i = 1;i <= n;i ++){
    lsh[i] = lower_bound(a + 1,a + size + 1,b[i]) - a; //查找对应位置
    tmp[lsh[i]] = b[i];
}
```

## #2.2 新插入一个数

当做单点修改，辅以动态开点

``` cpp
inline int create(){ //动态开点
    tot ++;
    p[tot].ls = p[tot].rs = p[tot].sum = 0;
    return tot;
}

inline void change(int k,int l,int r,int x){
    p[k].sum ++; //统计次数时，一次只增加一，不需pushup()，其他题目具体分析
    if (l == r)
      return;
    int mid = (l + r) >> 1;
    if (mid >= x){
        if (!p[k].ls) //不存在就开点
          p[k].ls = create();
        change(p[k].ls,l,mid,x);
    }
    else {
        if (!p[k].rs) //同上
          p[k].rs = create();
        change(p[k].rs,mid + 1,r,x);
    }
}
```



## #2.3 部分重要查询算法

这里只讲一种利用权值线段树维护的最常见的数据：**第 $k$ 小（大）的数**

对于一个结点，我们要找它所代表的范围内第 $k$ 小的数，一定有以下两种情况

- 左儿子范围内所有数出现次数和**大于** $k$，说明第 $k$ 小的数显然在**左子树**的区间里，那么就在左子树的区间里继续找第 $k$ 小的数
- 左儿子范围内所有数出现次数和**小于** $k$，说明第 $k$ 小的数显然在**右子树**的区间里，那么就在右子树的区间里继续找第 $k-sum[lson]$ 小的数

简单思考：**为什么在右子树里找第 $k-sum[lson]$ 小的数？而不是第 $k$ 小的数？**

这个问题留给各位自己思考，可以用画图的方式帮助理解

查询代码实现：

``` cpp
inline int query(int k,int l,int r,int kth){
    if (l == r){
        return l;
    }
    int mid = (l + r) >> 1;
    if (p[p[k].ls].sum >= kth)
      return query(p[k].ls,l,mid,kth);
    else
      return query(p[k].rs,mid + 1,r,kth -  p[p[k].ls].sum);
}
```



# #3.0 例题 [P1168 中位数](https://www.luogu.com.cn/problem/P1168)

不难想到，相当于每次在前 $2\times i+1$ 个数里找到第 $k+1$ 大的数，符合权值线段树的维护，码就完了

``` cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define INF 0x3fffffff
#define N 100010
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l));
#define mp(a,b) make_pair(a,b)
using namespace std;

struct Node{
    int ls,rs;
    int sum;
};
Node p[N << 2];

int n,cnt,tot;
ll a[N],lsh[N],b[N],tmp[N];

inline int create(){ //开点
    tot ++;
    p[tot].ls = p[tot].rs = p[tot].sum = 0;
    return tot;
}

inline void change(int k,int l,int r,int x){ //单点更新
    p[k].sum ++;
    if (l == r)
      return;
    int mid = (l + r) >> 1;
    if (mid >= x){
        if (!p[k].ls)
          p[k].ls = create();
        change(p[k].ls,l,mid,x);
    }
    else {
        if (!p[k].rs)
          p[k].rs = create();
        change(p[k].rs,mid + 1,r,x);
    }
}

inline int query(int k,int l,int r,int kth){ //区间查询
    if (l == r){
        return l;
    }
    int mid = (l + r) >> 1;
    if (p[p[k].ls].sum >= kth)
      return query(p[k].ls,l,mid,kth);
    else
      return query(p[k].rs,mid + 1,r,kth -  p[p[k].ls].sum);
}

int main(){
    scanf("%d",&n); //输入
    for (int i = 1;i <= n;i ++){
        scanf("%lld",&a[i]);
        b[i] = a[i];
    }
    sort(a + 1,a + n + 1); //离散化
    int size = unique(a + 1,a + n + 1) - a - 1;
    for (int i = 1;i <= n;i ++){
        lsh[i] = lower_bound(a + 1,a + size + 1,b[i]) - a;
        tmp[lsh[i]] = b[i];
    }
    cnt = 1;
    tot = 0;
    int root = create(); //建立根节点
    cnt = 0;
    for (int i = 1;i <= n;i ++){
        change(1,1,100001,lsh[i]); //注意要按输入顺序插入
        if (i % 2){ //在序列长度为奇数时
            int mid = (i + 1) >> 1; //查询第 k 小的数
            printf("%lld\n",tmp[query(1,1,100001,mid)]); //注意要转会原数
        }
    }
    return 0;
}
```



-----

# 更新日志及说明

## 更新

> - 初次完成编辑 - $\mathfrak{2021.2.6}$

## 个人主页

欢迎到以下地址支持作者！
**Github**：[戳这里](https://github.com/Dfkuaid/)
**Bilibili**：[戳这里](https://space.bilibili.com/312728987)
**Luogu**：[戳这里](https://www.luogu.com.cn/user/162191)