> [题目链接](http://poj.org/problem?id=3419)

## #1.0 题意简述

给定一个长度为 $n$ 的序列，$q$ 个询问，每次询问区间 $[L,R]$ 中最长的可行连续子序列的长度。定义一个序列为可行序列，当且仅当该序列中所有数字出现次数 $\le1$。

## #2.0 大体思路

不难发现答案具有二分性，于是可以采用二分答案，来考虑如何判断是否可行。

首先不难想到可以尝试对于每个 $l$ 找到满足 $[l,r]$ 是可行序列的最大的 $r$，记录其最大长度，长度数组记为 $a_i$，这一步通过**双指针**可以 $O(n)$ 解决。之后我们的判定就变成了对于 $x$，判断在 $[L,R-x+1]$ 中是否存在一个位置 $i$ 满足 $a_i\ge x$，也就可以转化为判断
$$
\max_{L\le i\le R-x+1}\{a_i\}\ge x
$$
是否为真，前面的部分是经典的 RMQ 问题，可以用 st 表解决，总体时间复杂度为 $O(n\log n+q\log n)$.

## #3.0 Code

``` cpp
const int N = 4000100;
const int INF = 0x3fffffff;

int n, m, a[N], len[N];
int vis[N], st[N][30], lg2[N];

template <typename T>
inline T Max(const T a, const T b) {
    return a > b ? a : b;
}

inline void get_len() {
    for (int l = 1, r = 0; l <= n; ++ l) {
        while (r < n && !vis[a[r + 1]])
          ++ r, vis[a[r]] = 1;
        len[l] = r - l + 1, vis[a[l]] = 0;
    }
}

inline void prework() {
    lg2[1] = 0;
    for (int i = 2; i <= n; ++ i)
      lg2[i] = lg2[i >> 1] + 1;
    for (int i = 1; i <= n; i ++)
      st[i][0] = len[i];
    for (int j = 1; j <= 22; ++ j)
      for (int i = 1; i <= n; ++ i)
        if (i + (1 << (j - 1)) <= n)
          st[i][j] = Max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        else st[i][j] = st[i][j - 1];
}

inline bool check(int l, int r, int x) {
    int L = lg2[r - l - x + 2];
    int res = Max(st[l][L], st[r - x - (1 << L) + 2][L]);
    if (res >= x) return true;
    else return false;
}

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", &a[i]);
        a[i] += 1e6;
    }
    get_len(); prework();
    while (m --) {
        int x, y; scanf("%d%d", &x, &y); x ++, y ++;
        int l = 0, r = y - x + 1, ans = 0;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(x, y, mid))
              ans = mid, l = mid + 1;
            else r = mid - 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}
```

