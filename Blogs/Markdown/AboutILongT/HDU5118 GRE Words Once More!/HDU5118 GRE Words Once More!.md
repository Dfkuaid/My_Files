> [题目链接](https://acm.hdu.edu.cn/showproblem.php?pid=5118)

## #1.0 题意简述

给定一个 DAG，每条边有一个权值，DAG 上有些点为标记点，定义一个 GRE 为从 $1$ 号节点开始到任意标记点结束，所经过的路径上每个权值作为一位拼成的串；特别的，保证 $1$ 号点永远不是特殊点。

现在要求从 $1$ 号点开始的第 $k$ 小的 GRE 的长度。GRE 的比较方式如下：

- 从头比较每一位，若前面都相等，那么当前位小的 GRE 更小；
- 若 $A$ 是 $B$ 的一个前缀，那么 $A<B$；

**多组数据**，开始时会输入数据组数 $T$.

## #2.0 大体思路

### #2.1 比较简单~~但看起来很菜~~的做法

首先不难想到，对于在 $i$ 号节点出发的 GRE，经过权值较小的边的 GRE 一定较小，于是不难想到一种暴力的做法：通过按照 GRE 大小进行 dfs，直接得到第 $k$ 小的 GRE 的长度，注意到由于 $k\le10^8$，于是我们只用找到排名前 $\min\{10^8,GRE\_tot\}$ 的 GRE 的长度即可。

那么如何按照 GRE 大小进行 dfs 呢？这取决于存边的顺序，而输入的边没有顺序，于是这里采用 `vector` 存图，在 dfs 开始前现将每个点的出边按边权从小到大排序，这样存图的时间复杂度为 $O(m\log m)$.

但是即使是只用找到排名前 $\min\{10^8,GRE\_tot\}$ 个 GRE 的长度，直接 dfs 也是无法保证时间复杂度的，所以我们需要考虑记忆化，考虑如何将之前的信息进行利用，不难发现，不论何时访问点 $i$（即不论点 $i$ 前的 GRE 片段是什么），从点 $i$ 开始的 GRE 的相对大小是不变的，且在答案数组中一定是连续的，假设我们已经得到了第一次进入 $i$ 时的各个 GRE 的长度，不难想到当前这一次访问 $i$ 号节点得到的 GRE 长度，应当是第一次得到的长度减去第一次访问到 $i$ 时的深度，加上当前的深度。

而我们需要单独开数组保存第一次到达 $i$ 时，从 $i$ 出发的 GRE 长度吗？不需要，因为我们的答案数组就是 GRE 长度，而且由于每一次到达 $i$ 后从 $i$ 出发的 GRE 大小一定连续，所以我们只需要保存在答案数组中的开始位置和数量即可。

这样的话，整体时间复杂度为 $O(m\log m+\min\{10^8,GRE\_tot\})$.

### #2.1 比较困难~~但可以装B~~的做法

设 $f_{i,j}$ 表示从 $i$ 开始第 $j$ 小的 GRE 长度，考虑用一种数据结构进行维护，单个数据结构维护从 $i$ 开始的各个 GRE 长度，考虑转移过程，发现需要支持以下几种操作：

- 合并两个数据结构
- 全局加一
- 插入一个结点

以上三种操作都可以采用**可持久化平衡树**进行维护，同样的，当一棵树的大小超过 $10^8$，就可以把多余的部分删去了。

实现时细节极多（当然我没实现，只是脑中 yy 了一下[doge]），这样的合并需要按照逆拓扑序进行遍历、合并，即建出原图的反图进行拓扑。由于同一棵平衡树可能需要合并多次，所以需要可持久化。由于是采用拓扑，所以不好控制遍历边的顺序，于是我们合并时同样需要先进行分裂，所以需要维护权值，再将当前平衡树合并进去，涉及到改变整棵平衡树的权值，需要进行打标记处理。

合并之后再将整棵平衡树点数维持在 $10^8$ 以内，多出的部分回收处理，所以还需要维护每个子树的大小。

~~总之就是很麻烦就对了。~~

## #3.0 Code

``` cpp
#define mset(l, x) memset(l, x, sizeof(l))

const int N = 100010;
const int M = 100000010;
const int LIMIT = 1e8;

struct Edge {
    int u, v, w;
    Edge (int _u, int _v, int _w) {u = _u, v = _v, w = _w;}
    inline bool operator < (const Edge x) const {return w < x.w;}
};

vector<Edge> G[N];

int s[N], n, m, q, sum, ans[M];
int tot[N], fv[N], fvd[N];

inline void add_edge(int u, int v, int w) {G[u].push_back(Edge(u, v, w));}

void dfs(int u, int dep) {
    if (sum >= LIMIT) return;
    if (～tot[u]) {
        for (int i = 1; i <= tot[u]; ++ i) {
            if (sum >= LIMIT) return;
            ans[++ sum] = ans[fv[u] + i] + dep - fvd[u];
        } return;
    }
    fv[u] = sum, fvd[u] = dep;
    if (s[u]) ans[++ sum] = dep;
    for (unsigned int i = 0; i < G[u].size(); ++ i)
      dfs(G[u][i].v, dep + 1);
    tot[u] = sum - fv[u];
}

int main() {
    int T; scanf("%d", &T);
    for (int t = 1; t <= T; ++ t) {
        scanf("%d%d%d", &n, &m, &q); s[1] = sum = 0;
        for (int i = 1; i <= n; ++ i) G[i].clear();
        for (int i = 2; i <= n; ++ i) scanf("%d", &s[i]);
        for (int i = 1; i <= m; ++ i) {
            int u, v, w; scanf("%d%d%d", &u, &v, &w);
            add_edge(u, v, w);
        }
        for (int i = 1; i <= n; ++ i)
          sort(G[i].begin(), G[i].end());
        mset(tot, -1); dfs(1,0);
        printf("Case #%d:\n", t);
        for (int i = 1; i <= q; ++ i) {
            int x; scanf("%d", &x);
            if (x <= sum) printf("%d\n", ans[x]);
            else printf("-1\n");
        }
    }
    return 0;
}
```

