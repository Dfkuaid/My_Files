#define LOCAL
#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int t, n, a[N], f[N][3][3], g[N][3][3][3], c[N][3];

inline bool check(int x, int y, int z, int k) {
    if (x > y) swap(x, y); if (y > z) swap(y, z);
    if (x > y) swap(x, y); return y == k;
}

void print(int x, int y, int z) {
    if (!x) {printf("%d ", a[1]); return;}
    print(g[x][y][z][0], g[x][y][z][1], g[x][y][z][2]);
    printf("%d ", c[x][z]);
}

inline void MAIN() {
    read(n);
    for (int i = 1; i <= n; ++ i) for (int j = 0; j < 3; ++ j)
      for (int k = 0; k < 3; ++ k) f[i][j][k] = 0;
    for (int i = 1; i <= n - 2; ++ i) read(a[i]);
    for (int i = 1; i <= n; ++ i)
      for (int j = max(1, i - 2), s = 0; j <= min(i, n - 2); ++ j)
        c[i][s ++] = a[j];
    f[2][0][0] = 1; f[2][0][1] = (n > 3) ? 1 : 0;
    for (int i = 2; i < n; ++ i) for (int j = 0; j < 3; ++ j)
      for (int k = 0; k < 3; ++ k) if (f[i][j][k])
        for (int l = 0; l < 3; ++ l)
          if (check(c[i - 1][j], c[i][k], c[i + 1][l], a[i - 1])) {
              f[i + 1][k][l] = 1; g[i + 1][k][l][0] = i;
              g[i + 1][k][l][1] = j; g[i + 1][k][l][2] = k;
          }
    int flag = 0;
    for (int i = 0; i < 2; ++ i)
      if (f[n][i][0]) {
          print(g[n][i][0][0], g[n][i][0][1], g[n][i][0][2]);
          printf("%d\n", c[n][0]); flag = 1; break;
      }
    if (!flag) puts("-1");
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(t); while (t --) MAIN(); return 0;
}
