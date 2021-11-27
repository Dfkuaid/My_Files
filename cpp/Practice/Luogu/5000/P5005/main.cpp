#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 110;
const int M = 1 << 6;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int n, m, rg1[M], rg2[M][M], f[2][M][M], ans;

inline void madd(int &x, int y) {x = x + y < MOD ? x + y : x + y - MOD;}

inline void print_b(int x, char c) {
    for (int i = m - 1; ~i; -- i) printf("%d", (x >> i) & 1); putchar(c);
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(m);
    for (int s = 0; s < (1 << m); ++ s)
      for (int i = 0; i < m; ++ i) if ((s >> i) & 1) {
          if (i > 1 && !((s >> i - 1) & 1)) rg1[s] |= (1 << i - 2);
          if (i < m - 2 && !((s >> i + 1) & 1)) rg1[s] |= (1 << i + 2);
      }
    for (int s1 = 0; s1 < (1 << m); ++ s1)
      for (int s2 = 0; s2 < (1 << m); ++ s2) {
          if (s2 & rg1[s1]) continue;
          rg2[s1][s2] |= rg1[s2];
          for (int i = 0; i < m; ++ i)
            if (((s1 >> i) & 1) && !((s2 >> i) & 1)) {
                if (i > 0) rg2[s1][s2] |= (1 << i - 1);
                if (i < m - 1) rg2[s1][s2] |= (1 << i + 1);
            }
      }
    for (int s = 0; s < (1 << m); ++ s) f[1][s][0] = 1;
    for (int i = 2; i <= n; ++ i)
      for (int s1 = 0; s1 < (1 << m); ++ s1)
        for (int s2 = 0; s2 < (1 << m); ++ s2) {
            if (s2 & rg1[s1] || s1 & rg1[s2]) continue;
            f[i & 1][s1][s2] = 0;
            for (int s3 = 0; s3 < (1 << m); ++ s3) {
                if (s3 & rg2[s1][s2] || rg2[s3][s2] & s1) continue;
                madd(f[i & 1][s1][s2], f[!(i & 1)][s2][s3]);
            }
        }
    for (int s1 = 0; s1 < (1 << m); ++ s1)
      for (int s2 = 0; s2 < (1 << m); ++ s2) {
          if (s2 & rg1[s1] || s1 & rg1[s2]) continue;
          madd(ans, f[n & 1][s1][s2]);
      }
    printf("%d", ans); return 0;
}