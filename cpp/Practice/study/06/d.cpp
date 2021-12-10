#define LOCAL
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
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

int T, t, n, v, w[N], s[N], ans, f[N];

inline void reset() {ans = 0;}

void MAIN() {
    read(n), read(v), reset();
    for (int i = 1; i <= n; ++ i) read(w[i]);
    sort(w + 1, w + n + 1);
    for (int i = 1; i <= n; ++ i) s[i] = s[i - 1] + w[i];
    for (int i = 1; i <= n; ++ i) {
        int tv = v - s[i - 1]; if (tv < 0) break;
        memset(f, 0, sizeof f); f[0] = 1;
        for (int j = i + 1; j <= n; ++ j)
          for (int o = tv; o >= w[j]; -- o)
            f[o] += f[o - w[j]];
        for (int j = tv; tv < w[i] + j && j; -- j) ans += f[j];
        if (tv < w[i] && i > 1) ++ ans;
    }
    printf("%d %d\n", T, ans);
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(t);  while (++ T <= t) MAIN(); return 0;
}
