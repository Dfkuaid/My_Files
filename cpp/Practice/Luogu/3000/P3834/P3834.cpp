#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 1000100;
const int INF = 0x3fffffff;

struct Node {
    int ls, rs;
    int sum;
};
Node p[N << 2];

struct Ques {
    int l, r, k, idx;
    bool operator < (const Ques &b) const {
        return r < b.r;
    }
};
Ques q[N];

int n, m, a[N], cnt, t[N], tot, rt[N], ans[N];

inline void pushup(int k) {
    p[k].sum = p[p[k].ls].sum + p[p[k].rs].sum;
}

void build(int &k, int l, int r) {
    if (!k) k = ++ cnt;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(p[k].ls, l, mid);
    build(p[k].rs, mid + 1, r);
}

void modify(int lt, int &k, int l, int r, int x) {
    if (!k) k = ++ cnt;
    p[k].sum = p[lt].sum + 1;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (x <= mid) {
        p[k].rs = p[lt].rs;
        modify(p[lt].ls, p[k].ls, l, mid, x);
    } else {
        p[k].ls = p[lt].ls;
        modify(p[lt].rs, p[k].rs, mid + 1, r, x);
    }
}

int query(int lt, int k, int l, int r, int x) {
    if (l == r) return l;
    int mid = (l + r) >> 1;
    int sum_l = p[p[k].ls].sum - p[p[lt].ls].sum;
    if (sum_l >= x) return query(p[lt].ls, p[k].ls, l, mid, x);
    else return query(p[lt].rs, p[k].rs, mid + 1, r, x - sum_l);
}

inline int mpg(int x) {
    return lower_bound(t + 1, t + tot + 1, x) - t;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++) {
        scanf("%d", &a[i]);
        t[i] = a[i];
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &q[i].l, &q[i].r, &q[i].k);
        q[i].idx = i;
    }
      
    sort(q + 1, q + m + 1);
    sort(t + 1, t + n + 1);
    tot = unique(t + 1, t + n + 1) - t - 1;
    build(rt[0], 1, tot);
    for (int i = 1, j = 1; i <= n; i ++) {
        modify(rt[i - 1], rt[i], 1, tot, mpg(a[i]));
        while (q[j].r == i)
          ans[q[j].idx] = query(rt[q[j].l - 1], rt[i], 1, tot, q[j].k), j ++;
    }
    for (int i = 1; i <= m; i ++)
      printf("%d\n", t[ans[i]]);
    return 0;
}
