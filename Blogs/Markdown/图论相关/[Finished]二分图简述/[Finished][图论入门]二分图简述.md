# #1.0 一些基础

## #1.1 啥是二分图？

节点由两个集合组成，且两个集合内部没有边的图。<sup>[[1]](#refer-auth)</sup>

![](https://pic.imgdb.cn/item/60b2eb6708f74bc15995f2a0.png)

## #1.2 二分图的判定

首先我们需要了解一个二分图的重要性质：**二分图不存在长度为奇数的环**，即不存在奇环。原因很简单：因为每一条边都是从一个集合走到另一个集合，只有走偶数次才可能回到同一个集合。

那么，我们便可以运用以上性质，结合 $\text{DFS}$ 或 $\text{BFS}$ 对二分图进行判定。

``` cpp
inline bool dfs(int x){
    for (int i = head[x];i;i = e[i].nxt)
      if (v[e[i].v]){
          if (!((id[x] - id[e[i].v]) & 1))
            return false;
      }
      else{
          id[e[i].v] = id[x] + 1;
          v[e[i].v] = 1;
          if (!dfs(e[i].v))
            return false;
      }
    return true;
}
/*在 main() 中：*/
v[1] = 1,id[1] = 1;
if (dfs(1)) puts("Yes.");
else puts("No.");
```

# #2.0 二分图最大匹配

## #2.1 匈牙利算法

> 美国数学家哈罗德·库恩于1955年提出该算法。此算法之所以被称作匈牙利算法，是因为算法很大一部分是基于以前匈牙利数学家Dénes Kőnig和Jenő Egerváry的工作之上创建起来的。<sup>[[2]](#refer-auth)</sup>

算法的本质很暴力：不断尝试，改变之前的选择，就如同你一步一步的模拟。尝试每一个选择，如果某个选择已经被搭配，尝试将原有搭配拆散重新搭配，直到找到第一个可行的搭配，正确性是显然的。

![](https://pic.imgdb.cn/item/60b3012e08f74bc159c3ea10.gif)

在有些时候，我们甚至可以不用建双向边。

``` cpp
const int N = 100010;
const int INF = 0x3fffffff;

struct Edge{
    int u,v;
    int nxt;
};
Edge e[N << 1];

int n,m,r,cnt,head[N];
int v[N],match[N],ans;

inline void add(int u,int v){
    e[cnt].u = u;
    e[cnt].v = v;
    e[cnt].nxt = head[u];
    head[u] = cnt ++;
}

inline bool dfs(int x){
    for (int i = head[x];i != -1;i = e[i].nxt)
      if (!v[e[i].v]){
          v[e[i].v] = 1;
          if (!match[e[i].v] || dfs(match[e[i].v])){
              match[e[i].v] = x;
              return true;
          }
      }
    return false;
}

int main(){
    mset(head,-1);
    scanf("%d%d%d",&n,&m,&r);
    for (int i = 1;i <= r;i ++){
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v + n);add(v + n,u); //有时候可以不建双向边
    }
    for (int i = 1;i <= n;i ++){
        mset(v,0);
        if (dfs(i)) ans ++;
    }
    printf("%d",ans);
    return 0;
}
```

匈牙利算法的时间复杂度为 $O(nm).$

## #2.2 转换为网络最大流

~~我不会，先咕着。~~

## #2.3 关于建模

二分图的建模一般要满足以下两要素:
1. ```0 要素```：每个集合内的点没有边相连，
2. ```1 要素```：每个点之多与一个点相连。

# #3.0 扩展

## #3.1 二分图最大独立集

选最多的点，满足两两之间没有边相连。

二分图中，最大独立集 = $n$ - 最大匹配。

## #3.2 二分图最大点覆盖

选最少的点，满足每条边至少有一个端点被选，不难发现补集是独立集。

二分图中，最小点覆盖 = $n$ - 最大独立集 = 最大匹配。

# #4.0 例题

> 如何建图是最重要的一环！

## #4.1 [P2756 飞行员配对方案问题](https://www.luogu.com.cn/problem/P2756)

很简单的板子题。

我们将外籍飞行员看做左点，英籍飞行员看做右点，为每个左点找到合适的右点即可，由于输入的顺序给定所以可以建单向边。

``` cpp
const int N = 1010;
const int INF = 0x3fffffff;

struct Edge{
    int u,v;
    int nxt;
};
Edge e[N << 1];

int m,n,v[N],match[N];
int cnt,head[N],ans;

inline void add(const int &u,const int &v){
    e[cnt].u = u;
    e[cnt].v = v;
    e[cnt].nxt = head[u];
    head[u] = cnt ++;
}

inline bool dfs(int x){
    for (int i = head[x];i != -1;i = e[i].nxt)
      if (!v[e[i].v]){
          v[e[i].v] = 1;
          if (!match[e[i].v] || dfs(match[e[i].v])){
              match[e[i].v] = x;
              match[x] = e[i].v;
              return true;
          }
      }
    return false;
}

int main(){
    mset(head,-1);
    scanf("%d%d",&m,&n);
    int a = 0,b = 0;
    scanf("%d%d",&a,&b);
    while (a != -1 && b != -1){
        add(a,b);
        scanf("%d%d",&a,&b);
    }
    for (int i = 1;i <= m;i ++){
        mset(v,0);
        if (dfs(i)) ans ++;
    }
    printf("%d\n",ans);
    for (int i = 1;i <= m;i ++)
      if (match[i])
        printf("%d %d\n",i,match[i]);
    return 0;
}
```

<div id='refer-auth'></div>

# 参考资料

[1] [二分图 - OI Wiki](https://oi-wiki.org/graph/bi-graph/)
[2] [匈牙利算法_百度百科](https://baike.baidu.com/item/%E5%8C%88%E7%89%99%E5%88%A9%E7%AE%97%E6%B3%95)