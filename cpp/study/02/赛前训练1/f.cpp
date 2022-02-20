#define LOCAL
#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 1010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T Max(T a, T b) {return a > b ? a : b;}
template <typename T> inline T Min(T a, T b) {return a < b ? a : b;}

char s[N];
int t, n, m, f[N][N][4][2], cvis[N][N], ans;

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(t);
    while (t --) {
        read(n), read(m); mset(f, 0); ans = 0;
        for (int i = 1; i <= n; ++ i) {
            scanf("%s", s + 1);
            for (int j = 1; j <= m; ++ j)
              cvis[i][j] = s[j] ^ 48;
        }
        for (int i = m; i >= 1; -- i)
          for (int j = 1; j <= n; ++ j) {
              if (!cvis[j][i]) continue;
              f[j][i][0][0] = f[j - 1][i][0][1] + 1;
              f[j][i][0][1] = f[j][i + 1][0][0] + 1;
          }
        for (int i = m; i >= 1; -- i)
          for (int j = n; j >= 1; -- j) {
              if (!cvis[j][i]) continue;
              f[j][i][1][0] = f[j][i + 1][1][1] + 1;
              f[j][i][1][1] = f[j + 1][i][1][0] + 1;
          }
        for (int i = 1; i <= m; ++ i)
          for (int j = n; j >= 1; -- j) {
              if (!cvis[j][i]) continue;
              f[j][i][2][0] = f[j + 1][i][2][1] + 1;
              f[j][i][2][1] = f[j][i - 1][2][0] + 1;
          }
        for (int i = 1; i <= m; ++ i)
          for (int j = 1; j <= n; ++ j) {
              if (!cvis[j][i]) continue;
              f[j][i][3][0] = f[j][i - 1][3][1] + 1;
              f[j][i][3][1] = f[j - 1][i][3][0] + 1;
          }
        for (int i = 1; i <= n; ++ i)
          for (int j = 1; j <= m; ++ j) {
              if (!cvis[i][j]) continue; int res = 0;
              for (int k = 0; k < 4; ++ k) res += f[i][j][k][0];
              ans = Max(ans, res - 3);
          }
        printf("%d\n", ans);
    }
    return 0;
}
