# #1.0 何为强连通分量？

若一张有向图的节点两两互相可达，则称这张图是 **强连通的** (Strongly connected)。

强连通分量（Strongly Connected Components，SCC）的定义是：**极大的强连通子图**。

# #2.0 Tarjan 算法

> $\text{Robert E. Tarjan}$　罗伯特·塔扬 ($1948$ ~ )，生于美国加州波莫纳，计算机科学家。
>
> $\text{Tarjan}$ 发明了很多算法结构。不少他发明的算法都以他的名字命名，以至于有时会让人混淆几种不同的算法。比如求各种连通分量的 $\text{Tarjan}$ 算法，求 LCA（Lowest Common Ancestor，最近公共祖先）的 $\text{Tarjan}$ 算法。并查集、Splay、Toptree 也是 Tarjan 发明的。

## #2.1 DFS 生成树

有向图的 DFS 生成树主要有 4 种边（不一定全部出现）：

 - **树边（tree edge）**：绿色边，每次搜索找到一个还没有访问过的结点的时候就形成了一条树边。
 - **反祖边（back edge）**：黄色边，也被叫做回边，即指向祖先结点的边。
 - **横叉边（cross edge）**：红色边，它主要是在搜索的时候遇到了一个已经访问过的结点，但是这个结点 并不是 当前结点的祖先时形成的。
 - **前向边（forward edge）**：蓝色边，它是在搜索的时候遇到子树中的结点的时候形成的。

