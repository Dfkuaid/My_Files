#define LOCAL
#include <bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;

const int N = 100010;
const ll INF = 1e18 + 1;
const ll UPPER_LIMIT = 1e18;
const char cut_off[22] = {'-', '-', '-', '-', '-', '-', '-', '-',
    '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'};

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T Min(T x, T y) {return x < y ? x : y;}
template <typename T> inline T Max(T x, T y) {return x > y ? x : y;}
template <typename T> inline T Abs(T x) {return x < 0 ? -x : x;}

struct Object {int x, l, r;} q[N];

int t, n, l, p, g[N]; ld f[N]; ll len[N], sum[N], frt, tal; char s[N][50];

inline void reset() {
    frt = 0, tal = -1; sum[0] = f[0] = 0;
    for (int i = 1; i <= n; ++ i) f[i] = UPPER_LIMIT + 1;
}

inline ld fpow(ld x, ll y) {
    ld res = 1;
    while (y) {
        if (y & 1) res *= x;
        y >>= 1; x = x * x;
    }
    return res;
}

void print(int x) {
    if (g[x]) print(g[x]);
    for (int i = g[x] + 1; i < x; ++ i) printf("%s ", s[i]);
    printf("%s\n", s[x]);
}

inline ld calc(int L, int R) {return fpow(Abs(sum[R] - sum[L] + R - L - 1 - l), p);}
inline bool check(int x, int y, int z) {
    return 1ull * f[x] + 1ull * calc(x, z) < 1ull * f[y] + 1ull * calc(y, z);
}

inline int bny_search(int L, int R, int x, int y) {
    int res = R;
    while (L <= R) {
        int mid = L + R >> 1;
        if (check(x, y, mid))
          R = mid - 1, res = mid;
        else L = mid + 1;
    }
    return res;
}

void MAIN() {
    read(n), read(l), read(p); reset();
    for (int i = 1; i <= n; ++ i) scanf("%s", s[i]);
    for (int i = 1; i <= n; ++ i) len[i] = strlen(s[i]);
    for (int i = 1; i <= n; ++ i) sum[i] = sum[i - 1] + len[i];
    q[++ tal] = (Object){0, 1, n}; int nl = 0;
    for (int i = 1; i <= n; ++ i) {
        while (frt <= tal && q[frt].r < i) ++ frt;
        g[i] = q[frt].x, f[i] = f[g[i]] + calc(g[i], i), nl = n + 1;
        while (frt <= tal && check(i, q[tal].x, q[tal].l)) nl = q[tal --].l;
        if (frt <= tal && check(i, q[tal].x, q[tal].r))
          nl = bny_search(q[tal].l, q[tal].r, i, q[tal].x);
        if (frt <= tal) q[tal].r = nl - 1;
        if (nl <= n) q[++ tal] = (Object){i, nl, n};
    }
    if (f[n] <= UPPER_LIMIT) printf("%lld\n", (ll)(f[n] + 0.5)), print(n);
    else puts("Too hard to arrange");
    puts(cut_off);
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(t); while (t --) MAIN(); return 0;
}
