#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 510;
const int MOD = 1e9 + 7;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int n, k, f[N][N], g[N][N][2][N], sum[N][N][2], vis[N][N]; char s[N];

inline bool check(int i, int j) {
    return (s[i] == '(' && s[j] == ')') || (s[i] == '?' && s[j] == ')') || (s[i] == '(' && s[j] == '?') || (s[i] == '?' && s[j] == '?') ? 1 : 0;
}

int main() {
    freopen("bracket.in", "r", stdin);
    freopen("bracket.out", "w", stdout);
    read(n), read(k); scanf("%s", s + 1);
    for (int i = 1; i <= n; ++ i) if (s[i] == '*' || s[i] == '?') vis[i][i] = 1;
    for (int i = 2; i <= n; ++ i) 
      for (int l = 1, r = l + i - 1; r <= n; ++ l, ++ r) {
          vis[l][r] = vis[l][l] & vis[l + 1][r];
          if (check(l, r)) {
              if (l == r - 1) f[l][r] = 1;
              else (f[l][r] += (f[l + 1][r - 1] + sum[l + 1][r - 1][0] + sum[l + 1][r - 1][1]) % MOD) %= MOD;
              for (int j = l + 1; j < r - 1; ++ j) {
                  (f[l][r] += (f[l][j] * f[j + 1][r]) % MOD) %= MOD;
                  (f[l][r] += (f[l][j] * sum[j + 1][r][0]) % MOD) %= MOD;
              }
              if (r - l - 1 > 0 && vis[l + 1][r - 1] && r - l - 1 <= k) ++ f[l][r];
          }
          if (s[l] == '?' || s[l] == '*') {
              for (int j = min(k, r - l + 1); j >= 2; -- j)
                (g[l][r][0][j] += g[l + 1][r][0][j - 1]) %= MOD;
              g[l][r][0][1] += f[l + 1][r];
              for (int j = min(k, r - l + 1); j >= 1; -- j)
                (sum[l][r][0] += g[l][r][0][j]) %= MOD;
          }
          if (s[r] == '?' || s[r] == '*') {
              for (int j = min(k, r - l + 1); j >= 2; -- j)
                (g[l][r][1][j] += g[l][r - 1][1][j - 1]) %= MOD;
              g[l][r][1][1] += f[l][r - 1];
              for (int j = min(k, r - l + 1); j >= 1; -- j)
                (sum[l][r][1] += g[l][r][1][j]) %= MOD;
          }
      }
    printf("%d", f[1][n]); return 0;
}