![](https://pic.imgdb.cn/item/60b446ac39f6859bc2610343.jpg)

显然，如果结点 $u$ 是某个强连通分量在搜索树中遇到的第一个结点，那么这个强连通分量的其余结点肯定是在搜索树中以 $u$ 为根的子树中。$u$ 被称为这个强连通分量的根。

## #2.2 算法流程

在 Tarjan 算法中为每个结点  维护了以下几个变量：

1. ```dfn[u]```：深度优先搜索遍历时结点 $u$ 被搜索的次序。
2. ```low[u]```：设以 $u$ 为根的子树为 $\text{subtree}_u$。定义 ```low[u]``` 为以下结点的 ```dfn``` 的最小值：$\text{subtree}_u$ 中的结点；从 $\text{subtree}_u$ 通过一条不在搜索树上的边能到达的结点。

按照深度优先搜索算法搜索的次序对图中所有的结点进行搜索。在搜索过程中，对于结点 $u$ 和与其相邻的结点 $v$（$v$ 不是 $u$ 的父节点）考虑 $3$ 种情况：

- $v$ 未被访问：继续对 $v$ 进行深度搜索。在回溯过程中，用 ```low[v]``` 更新 ```low[u]```。因为存在从 $u$ 到 $v$ 的直接路径，所以 $v$ 能够回溯到的已经在栈中的结点，$u$ 也一定能够回溯到。
- $v$ 被访问过，已经在栈中：即已经被访问过 $v$，根据 ```low``` 值的定义（能够回溯到的最早的已经在栈中的结点），则用 ```low[v]``` 更新 ```low[u]```。
- $v$ 被访问过，已不在在栈中：说明 $v$ 已搜索完毕，其所在连通分量已被处理，所以不用对其做操作。

![](https://pic.imgdb.cn/item/60b4531c39f6859bc2da53e0.gif)

> 图中红色节点表示在栈内，黑色表示已出栈。

观察上面的流程，会发现上图的 SCC 的编号与该图缩点后自顶向下的拓扑序（从入度为零的点开始）相反，这个结论我们会在 2-sat 问题构造解时用到。

## #2.3 代码实现

``` cpp
inline void tarjan(int x){
    dfn[x] = low[x] = ++ T; //T 初值为 0 的全局变量
    st[++ frt] = x;inst[x] = true; //st[] 是栈，inst[] 表示当前是否在栈内
    for (int i = head[x];i;i = e[i].nxt)
      if (!dfn[e[i].v]){
          tarjan(e[i].v);
          low[x] = min(low[x],low[e[i].v]);
      }
      else if (inst[e[i].v])
        low[x] = min(low[x],dfn[e[i].v]);
    if (dfn[x] == low[x]){
        int y;cnt ++; //cnt 是全局变量，记录强连通分量的个数
        do{
            y = st[frt --];
            inst[y] = false;
            belong[y] = cnt;
        } while (y != x);
    }
}
```

# #3.0 例题

## #3.1 [P3387 【模板】缩点](https://www.luogu.com.cn/problem/P3387)

### #3.1.1 思路

因为边和点都可以随便走，故在一个强连通分量里，只要有一个点被访问，那么整个强连通分量都可以被访问，所以可以将整个强连通分量缩点，再用拓扑做 DAG 上的动态规划。

注意以下几点：
 - 缩点时我们可以选定 ```dfn``` 最小的那个为整个强连通分量的代表元素；
 - 我们应当将整个强连通分量的点权加到代表元素上；
 - 缩点后需要重新建图，建图方法：
   - 遍历所有的边，
   - 检查该边两端的两点是否在同一连通分量：
     - 是，则建边。
     - 不是，不管。
 - 建边时需要记录入度（出度不必要）。

### #3.1.2 代码实现

``` cpp
const int N = 100010;
const int INF = 0x3fffffff;

struct Edge{
    int u,v;
    int nxt;
};
Edge e[N],ne[N];

int n,m,cnt = 1,ncnt = 1,head[N],T,cnt2,belong[N];
int dfn[N],low[N],st[N],inst[N],frt,fl[N],ans;
int icnt[N],ocnt[N],data[N],nhead[N],f[N];

queue <int> q;

inline int Min(const int &a,const int &b){
    return a < b ? a : b;
}

inline int Max(const int &a,const int &b){
    return a > b ? a : b;
}

inline void add(const int &u,const int &v){
    e[cnt].u = u;
    e[cnt].v = v;
    e[cnt].nxt = head[u];
    head[u] = cnt ++;
}

inline void addn(const int &u,const int &v){
    ne[ncnt].u = u;
    ne[ncnt].v = v;
    ne[ncnt].nxt = nhead[u];
    nhead[u] = ncnt ++; 
    icnt[v] ++;ocnt[u] ++;
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
        int y;
        do{
            y = st[frt --];
            inst[y] = false;
            belong[y] = x;
            if (x != y) data[x] += data[y];
        } while (y != x);
        fl[x] = true;
    }
}

inline void tobo(){
    for (int i = 1;i <= n;i ++)
      if (!icnt[i] && fl[i]){
          q.push(i);
          f[i] = data[i];
      }
    while (q.size()){
        int now = q.front();q.pop();
        for (int i = nhead[now];i;i = ne[i].nxt){
            icnt[ne[i].v] --;
            f[ne[i].v] = Max(f[ne[i].v],data[ne[i].v] + f[now]);
            if (!icnt[ne[i].v])
              q.push(ne[i].v);
        }
    }
    for (int i = 1;i <= n;i ++)
      ans = Max(ans,f[i]);
}

int main(){
    scanf("%d%d",&n,&m);
    for (int i = 1;i <= n;i ++)
      scanf("%d",&data[i]);
    for (int i = 1;i <= m;i ++){
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v);
    }
    for (int i = 1;i <= n;i ++)
      if (!dfn[i]) tarjan(i);
    for (int i = 1;i <= m;i ++)
      if (belong[e[i].u] != belong[e[i].v])
        addn(belong[e[i].u],belong[e[i].v]);
    tobo();
    printf("%d",ans);
    return 0;
}
```

<div id='refer-auth'></div>

# 参考资料

[1] [强连通分量 - OI Wiki](https://oi-wiki.org/graph/scc/)
[2] [Tarjan缩点算法 - 11D_Beyonder](https://pro_11d_beyonder.gitee.io/2020/03/30/Tarjan%E7%BC%A9%E7%82%B9%E7%AE%97%E6%B3%95/#)