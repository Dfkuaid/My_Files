# #0.0 问题简述

给定一个字符串，求出其最长回文子串。例如：

- $s=“abcd”$，最长回文长度为 $1$；
- $s=“ababa”$，最长回文长度为 $5$；
- $s=“abccb”$，最长回文长度为 $4$，即 $bccb$。

# #1.0 朴素算法

首先注意到回文串可能有奇、偶两种不同的情况，讨论起来比较复杂，这里先只看奇回文的情况。

思路很简单：枚举每个字符作为回文串的中点，不断向左右两端扩展，直到到达边界或两边字符不同。

伪代码：

$$
\begin{aligned}
&\text{Function }is\_ok(a,b,s)\\
&1.\ \quad\text{If } a\geqslant0\text{ && }b<length(s)\\
&2.\ \quad\qquad\text{then return }true\\
&3.\ \quad\qquad\text{else return }false\\
&\\
&\text{Procedure}\ Brute\_Force(s:string)\\
&1.\ \quad ans\gets 0\\
&2.\ \quad\text{For }i\gets0\text{ to }length(s)-1\\
&3.\ \quad\qquad\text{do }j\gets0\\
&4.\ \quad\qquad\text{While }is\_ok(i-j,i+j,s)\text{ && }s[i-j]=s[i+j]\\
&5.\ \quad\qquad\qquad\text{do }ans\gets\max\{ans,2\times j+1\}\\
&6.\ \quad\qquad\text{End While}\\
&7.\ \quad\text{End For}\\
\end{aligned}
$$

不难看出，这样的过程的时间复杂度是 $O(n^2)$ 的。

# #2.0 Manacher 算法

> 个人觉得，$\texttt{Manacher}$ 算法比较适合直接看算法流程来进行学习、理解，所以直接来看算法怎么实现吧！

## #2.1 初步处理

第一步，将上文提到的奇偶回文串的问题解决掉，具体方案是：

1. 在字符串首尾及每个字符间都插入一个 "#"，这样可以使得原先的奇偶回文都变为奇回文；
2. 在首尾两端各插入 "$" 和 "^"，这样中心扩展回文的时候会自动退出循环，不需每次判断是否越界。

注意：上述新插入的三个字符，即 "#"、 "$" 和 "^"，必须各异，且不可以与原字符串中的字符相同。

定义 `p[i]` 为以 `i` 为中心的最长回文半径长度。

让我们来看一个例子：$abcbaba$，处理后如下表：

|  i   | 0    | 1    | 2    | 3    | 4    | 5    | 6    | 7    | 8    | 9    | 10   | 11   | 12   | 13   | 14   | 15   | 16   |
| :--: | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| S[i] | $    | #    | a    | #    | b    | #    | c    | #    | b    | #    | a    | #    | b    | #    | a    | #    | ^    |
| p[i] | 1    | 1    | 2    | 1    | 2    | 1    | 6    | 1    | 2    | 1    | 4    | 1    | 2    | 1    | 2    | 1    | 1    |

不难发现 `p[i]-1` 便是原字符串中以 `S[i]` 为中心的最长回文串的长度。

## #2.2 求解 p 数组

接下来我们的重点就是如何求出 `p[]`。这里定义几个变量：

- `id` 表示当前位置加上该位置最长回文半径可覆盖的范围最远的位置；
- `mx` 表示 `id + p[id]`，即 `id` 加上 `id` 的最长回文半径可覆盖的最远范围的右边界；

那么我们应该如何运用 `id` 和 `mx` 来帮助求解 `p[]` 呢？来看下面的讨论。

![](https://pic.imgdb.cn/item/60e002375132923bf8433e3c.png)

如上图，假设当前枚举的 $i < mx$ ，那么以 $i$ 为中心的回文串就只有以下几种状态：

1. 完全被 $mx$ 的对称点 和 $mx$ 包含；
2. 超出 $mx$ 的范围；

我们发现，位置 $i$  关于 $id$ 的对称点 $i'$ 的最长回文半径已经求出，而我们知道，$mx$ 是以 $id$ 为中心的最长回文半径可以覆盖到的最远距离的有边界，也就意味着 $[mx'+1,mx-1]$ 这个串必然是回文串，所以 $[mx'+1,id]$ 应当是和 $[id,mx-1]$ 这个串关于 $id$ 对称。

![](https://pic.imgdb.cn/item/60e008c85132923bf87e2813.png)

所以，如上图，如果以 $i'$ 为中心的最长回文串无法超出 $mx'$，那么 $i$ 的最长回文串一定也不会覆盖 $mx$；

![](https://pic.imgdb.cn/item/60e009d25132923bf8878b77.png)

但如果以 $i'$ 为中心的最长回文串的范围超出了 $mx'$，即超出了以 $id$ 为中心的回文串的范围，那么以 $i$ 为中心的回文串一定不会超出 $mx$，也就是一定不会超出以 $id$ 为中心的回文串的范围。如上图，两端紫红色的文本串必然不是相同的，否则这与 $mx$ 的定义相悖，于是以 $i$ 为中心的回文串必然不会超过 $mx.$

![](https://pic.imgdb.cn/item/60e00b7e5132923bf896b2a7.png)

但是，假如如上图，以 $i'$ 为中心的回文串恰好与以 $id$ 为中心的回文串左端对齐，那么以 $i$ 为中心的回文串却是有可能向左右两端继续扩展的。

综合上面所说的几点，我们可以得到以下代码：

``` cpp
if (i < mx) p[i] = min(p[2 * id - i], mx - i);
else p[i] = 1;
while (s[i - p[i]] == s[i + p[i]]) p[i] ++;
```

没错，上面这 $3$ 行代码就已经是 $\texttt{Manacher}$ 算法的核心了，下附完整代码。

## #2.3 代码实现

``` cpp
const int N = 23000010;
const int INF = 0x3fffffff;

int len, ans= -1, p[N];
char s[N];

template <typename T>
inline T Min(const T a, const T b) {
    return a < b ? a : b;
}

template <typename T>
inline T Max(const T a, const T b) {
    return a > b ? a : b;
}

inline void input() {
    s[len ++] = '$', s[len ++] = '#';
    while (cin >> s[len]) s[++ len] = '#', ++ len;
    s[len ++] = '^', s[len] = '\0';
}

inline void Manacher() {
    int id = 0, mx = 0;
    for (int i = 0; i < len; i ++) {
        if (i < mx) p[i] = Min(p[2 * id - i], mx - i);
        else p[i] = 1;
        while (s[i - p[i]] == s[i + p[i]]) p[i] ++;
        if (mx < i + p[i]) id = i, mx = i + p[i];
        ans = Max(ans, p[i] - 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); input();
    Manacher(); cout << ans;
    return 0;
}
```

$\texttt{Manacher}$ 算法的时间复杂度仅为 $O(n)$，是极为优秀的回文串算法。

说实话，笔者觉得 $\texttt{Manacher}$ 要比 $\texttt{KMP}$ 好写、好理解的多。



# 参考资料

[1] [Manacher 算法 - 刘毅](https://ethsonliu.com/2018/04/manacher.html)

