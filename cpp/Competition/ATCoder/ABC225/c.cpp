#define LOCAL
#include <bits/stdc++.h>
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

int n, m, a[N][10];

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(m);
    for (int i = 1; i <= n; ++ i)
      for (int j = 1; j <= m; ++ j)
        read(a[i][j]);
    for (int i = 1; i <= n; ++ i) {
        for (int j = 2; j <= m; ++ j)
          if (a[i][j] != a[i][j - 1] + 1 || a[i][j] % 7 < a[i][j - 1] % 7) {
              puts("No"); return 0;
          }
    }
    for (int i = 2; i <= n; ++ i) 
      if (a[i][1] != a[i - 1][1] + 7) {
          puts("No"); return 0;
      }
    puts("Yes"); return 0;
}
