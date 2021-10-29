#define LOCAL
#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 2000010;
const int LIMIT = 1e9;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

struct BIT {
    int val[N], len;
    
    inline BIT() {len = 0;};
    inline void init(int x) {len = x;}
    inline void reset() {while (len) val[len --] = 0;}
    inline void add(int x, int c) {while (x <= len) val[x] += c, x += (x & -x);}
    inline ll query(int x) {
        ll res = 0; while (x) res += val[x], x -= (x & -x); return res;
    }
} bit;

#define lb(l, len, x) lower_bound(l + 1, l + len + 1, x)
#define ub(l, len, x) upper_bound(l + 1, l + len + 1, x)

int t, n, m, a[N], b[N], c[N], p[N], upper[N], lower[N], dct[N]; ll ans;

inline void reset() {bit.reset(); ans = 0;}

inline void discretize() {
    for (int i = 1; i <= n; ++ i) dct[i] = a[i];
    for (int i = 1; i <= m; ++ i) dct[n + i] = b[i];
    sort(dct + 1, dct + n + m + 1);
    int len = unique(dct + 1, dct + n + m + 1) - dct - 1;
    for (int i = 1; i <= n; ++ i) a[i] = lb(dct, len, a[i]) - dct;
    for (int i = 1; i <= m; ++ i) b[i] = lb(dct, len, b[i]) - dct;
}

void solve(int l, int r, int pl, int pr) {
    if (l > r) return; int mid = l + r >> 1, res = INF;
    upper[pl - 1] = 0, upper[pl] = (a[pl] > b[mid]);
    lower[pr + 1] = 0, lower[pr] = (a[pr] < b[mid]);
    for (int i = pl; i < pr; ++ i) upper[i + 1] = upper[i] + (a[i + 1] > b[mid]);
    for (int i = pr; i > pl; -- i) lower[i - 1] = lower[i] + (a[i - 1] < b[mid]);
    for (int i = pl; i <= pr; ++ i) if (upper[i - 1] + lower[i] < res)
      res = upper[i - 1] + lower[i], p[mid] = i;
    if (pl == pr) p[mid] = pl;
    solve(l, mid - 1, pl, p[mid]); solve(mid + 1, r, p[mid], pr);
}

inline void get_list() {
    int ap = 1, lp = 1;
    for (int i = 1; i <= m; ++ i) {
        while (ap <= n && ap < p[i]) c[lp ++] = a[ap], ++ ap;
        c[lp ++] = b[i];
    }
    while (ap <= n) c[lp ++] = a[ap], ++ ap;
}

inline void calculate() {
    for (int i = n + m; i >= 1; -- i) {
        ans += bit.query(c[i] - 1);
        bit.add(c[i], 1);
    }
}

void MAIN() {
    read(n), read(m); reset(); bit.init(n + m + 1);
    for (int i = 1; i <= n; ++ i) read(a[i]);
    for (int i = 1; i <= m; ++ i) read(b[i]);
    discretize(); sort(b + 1, b + m + 1); a[n + 1] = INF;
    solve(1, m, 1, n + 1); get_list();
    calculate(); printf("%lld\n", ans);
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(t); while (t --) MAIN(); return 0;
}
