#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int n, q[N], frt = 0, tal =  -1; ll L, c[N], s[N], f[N], val[N];

inline ll slope(int x, int y) {return (val[y] - val[x]) / (s[y] - s[x]);}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(L); L += 1, q[++ tal] = 0;
    for (int i = 1; i <= n; ++ i) read(c[i]);
    for (int i = 1; i <= n; ++ i) s[i] = s[i - 1] + c[i];
    for (int i = 1; i <= n; ++ i) s[i] += i;
    for (int i = 1; i <= n; ++ i) {
        while (frt < tal && slope(q[frt], q[frt + 1]) < 2 * s[i]) ++ frt;
        f[i] = val[q[frt]] - 2 * s[i] * s[q[frt]] + (s[i] - L) * (s[i] - L);
        val[i] = f[i] + 2 * s[i] * L + s[i] * s[i];
        while (frt < tal && slope(q[tal - 1], q[tal]) >= slope(q[tal - 1], i)) -- tal;
        q[++ tal] = i;
    }
    printf("%lld", f[n]); return 0;
}
