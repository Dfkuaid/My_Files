#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 2000010;
const int INF = 0x3fffffff;

int n, m, len, cnt[N], sum, ans[N], a[N];

struct Query {
    int l, r, id;

    inline bool operator < (const Query &b) const {
        if (l / len != b.l / len) return l < b.l;
        if ((l / len) & 1) return r < b.r;
        return r > b.r;
    }
};
Query q[N];

inline void add(int i) {
    if (!cnt[i]) sum ++;
    cnt[i] ++;
}

inline void del(int i) {
    if (-- cnt[i] == 0) sum --;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++)
      scanf("%d", &a[i]);
    scanf("%d", &m);
    for (int i = 1; i <= m; i ++) {
        scanf("%d%d", &q[i].l, &q[i].r);
        q[i].id = i;
    }
    len = n / sqrt(m);
    sort(q + 1, q + m + 1);
    for (int i = 1, l = 1, r = 0; i <= m; ++ i) {
        while (l > q[i].l) add(a[-- l]);
        while (r < q[i].r) add(a[++ r]);
        while (l < q[i].l) del(a[l ++]);
        while (r > q[i].r) del(a[r --]);
        ans[q[i].id] = sum;
    }
    for (int i = 1; i <= m; i ++)
      printf("%d\n", ans[i]);
    return 0;
}