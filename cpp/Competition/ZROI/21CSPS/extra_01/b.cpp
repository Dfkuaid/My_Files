#define DEBUG
#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 100010;
const ll MOD = 1e9 + 7;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int n, k; ll C[N][55], a[N], ans;

inline void init_C(int x, int y) {
    for (int i = 0; i <= x; ++ i) C[i][0] = 1;
    for (int i = 1; i <= x; ++ i)
      for (int j = 1; j <= i && j <= y; ++ j) {
          if (j == i) {C[i][j] = 1; break;}
          C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
      }
}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    read(n); read(k); init_C(n, k);
    for (int i = 1; i <= n; ++ i) read(a[i]);
    sort(a + 1, a + n + 1);
    for (int i = k; i <= n; ++ i)
      (ans += C[i - 1][k - 1] * a[i] % MOD) %= MOD;
    printf("%lld", ans); return 0;
}