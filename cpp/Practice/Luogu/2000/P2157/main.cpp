#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 1010;
const int INF = 0x3f3f3f3f;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T Min(T x, T y) {return x < y ? x : y;}

int T, n, f[N][256][20], t[N], b[N], ans;

inline int calc(int x, int y) {return x ? t[x] ^ t[y] : 0;}

void MAIN() {
    read(n); memset(f, 0x3f, sizeof f); f[1][0][7] = 0; ans = INF;
    for (int i = 1; i <= n; ++ i) read(t[i]), read(b[i]);
    for (int i = 1; i <= n; ++ i) for (int s = 0; s < (1 << 8); ++ s)
      for (int j = -8; j <= 7; ++ j) if (f[i][s][j + 8] != INF) {
          if (s & 1) f[i + 1][s >> 1][j + 7] = Min(f[i + 1][s >> 1][j + 7], f[i][s][j + 8]);
          else {
              int legal_pos = INF; 
              for (int k = 0; k <= 7; ++ k) if (!((s >> k) & 1)) {
                  if (i + k > legal_pos) break; else legal_pos = Min(legal_pos, i + k + b[i + k]);
                  f[i][s | (1 << k)][k + 8] = Min(f[i][s | (1 << k)][k + 8], f[i][s][j + 8] + calc(i + j, i + k));
              }
          }
      }
    for (int i = -8; i <= 0; ++ i) ans = Min(ans, f[n + 1][0][i + 8]); printf("%d\n", ans);
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(T); while (T --) MAIN(); return 0;
}
