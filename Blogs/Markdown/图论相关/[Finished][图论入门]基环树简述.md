[TOC]

# #1.0 啥是基环树？

首先，严格地讲，基环树不是树，它是一张**有 $n$ 个节点、$n$ 条边的图**。

## #1.1 无向图上的基环树

可以将这种有 $n$ 个节点、$n$ 条边的无向联通图看做在一棵树上加了一条边，形成了一张恰好包含一个环的图，如下图：

![](https://img.imgdb.cn/item/6082c314d1a9ae528fd74600.png)

这便是一个无向图上的基环树。

当然，如果不保证联通，那么有 $n$ 个节点、$n$ 条边的无向图也有可能是一个基环树森林。

## #1.2 有向图上的基环树

### #1.2.1 内向树

每个节点以自己为起点的边只有一条。

![](https://img.imgdb.cn/item/6082c4d0d1a9ae528febcff3.png)



### #1.2.2 外向树

每个节点以自己为终点的边只有一条。

![](https://img.imgdb.cn/item/6082c448d1a9ae528fe536d9.png)



# #2.0 基环树的一般处理思路

> 下面都以无向图为例子。

## #2.1 大体方法

看起来基环树似乎比一棵树变得麻烦了许多。

但不要害怕，我们也是有一般方法的：

1. 找到唯一的环；
2. 对环之外的部分按照若干棵树处理；
3. 考虑与环一起计算。

## #2.2 找到环

### #2.2.1 思路

找到环可以采用 $\text{DFS}$ 来实现（我不会 $\text{BFS}$ QwQ）.

以下是本人的口胡做法：

1. 从任意一点开始搜索；
2. 每次拓展到的点涂为灰色，回溯的点涂为黑色；
3. 重复第一、二步，直到通过一条未经过过的边拓展到一个灰色节点；
4. 将拓展到的灰色节点涂为红色，函数返回 ```true```；
5. 将经过的回溯时经过的节点涂为橙色，函数返回 ```true```；
6. 重复第 5. 步，直到回溯到被涂为红色的节点，函数返回 ```false```，算法结束。

经过以上几步，我们便得到了唯一的环——颜色最显眼的那些！其中红色节点是环的衔接处。

如下图：

![](https://img.imgdb.cn/item/6082cc51d1a9ae528f45112b.gif)



注意到，上面的模拟过程中，以节点 $10$ 为根的子树并没有被遍历，是因为 $\text{DFS}$ 的实现本身便是一路到底，所以可能并不能遍历整颗基环树。

那么，当我们面对的是一个基环树森林时，便要注意了：如果以节点是否被访问过为标志，那么，标记一整棵基环树有以下几种方法：

- 在环上节点递归前，用另一个 $\text{DFS}$ 遍历该节点能到达的所有节点，并标记。
- 在对去掉环之后的若干棵子树进行处理时进行另一种标记 ```tag2[]```，判断是否是一棵新的基环树的依据为 ```tag2[]``` 是否被标记。
- 建图时使用并查集。

还有几个要注意的点：

- 判断一个点是否可以被拓展的条件是拓展所经过的边是否已被经过，由于无向图建边是两个方向各建一条边，所以标记时需要成对变换，将这两条边同时标记。

### #2.2.2 代码实现

``` cpp
//R[] 存储的是环上的节点

inline bool Get_ring(int x,int from){
    if (v[x] == 1){
        v[x] = 2;v2[x] = 1;
        R[++ tot] = x;
        return true;
    }
    v[x] = 1;int opt = 0;
    for (int i = head[x];i != -1;i = e[i].nxt){
        if (v_e[i]) continue;
        v_e[i] = v_e[i ^ 1] = true;
        if (Get_ring(e[i].v,x)){
            pre_e[e[i].v] = i;
            if (v[x] != 2){
                R[++ tot] = x;
                v2[x] = 1;
                return true;
            }
            else return false;
        }
    }
    return false;
}
```



## #2.3 剩下的操作

剩下的两步多要视题目而定了，不过一般是一个树形DP（子树不考虑环）加一个线性DP+单调队列优化（在环上，断环为链，复制一遍）



# #3.0 例题

## #3.1 [[IOI2008]Island](https://www.luogu.com.cn/problem/P4381)

不难发现，是让我们求一个基环树森林中所有基环树的直径之和。

那么基环树直径怎么求？三步走。

- 找到链
- 对去掉链后的若干棵子树进行树形DP，求出他们直径中的最大值，同时记录以环上每个点为起点，不经过其他环上节点的最长链的长度
- 在环上线性DP+单调队列优化

``` cpp
const int N = 7002100;
const int INF = 0x3fffffff;

struct Edge{
    int u,v,w;
    int nxt;
};
Edge e[N << 1];

int head[N],tot,v[N],v_e[N << 1],res;
int p,q,n,pre[N],pre_e[N],R[N << 1],v2[N],f[N];
int deq[N << 1],frt,tal,sum[N << 1],ans;

inline void add(int u,int v,int w){
    e[tot].u = u;
    e[tot].v = v;
    e[tot].w = w;
    e[tot].nxt = head[u];
    head[u] = tot ++;
}

inline bool Get_ring(int x,int from){
    if (v[x] == 1){
        v[x] = 2;v2[x] = 1;
        R[++ tot] = x;
        return true;
    }
    v[x] = 1;int opt = 0;
    for (int i = head[x];i != -1;i = e[i].nxt){
        if (v_e[i]) continue;
        v_e[i] = v_e[i ^ 1] = true;
        if (Get_ring(e[i].v,x)){
            pre_e[e[i].v] = i;
            if (v[x] != 2){
                R[++ tot] = x;
                v2[x] = 1;
                return true;
            }
            else return false;
        }
    }
    return false;
}

inline void dp(int x){
    for (int i = head[x];i != -1;i = e[i].nxt){
        int y = e[i].v;
        if (v2[y]) continue;
        v2[y] = true;dp(y);
        ans = max(ans,f[x] + f[y] + e[i].w);
        f[x] = max(f[x],f[y] + e[i].w);
    }
}

signed main(){
    mset(head,-1); //memset(head,-1,sizeof(head));
    scanf("%lld",&n);
    for (int i = 1;i <= n;i ++){
        int v,w;
        scanf("%lld%lld",&v,&w);
        add(i,v,w);add(v,i,w);
    }
    for (int i = 1;i <= n;i ++){
        if (v2[i]) continue;
        ans = 0;tot = 0;
        frt = 0;tal = -1;
        Get_ring(i,0);
        for (int i = 1;i <= tot;i ++){
            dp(R[i]);R[i + tot] = R[i];
        }
        for (int i = 1;i <= tot * 2;i ++)
          sum[i] = sum[i - 1] + e[pre_e[R[i]]].w;
        for (int i = 1;i <= tot * 2;i ++){
            while (frt <= tal && i - deq[frt] + 1 > tot) frt ++;
            if (frt <= tal) ans = max(ans,f[R[deq[frt]]] + f[R[i]] + sum[i - 1] - sum[deq[frt] - 1]);
            while (frt <= tal &&  f[R[deq[tal]]] - sum[deq[tal] - 1] <= f[R[i]] - sum[i - 1])
              tal --;
            deq[++ tal] = i;
        }
        res += ans;
    }
    cout << res;
    return 0;
}
```

