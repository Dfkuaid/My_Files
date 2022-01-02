#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 3010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T Min(T x, T y) {return x < y ? x : y;}

int n, m, pos[N], w[N][N], f[N][N], g[N][N];

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(m); memset(f, 0x3f, sizeof f);
    for (int i = 1; i <= n; ++ i) read(pos[i]);
    sort(pos + 1, pos + n + 1);
    for (int i = 1; i <= n; ++ i) for (int j = i + 1; j <= n; ++ j)
      w[i][j] = w[i][j - 1] + pos[j] - pos[i + j >> 1];
    for (int i = 0; i <= m; ++ i) f[0][i] = 0;
    for (int i = 0; i <= m; ++ i) g[n + 1][i] = n - 1;
    for (int j = 1; j <= m; ++ j) for (int i = n; i >= 1; -- i)
      for (int k = g[i][j - 1]; k <= g[i + 1][j]; ++ k) 
        if (f[i][j] > f[k][j - 1] + w[k + 1][i])
          f[i][j] = f[k][j - 1] + w[k + 1][i], g[i][j] = k;
    printf("%d", f[n][m]); return 0;
}
