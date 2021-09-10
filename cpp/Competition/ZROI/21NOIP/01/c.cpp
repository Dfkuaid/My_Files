#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 101;
const int INF = 0x3fffffff;

int f[N * N][N][N], pre[N][N], MOD, mxl[N * N];

inline void prework(int n) {
    for (int i = 1; i <= n * (n - 1) / 2; ++ i) mxl[i] = n;
    for (int i = n - 1; i; -- i)
      for (int j = (n - i) * (n - i - 1) / 2 + 1; j <= (n - i) * (n - i - 1) / 2 + n - i; ++ j)
        mxl[n * (n - 1) / 2 + j] = i;
}

inline int red(int x) {return x >= MOD ? x - MOD : x;}

inline void solve(int n) {
    mset(f, 0); f[1][n][1] = 1;
    for (int i = 2; i <= n * (n - 1); ++ i) {
        for (int j = 1; j <= n && j <= i; ++ j) {
            pre[1][j] = f[i - 1][1][j];
            for (int k = 2; k <= mxl[i - 1]; ++ k)
              pre[k][j] = red(pre[k - 1][j] + f[i - 1][k][j]);
        }
        for (int j = 1; j <= mxl[i]; ++ j)
          for (int k = 1; k <= n && k <= i && k <= (n - j + 1); ++ k) {
              int l = max(j, n - i + k - 1);
              if (l > j) continue; /*若下界比当前的要大，那么状态不合法*/
              f[i][j][k] = (pre[mxl[i - 1]][k - 1] - 
                           pre[l + (l == j) - 1][k - 1] + MOD) % MOD;
              if (l == j) f[i][j][k] = red(f[i][j][k] + f[i - 1][j][k]);
          }
    }
    for (int i = 1; i <= n * (n - 1); ++ i) {
        int ans = 0;
        for (int j = 1; j <= n; ++ j)
          for (int k = 1; k <= n; ++ k)
            ans = red(ans + f[i][j][k]);
        printf("%d ", ans);
    } printf("\n");
}

int main() {
    int T, n; scanf("%d", &T);
    while (T --) {
        scanf("%d%d", &n, &MOD);
        prework(n); solve(n);
    }
    return 0;
}