[TOC]

# #1.0 最小生成树（MST）

## #1.1 Kruskal 算法

### #1.1.1 简单理解

这是一种最常用的最小生成树求法，大致思想为：

一直维护一个最小生成树森林。起初，可认为生成森林由 $0$ 条边组成，每个节点构成一颗仅包含自己一个点的树，在任意时刻，$\text{Kruskal}$ 算法在剩余的边中选出一条权值最小的，且这条边的两个端点位于两棵不连通的树中，将这两个点所在的树合并，直到再没有满足条件的边，算法结束。

判断两个点是否在同一棵树中可以采用并查集，时间复杂度为 $O(m\log n)$，$m$ 为边数，$n$ 为点数，路径压缩的并查集时间复杂度为 $O(\log n).$

至于算法的正确性...

~~显然。~~我们来看，假设从两个目前不连通的点 $x$ 到 $y$ 存在一条边 $(x,y,z_1)$，还有另一条边 $(x,y,z_2)$，若 $z_1<z_2$，显然我们选取权值更小的边得到的生成树边权和更小。假设在 $x$ 到 $y$ 之间还存在一条路径，其中经过点 $u$，若枚举到边 $(x,y,z_1)$ 时 $x,y$ 未在同一棵树中，显然说明路径 $x\to u\to y$ 中至少存在一条边权值大于 $z_1$，那么同样可以使三点联通，选权值小的边更加划算。其他情况亦然。

### #1.1.2 代码实现

``` cpp
struct Edge{
    int u,v;
    int nxt,w;
}
Edge es[M];

inline int cmp(Edge a,Edge b){
    return a.w < b.w;
}

inline void Kruskal(){
    for (int i = 1;i <= n;i ++)
      fa[i] = i;
    sort(es + 1,es + m + 1,cmp);
    for (int i = 1;i <= m;i ++){
        int fx = getf(es[i].u);
        int fy = getf(es[i].v);
        if (fx == fy) continue;
        fa[fx] = fy;
        ans += es[i].w;
    }
}
```

## #1.2 Prim 算法

> 相较于 $\text{Kruskal}$ 算法， $\text{Prim}$ 算法使用的要更少一些，原因也很简单：难写，时间复杂度不优。

### #1.2.1 简单理解

与 $\text{Kruskal}$ 算法思想略有不同： $\text{Prim}$ 算法总是维护最小生成树的一部分。

所有点划分为两个集合 $T,S$，$T$ 表示已在最小生成树中的点， $S$ 则是剩下的点的集合。维护这样一个数组：```d[x]```，表示不在 $T$ 中的点 $x$ 到集合 $T$ 上最短的边的权值。每次选择 ```d[]``` 最小的点加入 $T$，最终将所有点加入 $T$ 后算法结束，时间复杂度为 $O(n^2)$。

具体的实现可以类比 $\text{dijkstra}$ 算法，每将一个点 $x$ 加入 $T$，遍历所有不在 $T$ 中的与 $x$ 相连的点，更新其 ```d[]```，最终答案便是 $\sum_{i=2}^nd_n.$

显然以上过程可使用堆优化至 $O(n\log n)$，在边数较小时与 $\text{Kruskal}$ 复杂度差距不大，在边数较多时相对较优，但实现较为复杂，所以一般除非边数极大（如完全图），$\text{Prim}$ 算法并不常用。

### #1.2.2 代码实现

留作习题.

## #1.3 例题

### #1.3.1 [[NOIP2013 提高组] 货车运输](https://www.luogu.com.cn/problem/P1967)

首先，为保证所经过的边最小边权尽可能大，我们要构建一颗 **最大生成树**，其构建过程与 $\text{MST}$ 的构建一模一样，改一下排序顺序即可。 

剩下的需要倍增处理，详细的题解请见：

----------------------------------------------------------------------------------------------

