#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 500010;
const int INF = 0x3fffffff;

template <typename T>
inline T Max(const T a, const T b) {return a > b ? a : b;}

struct OBJ {int a, b, c;} p[N];
int n, sum[N], f[N], ans, t[N], tc[N];

inline bool cmp(int x, int y) {
    return (p[x].b == p[y].b) ? (p[x].c > p[y].c) : (p[x].b < p[y].b);
}

inline void insert(int x, int c) {
    while (x <= n) sum[x] = Max(sum[x], c), x += x & (-x);
}

inline int query(int x) {
    int res = 0;
    while (x > 0) res = Max(res, sum[x]), x -= x & (-x);
    return res;
}

inline void del(int x) {while (x <= n) sum[x] = 0, x += x & (-x);}

void cdq(int l, int r) {
    if (l == r) {return;}
    int mid = l + r >> 1; cdq(l, mid);
    for (int i = l; i <= r; ++ i) t[i] = i;
    sort(t + l, t + r + 1, cmp);
    for (int i = l; i <= r; ++ i)
      if (t[i] <= mid) insert(p[t[i]].c, f[t[i]]);
      else f[t[i]] = Max(f[t[i]], query(p[t[i]].c - 1) + 1);
    for (int i = l; i <= mid; ++ i) del(p[i].c);
    cdq(mid + 1, r);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d%d", &p[i].b, &p[i].c);
        p[i].a = i; tc[i] = p[i].c, f[i] = 1;
    }
    sort(tc + 1, tc + n + 1);
    int cn = unique(tc + 1, tc + n + 1) - tc - 1;
    for (int i = 1; i <= n; ++ i)
      p[i].c = lower_bound(tc + 1, tc + cn + 1, p[i].c) - tc;
    cdq(1, n);
    for (int i = 1; i <= n; ++ i) ans = Max(ans, f[i]);
    printf("%d", ans);
    return 0;
}