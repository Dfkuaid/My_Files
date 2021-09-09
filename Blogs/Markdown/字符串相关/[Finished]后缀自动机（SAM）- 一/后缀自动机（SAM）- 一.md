> 我们约定，$S$ 为字符串，$|S|$ 为该字符串的长度，文中的所有字符串的下标从 $0$ 开始。

# #1.0 何为后缀自动机

## #1.1 简单介绍

**后缀自动机**（$\texttt{Suffix automaton, SAM}$），是一个能解决许多字符串相关问题的有力的数据结构。

举个例子，以下的字符串问题都可以在线性时间内通过 SAM 解决。

- 在另一个字符串中搜索一个字符串的所有出现位置。
- 计算给定的字符串中有多少个不同的子串。

直观上，字符串的 SAM 可以理解为给定字符串的 所有子串 的压缩形式。值得注意的事实是，SAM 将所有的这些信息以高度压缩的形式储存。对于一个长度为 $n$ 的字符串，它的空间复杂度仅为 $O(n)$。此外，构造 SAM 的时间复杂度仅为 $O(n)$。

## #1.2 后缀自动机的定义

字符串 $s$ 的 $\tt{SAM}$ 是一个接受 $s$ 的所有后缀的最小 $\tt{DFA}$<sup>[[1]](#refer-auth)</sup>（确定性有限自动机或确定性有限状态自动机<sup>[[2]](#refer-auth)</sup>）。

换句话说：

- $\tt{SAM}$ 是一张有向无环图。结点被称作 **状态**，边被称作状态间的 **转移**。
- 图存在一个源点 $t_0$，称作 **初始状态**，其它各结点均可从 $t_0$ 出发到达。
- 每个 **转移** 都标有一些字母。从一个结点出发的所有转移均 **不同**。
- 存在一个或多个 **终止状态**。如果我们从初始状态 $t_0$ 出发，最终转移到了一个终止状态，则路径上的所有转移连接起来一定是字符串 $s$ 的一个后缀。$s$ 的每个后缀均可用一条从 $t_0$ 到某个终止状态的路径构成。
- 在所有满足上述条件的自动机中，$\tt{SAM}$ 的结点数是最少的。

> 在后缀自动机中，每一个状态对应着一个字符串的 **等价类**，而这个 “等价类” 具体是什么，下面会介绍。

比如字符串 $“bccb”$ 的 $\tt SAM$ 如下：

![](https://pic.imgdb.cn/item/60e580f15132923bf8ffd1c6.png)

## #1.3 性质

$\tt{SAM}$ 包含关于字符串 $s$ 的所有子串的信息，任意从初始状态开始的路径，如果我们将转移路径上的标号写下来都会形成一个 $s$ 的子串；同样，每一个 $s$ 的子串对应从 $t_0$ 开始的某条路径。

为了简化表达，我们称子串对应一条路径，反过来，我们说任意一条路径对应它的标号构成的字符串。

到达某个状态的路径可能不止一条，因此我们说一个状态对应一些字符串的集合，这个集合的每一个元素对应这些路径。

# #2.0 SAM 的建立

在解释 $\tt{SAM}$ 的建立前，我们需要先定义几个概念。

<div id='endpos-def'></div>

## #2.1 endpos

定义字符串 $s$ 的任意一个非空子串 $t$ 的 $\texttt{endpos}(t)$ 为 $t$ 在 $s$ 中的所有结束位置组成的集合。

如，$s=“bccb”$，那么 $\texttt{endpos}(“c”)=1,2$。注意两个子串 $t_1,t_2$ 的 $\tt endpos$ 可能相等，比如 $\texttt{endpos}(“bcc”)=\texttt{endpos}(“cc”)=2$，我们将这样的 $\tt endpos$ 相等的子串划分为一个等价类。

注意，我们定义 $\tt SAM$ 的每一个状态对应着一个 **等价类**，那么 $\tt SAM$ 中的节点总数为所有等价类的数量加一（$t_0$ 节点）。

由 $\tt endpos$ 可以得到的一些重要结论：

1. 字符串 $s$ 的两个非空子串 $u,w$ ，（假设 $|u|<|w|$）的 $\tt endpos$ 相同，当且仅当字符串 $u$ 在 $s$ 中的每次出现，都是以 $w$ 的后缀形式存在的。
    
    正确性显然。

2. 考虑两个非空子串 $u$ 和 $w$（假设 $|u|<|w|$）。那么要么 $\texttt{endpos}(u)\cap\texttt{endpos}(w)=\varnothing$ ，要么 $\texttt{endpos}(w)\subseteq\texttt{endpos}(u)$，取决于 $u$ 是否为 $w$ 的一个后缀：

    $$
    \begin{cases}\texttt{endpos}(w)\subseteq\texttt{endpos}(u),&\text{if }u\text{ is s suffix of }w\\\texttt{endpos}(u)\cap\texttt{endpos}(w)=\varnothing,&\text{otherwise}\end{cases}
    $$

    **证明**：如果集合 $\texttt{endpos}(w)$ 与 $\texttt{endpos}(u)$ 有至少一个公共元素，那么由于字符串 $u$ 与 $w$ 在相同位置结束，故 $u$ 是 $w$ 的一个后缀。所以在每次 $w$ 出现的位置，子串 $u$ 也会出现。所以 $\texttt{endpos}(w)\subseteq\texttt{endpos}(u)$
3. 考虑一个 $\tt endpos$ 等价类，将类中的所有子串按长度非递增的顺序排序。每个子串都不会比它前一个子串长，与此同时每个子串也是它前一个子串的后缀。换句话说，设其中最长者长 $x$，最短者长 $y$，对于同一等价类的任一两子串，较短者为较长者的后缀，且该等价类中的子串长度恰好覆盖整个区间 $[x,y]$。

    **证明**：结合性质 $1.$ 考虑，记 $w$ 为等价类中最长的字符串、$u$ 为等价类中最短的字符串。字符串 $u$ 是字符串 $w$ 的真后缀。现在考虑长度在区间 $[|w|,|u|]$ 中的 $w$ 的任意后缀 $v$。容易看出，这个后缀也在同一等价类中，因为这个后缀只能在字符串 $s$ 中以 $w$ 的一个后缀的形式存在（也因为较短的后缀 $u$ 在 $s$ 中只以 $v$ 的后缀的形式存在）。因此结合性质 $2.$，有 $\texttt{endpos}(w)\subseteq\texttt{endpos}(v)\subseteq\texttt{endpos}(u)$，而 $\texttt{endpos}(w)=\texttt{endpos}(u)$，于是有 $\texttt{endpos}(w)=\texttt{endpos}(v)=\texttt{endpos}(u)$

## #2.2 后缀链接 link

考虑 $\tt SAM$ 中某一个不是 $t_0$ 的状态 $v$，我们已经知道，状态 $v$ 对应于具有相同 $\tt endpos$ 的等价类，设 $w$ 是最长的一个，那么所有等价类中的字符串都是 $w$ 的后缀。

我们还知道字符串 $w$ 的前几个后缀全部包含于这个等价类，且所有其它后缀都在其他的等价类中，我们记 $t$ 为最长的等价类不和 $w$ 的等价类相同的后缀。然后将 $v$ 的后缀链接连到 $t$ 的等价类上。

为了方便，我们规定：$\text{endpos}(t_0)=\{−1,0,...,|s|−1\}$。

将所有节点由后缀链接连接起来，会得到一棵树，这棵树的相关性质我们会在后面 [#3.0 后缀链接树](#suffix-link-tree) 一节进行讨论。

## #2.3 开胃小菜

> 在开始我们的大餐前，让我们先来点开胃小菜吧！在这里会总结一点上面的结论，同时定义一些符号。

- $s$ 的子串可以被划分成多个等价类。
- $\tt SAM$ 由若干状态构成，其中每一个状态对应一个等价类。对于每一个状态 $v$，一个或多个子串与之匹配，我们记 $\texttt{longest}(v)$ 为里面最长的一个，记 $\texttt{len}(v)$ 为它的长度，记 $\texttt{shortest}(v)$ 为最短的子串，它的长度为 $\texttt{minlen}(v)$ ，那么所有字符串的长度恰好覆盖 $[\texttt{minlen}(v),\texttt{len}(v)]$ 中的每一个整数。
- 后缀链接可以定义为连接到对应字符串 $\texttt{longest}(v)$ 的长度为 $\texttt{minlen}(v)−1$ 的后缀的一条边。从根节点 $t_0$ 出发的后缀链接可以形成一棵树。这棵树也表示 $\texttt{endpos}$ 集合间的包含关系。
- 对于任意非 $t_0$ 节点 $v$，有
    $$
    \texttt{minlen}(v)=\texttt{len}(\texttt{link}(v))+1
    $$
- 如果我们从任意节点 $v_0$ 开始一直走到 $t_0$ ，那么沿途所有字符串的长度形成了连续的区间 $[0,\texttt{len}(v_0)]$。

## #2.4 算法流程

> 在下面的过程中，有不少地方从 “后缀” 角度思考会比较简单，同样也必须谨记 “等价类” 这一概念。二者结合才能更好地理解算法。

这里采用的构造 $\tt SAM$ 的算法是 **在线** 算法。也就是说，我们在构建 $\tt SAM$ 时，是一个一个字符地插入，逐渐将整个 $\tt SAM$ 构建起来。

为了保证线性的空间复杂度，我们将只保存 $\tt len$ 和 $\tt link$ 的值和每个状态的转移列表，我们不会标记终止状态（但是我们稍后会展示在构造 $\tt SAM$ 后如何分配这些标记）。令 $\tt last$ 表示在添加当前字符之前，整个字符串对应的状态。

这里我会一步一步的讲述步骤，同时讲解正确性。假设现在我们要加入字符 $c.$

**步骤一**：新建 `cur` 节点，同时令 `len[cur] = len[last] + 1`。

这一步并不难理解，当前的 `cur` 节点对应的状态是 $c$ 加入后整个字符串对应的状态，显然 `len[cur]` 应当是此时字符串的长度，而 `len[last]` 是 $c$ 加入前整个字符串的长度。

**步骤二**：我们现在需要求出 `link[cur]`。我们从状态 `now = last` 开始，看当前的 `now` 状态是否有字符 $c$ 的转移，

- 如果有，那么进入下一步；
- 如果没有，那么就将 `now` 状态的 $c$ 字符转移指向 `cur`，然后向前跳 `now = link[now]`，直到找都一个有的，进入下一步；或 `now == -1`，此时令 `link[now] = 0`，进入步骤五；

这里我们分两种情况讨论正确性：

- 存在字符 $c$ 的转移；

...这种情况在这一步并没有太多涉及，留到下一步再说...

不过跳出循环的正确性是很显然的，因为每一个 `link` 必然对应着一个当前状态对应的等价类中最长的子串的一个 **真后缀**，所以向前跳 `link` 时的长度只会严格递减，再向前跳就满足不了 `link` 要求的长度最大了。

- 不存在 $c$ 的转移；

我们先来看第一个操作：将 `now` 状态的 $c$ 字符转移指向 `cur`，再向前跳 `link`；

我们知道，我们从 `last` 开始向前跳 `link`，得到的一定是与当前状态不在同一等价类、在加入 $c$ 字符前的字符串真后缀（在非结尾位置也有出现），这样的真后缀加上 $c$ 字符后形成的串必然未曾在之前出现过，那么这是这个串的第一次出现，在整个字符串的末尾，与 `cur` 属于同一等价类。

举个例子，假如当前字符串为 $“bcc”$，我们现在要插入 $“b”$，那么先跳到的状态对应的最长的字串为 $“c”$，$“c”$ 是 $“bcc”$ 的一个真后缀，但不止在末尾处出现，显然他是应当可以从 $“c”$ 转移到 $“cb”$ 的，这个结论并不失一般性。

然后第二个操作是：当 `now == -1` 时，令 `link[cur] = 0`。这一步正确性显然。

**步骤三**：检查当前 `p = now` 状态通过 $c$ 字符转移得到的状态 `q`，如果满足 `len[q] == len[p] + 1`，那么直接令 `link[cur] = q`，进入步骤五；否则进入下一步。

> 步骤三和步骤四是笔者理解时的难点，过了这个坎就一路平坦了！

首先我们先要理解这样一个问题：**为什么要要求 $\texttt{len}(q)=\texttt{len}(p)+1$?**

$\texttt{len}(q)=\texttt{len}(p)+1$ 意味着 $q$ 所代表的状态中，最长的那个是从 $p$ 转移过来的，而 $p$ 是什么？是有 $c$ 字符转移的、与在 $c$ 插入前整个字符串不在同一等价类的、最长的、$c$ 插入前整个字符串的真后缀，于是不难推出，$q$ 是**与在 $c$ 插入后整个字符串不在同一等价类的、最长的、$c$ 插入后整个字符串的真后缀**，这与 $\texttt{link}(cur)$ 的定义相吻合，于是应当有 `link[cur]=q`；

那么除了 $\texttt{len}(q)=\texttt{len}(p)+1$，还会有什么情况呢？根据 $\tt len$ 的定义，剩下的只有一种可能了：$\texttt{len}(q)>\texttt{len}(p)+1$，而这种情况正是我们下一步要讨论的情况。

**步骤四**：将 `q` 节点分裂，具体步骤如下：

- 创建 `q` 的副本 `clone`，除 $\tt len$ 以外的所有信息（后缀链接 `link`，转移 `ch`）全部复制过来；
- 令 `len[clone] = len[p] + 1`，
- 令 `link[cur] = clone, link[q] = clone`；
- 顺着 `now` 及 `link` 向前跳，不断将字符 $c$ 的转移目标为 `q` 的状态的转移目标设置为 `clone`；

这里的所有步骤整体分为两个主题：**拆分 $q$ 状态** 和 **修改转移**。

来看看我们为什么要拆分 $q$ 状态：因为 $\texttt{len}(q)>\texttt{len}(p)+1$，所以意味着当前 $q$ 中最长的串转移来源 $v\ne p$，于是有 $\texttt{len}(v)>\texttt{len}(p)$，显然 $v$ 所代表的状态中的最长串不可能是在加入 $c$ 字符前的整个字符串的的真后缀（如果是，一定会比 $p$ 先被跳到，否则意味着这个串与整个字符串属于同一个等价类，完全不可能），那么同样可以得到状态 $q$ 中长度大于 $\texttt{len}(p)+1$ 的一定不会在插入字符 $c$ 后的字符串末尾出现，而长度小于等于 $\texttt{len}(p)+1$ 的却可以，所以说 $q$ 中的串实际已经不属于同一个等价类了，我们需要将他们分开~~防止搓起来~~，显然原本的转移并没有受到影响，可以复制过来，而原本 $q$ 的 $\tt link$ 现在应当变成 $clone$ 的，仔细看一看刚才分裂的过程和原因不难发现， $clone$ 成了 $q$ 的 $\tt link$ 指向的节点。

再来看修改转移的部分：

我们这里是把所有 $p$ 的真后缀的字符 $c$ 指向 $q$ 的转移指向 $clone$，这里结合上面分裂的步骤思考，不难发现所有修改的过程都是正确的，那么我们来看为什么遇到第一个转移目标不是 $q$ 的就可以停止。

按照我们上面的过程构建自动机，不难发现从 `last` 开始，沿着 $\tt link$ 向前跳的过程中，$c$ 字符转移的赋值是不可能跳开一段再赋值为同一个值的，所以当一个位置出现目标不为 $q$ 的转移，再向前的也就没必要再看了。

不从 $\tt SAM$ 的构造过程上来看，直接按照其性质也可以证明：我们知道 `v = link[now]` 所指向的状态中的串必然都是 `p = now` 的状态中的最长串的真后缀，且不属于同一等价类，所以应当有 $\texttt{endpos}(p)\subsetneqq\texttt{endpos}(v)$，同时因为 `u = link[v]` 所指向的状态中的串必然都是 `v` 的状态中的最长串的真后缀，且不属于同一等价类，所以也应当有 $\texttt{endpos}(v)\subsetneqq\texttt{endpos}(u)$，所以如果此时 $v$ 的字符 $c$ 的转移目标与 $q$ 不是同一个等价类，之前的也一定不会是。这一部分如果考虑字符串上的 $\tt endpos$ 的意义会更好理解。

**步骤五**：令 `last = cur`，算法结束。不解释。

## #2.5 代码实现

``` cpp
inline void insert(int c) {
    int cur = ++ tot;
    p[cur].len = p[last].len + 1;
    int now = last;
    while ((~now) && !p[now].ch[c])
      p[now].ch[c] = cur, now = p[now].link;
    if (!(~now)) p[cur].link = 0;
    else {
        int q = p[now].ch[c];
        if (p[q].len == p[now].len + 1)
          p[cur].link = q;
        else {
            int clone = ++ tot; p[clone] = p[q];
            p[clone].len = p[now].len + 1;
            p[cur].link = p[q].link = clone;
            while ((~now) && p[now].ch[c] == q)
              p[now].ch[c] = clone, now = p[now].link;
        }
    }
    last = cur;
}
```

<div id='suffix-link-tree'></div>

# #3.0 后缀链接树

> 这个名字只是笔者瞎起的，因为实在没有在网上找到较为规范的叫法。

## #3.1 一些约定


- $\texttt{SLT(Suffix link tree)}$ 指的是后缀链接树；
- $(u,v)$ 表示树上一条从父亲 $u$ 指向儿子 $v$ 的边，$E$ 为树上的边集，$V$ 为点集；
- 若 $x$ 为 $\tt SLT$ 上的节点，那么 $\texttt{endpos}(x)$ 表示的是节点 $x$ 所对应的等价类（相应的 $\tt endpos$）。

## #3.1 一些性质

将所有节点由后缀链接连接起来，会得到一棵树，这棵树上的叶节点所代表的状态（等价类）中**最长的**串一定是原本字符串的一个只出现一次的前缀。比如 $S=“bccb”$ 的后缀链接树便如下图：

![](https://pic.imgdb.cn/item/60e5a6c05132923bf89f6349.png)

（节点上的字符串为对应等价类中最长的串）

这一点经过简单思考也是不难发现的，因为一个状态如果不是任何一个状态的后缀链接所指向的状态，那么意味着这个状态中的**最长串**必然不是其他任何一个原字符串子串的后缀，这样的串必然是原串的一个前缀，且这个前缀必然只在原串中出现一次，否则便可以作为其他子串的真后缀出现。

还有几个很显然的性质：

- 原字符串的一个前缀在处于前缀位置时不会作为其他任意一个子串的真后缀。
- 在如果一个状态包含整个字符串的一个前缀，那么这个前缀必然是这个状态中最长的串。
- 一个状态中的所有串在原字符串中的出现次数相等。

因此我们也可以得到一个性质：

在 $\tt SLT$ 上，如果一个节点所对应的等价类不包括原串的一个前缀，那么应当有

$$
\begin{cases}
|\texttt{endpos}(u)|=\sum\limits_{(u,v)\in E}|\texttt{endpos}(v)|,\\
\texttt{endpos}(u)=\bigcup\limits_{(u,v)\in E}\texttt{endpos}(v).
\end{cases}\tag1
$$

如果包含前缀的话，则有

$$
\begin{cases}
|\texttt{endpos}(u)|=\sum\limits_{(u,v)\in E}|\texttt{endpos}(v)|+1,\\
\texttt{endpos}(u)=\left(\bigcup\limits_{(u,v)\in E}\texttt{endpos}(v)\right)\cup\{\texttt{len}(u)-1\}.
\end{cases}\tag2
$$

要说明 $(1)(2)$ 式正确有一点需要证明：

$$
\bigcup\limits_{(u,v_1),(u,v_2)\in E}\left(\texttt{endpos}(v_1)\cap\texttt{endpos}(v_2)\right)=\varnothing.
$$

**证明**：

不失一般性，设 $v_1,v_2$ 分别为 $u$ 的两个儿子，不妨设 $|\texttt{endpos}(v_1)|<|\texttt{endpos}(v_2)|$，如果有

$$
\texttt{endpos}(v_1)\cap\texttt{endpos}(v_2)\ne\varnothing,
$$

由上面 [#2.1 endpos](#endpos-def) 的性质 2. 可以知道，应当有

$$
\texttt{endpos}(v_1)\subseteq\texttt{endpos}(v_2),
$$

也就是 $v_2$ 中的串应当都是 $v_1$ 中串的真后缀，所以有 $\texttt{len}(v_2)<\texttt{len}(v_1)$。

那么让我们重新回到后缀链接的定义，简单考虑一下，作为父节点的 $u$ 所包含的每一个字符串都应当是其子节点包含字符串的真后缀，所以 $\texttt{len}(u)<\texttt{len}(v_2)$，又因为 $v_1\ne v_2$，根据后缀链接的定义，$v_2$ 应当是 $v_1$ 的后缀链接指向的节点，这与假设相悖，故不成立。

于是应当对 $u$ 的任意两个儿子 $v_1,v_2$，有

$$
\texttt{endpos}(v_1)\cap\texttt{endpos}(v_2)=\varnothing,
$$

也就有

$$
\bigcup\limits_{(u,v_1),(u,v_2)\in E}\left(\texttt{endpos}(v_1)\cap\texttt{endpos}(v_2)\right)=\varnothing.
$$

<div align=right>证毕.</div>

<br>

对于 $(2)$ 式我们需要特殊讨论，多出来的 “$+1$” 和 “$\cup\{\texttt{len}(u)-1\}$” 并不难理解：$S$ 的一个前缀为 $T$，不会存在一个将在 **处于前缀位置** 的 $T$ 作为真后缀的字符串，但 $T$ 在其他位置的出现却可以被作为真后缀。而我们知道，如果一个状态包含整个字符串的一个前缀，那么这个前缀必然是这个状态中最长的串，而我们在文章开始便说明了所有的字符串下标都从 $0$ 开始，所以相应的 $\tt endpos$ 应当为 $\texttt{len}(u)-1.$

## #3.2 运用

来看一道[例题](https://www.luogu.com.cn/problem/P3804)吧。

给定一个只包含小写字母的字符串 $S$，请你求出 $S$ 的所有出现次数不为 $1$ 的子串的出现次数乘上该子串长度的最大值。

考虑运用上面的性质，

- 一个状态中的所有串在原字符串中的出现次数相等；
- 在一个串出现的位置上他的子串一定也在同样位置出现。

我们只需要对于任意一个前缀的对应状态出现次数设为 $1$，建出 $\tt SLT$，在上面做树形 $\tt DP$ 即可。

``` cpp
const int N = 2000010;
const int INF = 0x3fffffff;

template <typename T>
inline T Max(const T a, const T b) {
    return a > b ? a : b;
}

struct Node {
    int link, len;
    int ch[30];
};

struct Edge {
    int u, v;
    int nxt;
};
Edge e[N];

int head[N], cnt = 1, f[N];

struct SAM {
    Node p[N]; int tot, last;

    inline SAM() {
        p[0].len = 0, p[0].link = -1;
        tot = 0, last = 0;
    }

    inline void insert(int c) {
        int cur = ++ tot; ++ f[cur]; //注意这里 f[cur] ++
        p[cur].len = p[last].len + 1;
        int now = last;
        while ((~now) && !p[now].ch[c])
          p[now].ch[c] = cur, now = p[now].link;
        if (!(~now)) p[cur].link = 0;
        else {
            int q = p[now].ch[c];
            if (p[q].len == p[now].len + 1)
              p[cur].link = q;
            else {
                int clone = ++ tot; p[clone] = p[q];
                p[clone].len = p[now].len + 1;
                p[cur].link = p[q].link = clone;
                while ((~now) && p[now].ch[c] == q)
                  p[now].ch[c] = clone, now = p[now].link;
            }
        }
        last = cur;
    }
};
SAM sam;

char s[N];
int n, ans;

inline void add(const int u, const int v) {
    e[cnt].u = u, e[cnt].v = v;
    e[cnt].nxt = head[u], head[u] = cnt ++;
}

void dp(int x) {
    for (int i = head[x]; i; i = e[i].nxt) {
        dp(e[i].v); f[x] += f[e[i].v];
    }
    if (f[x] > 1) ans = Max(f[x] * sam.p[x].len, ans);
}

int main() {
    scanf("%s", s); n = strlen(s);
    for (int i = 0; i < n; ++ i)
      sam.insert(s[i] - 'a');
    for (int i = 1; i <= sam.tot; ++ i)
      add(sam.p[i].link, i);
    dp(0);
    printf("%d", ans);
    return 0;
}
```

<div id='refer-auth'></div>

# 参考资料

[1] [后缀自动机 (SAM) - OI Wiki](https://oi-wiki.org/string/sam/)

[2] [自动机 - OI Wiki](https://oi-wiki.org/string/automaton/)

[3] [自动机入门——后缀自动机 - hyl天梦](https://www.cnblogs.com/TianMeng-hyl/p/14927170.html)