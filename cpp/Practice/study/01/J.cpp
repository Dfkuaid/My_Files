#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 55;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T Max(const T &a, const T &b) {return a > b ? a : b;}
template <typename T> inline T Min(const T &a, const T &b) {return a < b ? a : b;}

#define lb(T, l, x) lower_bound(T + 1, T + l + 1, x)

int n, m, a, b, p[N], f[N][N], g[N][N][N][N], t[N];

int main() {
    mset(f, 0x3f); mset(g, 0x3f); read(n); read(a); read(b);
    for (int i = 1; i <= n; ++ i) read(p[i]), t[i] = p[i];
    sort(t + 1, t + n + 1); m = unique(t + 1, t + n + 1) - t - 1;
    for (int i = 1; i <= n; ++ i) p[i] = lb(t, m, p[i]) - t;
    for (int i = 1; i <= n; ++ i) f[i][i] = a, g[i][i][p[i]][p[i]] = 0;
    for (int len = 2; len <= n; ++ len)
      for (int l = 1, r = l + len - 1; r <= n; ++ l, ++ r) {
          for (int i = 1; i <= m; ++ i) for (int j = i; j <= m; ++ j)
            g[l][r][Max(j, p[r])][Min(i, p[r])] = Min(g[l][r][Max(j, p[r])][Min(i, p[r])], g[l][r - 1][j][i]);
          for (int i = 1; i <= m; ++ i) for (int j = i; j <= m; ++ j) for (int k = l; k < r; ++ k)
            g[l][r][j][i] = Min(g[l][r][j][i], g[l][k][j][i] + f[k + 1][r]);
          for (int i = 1; i <= m; ++ i) for (int j = i; j <= m; ++ j)
            f[l][r] = Min(f[l][r], g[l][r][j][i] + a + b * (t[j] - t[i]) * (t[j] - t[i]));
      }
    printf("%d", f[1][n]); return 0;
}
