#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = (1 << 18) + 10;
const ll MOD = 1e9 + 7;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int n, m, u, v, e[20], re[20]; ll pw[310], f[N], num[N], lb[N], cnt[N];

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n); read(m); pw[0] = 1; f[0] = 1;
    for (int i = 1; i <= m; ++ i) pw[i] = (pw[i - 1] << 1) % MOD;
    for (int i = 1; i < (1 << n); ++ i) cnt[i] = cnt[i >> 1] + (i & 1);
    for (int i = 1; i < (1 << n); ++ i) lb[i] = (i & 1 ? 1 : lb[i >> 1] + 1);
    for (int i = 1; i <= m; ++ i) read(u), read(v), e[u] |= (1 << v - 1), re[v] |= (1 << u - 1);
    for (int i = 1; i < (1 << n); ++ i) {
        for (int t = (i - 1 & i), j = i - t; ; t = (t - 1 & i), j = i - t) {
            num[j] = num[j - (j & -j)] - cnt[re[lb[j]] & j] + cnt[e[lb[j]] & i - j];
            (f[i] += ((cnt[j] & 1 ? 1 : MOD - 1) * pw[num[j]]) % MOD * f[i - j]) %= MOD;
            if (!t) break;
        }
    }
    printf("%d", (pw[m] - f[(1 << n) - 1] + MOD) % MOD); return 0;
}
