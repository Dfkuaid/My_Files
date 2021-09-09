# #0.0 写在前面

Splay（伸展树）是较为重要的一种平衡树，理解起来也依旧很容易，但是细节是真的多QnQ，学一次忘一次，还是得用博客加深一下理解（

# #1.0 Splay!

## #1.1 基本构架

Splay 是如何维护树的平衡的呢？近乎不维护...但其实能使 Splay 的形态接近平衡的原因是每一次操作后都将操作的点拉到根部（`splay()` 操作），这似乎是基于统计学的某个结论：这次操作过的数据很有可能还是下一次的操作目标(?)不懂欸QuQ

总之，在实践中我们可以得到这样一点：Splay 能用，并且好用！这就足够了。

对于 Splay 上的每个节点，我们维护如下几个信息：

``` cpp
struct Tree {int son[2], f, cnt, size, val;} t[N];
```

此外还有一些较为常用的基本操作如下：

``` cpp
inline void clear(int k) { //清空 k 号节点
    t[k].cnt = t[k].f = t[k].size = t[k].son[1] = t[k].son[0] = t[k].val = 0;
}

inline void pushup(int k) { //更新 k 号点的大小
    t[k].size = t[t[k].son[0]].size + t[t[k].son[1]].size + t[k].cnt;
}

/*获取当前节点的儿子种类，0 为左儿子，1 为右儿子*/
inline int get(int k) {return k == t[t[k].f].son[1];} 

/*将 x 作为 y 的 op 儿子（0 左 1 右）连边*/
inline void connect(int x, int y, int op) {
    if (x) {t[x].f = y;} if (y) {t[y].son[op] = x;}
}
```

## #1.2 核心操作

核心操作当然就是 `splay()` 操作了，它可以将一个点拉到根部。`splay()` 操作中将一个点上旋的操作是一次旋两个点：

- 父亲与儿子的儿子类型相同，先旋父亲再旋儿子；
- 父亲与儿子的儿子类型不同，先旋儿子再旋父亲；
- 如果父亲是根，那么只旋儿子。

这里的旋转依旧是传统的左旋和右旋，但是我们不再分开讨论，将他们的共同点抽象出来，我们不难得到以下结论：

设当前要旋转的点是 $k$，$f$ 是 $k$ 的父亲，$ff$ 是 $f$ 的父亲，$r$ 是 $k$ 的儿子类型， $rf$ 是 $f$ 的儿子类型，那么我们应当将 $k$ 的 $r\ \hat{}\ 1$ 类型的儿子作为 $f$ 新的 $r$ 类型的孩子，$f$ 变为 $k$ 的 $r\ \hat{}\ 1$ 类型的儿子，$k$ 作为 $ff$ 的新的 $rf$ 类型的孩子。

经过以上的抽象，旋转操作就变得简洁很多了。

``` cpp
inline void rotate(int k) {
    int f = t[k].f, ff = t[f].f, r = get(k), rf = get(f);
    connect(t[k].son[r ^ 1], f, r); connect(f, k, r ^ 1);
    connect(k, ff, rf); pushup(f); pushup(k);
}

inline void splay(int k) {
    for (int f = t[k].f; f = t[k].f, f; rotate(k))
      if (t[f].f) rotate(get(k) == get(f) ? f : k);
    rt = k;
}
```

## #1.3 基本操作

记住一点，不论什么操作后都需要将对应的节点通过 `splay()` 拉至根部。

### #1.3.1 插入

插入的本质就是 BST 的插入，从根节点向下，不断根据权值大小判断进入哪个子树，插入后需要将操作的节点 `splay()` 至根部。

``` cpp
inline void insert(int k) {
    if (!rt){
        rt = ++ tot, t[rt].val = k;
        t[rt].cnt ++; pushup(rt); return;
    }
    int now = rt, f = 0;
    while (true) {
        if (t[now].val == k) {
            t[now].cnt ++; pushup(now);
            pushup(f); splay(now); break;
        }
        f = now; now = t[now].son[t[now].val < k];
        if (! now) {
            t[++ tot].val = k, t[tot].f = f;
            t[tot].cnt ++; t[f].son[t[f].val < k] = tot;
            pushup(tot); pushup(f); splay(tot); break;
        }
    }
}
```

### #1.3.2 查询排名

根据权值大小判断进入左子树还是右子树，进入右子树时需要加上当前节点的大小和左子树的大小。查询结束后进行 `splay()` 操作。

``` cpp
inline int rk(int k) {
    int res = 0, now = rt;
    while (true) {
        if (k < t[now].val) now = t[now].son[0];
        else {
            res += t[t[now].son[0]].size;
            if (k == t[now].val) splay(now), return res + 1;
            res += t[now].cnt; now = t[now].son[1];
        }
    }
}
```

### #1.3.3 查询第 k 大

依旧是传统的通过左子树大小进行查找。

