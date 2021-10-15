#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 2010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int n; char s[N];

bitset <N> mp[N], beat[N], res, lasL[N], lasR[N];

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n);
    for (int i = 1; i <= n; ++ i) {
        scanf("%s", s + 1);
        for (int j = 1; j <= n; ++ j)
          beat[i][j] = s[j] ^ 48;
    }
    for (int i = 1; i <= n; ++ i)
      lasL[i][i] = 1, lasR[i][i] = 1;
    for (int len = 1; len < n; ++ len)
      for (int l = 1, r = len; r <= n; ++ l, ++ r) {
          res = lasL[l] & lasR[r];
          if (r != n && (beat[r + 1] & res).any())
            lasL[l][r + 1] = 1;
          if (l != 1 && (beat[l - 1] & res).any())
            lasR[r][l - 1] = 1;
      }
    res = lasL[1] & lasR[n];
    for (int i = 1; i <= n; ++ i)
      if (res[i]) printf("%d ", i);
    return 0;
}
