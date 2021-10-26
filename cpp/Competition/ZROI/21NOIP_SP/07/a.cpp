#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 300010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T Max(T a, T b) {return a > b ? a : b;}

int n, lmt, a[N], mx[20][N], sec[20][N], vis[20][N], ans[N];

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n); lmt = 1 << n;
    for (int i = 1; i <= lmt; ++ i) read(a[i]);
    for (int i = 1; i <= lmt; ++ i) mx[0][i] = a[i], sec[0][i] = -INF;
    for (int i = 1; i <= n; ++ i)
      for (int j = 1; j + (1 << i) - 1 <= lmt; j += (1 << i)) {
          if (mx[i - 1][j] < mx[i - 1][j + (1 << i - 1)]) {
              mx[i][j] = mx[i - 1][j + (1 << i - 1)];
              sec[i][j] = Max(sec[i - 1][j + (1 << i - 1)], mx[i - 1][j]);
          } else {
              mx[i][j] = mx[i - 1][j];
              sec[i][j] = Max(sec[i - 1][j], mx[i - 1][j + (1 << i - 1)]);
          }
          vis[i][sec[i][j]] |= 1;
      }
    for (int i = 1; i <= n; ++ i)
      for (int j = 1; j <= lmt; ++ j)
        vis[i][j] |= vis[i][j - 1];
    for (int i = 1; i <= lmt; ++ i)
      for (int j = 1; j <= n; ++ j)
        if (vis[j][a[i] - 1]) ans[a[i]] = j;
    for (int i = 1; i <= lmt; ++ i) printf("%d ", ans[i]);
    return 0;
}
