[TOC]

~~#0.0 引入~~ 本篇没有引入，这才像分块一样朴（bao）素（li）（￣へ￣）

# #1.0 直入正题

## #1.1 啥是分块？~~可以吃吗?~~

~~不能~~

$\Large{\textbf{分块}}$ 的基本思想是，通过对原数据的**适当划分**，并在划分后的**每一个块上预处理**部分信息，从而较一般的暴力算法取得更优的时间复杂度。分块的优点是**通用性更好**，可以维护很多树状数组和线段树无法维护的信息。[<sup>[1]</sup>](#refer-anchor)

当然，也有对询问进行分块的算法，那叫 **莫队**，不在本文的讨论范围

简单来说就是**带有一定预处理的暴力**，可以处理一些不满足区间可加性的信息（比如众数），那么这样来看分块就没有太固定的做法了，但是，总体的思路还是有的：**大块维护，小块朴素**

## #1.2 如何分块

一般来讲，块的长度取决于题目是什么以及你的算法，并没有特别固定的要求

我们来看数 $a_{i}$ 应该在哪一块，如果块长为 $len$，那么显然 $a_1,a_2,\cdots,a_{len}$ 是第一块，$a_{len+1},a_{len+2},\cdots,a_{2\cdot len}$ 是第二块，以此类推，容易看出，第 $i$ 个数 $a_i$ 所在块的编号为 $\lfloor\dfrac{i-1}{len}\rfloor+1$，第 $i$ 块的左端点编号为 $(i-1)\times len+1$，右端点为 $i\times len$

```cpp
inline void divide(){
    len = sqrt(n); 
    for (int i = 1;i <= n;i ++)
      id[i] = (i - 1) / len + 1;
    for (int i = 1;i <= id[n];i ++){
        sub[i][0] = (i - 1) * len + 1;
        sub[i][1] = i * len;
    }
    sub[id[n]][1] = min(sub[id[n]][1],n);
}
```

## #1.3 块的处理

总的来说，还是那句话：**大块维护，小块朴素**

就是对于整块的操作，能区间维护的就区间维护，不能就只维护需要的区间信息

对于不足一整块的点，朴素的扫一遍，同时维护所在区间信息

具体的还要**看题而定**



# #2.0 例题

## #2.1 P3870 [TJOI2009]开关

> [传送门](https://www.luogu.com.cn/problem/P3870)

设每个灯的状态，$0$ 表示关闭，$1$ 表示开启，容易知道是让我们维护区间中 $1$ 的数量，区间修改就是将区间中的数取反。

这么看来，我们可以对每个块维护一个标记，表示**是否将区间内的数取反**，那么每次对于一个整块的操作，直接在标记上进行即可，那么每一次**整块取反**后，区间中为 $1$ 的数的数量应该变为 ```len - sum[k]```（```len``` 表示块长， ```sum[k]``` 表示块 $k$ 中 $1$ 的数量）。

那么，对于不是整块的点，我们采用朴素的算法，对每个点进行修改

- 在修改前，若该点记录的状态与块上标记 **异或** 后得到的结果为 $1$，那么意味着修改后所在块中 $1$ 的数量要减少 $1$，就需要```sum[k] --```
- 修改时，只需要将记录的该点状态异或 $1$ 即可
- 修改后，若该点当前状态与块上标记异或后得到的结果为 $1$，就说明原来状态是 $0$，块中 $1$ 的数量增加了 $1$，那么就需要```sum[k] ++```

查询时也是同样的思想，整块的直接查看区间信息，非整块的朴素统计

**关于异或（$\hat{}$）：**
$$
\begin{aligned}
1\hat{}0=1\\
0\hat{}0=0\\
1\hat{}1=0\\
\end{aligned}
$$
**代码**

``` cpp
const int N = 200100;
const int INF = 0x3fffffff;

int n,cnt,m,id[N];
int sub[N][2],lazy[N],c[N],sum[N];

inline void change(int a,int b){
    int l = id[a],r = id[b];
    if (l == r){ //同一个块，朴素修改
        for (int i = a;i <= b;i ++){
            sum[l] -= (c[i] ^ lazy[l]);
            c[i] ^= 1;
            sum[l] += (c[i] ^ lazy[l]);
        }
        return;
    }
    for (int i = a;i <= sub[l][1];i ++){ //非整块，朴素修改
        sum[l] -= (c[i] ^ lazy[l]);
        c[i] ^= 1;
        sum[l] += (c[i] ^ lazy[l]);
    }
    for (int i = l + 1;i < r;i ++){ //整块，区间维护
        lazy[i] ^= 1;
        sum[i] = cnt - sum[i];
    }
    for (int i = sub[r][0];i <= b;i ++){ //非整块，朴素修改
        sum[r] -= (c[i] ^ lazy[r]);
        c[i] ^= 1;
        sum[r] += (c[i] ^ lazy[r]);
    }
}

inline int ask(int a,int b){ //与上面基本相同
    int res = 0,l = id[a],r = id[b];
    if (l == r){
        for (int i = a;i <= b;i ++)
          res += (c[i] ^ lazy[l]);
        return res;
    }
    for (int i = a;i <= sub[l][1];i ++)
        res += (c[i] ^ lazy[l]);
    for (int i = l + 1;i < r;i ++)
      res += sum[i];
    for (int i = sub[r][0];i <= b;i ++)
        res += (c[i] ^ lazy[r]);
    return res;
}

inline void divide(){
    cnt = sqrt(n);
    for (int i = 1;i <= n;i ++)
      id[i] = (i - 1) / cnt + 1;
    for (int i = 1;i <= id[n];i ++){
        sub[i][0] = (i - 1) * cnt + 1;
        sub[i][1] = i * cnt;
    }
    sub[id[n]][1] = min(sub[id[n]][1],n);
}

int main(){
    scanf("%d%d",&n,&m);
    divide();
    while (m --){
        int op,a,b;
        scanf("%d%d%d",&op,&a,&b);
        if (!op)
          change(a,b);
        else
          printf("%d\n",ask(a,b));
    }
    return 0;
}
```

显然对于整块的处理是 $O(1)$ 的，散点则是 $O(\sqrt{n})$ 的，总体时间复杂度为 $O(m\sqrt{n})$

## #2.2 P4145 上帝造题的七分钟2 / 花神游历各国

> [传送门](https://www.luogu.com.cn/problem/P4145)

首先，开根这种操作是**不能区间维护**的，所以每一次开根都需要落实到每一个数上，但是，因为是 $\lfloor\sqrt{a_i}\rfloor$，显然一个数在有限次操作后会变为 $1$，于是，这个数再也不会改变它对区间的贡献了，那么我们可以对每个块维护一个信息：**是否全为 $1$**，如果是，那对于此块内的修改可以忽略，且在统计时可以直接加上块长。

其他并没有什么特殊的，正常做即可

``` cpp
const int N = 100010;
const int INF = 0x3fffffff;

int n,m,len;
ll a[N],sum[N];
int id[N],sub[N][2];
int tag[N];

inline void check(int k){ //检查整块是否都为1
    bool flag = true;
    for (int i = sub[k][0];i <= sub[k][1];i ++)
      if (a[i] > 1){
          flag = false;
          break;
      }
    if (flag)
      tag[k] = true;
}

inline void change(int l,int r){
    int lp = id[l],rp = id[r];
    if (lp == rp){ //在同一块内，朴素维护
        if (tag[lp]) return;
        for (int i = l;i <= r;i ++){
            sum[lp] -= a[i];
            a[i] = sqrt(a[i]);
            sum[lp] += a[i];
        }
        check(lp);
        return;
    }
    if (!tag[lp]){ //朴素维护散点
        for (int i = l;i <= sub[lp][1];i ++){
            sum[lp] -= a[i];
            a[i] = sqrt(a[i]);
            sum[lp] += a[i];
        }
        check(lp);
    }
    if (!tag[rp]){ //朴素维护散点
        for (int i = sub[rp][0];i <= r;i ++){
            sum[rp] -= a[i];
            a[i] = sqrt(a[i]);
            sum[rp] += a[i];
        }
        check(rp);
    }
    for (int i = lp + 1;i < rp;i ++)
      if (!tag[i]){ //区间维护，仍旧需要一个点一个点的修改，同时检查是否全为1
          sum[i] = 0;
          bool flag = true;
          for (int j = sub[i][0];j <= sub[i][1];j ++){
              a[j] = sqrt(a[j]);
              sum[i] += a[j];
              if (a[j] > 1) flag = false;
          }
          if (flag)
            tag[i] = true;
      }
}

inline ll ask(int l,int r){ //区间查询
    int lp = id[l],rp = id[r];
    ll res = 0;
    if (lp == rp){ //朴素维护
        for (int i = l;i <= r;i ++)
          res += a[i];
        return res;
    }
    if (!tag[lp])
      for (int i = l;i <= sub[lp][1];i ++)
        res += a[i];
    else 
      res += (sub[lp][1] - l + 1); //直接加块长即可
    if (!tag[rp])
      for (int i = sub[rp][0];i <= r;i ++)
        res += a[i];
    else 
      res += (r - sub[rp][0] + 1); 
    for (int i = lp + 1;i <= rp - 1;i ++) //区间维护
      res += sum[i];
    return res;
}

int main(){
    scanf("%d",&n);
    
    len = sqrt(n); //输入与分块一气呵成
    for (int i = 1;i <= n;i ++){
        scanf("%lld",&a[i]);
        id[i] = (i - 1) / len + 1;
        sum[id[i]] += a[i];
    }
    for (int i = 1;i <= id[n];i ++){
        sub[i][0] = (i - 1) * len + 1;
        sub[i][1] = i * len;
    }
    sub[id[n]][1] = min(sub[id[n]][1],n);
    
    scanf("%d",&m);
    while (m --){
        int k,l,r;
        scanf("%d%d%d",&k,&l,&r);
        if (l > r) swap(l,r);
        if (!k) change(l,r);
        else printf("%lld\n",ask(l,r));
    }
    return 0;
}
```



<div id = "refer-anchor"></div>

-----------

# 参考及更新日志

## 参考文章

[1] [分块思想 OI-Wiki](https://oi-wiki.org/ds/decompose/)

## 更新

> - 初次完成编辑 - $2021.4.2$

