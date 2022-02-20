#define LOCAL
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <string>
#include <cstring>
#define ll long long
using namespace std;

const int N = 1010;
const int M = 10010;
const int INF = 0x3f3f3f3f;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int n, f[N][M], w0[N], w1[N];

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n); memset(f, 0x3f, sizeof f); f[0][5000] = 0;
    for (int i = 1, a = 0, b = 0; i <= n; ++ i)
      read(a), read(b), w0[i] = a - b, w1[i] = b - a;
    for (int i = 1; i <= n; ++ i)
      for (int j = 0; j <= 10000; ++ j) {
          if (j + w0[i] >= 0 && j + w0[i] <= 10000)
            f[i][j + w0[i]] = min(f[i][j + w0[i]], f[i - 1][j]);
          if (j + w1[i] >= 0 && j + w1[i] <= 10000)
            f[i][j + w1[i]] = min(f[i][j + w1[i]], f[i - 1][j] + 1);
      }
    for (int i = 0; i <= 5000; ++ i)
      if (f[n][5000 + i] != INF || f[n][5000 - i] != INF) {
          printf("%d", min(f[n][5000 + i], f[n][5000 - i])); break;
      }
    return 0;
}