<div style="width=10px;line_height: 1px;">
<a href=https://www.cnblogs.com/Dfkuaid-210/p/14673527.html style="text-decoration:none;">
      <font face="黑体" size=6>
            <b>关于我想了很久才想出这题咋做这档事 - 5</b>
      </font>
      <font face="黑体" size=2>
            <br>&nbsp;&nbsp;发表于 2021-04-18 15:10&nbsp;Dfkuaid<br>
      </font>
      <font face="黑体" size=6>   </font>
      <font face="FangSong" size=4>
            摘要：&nbsp;洛谷 P1967 [NOIP2013 提高组] 货车运输、P4116 Qtree3、P2801 教主的魔法 题解 &nbsp;<br>
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

# #2.0 树的直径问题

> 树的直径： 树中最远的两个节点之间的距离。

## #2.1 树形DP求直径

### #2.1.1 思路

我们设 $d_x$ 表示从节点 $x$ 出发到 $x$ 的子树中可走到的最远距离，设 $y_i$ 表示 $x$ 的子节点，显然有：
$$
d_x=\max\limits_{1\leq i\leq t}\{d_{y_i}+e(x,y_i)\},
$$
其中 $t$ 为 $x$ 的子节点的个数，而 $e(x,y_i)$ 表示从 $x$ 到 $y_i$ 的边的长度。

设 $f_x$ 表示经过 $x$ 的最长链的长度，对于 $x$ 的任意两个节点 $y_i,y_j$，显然有：
$$
f_x=\max\limits_{1\leq j<i\leq t}\{d_{y_j}+d_{y_i}+e(x,y_j)+e(x,y_i)\},
$$
不过我们并不需要枚举 $i,j$。

假设我们当前求得了 $d_{y_i}$，不难发现，我们如果要用 $y_i$ 更新 $f_x$，应当找到 $d_{y_j}+e(x,y_j)$ 最大的 $j$，而此时 $d_x$ 储存的正是这个值，所以我们可以先用 $d_{x}+d_{y_i}+e(x,y_i)$ 更新 $f_x$，再用 $d_{y_i}+e(x,y_i)$ 更新 $d_x.$

### #2.1.2 代码实现

``` cpp
inline void dp(int x){
    v[x] = 1;
    for (int i = head[x];i;i = e[i].nxt){
        int y = e[i].v;
        if (v[y]) continue;
        dp(y);
        ans = max(ans,d[x] + d[y] + edge[i]);
        d[x] = max(d[x],d[y] + edge[i]);
    }
}
```



## #2.2 两次BFS（或DFS）求直径

步骤分为两步：

- 从任意一点出发，找到离该点距离最远的一点 $u$；
- 再从 $u$ 出发，找到距离 $u$ 最远的一点 $v$；

从 $u$ 到 $v$ 的路径便是树的一条直径。

这样做有一个好处：**能更容易的找到树的直径上的节点**。

但也有一个缺点：**这种做法无法处理负边权**

算法正确性用反证法证明不难，这里不再赘述。

``` cpp
/*以下的代码可以简写为一段，多增加些参数即可*/
inline int get_len(){
	mset(v,0);mset(l,0);
	int s = 1,mxn = 0;
	while (!q.empty())
	  q.pop();
	q.push(s);v[s] = true;
	while (q.size()){ //第一次找
		int now = q.front();
		q.pop();
		for (int i = head[now];i != -1;i = t[i].next){
			if (v[t[i].v]) continue;
			v[t[i].v] = true;
			l[t[i].v] = l[now] + t[i].w;
			if (l[t[i].v] > mxn){
				mxn = l[t[i].v];
				p = t[i].v;
			}
			q.push(t[i].v);
		}
	}
	mset(v,0);mset(l,0);
	mxn = 0;q.push(p);v[p] = true;
	while (q.size()){ //第二次找
		int now = q.front();
		q.pop();
		for (int i = head[now];i != -1;i = t[i].next){
			if (v[t[i].v]) continue;
			v[t[i].v] = true;
			l[t[i].v] = l[now] + t[i].w;
			pre[t[i].v] = now;
			path[t[i].v] = i;
			if (l[t[i].v] > mxn){
				mxn = l[t[i].v];
				qe = t[i].v;
			}
			q.push(t[i].v);
		}
	}
	return mxn;
}
```
