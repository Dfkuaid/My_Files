[TOC]

# #1.0 简单的定义

“**最近公共祖先（LCA）**”  指的是两个点的公共祖先里面，离根最远的那个。

# #2.0 LCA 的求法

$\text{LCA}$ 的求法有许多，这里简单介绍几种：倍增、树链剖分。 

## #2.1 倍增算法

### #2.1.1 预处理

设 $f_{i,k}$ 表示节点 $i$ 的第 $2^k$ 辈祖先，那么显然 $f_{i,0}$ 即为 $i$ 的父节点，且有以下关系：
$$
f_{i,k}=f_{f_{i,k-1},k-1}.
$$
（上式十分简单，还请自行理解）

那么，我们显然可以采用 $\text{BFS}$ 或 $\text{DFS}$ 的框架预处理出所有的 $f_{i,k}(0\leq k\leq t)$，其中 $t=\log_2N+1$，$N$ 为节点个数，"$+1$" 是为了防止精度问题。

### #2.1.2 求 LCA

使用倍增求 $\text{LCA}$ 的步骤分：

1. 将两节点跳到同一深度;

   (a) 此时若两者是同一节点，返回其一即可.

   (b) 否则执行 2.

2. 将两者同时向上跳同一高度（两者不能跳到同一节点），直到两者的所有祖先都相等；

3. 显然，此时两者的父节点便是我们要求的 $\text{LCA}$。

要注意，我们在将节点向上跳的过程中，假设我们要将 $x$ 跳到 $y$，那么就相当于将两者之间的深度之差 $h$ **转化为二进制**，对于转化为二进制后的 $h$，考虑第 $k$ 位，若为 $1$，则将其之间的深度差 $h$ 缩短 $2^{k-1}$，也就是将 $x$ 向上跳到当前所在节点的第 $k-1$ 辈祖先，重复这个过程，最终将 $h$ 缩小为 $0$。那么，考虑将 $h$ 转化为二进制的过程，应当是自大而小的得到每一位的值，所以，在步骤 1. 2. 中，枚举向上跳的高度 $2^k$，$k$ 应当自大而小的枚举。

### #2.1.3 代码实现

``` cpp
inline void prework(){
    queue <int> q;
    q.push(rt);
    vis[rt] = true;
    while (q.size()){
        int now = q.front();q.pop();
        for (int j = head[now];j;j = e[j].nxt){
            int y = e[j].v;
            if (vis[y]) continue;
            f[y][0] = now;d[y] = d[now] + 1;
            for (int k = 1;k <= t;k ++)
              f[y][k] = f[f[y][k - 1]][k - 1];
            q.push(y);
        }
    }
}

inline int LCA(int x,int y){
    if (d[x] < d[y]) swap(x,y);
    for (int i = t;i >= 0;i --)
      if (d[f[x][i]] >= d[y])
        x = f[x][i];
    if (x == y) return x;
    for (int i = t;i >= 0;i --)
      if (f[x][i] != f[y][i])
        y = f[y][i],x = f[x][i];
    return f[x][0];
}
```

## #2.2 树链剖分

其实这个在我曾专门写过的一篇博客里有过详细介绍，这里不多赘述。

----------------------------------------------------------------------------------------------

<div style="width=10px;line_height: 1px;">
<a href=https://www.cnblogs.com/Dfkuaid-210/p/14539642.html style="text-decoration:none;">
      <font face="黑体" size=6>
            <b>[算法入门]树链剖分 - 轻重链剖分</b>
      </font>
      <font face="黑体" size=2>
            <br>&nbsp;&nbsp;发表于 2021-03-15 19:59&nbsp;Dfkuaid<br>
      </font>
      <font face="黑体" size=6>   </font>
      <font face="FangSong" size=4>
            摘要：&nbsp;浅谈 树链剖分 - 轻重链剖分 &nbsp;<br>
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

## #2.3 其他算法

类似的还有 向上标记法、$\text{Tarjan}$ 算法等。不过鉴于笔者对其掌握还不熟练，这里不多介绍，以后一定会补上。

# #3.0 例题

## #3.1 [[NOIP2013 提高组] 货车运输](https://www.luogu.com.cn/problem/P1967)

### #3.1.1 变图为树

> 初次看到该题是本人在练习树剖的时候，当时拿过题面来二话不说就写了个树剖，然后发现 **每个点之间道路不唯一** ....（当然树剖应该也可以做，不过不是上来不处理就剖）

不难想到，在走从 $x$ 到 $y$ 的某一条路径时，限制货车装载量的是该条路径上的最小限重，那我们就应该让所选取的路径上的最小限重尽可能大，那怎么选？**最大生成树**.可以保证选出的边限重尽可能大。

最大生成树的构建与最小生成树大同小异，我们只需将 Kruskal 算法中的排序变为从大到小排即可。

注意到 **初始图不一定联通**，那么我们会求出一个最大生成树森林。

### #3.1.2 变树为链

现在，题目变成了：求从 $x$ 到 $y$ 的路径上的最小边权。

一看到树上的路径类问题，容易想到：**树链剖分**，但是，树剖太麻烦了，还不好调，~~我还懒得写~~，那怎么办？别急，我们慢慢来。

从 $x$ 到 $y$ 的路径就是从 $x$ 到 $\text{LCA}(x,y)$，再从 $\text{LCA(x,y)}$ 到 $y$，那我们就可以求从 $x$ 到 $\text{LCA}(x,y)$ 的最小边权，再求从 $\text{LCA(x,y)}$ 到 $y$ 的最小边权，比较两者的大小即可，那怎么求 $\text{LCA}(x,y)$？