``` cpp
inline int kth(int k) {
    int now = rt;
    while (true) {
        if (k <= t[t[now].son[0]].size) now = t[now].son[0];
        else {
            k -= t[t[now].son[0]].size + t[now].cnt;
            if (k <= 0) splay(now), return t[now].val;
            now = t[now].son[1];
        }
    }
}
```

### #1.3.4 前驱 & 后继

我们直接将要查前驱/后继的数插入 Splay，此时所在节点就被拉到了根部，直接找根的左/右子树的最右/左点即可，最后再删掉该点。

``` cxx
inline int pre() {
    int cur = t[rt].son[0];
    while (t[cur].son[1]) cur = t[cur].son[1];
    splay(cur); return cur;
}

inline int nxt() {
    int cur = t[rt].son[1];
    while (t[cur].son[0]) cur = t[cur].son[0];
    splay(cur); return cur;
}
```

### #1.3.5 删除

主要是进行分类讨论，这一部分不多解释，详见下方代码

``` cpp
inline void del(int k) {
    rk(k); //调用 rk() 的主要目的是将该点拉到根部
    if (t[rt].cnt > 1) {
        t[rt].cnt --; pushup(rt); return;
    } else if (!t[rt].son[0] && !t[rt].son[1]) {
        clear(rt); rt = 0; return;
    } else if (!t[rt].son[0]) {
        int tmp = rt; rt = t[tmp].son[1];
        t[rt].f = 0; clear(tmp); return;
    } else if (!t[rt].son[1]) {
        int tmp = rt; rt = t[tmp].son[0];
        t[rt].f = 0; clear(tmp); return;
    }
    int tmp = rt, l = pre(); splay(l);
    /*分析旋转过程不难发现，前驱的右子树一定为空*/
    /*同样在最终将前驱旋转至根部时，右子树一定也为空*/
    /*所以最后要删掉点的左子树一定为空*/
    /*也可以考虑 BST 的性质，前驱和当前点之间不会再有其他点*/
    connect(t[tmp].son[1], rt, 1);
    clear(tmp); pushup(rt);
}
```

# #2.0 经典例题

## #2.1 [P3369 【模板】普通平衡树](https://www.luogu.com.cn/problem/P3369)

就是上面操作的结合。

``` cpp
const int N = 100010;
const int INF = 0x3fffffff;

struct Tree {int son[2], f, cnt, size, val;} t[N];

int rt, tot, n;

inline void clear(int k) {
    t[k].cnt = t[k].f = t[k].size = t[k].son[1] = t[k].son[0] = t[k].val = 0;
}

inline void pushup(int k) {
    t[k].size = t[t[k].son[0]].size + t[t[k].son[1]].size + t[k].cnt;
}

inline int get(int k) {return k == t[t[k].f].son[1];}

inline void connect(int x, int y, int op) {
    if (x) {t[x].f = y;} if (y) {t[y].son[op] = x;}
}

inline void rotate(int k) {
    int f = t[k].f, ff = t[f].f, r = get(k), rf = get(f);
    connect(t[k].son[r ^ 1], f, r); connect(f, k, r ^ 1);
    connect(k, ff, rf); pushup(f); pushup(k);
}

inline void splay(int k) {
    for (int f = t[k].f; f = t[k].f, f; rotate(k))
      if (t[f].f) rotate(get(k) == get(f) ? f : k);
    rt = k;
}

inline void insert(int k) {
    if (!rt){
        rt = ++ tot, t[rt].val = k;
        t[rt].cnt ++; pushup(rt); return;
    }
    int now = rt, f = 0;
    while (true) {
        if (t[now].val == k) {
            t[now].cnt ++; pushup(now);
            pushup(f); splay(now); break;
        }
        f = now; now = t[now].son[t[now].val < k];
        if (! now) {
            t[++ tot].val = k, t[tot].f = f;
            t[tot].cnt ++; t[f].son[t[f].val < k] = tot;
            pushup(tot); pushup(f); splay(tot); break;
        }
    }
}

inline int rk(int k) {
    int res = 0,now = rt;
    while (true) {
        if (k < t[now].val) now = t[now].son[0];
        else {
            res += t[t[now].son[0]].size;
            if (k == t[now].val) splay(now), return res + 1;
            res += t[now].cnt; now = t[now].son[1];
        }
    }
}

inline int kth(int k) {
    int now = rt;
    while (true) {
        if (k <= t[t[now].son[0]].size) now = t[now].son[0];
        else {
            k -= t[t[now].son[0]].size + t[now].cnt;
            if (k <= 0) splay(now), return t[now].val;
            now = t[now].son[1];
        }
    }
}

inline int pre() {
    int cur = t[rt].son[0];
    while (t[cur].son[1]) cur = t[cur].son[1];
    splay(cur); return cur;
}

inline int nxt() {
    int cur = t[rt].son[1];
    while (t[cur].son[0]) cur = t[cur].son[0];
    splay(cur); return cur;
}

inline void del(int k) {
    rk(k);
    if (t[rt].cnt > 1) {
        t[rt].cnt --; pushup(rt); return;
    } else if (!t[rt].son[0] && !t[rt].son[1]) {
        clear(rt); rt = 0; return;
    } else if (!t[rt].son[0]) {
        int tmp = rt; rt = t[tmp].son[1];
        t[rt].f = 0; clear(tmp); return;
    } else if (!t[rt].son[1]) {
        int tmp = rt; rt = t[tmp].son[0];
        t[rt].f = 0; clear(tmp); return;
    }
    int tmp = rt, l = pre(); splay(l);
    connect(t[tmp].son[1], rt, 1);
    clear(tmp); pushup(rt);
}

int main() {
    scanf("%d", &n); int opt,x;
    while (n --){
        scanf("%d%d", &opt, &x);
        if (opt == 1) insert(x);
        else if (opt == 2) del(x);
        else if (opt == 3) printf("%d\n", rk(x));
        else if (opt == 4) printf("%d\n", kth(x));
        else if (opt == 5)
          insert(x), printf("%d\n", t[pre()].val), del(x);
        else insert(x), printf("%d\n", t[nxt()].val), del(x);
    }
    return 0;
}
```

