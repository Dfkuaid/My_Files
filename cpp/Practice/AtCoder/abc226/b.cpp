#define LOCAL
#include <bits/stdc++.h>
#define ll long long
#define mp(a, b) make_pair(a, b)
using namespace std;

const int N = 200010;
const int BASE1 = 131;
const int BASE2 = 13331;
const int MOD2 = 998244353;
const int MOD1 = 19270817;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int n, l[N], cnt;

map <pair <int, int>, bool> m[N];

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n);
    for (int i = 1; i <= n; ++ i) {
        read(l[i]); int k1 = 0, k2 = 0, x = 0;
        for (int j = 1; j <= l[i]; ++ j) {
            read(x);
            k1 = (1ll * k1 * BASE1 + x) % MOD1;
            k2 = (1ll * k2 * BASE2 + x) % MOD2;
        }
        if (!m[l[i]][mp(k1, k2)])
          ++ cnt, m[l[i]][(mp(k1, k2))] = 1;
    }
    printf("%d", cnt); return 0;
}
