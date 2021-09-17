#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const ll MOD = 1e9;
const int N = 2000010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int n, npr[N][2], cnt; ll f[N][21];

ll gcd(ll x, ll y) {return y ? gcd(y, x % y) : x;}

int main() {
    read(n);
    for (int i = 1; i < n; ++ i)
      for (int j = i + 1; j <= n; ++ j)
        if (gcd(i, j) == 1) npr[++ cnt][0] = i, npr[cnt][1] = j;
    f[0][1] = 1;
    for (int i = 1; i <= cnt; ++ i)
      for (int j = 1; j <= n; ++ j) {
          f[i][j] = (f[i][j] + f[i - 1][j]) % MOD;
          if (npr[i][0] <= j)
            (f[i][max(npr[i][1], j)] += f[i - 1][j]) %= MOD;
      }
    printf("%lld", f[cnt][n]);
    return 0;
}