答：~~树链剖分<sub>How old are you？(怎么老是你？)</sub>，~~显然倍增啊！

所以，我们可以设 $f_{i,k}$ 表示 $i$ 的 $2^k$ 辈祖先，$g_{i,k}$ 表示从 $i$ 到 $i$ 的 $2^k$ 辈祖先的路径上的最小边权，易知：
$$
f_{i,k} = f_{f_{i,k-1},k-1},g_{i,k}=\min(g_{i,k-1},g_{f_{i,k-1},k-1}).
$$
那么 $f_{i,0}$ 便是 $i$ 的父节点，$g_{i,0}$ 便是从 $i$ 到其父节点的边的权值。

这样的话，我们就可以用倍增预处理 $f_{i,k}$ 和 $g_{i,k}$，这里要注意我们之前求得的是最大生成树森林，可能有多于一颗的最大生成树。所以我们不能单单只从一个点开始。

### #3.1.3 回答

至于回答时，可以直接采用倍增求 $\text{LCA}$ 的框架，只不过在每次向上跳后更新下答案即可

### #3.1.4 代码

```cpp
const int N = 10010;
const int M = 50010;
const int INF = 0x3fffffff;

struct Edge{
    int u,v;
    int w,nxt;
};
Edge e[M << 2],es[M];

int tot,n,m,head[N],fa[N],vis[N],rt[N];
int f[N][50],t,d[N],g[N][50],qe;

queue <int> q;

inline int cmp(const Edge a,const Edge b){
    return a.w > b.w;
}

inline void add(int u,int v,int w){
    e[++ tot].u = u;
    e[tot].v = v;
    e[tot].w = w;
    e[tot].nxt = head[u];
    head[u] = tot;
}

inline int getf(int x){
    while (x != fa[x])
      x = fa[x] = fa[fa[x]];
    return x;
}

inline void maxest(){ //求最大生成树
    for (int i = 1;i <= n;i ++)
      fa[i] = i;
    sort(es + 1,es + m + 1,cmp);
    for (int i = 1;i <= m;i ++){
        int fx = getf(es[i].u);
        int fy = getf(es[i].v);
        if (fx == fy) continue;
        add(es[i].u,es[i].v,es[i].w); //将最大生成树按邻接表存图
        add(es[i].v,es[i].u,es[i].w);
        fa[fx] = fy;
    }
}

inline void prework(){ //倍增的预处理算法
    tot = 0;mset(g,0x3f); //memset(g,0x3f,sizeof(g));
    for (int i = 1;i <= n;i ++){ //这是一个最大生成树森林，所以不能只从一个点开始
        if (vis[i]) continue;
        rt[++ tot] = i;vis[i] = true;
        q.push(i);
        while (q.size()){
            int now = q.front();q.pop();
            for (int j = head[now];j;j = e[j].nxt){
                int y = e[j].v;
                if (vis[y]) continue;
                f[y][0] = now;d[y] = d[now] + 1;
                g[y][0] = e[j].w;vis[y] = true;
                for (int k = 1;k <= t;k ++){
                    f[y][k] = f[f[y][k - 1]][k - 1];
                    g[y][k] = min(g[y][k - 1],g[f[y][k - 1]][k - 1]);
                }
                q.push(y);
            }
        }
    }
}

inline int ExLCA(int x,int y){ //以倍增求 LCA 为框架
    int res = INF;
    if (d[x] < d[y]) swap(x,y);
    for (int i = t;i >= 0;i --) //跳到同一高度
      if (d[f[x][i]] >= d[y]){
          res = min(res,g[x][i]);
          x = f[x][i];
      }
    if (x == y) return res;
    for (int i = t;i >= 0;i --) //同时向上跳
      if (f[x][i] != f[y][i]){
          res = min(res,g[y][i]);
          y = f[y][i];
          res = min(res,g[x][i]);
          x = f[x][i];
      }
    res = min(res,g[x][0]); //更新答案
    res = min(res,g[y][0]);
    return res;
}

int main(){
    scanf("%d%d",&n,&m);
    t = (int)(log(n) / log(2)) + 1;
    for (int i = 1;i <= m;i ++)
      scanf("%d%d%d",&es[i].u,&es[i].v,&es[i].w);
    maxest();prework();
    scanf("%d",&qe);
    while (qe --){
        int x,y;
        scanf("%d%d",&x,&y);
        if (getf(x) != getf(y)){puts("-1");continue;} //判断是否联通
        printf("%d\n",ExLCA(x,y));
    }
    return 0;
}
```

## #3.2 [[BJWC2010]严格次小生成树](https://www.luogu.com.cn/problem/P4180)

先求出一颗最小生成树，设边权值和为 ```sum```，那么，对于一条非树边 $(x,y,z)$，找到树上 $x\to y$ 的路径上的边权最大值 ```m1``` 与严格次大值 ```m2```，那么显然有：

- 若 ```m1 < z```，那么将 ```m1``` 这条边更换为 $(x,y,z)$ 后的权值和便是一个候选答案；
- 若 ```m1 == z```，那么将 ```m2``` 这条边更换为 $(x,y,z)$ 后的权值和便是一个候选答案；

显然不会有 ```m1 > z``` 或 ```m2 > z``` 的情况，因为这与最小生成树的定义矛盾。

那么，问题在于如何求出 $x\to y$ 的路径上的边权最大值与严格次大值？

与上一道例题相似，我们依旧可以采用倍增预处理，以倍增求 $\text{LCA}$ 为框架更新答案，只不过因为要同时处理最大值与严格次大值，所以更新所要讨论的情况复杂些，这里留作思考。