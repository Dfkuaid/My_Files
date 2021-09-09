# #0.0 写在前面

（~~话说好久没在博客前写前言了呢~~）

总之就是一直就想写几篇博客来专门记录一下平衡树的知识，可是总是咕咕咕QuQ，今天总算是把 fhq Treap 学了，趁热打铁赶紧来一发（。

Treap 分为两类

- [[经典套装]带旋 Treap](#treap-with-spin)
- [[进阶套装]无旋 Treap(fhq Treap)](#treap-without-spin)

总体来讲都很好理解，fhq Treap 相对于传统的带旋 Treap 支持的操作好像更多（？）写起来也要简洁不少。

<div id="treap-with-spin"></div>

# #1.0 带旋 Treap

> 我已经想不起来我上次写带旋 Treap 是啥时候了QwQ

咕咕咕~原因有贰：

- 自己一年半之前写的带旋 Treap 实在是太丑了，~~不想再写一遍~~；
- 带旋 Treap 一般不会用到，fhq Treap 就够了。

<div id="treap-without-spin"></div>

# #2.0 无旋 Treap (fhq Treap)

## #2.1 基本架构

fhq Treap 如何解决平衡性的问题呢？引入一个**附加权值**，整体的结构对于所维护的权值满足 BST 的性质，对于附加权值满足堆序。那么用什么来作为附加权值呢？我们需要用他来使整棵树尽可能平衡，所以采用**随机数**作为附加权值。

``` cpp
struct Node {int val, tar, siz, ls, rs;} p[N];

inline void pushup(int k) {p[k].siz = p[p[k].ls].siz + p[p[k].rs].siz + 1;}
inline int new_node(int x) {p[++ cnt] = (Node){x, rand(), 1, 0, 0}; return cnt;}
```

fhq Treap 有很大的一个优点：**短小精悍**！他的主要函数只有两个：`split()` 和 `merge()`，所有的其他操作又可以在运用分裂与合并得到很好的解决，并且这个东西可以搞除了 LCT 以外一切 bst，无旋 treap，splay 所能搞的东西。

## #2.2 运转核心

### #2.2.1 Split!

分裂是将一个 Treap 按权值（注意不是附加权值）变成两个 Treap 的过程，我们将权值小于等于 $v$ 的部分分到一棵 Treap 中，剩下的分到另一棵 Treap 中。

分裂的过程也很好想，如果一个节点的权值小于等于 $v$，那么左子树的节点的权值一定都小于等于 $v$，去分裂右子树即可，反之亦然。

``` cpp
void split(int k, int v, int &x, int &y) {
    if (!k) {x = y = 0; return;}
    if (p[k].val <= v) {
        x = k; split(p[k].rs, v, p[k].rs, y);
    } else {
        y = k; split(p[k].ls, v, x, p[k].ls);
    } pushup(k);
}
```

### #2.2.2 Merge!

现在我们有两个 Treap，不妨叫他们左 Treap 和右 Treap，其中要求左 Treap 中的权值最大值要小于右 Treap 中的权值最小值。现在我们要将这两棵 Treap 合并。

如果当前左 Treap 节点的附加权值小于右 Treap 节点的附加权值，那么就将当前左 Treap 节点的右子树与当前右 Treap 节点继续进行合并；否则，就将当前左 Treap 节点与当前右 Treap 节点的左子树继续进行合并；

``` cpp
int merge(int x, int y) {
    if (!x || !y) return x + y;
    if (p[x].tar < p[y].tar) {
        p[x].rs = merge(p[x].rs, y);
        pushup(x); return x;
    } else {
        p[y].ls = merge(x, p[y].ls);
        pushup(y); return y;
    }
}
```

## #2.3 各种操作

核心操作就这样结束了，剩下我们来看各种操作如何用 `split()` 和 `merge()` 完成。

### #2.3.1 插入

将 Treap 按插入值 $v$ 进行分裂，再将三部分合并。

``` cpp
inline void insert(int v) {
    int x = 0, y = 0; split(rt, v, x, y);
    rt = merge(merge(x, new_node(v)), y);
}
```

### #2.3.2 删除

将原 Treap 分裂为三部分：

- 小于 v；
- 等于 v；
- 大于 v；

因为 fhq Treap 的节点不计重复，多个相同权值以不同的节点出现，所以我们要将第二部分的左右子树合并，这样根部的一个 $v$ 就被删掉了，之后再将三部分合并即可。

``` cpp
inline void del(int v) {
    int x = 0, y = 0, z = 0;
    split(rt, v, x, z);
    split(x, v - 1, x, y);
    y = merge(p[y].ls, p[y].rs);
    rt = merge(merge(x, y), z);
}
```

### #2.3.3 前驱

按 $v-1$ 分裂，在权值小于 $v$ 的树中尽可能向右走。

``` cpp
inline int pre(int v) {
    int x = 0, y = 0, pos; split(rt, v - 1, x, y);
    pos = x; while (p[pos].rs) pos = p[pos].rs;
    merge(x, y); return p[pos].val;
}
```

### #2.3.4 后继

按 $v$ 分裂，在权值大于 $v$ 的树中尽可能向左走。

``` cpp
inline int nxt(int v) {
    int x = 0, y = 0, pos; split(rt, v, x, y);
    pos = y; while (p[pos].ls) pos = p[pos].ls;
    merge(x, y); return p[pos].val;
}
```

### #2.3.5 求排名

按 $v-1$ 分裂，权值小于 $v$ 的树的大小加一即为排名。

``` cpp

void rk(int v) {
    int x = 0, y = 0; split(rt, v - 1, x, y);
    int ans = (p[x].siz + 1); rt = merge(x, y);
}
```

### #2.3.6 排名第 k

非常普遍的操作方法，看左子树的大小是否大于等于 $v$，

- 是，进入左子树；
- 否，大小刚好等于 $v-1$，那么当前节点即为答案；
- 否则进入右子树；

``` cpp
inline int kth(int k, int v) {
    while (true) {
        if (p[p[k].ls].siz >= v) k = p[k].ls;
        else if (p[p[k].ls].siz + 1 == v) return p[k].val;
        else v -= p[p[k].ls].siz + 1, k = p[k].rs;
    }
}
```

# #3.0 经典练习

## #3.1 [P6136 【模板】普通平衡树（数据加强版）](https://www.luogu.com.cn/problem/P6136)

就是上面的操作，注意强制在线和合并答案；

``` cpp
const int N = 1100010;
const int INF = 0x3fffffff;

struct Node {int val, tar, siz, ls, rs;} p[N];

int n, m, cnt, rt, lst, ans;

inline void pushup(int k) {p[k].siz = p[p[k].ls].siz + p[p[k].rs].siz + 1;}
inline int new_node(int x) {p[++ cnt] = (Node){x, rand(), 1, 0, 0}; return cnt;}

void split(int k, int v, int &x, int &y) {
    if (!k) {x = y = 0; return;}
    if (p[k].val <= v) {
        x = k; split(p[k].rs, v, p[k].rs, y);
    } else {
        y = k; split(p[k].ls, v, x, p[k].ls);
    } pushup(k);
}

int merge(int x, int y) {
    if (!x || !y) return x + y;
    if (p[x].tar < p[y].tar) {
        p[x].rs = merge(p[x].rs, y);
        pushup(x); return x;
    } else {
        p[y].ls = merge(x, p[y].ls);
        pushup(y); return y;
    }
}

inline void insert(int v) {
    int x = 0, y = 0; split(rt, v, x, y);
    rt = merge(merge(x, new_node(v)), y);
}

inline void del(int v) {
    int x = 0, y = 0, z = 0;
    split(rt, v, x, z);
    split(x, v - 1, x, y);
    y = merge(p[y].ls, p[y].rs);
    rt = merge(merge(x, y), z);
}

void rk(int v) {
    int x = 0, y = 0; split(rt, v - 1, x, y);
    lst = (p[x].siz + 1); rt = merge(x, y);
}

inline int kth(int k, int v) {
    while (true) {
        if (p[p[k].ls].siz >= v) k = p[k].ls;
        else if (p[p[k].ls].siz + 1 == v) return p[k].val;
        else v -= p[p[k].ls].siz + 1, k = p[k].rs;
    }
}

inline int pre(int v) {
    int x = 0, y = 0, pos; split(rt, v - 1, x, y);
    pos = x; while (p[pos].rs) pos = p[pos].rs;
    merge(x, y); return p[pos].val;
}

inline int nxt(int v) {
    int x = 0, y = 0, pos; split(rt, v, x, y);
    pos = y; while (p[pos].ls) pos = p[pos].ls;
    merge(x, y); return p[pos].val;
}

int main() {
    srand((unsigned)time(NULL));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i) {
        int x; scanf("%d", &x); insert(x);
    }
    while (m --) {
        int opt, x; scanf("%d%d", &opt, &x); x ^= lst;
        if (opt == 1) insert(x);
        else if (opt == 2) del(x);
        else if (opt == 3) rk(x);
        else if (opt == 4) lst = kth(rt, x);
        else if (opt == 5) lst = pre(x);
        else lst = nxt(x);
        if (opt >= 3) ans ^= lst;
    }
    printf("%d", ans);
    return 0;
}
``