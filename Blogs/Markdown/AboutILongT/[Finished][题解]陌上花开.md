> [题目链接](https://www.luogu.com.cn/problem/P3810)

## #Part. 1 题目描述

有 $n$ 个元素，第 $i$ 个元素有 $a_i,b_i,c_i$ 三个属性，设 $f(i)$ 表示满足 $a_j \leq a_i$ 且 $b_j \leq b_i$ 且 $c_j \leq c_i$ 且 $j \ne i$ 的 $j$ 的数量。对于 $d \in [0, n)$，求 $f(i) = d$ 的数量。

## #Part. 2 思路

> 谁能想到，笔者做这道题的瓶颈是**树状数组**呢...QwQ

本题是三维偏序的板子题。我们在这里采用 **CDQ 分治**解决这道题。

$\tt CDQ$ 分治处理序列点对问题的经典三步骤：

- 找到中点 $mid$；
- 递归处理在左区间 $[l,mid]$ 和右区间 $[mid+1,r]$ 中的答案；
- 统计跨过中点 $mid$ 的点对；

首先对于这样的问题，我们首先考虑减少干扰我们的条件，所以将所有元素进行排序，令 $a$ 为第一关键字，$b$ 为第二关键字，$c$ 为第三关键字，这样一来在所有的区间内，右边的 $a$ 一定比左边的 $a$ 要大。同时注意到可能会有相同的元素，这里需要去重。

``` cpp
struct flo {
    int a, b, c, id, tot;
    
    inline bool operator < (const flo &t) const {
        if (a == t.a) {
            if (b == t.b) return c < t.c;
            else return b < t.b;
        } else return a < t.a;
    }

    inline bool operator != (const flo &t) const {
        return (a != t.a || b != t.b || c != t.c) ? true : false;
    }
};
flo p[N], v[N], q[N];

/*在 main() 中*/
sort(p + 1, p + n + 1); //排序
v[++ cnt] = p[1]; v[cnt].id = v[cnt].tot = 1;
for (int i = 2; i <= n; ++ i)
  /*去重，因为已经排好了序，所以相同的元素
  必定相邻，只需判断当前元素与上一个记录的
  元素是否相同，如果是，那么增加个数即可，
  否则记录当前元素*/
  if (p[i] != v[cnt]) { 
      v[++ cnt] = p[i];
      v[cnt].id = cnt;
      v[cnt].tot ++;
  } else v[cnt].tot ++;
```



下面的重点便是 $\tt CDQ$ 的过程了，因为递归的过程是完全相同的子问题，那么假设对于区间 $[l,r]$ 我们现在已经处理完 $[l,mid]$ 和 $[mid+1,r]$，现在来看如何统计跨过中点的点对信息。

这种 “处理左边...处理右边...合并两边” 的方式是否觉得有些眼熟？好像**归并排序**便是这样的过程，那么如果我们在处理完一个区间的同时，可以将这个区间**按照 $b$ 从大到小排序**，我们发现，如果这样做，那么在处理整个区间 $[l,r]$ 时，$[l,mid]$ 中的 $a$ 一定比 $[mid+1,r]$ 中的 $a$ 小，而在两个小区间中，是按照 $b$ 升序，那么对于一个右区间中的元素 $t$，可能对它的答案造成贡献的只有在左区间中 $b$ 小于等于 $t.b$ 的元素，我们设左区间中第一个 $b$ 值大于 $t$ 的 $b$ 值的元素为 $t$ 的**决策点**。很显然，这样的决策点是具有单调性的，即如果对于一个在右区间中的位置比 $t_1$ 靠右的元素 $t_2$，如果 $t_1$ 的决策点是 $s_1$，那么 $t_2$ 的决策点一定不会比 $s_2$ 靠左，所以我们可以直接维护一左一右两个指针。

那么，对于一个右区间中的元素 $t$，左区间中对他的答案的贡献一定是在他的决策点左边的元素中，$c$ 值比 $t$ 的 $c$ 小的元素个数，那么这个数量怎么维护？很简单，我们可以维护一个**权值树状数组**（权值线段树），每向右扩展一个左区间的元素，就将这个元素的包含的个数加入到树状数组中对应 $c$ 的位置，每当找到一个右区间元素的决策点，那么就查询当前的树状数组中有多少个元素小于等于 $c$。

## #Part. 3 代码实现

``` cpp
const int N = 1000010;
const int INF = 0x3fffffff;

struct flo {
    int a, b, c, id, tot;
    
    inline bool operator < (const flo &t) const {
        if (a == t.a) {
            if (b == t.b) return c < t.c;
            else return b < t.b;
        } else return a < t.a;
    }

    inline bool operator != (const flo &t) const {
        return (a != t.a || b != t.b || c != t.c) ? true : false;
    }
};
flo p[N], v[N], q[N];

int n, k, cnt, ftot[N], ans[N], c[N << 8], res[N];

/*树状数组部分*/

inline int lowbit(int x) {return (x & (-x));}

void insert(int i, int x) {
    while (i <= N){
        c[i] += x;
        i += lowbit(i);
    }
}

int query(int x) {
    int res = 0;
    while (x > 0) {
        res += c[x];
        x -= lowbit(x);
    }
    return res;
}

void cdq(flo *arr, int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    cdq(arr, l, mid); cdq(arr, mid + 1, r);
    for (int i = l; i <= r; i ++) q[i] = arr[i];
    int L = l, R = mid + 1, pos = l;
    while (R <= r && L <= mid) { //归并排序同时维护信息
        if (q[L].b <= q[R].b) {
            insert(q[L].c, q[L].tot);
            arr[pos ++] = q[L ++];
        } else {
            ans[q[R].id] += query(q[R].c);
            arr[pos ++] = q[R ++];
        }
    }
    while (R <= r) ans[q[R].id] += query(q[R].c), ++ R;
    while (L <= mid) {insert(q[L].c, q[L].tot);arr[pos ++] = q[L ++]; }
    //可能存在未处理完的数据
    for (int i = l; i <= mid; i ++) insert(q[i].c, -q[i].tot);
    //清空树状数组
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++ i)
      scanf("%d%d%d", &p[i].a, &p[i].b, &p[i].c);
    sort(p + 1, p + n + 1);
    v[++ cnt] = p[1]; v[cnt].id = v[cnt].tot = 1;
    for (int i = 2; i <= n; ++ i)
      if (p[i] != v[cnt]) {
          v[++ cnt] = p[i];
          v[cnt].id = cnt;
          v[cnt].tot ++;
      } else v[cnt].tot ++;
    cdq(v, 1, cnt);
    for (int i = 1; i <= cnt; ++ i)
      res[ans[v[i].id] + v[i].tot - 1] += v[i].tot;
    for (int i = 0; i < n; ++ i)
      printf("%d\n", res[i]);
    return 0;
}
```

> 想做法非常快...但是树状数组因为没怎么用过不大会写，卡了我好久...

$$
\Large\color{pink}{\textbf{❀陌上花开，可缓缓归矣~}}
$$

