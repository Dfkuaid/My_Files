# #0.0 前置知识

您需要了解 **强连通分量（Strongly Connected Components，SCC）** 的相关知识及求 SCC 的 $\text{Tarjan}$ 算法。

-----

<div style="width=10px;line_height: 1px;">
<a href=https://www.cnblogs.com/Dfkuaid-210/p/scc_tarjan.html style="text-decoration:none;">
      <font face="黑体" size=6>
            <b>[图论入门]Tarjan & 强连通分量</b>
      </font>
      <font face="黑体" size=2>
            <br>&nbsp;&nbsp;发表于 2021-05-31 11:31&nbsp;Dfkuaid<br>
      </font>
      <font face="黑体" size=6>   </font>
      <font face="FangSong" size=4>
            摘要：&nbsp;Tarjan 算法求强连通分量。&nbsp;<br>
      </font>
    <p align="right">
      <font face="黑体" size=4>
          阅读全文&nbsp;&nbsp;&nbsp;<br>
          <u>&nbsp;&nbsp;&nbsp;>>&nbsp;&nbsp;&nbsp;</u>&nbsp;&nbsp;&nbsp;<br>
      </font>
    </p>
</a>
</div>

-----

# #1.0 什么是 2-SAT 问题？

SAT 是适定性（Satisfiability）问题的简称。一般形式为 k - 适定性问题，简称 k-SAT。而当 $k>2$ 时该问题为 NP 完全的。所以我们只研究 $k=2$ 的情况。

2-SAT，简单的说就是给出 $n$ 个集合，每个集合有两个元素，已知若干个 $<a,b>$，表示 $a$ 与 $b$ 矛盾（其中 $a$ 与 $b$ 属于不同的集合）。然后从每个集合选择一个元素，判断能否一共选 $n$ 个两两不矛盾的元素。显然可能有多种选择方案，一般题中只需要求出一种即可。

# #2.0 解决方式

## #2.1 搜索

~~...答案总会出来的...~~

## #2.2 Tarjan SCC 缩点

### #2.2.1 建图

> 这里为了方便叙述，任一变量 $a$ 仅有两种取值：$0$ 和 $1.$
> $\lor$ 为逻辑或，$\land$ 为逻辑与，$\lnot$ 为逻辑非。

我们首先要将题目里的限制条件转化为图。这里我们连的边为有向边，边 $a\to b$ 表示由 $a$ 可以推出 $b$。这里用点 $a$ 表示变量 $a$ 为 $0$，点 $a+N$ 表示变量 $a$ 为 $1.$（$N$ 表示变量总数）

### #2.2.2 判断有无解

建图之后，整张图必然是由一个个 SCC 聚合而成，而在每个 SCC 中，可以由任意一个推出其他的所有。那么，如果 $a$ 与 $a+N$ 在同一个 SCC 中，便产生了矛盾，故可以使用 $\text{Tarjan}$ 求 SCC，然后再判断每个变量的两种情况是否在同一 SCC 内，若是，则无解。

``` cpp
inline void tarjan(int x){
    dfn[x] = low[x] = ++ T;
    st[++ frt] = x;inst[x] = true;
    for (int i = head[x];i;i = e[i].nxt)
      if (!dfn[e[i].v]){
          tarjan(e[i].v);
          low[x] = Min(low[x],low[e[i].v]);
      }
      else if (inst[e[i].v])
        low[x] = Min(low[x],dfn[e[i].v]);
    if (dfn[x] == low[x]){
        int y;cnt2 ++;
        do{
            y = st[frt --];
            scc[y] = cnt2;
            inst[y] = false;
        }while (x != y);
    }
}

/*在 main() 中*/
for (int i = 1;i <= 2 * n;i ++)
  if (!dfn[i]) tarjan(i);
for (int i = 1;i <= n;i ++)
  if (scc[i] == scc[i + n]){
      printf("IMPOSSIBLE");
      return 0;
  }
```

### #2.2.3 构造解

#### #2.2.3.1 拓扑排序

首先想到的一种显而易见的构造解的方式是拓扑排序。

我们可以将求完 SCC 的图进行缩点，然后我们注意到，选择一个“有出边的点”会使该边指向的点也必须被选择，而选择一个“零出度的点”则不会造成影响。

