#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 2000010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int n, m, a[N], q[N], frt, tal = -1, tot;

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(m);
    for (int i = m - 1; ~i; -- i) q[++ tal] = i;
    for (int i = 1, lst = 0; i <= n; ++ i) {
        int x; read(x); if (!x) continue;
        int len = i - lst - 1; ++ tot;
        q[++ tal] = -tot; tal = max(frt - 1, tal - len);
        while (frt <= tal && q[frt] + tot >= m) ++ frt;
        a[i - m + tal - frt + 1] = 1, lst = i;
    }
    for (int i = 1; i <= n; ++ i) printf("%d ", a[i]);
    return 0;
}
