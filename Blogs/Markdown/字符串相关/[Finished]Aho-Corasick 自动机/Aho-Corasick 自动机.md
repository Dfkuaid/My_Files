# #0.0 并不必要的前置知识

下面提到的“前置知识”只是如果会的话更方便理解，但并非必须会。

## #0.1 自动机相关概念

详见 [自动机 - OI Wiki](https://oi-wiki.org/string/automaton/)。当然不做了解也没有任何学习 $\texttt{Aho-Corasick}$ 自动机的困难。

但是有一点还是需要了解：**自动机上的每一个节点代表的是一个状态**，在 $\tt{AC}$ 自动机上，代表的就是从根节点一路走到该节点所经过的边上的字符所组成的字符串。

## #0.2 KMP 匹配算法

$\tt{AC}$ 自动机中用到了 [$\tt{KMP}$ 匹配算法](https://www.cnblogs.com/Dfkuaid-210/p/KMP.html) 中的部分思想，（~~当然也相信各位一定都能熟练掌握 KMP~~），但如果没有学习 $\texttt{KMP}$ 算法的话依旧没有任何问题。

# #1.0 何为 AC 自动机

## #1.1 概述

对于单模式串的匹配我们可以采用 $\texttt{KMP}$ 算法进行匹配，但是如果有多个模式串呢？

$\texttt{AC}$ 自动机（$\texttt{Aho-Corasick automaton}$）就是一种多模式匹配算法。它可以将多个模式串统一处理，对于每一个待匹配的文本串都可以一次与多个模式串进行匹配。

## #1.2 思想

考虑我们如何将多个不同的文本串联系起来，$\tt{Trie}$ 树是一个很常用的方法，而 $\tt{AC}$ 自动机便是以 $\tt{Trie}$ 树为骨架建造的。也就是将所有的模式串先插入到一棵 $\tt{Trie}$ 树中，再结合上我们在 $\tt{KMP}$ 匹配算法中的思想——假设与当前串不能匹配，那么我们沿着**失配边**走到当前串的一个后缀末，看看可不可以继续匹配，这种“失配边”有一个更加高端的名字——**后缀链接**，“后缀链接”的思想在许多字符串算法中都有使用。

# #2.0 AC 自动机的建立

## #2.1 骨架的形成

我们在上面提到过了，$\tt{Trie}$ 树就是 $\tt{AC}$ 自动机的“骨架”，那么在进行血肉的构建前，我们必须先把 $\tt{Trie}$ 树建立起来。

$\tt{AC}$ 自动机中 $\tt{Trie}$ 树的建立过程与一般的 $\tt{Trie}$ 树无异。

``` cpp
struct Trie {
    int ch[30];
    int fail, tag;
    /*fail 是失配边，下面都会详细讲解；
    tag 是作为单词词尾的标记，*/
};

inline void insert(char *s) {
    int now = 0, len = strlen(s);
    for (int i = 0; i < len; ++ i) {
        int k = s[i] - 'a';
        if (!t[now].ch[k]) t[now].ch[k] = ++ cnt;
        now = t[now].ch[k];
    }
    ++ t[now].tag;
}
```

我们所需要做的不过是将所有的模式串都插入到这一棵 $\tt{Trie}$ 树中。

## #2.2 肌肉的连接

如果说 $\tt{Trie}$ 树是 $\tt{AC}$ 自动机的骨架，那么失配边（后缀链接）便是令 $\tt{AC}$ 自动机运作起来的强有力的肌肉，下面来重点看失配边的作用与形成。

### #2.2.1 后缀链接的作用

如果你学习过 $\tt{KMP}$ 匹配算法便不难理解这里的失配边 `fail` 指针，它就类似于 $\tt{KMP}$ 算法中的 `next[]` 数组。每个节点的 `fail` 指针指向的是**当前节点代表的字符串的，在 $\tt{Trie}$ 树上以前缀出现的，最长的后缀所对应的节点**。

上面的整句话似乎有些绕或难以理解，来看下面这个例子：

我们在 $\tt{Trie}$ 树中依次插入 $\text{is, his, him}$ 这三个单词，得到的 $\tt{Trie}$ 树如下：

![](https://pic.imgdb.cn/item/60e3feb55132923bf88bd12a.png)

根据上面~~并不清晰的~~定义，$5$ 号节点的 `fail` 指针应当指向 $2$ 号节点，因为 '$\text{is}$' 是 '$\text{his}$' 的一个后缀，存在从 $0$ 号点出发的一个状态 '$\text{is}$'，且是符合上述要求的最长的一个。

要注意，如果不存在这样地后缀，那么该节点的 `fail` 应当指向 $0$ 节点。

上图完整地建出 `fail` 指针的样子如下图：

![](https://pic.imgdb.cn/item/60e401865132923bf8a2a9ac.png)

那么，我们在匹配的时候，在 $\tt{Trie}$ 树上逐步推进，如果发现当前节点不存在后面的字符对应的边，那么就沿着 `fail` 指针向前跳，直到能够找到对应的边或来到了 $0$ 号节点（无法匹配该字符），那么便可以继续匹配下一个字符。

那么现在我们可以写出一个简单的匹配函数：

``` cpp
/*先不要着急！这不是最终版本的查询函数*/
inline void query(char *s) {
    int res = 0, now = 0, len = strlen(s);
    for (int i = 0; i < len; ++ i) {
        int k = s[i]-'a';
        while (!t[now].ch[k] && now)
          now = t[now].fail;
        if (t[now].ch[k]) {
            now = t[now].ch[k];
            /*Do something you want to do*/
        }
    }
}
```

### #2.2.2 建立后缀链接

> 下文中，会不严谨地称呼“后缀链接指向的节点”为“后缀节点”。

那么如何建立后缀链接呢？

首先先点出几个很显然的性质：

- 除 $0$ 号点外，从 $0$ 号点到任意节点 $x$ 的 `fail` 指针指向的点所经过的边的数量一定少于 $0$ 号点到节点 $x$ 所经过的边数。

那么，结合上面的性质，考虑如何运用已经求得的 `fail` 指针来算出当前节点的 `fail` 指针。我们可以想到通过 $\tt{BFS}$ 来创建整张图的指针，大体流程如下：

当前要求 $u$ 的 `fail` 指针，$f$ 是 $u$ 的父节点，$f$ 通过 $c$ 连向 $u$：

1. 因为我们是 $\tt{BFS}$，故 $f$ 的 `fail` 指针必然已经求出，我们顺着 $f$ 的 `fail` 指针，查看指向的点是否具有 $c$ 这个字符的边。

    - 有，那么 $u$ 的 `fail` 指针指向的就是 $f$ 的 `fail` 指针指向的点的由 $c$ 相连的儿子；
    - 没有，那么继续跳 $f$ 的 `fail` 的 `fail`，直到找到或回到 $0$ 号节点。

2. 将当前节点入队。

来一张 gif 形象地说明一下吧~

![](https://pic.imgdb.cn/item/60e40e1d5132923bf8f08705.gif)

图中红色节点为队中节点，黑色节点为已出队节点。

但是我们发现，在寻找 $6$ 的后缀节点时，需要跳父节点的 `fail` 指针，时间上似乎并不优？可不可以直接取代这个过程呢？

可以。对于 $x$ 节点，我们只需要将它不存在的儿子设置为它的后缀节点 $y$ 的相应的儿子。注意到，即使 $y$ 的相应儿子也不存在也没关系，因为由上面我们提到过的结论可以知道，这样的 $y$ 的儿子一定已经连到 $y$ 的后缀节点的相应儿子了，以此类推。若是都不存在，那么最终一定会连到 $0$ 号节点上。

当然，这样的节点就没有入队的必要了。整个过程就像是压缩了路径。

``` cpp
inline void build() {
    queue <int> q;
    for (int i = 0; i < 26; ++ i)
        if (t[0].ch[i]) q.push(t[0].ch[i]);
    while (q.size()) {
        int now = q.front(); q.pop();
        for (int i = 0; i < 26; ++ i)
            if (t[now].ch[i]) {
                t[t[now].ch[i]].fail = t[t[now].fail].ch[i];
                q.push(t[now].ch[i]);
            } else t[now].ch[i] = t[t[now].fail].ch[i];
    }
}
```

随着构建方式的升级，匹配字符串的过程也可以更改了：

``` cpp
inline int query(char *s) {
    int res = 0, now = 0, len = strlen(s);
    for (int i = 0; i < len; ++ i) {
        now = t[now].ch[s[i] - 'a'];
        /*Do something you want to do*/
    }
    return res;
}
```

变得简单了很多，不是吗？

# #3.0 AC 自动机的应用

## #3.1 fail 树

不难发现，所有节点与所有的 `fail` 边可以构成一棵树，我们暂且叫他“$\tt{fail}$ 树”，不难发现，如果 $a$ 的后缀节点是 $b$，且 $a$ 和 $b$ 都是单词的结尾，那么如果一个文本在 $a$ 处有匹配，在 $b$ 处一定也会有匹配。

所以在 $b$ 上的匹配总次数就是在 $b$ 上匹配的次数与在 $\tt{fail}$ 树上所有 $b$ 的儿子的匹配总次数之和。

用这个结论可以解决 [LG P5357 【模板】AC自动机（二次加强版）](https://www.luogu.com.cn/problem/P5357)。

``` cpp
const int N = 1000010;
const int INF = 0x3fffffff;

struct Trie {
    int ch[30];
    int fail, tag, siz;
    inline Trie() {fail = tag = siz = 0;}
};

struct Edge {
    int u, v;
    int nxt;
};
Edge e[N];


int ecnt = 1, head[N], end[N];

struct AC_automaton {
    Trie t[N]; int cnt;

    inline AC_automaton() {cnt = 0;}

    inline void insert(char *s, int id) {
        int now = 0, len = strlen(s);
        for (int i = 0; i < len; ++ i) {
            int k = s[i] - 'a';
            if (!t[now].ch[k]) t[now].ch[k] = ++ cnt;
            now = t[now].ch[k];
        }
        ++ t[now].tag;
        end[id] = now;
    }

    inline void build() {
        queue <int> q;
        for (int i = 0; i < 26; ++ i)
          if (t[0].ch[i]) q.push(t[0].ch[i]);
        while (q.size()) {
            int now = q.front(); q.pop();
            for (int i = 0; i < 26; ++ i)
              if (t[now].ch[i]) {
                  t[t[now].ch[i]].fail = t[t[now].fail].ch[i];
                  q.push(t[now].ch[i]);
              } else t[now].ch[i] = t[t[now].fail].ch[i];
        }
    }

    inline void query(char *s) {
        int now = 0, len = strlen(s);
        for (int i = 0; i < len; ++ i) {
            now = t[now].ch[s[i] - 'a'];
            t[now].siz ++;
        }
    }
};
AC_automaton ac;

inline void add(const int &u, const int &v) {
    e[ecnt].u = u, e[ecnt].v = v;
    e[ecnt].nxt = head[u], head[u] = ecnt ++;
}

inline void dp(int x) {
    for (int i = head[x]; i; i = e[i].nxt) {
        dp(e[i].v);
        ac.t[x].siz += ac.t[e[i].v].siz;
    }
}

int main() {
    int n; scanf("%d", &n);
    char s[N], t[N];
    for (int i = 1; i <= n; ++ i)
      scanf("%s", s), ac.insert(s, i);
    scanf("%s", t); ac.build();
    ac.query(t);
    for (int i = 1; i <= ac.cnt; i ++)
      add(ac.t[i].fail, i);
    dp(0);
    for (int i = 1; i <= n; ++ i)
      printf("%d\n", ac.t[end[i]].siz);
    return 0;
}
```

# 参考资料

[1] [自动机入门——AC 自动机 - hyl天梦](https://www.cnblogs.com/TianMeng-hyl/p/14923851.html)

[2] [AC 自动机 - OI Wiki](https://oi-wiki.org/string/ac-automaton/)

[3] [强势图解AC自动机 - Sshwy](https://www.luogu.com.cn/blog/3383669u/qiang-shi-tu-xie-ac-zi-dong-ji)