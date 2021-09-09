# #0.0 前置知识

建议您熟练掌握：

- [权值线段树](https://www.cnblogs.com/Dfkuaid-210/p/14382621.html)
- [动态开点线段树](https://www.cnblogs.com/Dfkuaid-210/p/14365197.html)

下文中所有的线段树都会采用动态开点，不会过多说明。

# #1.0 线段树合并

## #1.1 是什么？

可能我们现在有几棵值域重合的权值线段树，现在我们需要将他们的信息整合到一棵权值线段树上，那么就需要线段树合并这一操作来维护。举最简单的例子：两棵权值线段树维护的是每个数出现的次数，现在将两棵树合并。如下图：

![](https://pic.imgdb.cn/item/60d54f98844ef46bb2c639a1.png)

只需将对应位置的值相加即可。

## #1.2 怎么想？

最~~暴力~~朴素的方法是单点修改，这样时间复杂度爆炸。

显然我们只需要让每一个节点维护的数量相加即可，如果遇到空节点（没有被动态开点）就说明这个节点没有维护的值，也就是 $0$，返回不为空的节点即可。

如果两个都不为空，那么递归合并左右子树，最后维护总体信息即可。

如果其中一个的节点可以用完就丢，那就放入回收站（优化空间）。

``` cpp
int merge (int x, int y) {
    if (!x || !y) return x + y;
    p[x].sum += p[y].sum;
    p[x].ls = merge(p[x].ls, p[y].ls);
    p[x].rs = merge(p[x].rs, p[y].rs);
    del(y);
    return x;
}

```

或者也可以这么写

``` cpp
int merge (int x, int y, int l, int r) {
    if (!x || !y) return x + y;
    int k = newnode(), mid = (l + r) >> 1;
    if (l == r) {
        p[k].sum = p[x].sum + p[y].sum;
        return;
    }
    p[k].ls = merge(p[x].ls, p[y].ls, l, mid);
    p[k].rs = merge(p[x].rs, p[y].rs, mid + 1, r);
    del(x); del(y); pushup(k); return k;
}
```

第二种可扩展性要更高一些，但实际原理是一样的。

合并的时间复杂度看起来并不优，如果两棵树都是满的那么时间复杂度为 $O(n).$


# #2.0 线段树分裂

## #2.1 是什么？

既然有合并的操作，有时也需要我们将权值线段树的一部分拆出来，将几棵树变成两棵树，这时候，就需要用上线段树分裂的操作。还是用上文的简单例子：权值线段树维护的是每个数出现的次数。

![](https://pic.imgdb.cn/item/60d57c87844ef46bb2f07229.png)

## #2.2 怎么办？

这里的分裂，采用按数量分裂的方式，即将第 $1$ \~ $k$ 个数的分到一颗线段树上（注意 $2$ 个 $x$ 算两个数），剩下的的分到另一棵树上。

这样来看，不难分出一下几种情况进行讨论：

- 当前节点的左子树的数量和 $v<k$，那么左子树不动，递归分裂右子树即可，注意在右子树上分裂的数量变为 $k-v$
- 当前节点的左子树的数量和 $v=k$，那么左子树依然不动，将右子树完全分裂出去即可
- 当前节点的左子树的数量和 $v>k$，这时右子树完全分裂出去，递归分裂左子树，$k$ 不变

``` cpp
void split (int x, int &y, ll k) {
    if (!x) return;
    y = NEW();//分裂出的新节点
    ll v = p[p[x].ls].sum;
    if (k > v) split(p[x].rs, p[y].rs, k - v); //递归右子树
    else swap(p[x].rs, p[y].rs); 
    /*新节点的右子树为空，交换就是将右子树完全分裂*/
    if (k < v) split(p[x].ls, p[y].ls, k); //递归左子树
    p[y].sum = p[x].sum - k, p[x].sum = k; //修改所维护的信息
}
```

但是注意到，如果是让我们将值域 $[1,k]$ 分离出来呢？那我们可以查询 $[1,k]$ 中有多少个数，即得到相应 $[1,k]$ 的数量，可进行分裂。

# #3.0 例题

## #3.1 [P4556 [Vani有约会]雨天的尾巴](https://www.luogu.com.cn/problem/P4556)

对树上的每个节点建一棵权值线段树，维护各种救济粮的出现数量及出现最多的次数和种类。但是如果对每个节点进行修改复杂度爆炸，但是树剖无法维护这么多信息，考虑树上差分+线段树合并。

对路径两端的点相应救济粮数量加一，此时如果将线段树维护的信息自叶子向根合并会发现两点的 $\texttt{LCA}$ 及以上位置救济粮数量加了 $2$，$\texttt{LCA}$ 处应当减少 $1$，如果 $\texttt{LCA}$ 不是根节点，则在 $\texttt{LCA}$ 的父亲处相应救济粮数量减一，这样向上合并的信息便是正确的了，这就是树上差分的思想。每个点上的答案就是所有子孙的线段树向上合并后得到的结果，这一步递归处理即可。

``` cpp
const int N = 6000010;
const int INF = 0x3fffffff;

struct Edge{
    int u,v;
    int next;
};
Edge e[N];

struct Node{
    int ls,rs;
    int l,r;
    int mxn,mxnp;
};
Node p[N << 2];

int A[N],B[N],C[N];
int n,m,tot,etot,head[N],L,rt[N];
int d[N],f[N],son[N],size[N],top[N],ans[N];

inline void add(int u,int v){
    e[etot].u = u, e[etot].v = v;
    e[etot].next = head[u], head[u] = etot ++;
}

inline void pushup(int k){
    if (p[p[k].ls].mxn >= p[p[k].rs].mxn){
        p[k].mxn = p[p[k].ls].mxn;
        p[k].mxnp = p[p[k].ls].mxnp;
    }else{
        p[k].mxn = p[p[k].rs].mxn;
        p[k].mxnp = p[p[k].rs].mxnp;
    }
}

inline int change(int k,int l,int r,int x,int c){
    if (!k) k = ++ tot; //采用动态开点
    if (l == r){ //到达叶子节点
        p[k].mxn += c, p[k].mxnp = l;
        return k; //注意要返回当前节点的编号
    }
    int mid = (l + r) >> 1; //递归处理
    if (mid >= x) p[k].ls = change(p[k].ls,l,mid,x,c);
    else p[k].rs = change(p[k].rs,mid + 1,r,x,c);
    pushup(k);return k; //记得 pushup()
}

/*dfs1 与 dfs2 是树剖，用于处理 LCA*/

inline void dfs1(int x,int fa,int depth){
    f[x] = fa;d[x] = depth;size[x] = 1;
    for (int i = head[x];i != -1;i = e[i].next){
        if (e[i].v == f[x]) continue;
        dfs1(e[i].v,x,depth + 1);
        size[x] += size[e[i].v];
        if (size[e[i].v] > size[son[x]])
          son[x] = e[i].v;
    }
}

inline void dfs2(int u,int t){
    top[u] = t;
    if (!son[u]) return;
    dfs2(son[u],t);
    for (int i = head[u];i != -1;i = e[i].next)
      if (e[i].v != son[u] && e[i].v != f[u])
        dfs2(e[i].v,e[i].v);
}

inline int lca(int x,int y){
    while (top[x] != top[y]){
        if (d[top[x]] < d[top[y]]) swap(x,y);
        x = f[top[x]];
    }
    if (d[x] < d[y]) swap(x,y);
    return y;
}

//线段树合并，这里的节点可以不回收处理

inline int merge(int a,int b,int l,int r){
    if (!a || !b) return a + b;
    if (l == r){
        p[a].mxn += p[b].mxn, 
        p[a].mxnp = l;
        return a;
    }
    int mid = (l + r) >> 1;
    p[a].ls = merge(p[a].ls,p[b].ls,l,mid);
    p[a].rs = merge(p[a].rs,p[b].rs,mid + 1,r);
    pushup(a);
    return a;
}

//处理最终答案，由叶子向上合并线段树

inline void lstep(int x){
    for (int i = head[x];i != -1;i = e[i].next)
      if (d[e[i].v] > d[x]){
          lstep(e[i].v);
          rt[x] = merge(rt[x],rt[e[i].v],1,L);
      }
    if (p[rt[x]].mxn) //ans[] 储存的是种类，如果存在救济粮才赋值
      ans[x] = p[rt[x]].mxnp;
}

int main(){
    mset(head,-1);
    scanf("%d%d",&n,&m);
    for (int i = 1;i < n;i ++){
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v);add(v,u);
    }
    
    dfs1(1,0,1);
    dfs2(1,1);
    
    for (int i = 1;i <= m;i ++){
        scanf("%d%d%d",&A[i],&B[i],&C[i]);
        L = max(L,C[i]);
    }
    for (int i = 1;i <= m;i ++){
        int anc = lca(A[i],B[i]);
        rt[A[i]] = change(rt[A[i]],1,L,C[i],1);
        rt[B[i]] = change(rt[B[i]],1,L,C[i],1);
        rt[anc] = change(rt[anc],1,L,C[i],-1);
        if (f[anc]) rt[f[anc]] = change(rt[f[anc]],1,L,C[i],-1);
    }
    lstep(1);
    for (int i = 1;i <= n;i ++)
      cout << ans[i] << endl;
    return 0;
}
```

## #3.2 [P5494 【模板】线段树分裂](https://www.luogu.com.cn/problem/P5494)

> 由于两题时间相隔久远，导致码风略有不同。

逐个来看各种操作

0. `0 p x y`：将可重集 $p$ 中大于等于 $x$ 且小于等于 $y$ 的值放入一个新的可重集中（新可重集编号为从 $2$ 开始的正整数，是上一次产生的新可重集的编号 $+1$）。

我们先找到 $[1,z]$ 和 $[y,z]$ 这两个区间各有多少个数，记为 $t_1,t_2$，然后先将 $[1,y-1]$ 的区间分裂出来，这一部分包含的数的数量是 $t_1-t_2$，再从 $[y,n]$ 中将 $[y,z]$ 分裂出来，这一部分包含的数的数量是 $t_2$，最后再将 $[1,y-1]$ 和 $[z+1,n]$ 合并即可。

1. `1 p t`：将可重集 $t$ 中的数放入可重集 $p$，且清空可重集 $t$（数据保证在此后的操作中不会出现可重集 $t$）。

这一步就是将 $p$ 和 $t$ 合并，然后 $t$ 上的节点就可以回收了。

2. `2 p x q`：在 $p$ 这个可重集中加入 $x$ 个数字 $q$。

权值线段树单点修改，不多说。

3. `3 p x y`：查询可重集 $p$ 中大于等于 $x$ 且小于等于 $y$ 的值的个数。

权值线段树区间查询，不多说。

4. `4 p k`：查询在 $p$ 这个可重集中第 $k$ 小的数，不存在时输出 `-1`。

注意这里 “第 $k$ 小” 是要算上重复的数的。即如果是 `1 1 2`，则 $2$ 是第三小。那么我们可以先查询可重集 $p$ 的数的个数，如果小于 $k$，则输出 `-1`，否则按照下面的分类进行查找：

- 当前节点左子树的数的数量 $v$ 大于等于 $k$，递归进入左子树
- 当前节点左子树的数的数量 $v$ 小于 $k$，递归进入右子树，$k$ 变为 $v-k.$

``` cpp
int kth (int k, int l, int r, int x) {
    if (l == r) return l;
    int mid = (l + r) >> 1;
    if (p[p[k].ls].sum >= x) return kth(p[k].ls, l, mid, x);
    else return kth(p[k].rs, mid + 1, r, x - p[p[k].ls].sum);
}
```

将上面的操作结合一下，就得到了本题的代码。

``` cpp
const int N = 1000010;
const int INF = 0x3fffffff;

struct Node {
    int ls, rs;
    int l, r;
    ll sum;
};
Node p[N << 2];

int n, m, tot, bac[N], cnt, tcnt = 1, rt[N];

inline int NEW() {return tot ? bac[tot --] : ++ cnt;}

inline void del(int k) {
    bac[++ tot] = k, p[k].ls = p[k].rs = p[k].sum = 0;
}

void modify (int &k, int l, int r, int pos, int ts) {
    if (!k) k = NEW();
    p[k].sum += ts;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (pos <= mid) modify(p[k].ls, l, mid, pos, ts);
    else modify(p[k].rs, mid + 1, r, pos, ts);
}

ll query (int k, int l, int r, int x, int y) {
    if (x <= l && r <= y) return p[k].sum;
    ll res = 0, mid = (r + l) >> 1;
    if (x <= mid) res += query(p[k].ls, l, mid, x, y);
    if (mid < y) res += query(p[k].rs, mid + 1, r, x, y);
    return res;
}

int kth (int k, int l, int r, int x) {
    if (l == r) return l;
    int mid = (l + r) >> 1;
    if (p[p[k].ls].sum >= x) return kth(p[k].ls, l, mid, x);
    else return kth(p[k].rs, mid + 1, r, x - p[p[k].ls].sum);
}

int merge (int x, int y) {
    if (!x || !y) return x + y;
    p[x].sum += p[y].sum;
    p[x].ls = merge(p[x].ls, p[y].ls);
    p[x].rs = merge(p[x].rs, p[y].rs);
    del(y);
    return x;
}

void split (int x, int &y, ll k) {
    if (!x) return;
    y = NEW();
    ll v = p[p[x].ls].sum;
    if (k > v) split(p[x].rs, p[y].rs, k - v);
    else swap(p[x].rs, p[y].rs);
    if (k < v) split(p[x].ls, p[y].ls, k);
    p[y].sum = p[x].sum - k, p[x].sum = k;
}

int main () {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++) {
        int x; scanf("%d", &x);
        modify(rt[1], 1, n, i, x);
    }
    for (int i = 1; i <= m; i ++) {
        int opt, x, y, z; scanf("%d", &opt);
        if (opt == 0) {
            scanf("%d%d%d", &x, &y, &z);
            ll k1 = query(rt[x], 1, n, 1, z);
            ll k2 = query(rt[x], 1, n, y, z);
            int tmp = 0;
            split(rt[x], rt[++ tcnt], k1 - k2);
            split(rt[tcnt], tmp, k2);
            rt[x] = merge(rt[x], tmp);
        } else if (opt == 1) {
            scanf("%d%d", &x, &y);
            rt[x] = merge(rt[x], rt[y]);
        } else if (opt == 2) {
            scanf("%d%d%d", &x, &y, &z);
            modify(rt[x], 1, n, z, y);
        } else if (opt == 3) {
            scanf("%d%d%d", &x, &y, &z);
            printf("%lld\n", query(rt[x], 1, n, y, z));
        } else if (opt == 4) {
            scanf("%d%d", &x, &y);
            if (p[rt[x]].sum < y) {printf("-1\n"); continue;}
            printf("%d\n", kth(rt[x], 1, n, y));
        }
    }
    return 0;
}
```

<div id='refer-auth'></div>

# 参考资料

[1] [题解 P6012 【模板】线段树分裂 - ix35_](https://www.luogu.com.cn/blog/ix-35/solution-p6012)