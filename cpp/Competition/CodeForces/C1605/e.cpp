#define LOCAL
#include <bits/stdc++.h>
#define ll long long
#define lb(l, len, x) lower_bound(l + 1, l + len + 1, x)
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T Abs(T x) {return x < 0 ? -x : x;}

int n, q; ll a[N], b[N], c[N], d[N], A[N], B[N], p[N], pos[N], t[N];

inline bool cmp(int x, int y) {return p[x] < p[y];}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n);
    for (int i = 1; i <= n; ++ i) read(a[i]);
    for (int i = 1; i <= n; ++ i) read(b[i]);
    for (int i = 2; i <= n; ++ i) B[i] = b[i] - a[i];
    for (int i = 1; i <= n; ++ i) {
        if (i == 1) d[i] = 0, c[i] = 1;
        else  d[i] = B[i] - d[i], c[i] = -c[i];
        for (int j = 2; j * i <= n; ++ j)
          d[i * j] += d[i], c[i * j] += c[i];
    }
    for (int i = 1; i <= n; ++ i) if (c[i]) p[i] = -d[i] / c[i];
    for (int i = 1; i <= n; ++ i) t[i] = i;
    sort(t + 1, t + n + 1, cmp), sort(p + 1, p + n + 1);
    for (int i = 1; i <= n; ++ i) pos[t[i]] = i;
    read(q);
    for (int i = 1; i <= n; ++ i) printf("%d ", B[i]); puts("");
    for (int i = 1; i <= n; ++ i) printf("%d ", c[i]); puts("");
    for (int i = 1; i <= n; ++ i) printf("%d ", d[i]); puts("");
    for (int i = 1; i <= n; ++ i) printf("%d ", p[i]); puts("");
    for (int i = 1; i <= n; ++ i) printf("%d ", pos[i]); puts("");
    while (q --) {
        ll x,  ans = 0; read(x); x -= a[1], d[1] = x;
        printf("d[1] : %d\n", Abs(x));
        int q = lower_bound(p + 1, p + n + 1, x) - p;
        printf("POS: %d\n", q);
    }
    return 0;
}