## #2.2 [P3391 【模板】文艺平衡树](https://www.luogu.com.cn/problem/P3391)

这题用到了 Splay 的另一个应用：处理序列。

对于每个节点，我们再多维护一个 tag，表示当前节点的子树的所有节点的左右儿子是否交换，通过两次 `splay()` 操作可以将操作区间提取出来。注意在旋转之前需要将当前节点和父亲节点的标记下传。

``` cpp
const int N = 400010;
const int INF = 0x3fffffff;

struct Tree {int son[2], f, cnt, size, val, tg;} t[N];

int rt,tot, n,m;

inline void clear(int k) {
    t[k].cnt = t[k].f = t[k].size = t[k].son[1] = t[k].son[0] = t[k].val = 0;
}

inline void pushup(int k) {
    t[k].size = t[t[k].son[0]].size + t[t[k].son[1]].size + t[k].cnt;
}

inline void pushdown(int k) {
    if (t[k].tg){
        t[t[k].son[0]].tg ^= 1; t[t[k].son[1]].tg ^= 1;
        swap(t[k].son[0],t[k].son[1]); t[k].tg = 0;
    }
}

inline int get(int k) {return k == t[t[k].f].son[1];}

inline void connect (int x, int y, int op){
    if (x) {t[x].f = y;} if (y) {t[y].son[op] = x;}
}

inline void rotate(int k) {
    pushdown(t[k].f), pushdown(k),;
    int f = t[k].f, ff = t[f].f, r = get(k), rf = get(f);
    connect(t[k].son[r ^ 1], f, r); connect(f, k, r ^ 1);
    connect(k, ff, rf); pushup(f); pushup(k);
}

inline void splay(int k, int g) {
    for (int f = t[k].f; f = t[k].f, f != g; rotate(k))
      if (t[f].f != g) rotate(get(k) == get(f) ? f : k);
    if (!g) rt = k;
}

inline int kth(int k) {
    int now = rt;
    while (true){
        pushdown(now);
        if (t[t[now].son[0]].size >= k)
          now = t[now].son[0];
        else{
            k -= t[t[now].son[0]].size + t[now].cnt;
            if (k <= 0) return now;
            now = t[now].son[1];
        }
    }
}

inline void reverse(int x, int y) {
    int l = x - 1, r = y + 1;
    l = kth(l + 1); r = kth(r + 1);
    splay(l, 0); splay(r, l);
    int cur = t[rt].son[1];
    cur = t[cur].son[0];
    t[cur].tg ^= 1;
}

inline void print(int k) {
    pushdown(k);
    if (t[k].son[0]) print(t[k].son[0]);
    if (t[k].val != 0 && t[k].val != n + 1)
      printf("%d ",t[k].val);
    if (t[k].son[1]) print(t[k].son[1]);
}

inline void build(int l, int r, int k, int f) {
    if (l > r) return;
    if (l == r){
        t[k].f = f; t[k].val = l;
        t[k].cnt = t[k].size = 1;
        return;
    }
    int mid = (l + r) >> 1;
    t[k].f = f; t[k].val = mid; t[k].cnt = 1;
    t[k].son[0] = ++ tot; build(l, mid - 1, tot, k);
    t[k].son[1] = ++ tot; build(mid + 1, r, tot, k);
    pushup(k);
}

int main(){
    scanf("%d%d", &n, &m);
    build(0, n + 1, ++ tot, 0);
    rt = 1;
    while (m --){
        int x, y; scanf("%d%d", &x, &y); reverse(x, y);
    }
    print(rt);
    return 0;
}
``