所以，这里我们可以进行自底向上的拓扑，而这种操作并不好实现，但与之等价的建反向边，再在新图上进行自顶向下的拓扑则要好实现许多。

在拓扑的过程中，判断当前 SCC 值是否已确定，若没有，则对所在的 SCC 标记为选择，对另一取值的点所在的 SCC 赋标记为不选择。

完成以上任务后，对于每个点的选择情况便已经确定了。

#### #2.2.3.2 利用 Tarjan SCC 的性质

上面的过程极为麻烦，让我们来用一个更巧妙的方法进行构造。

上面的方法中本身是一次拓扑逆序，而 Tarjan 求 SCC 的过程本质是 DFS，而先被标记的 SCC 在拓扑序中是靠后的，于是本身 Tarjan 求出的 SCC 序就是拓扑逆序，又根据我们上面得到的结论，可以知道，我们应当选取 SCC 序（即拓扑逆序）靠前的取值。

``` cpp
for (int i = 1;i <= n;i ++)
  printf("%d ",scc[i] > scc[i + n]);
```

### #2.2.4 限制条件转化为图

> 为什么要将这个问题放到最后？因为若不懂上面的算法流程与思想就难以理解现在在干什么。

限制条件可以有许多，这里举几个常见的例子：

1. **$a \lor b$ 为真**

我们连接边 $a\to b+N$ 以及 $b\to a+N.$

2. **$a \land b$ 为真**

连接边 $a+N\to b+N$ 以及 $b+N\to a+N.$

同时，我们还需要连接 $a\to a+N$ 以及 $b\to\ b+N$，制造矛盾，使当 $a,b$ 中有一者为 $0$ 时不能成立。

类似的关系还有很多，这里不一一赘述，但核心是不变的：要不重不漏地相互约束。

# #3.0 例题

## #3.1 [P4782 【模板】2-SAT 问题](https://www.luogu.com.cn/problem/P4782)

按上面所讲进行操作即可。

``` cpp
const int N = 5000010;
const int INF = 0x3fffffff;

struct Edge{
    int u,v;
    int nxt;
};
Edge e[N];

int n,m,cnt = 1,head[N],scc[N],frt;
int dfn[N],low[N],T,st[N],inst[N],cnt2;

inline int Min(const int &a,const int &b){
    return a < b ? a : b;
}

inline void add(const int &u,const int &v){
    e[cnt].u = u;
    e[cnt].v = v;
    e[cnt].nxt = head[u];
    head[u] = cnt ++;
}

inline void tarjan(int x){
    dfn[x] = low[x] = ++ T;
    st[++ frt] = x;inst[x] = true;
    for (int i = head[x];i;i = e[i].nxt)
      if (!dfn[e[i].v]){
          tarjan(e[i].v);
          low[x] = Min(low[x],low[e[i].v]);
      }
      else if (inst[e[i].v])
        low[x] = Min(low[x],dfn[e[i].v]);
    if (dfn[x] == low[x]){
        int y;cnt2 ++;
        do{
            y = st[frt --];
            scc[y] = cnt2;
            inst[y] = false;
        }while (x != y);
    }
}

int main(){
    scanf("%d%d",&n,&m);
    for (int i = 1;i <= m;i ++){
        int a,b,x,y;
        scanf("%d%d%d%d",&a,&x,&b,&y);
        add(a + (x ^ 1) * n,b + y * n);
        add(b + (y ^ 1) * n,a + x * n);
    }
    for (int i = 1;i <= 2 * n;i ++)
      if (!dfn[i]) tarjan(i);
    for (int i = 1;i <= n;i ++)
      if (scc[i] == scc[i + n]){
          printf("IMPOSSIBLE");
          return 0;
      }
    printf("POSSIBLE\n");
    for (int i = 1;i <= n;i ++)
      printf("%d ",scc[i] > scc[i + n]);
    return 0;
}

```

<div id='refer-auth'></div>

# 参考资料

[1] [2-SAT - OI Wiki](https://oi-wiki.org/graph/2-sat/)
[2] 算法竞赛进阶指南. 李煜东. 郑州: 河南电子音像出版社, 2017.10.
[3] [2-SAT问题 - CaptainLi](https://www.cnblogs.com/captain1/p/9760503.html)
[4] [【研究总结】2-sat问题 - JarjingX](https://blog.csdn.net/JarjingX/article/details/8521690)