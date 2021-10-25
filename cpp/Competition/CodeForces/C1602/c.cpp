#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 200010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int t, n, tot[N], a[N], ans[N], cnt;

int gcd(int x, int y) {return y ? gcd(y, x % y) : x;}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(t);
    while (t --) {
        read(n); memset(tot, 0, sizeof tot); cnt = 0;
        for (int i = 1; i <= n; ++ i) read(a[i]);
        for (int i = 1; i <= n; ++ i)
          for (int j = 0; j < 30; ++ j)
            tot[j] += (a[i] >> j) & 1;
        int g = 0;
        for (int i = 0; i < 30; ++ i)
          g = gcd(g, tot[i]);
        for (int i = 1; i * i <= g; ++ i) if (!(g % i)) {
            ans[++ cnt] = i;
            if (i * i != g) ans[++ cnt] = g / i;
        }
        sort(ans + 1, ans + cnt + 1);
        if (!g) for (int i = 1; i <= n; ++ i) printf("%d ", i);
        else for (int i = 1; i <= cnt; ++i) printf("%d ", ans[i]);
        putchar('\n');
    }
    return 0;
}
