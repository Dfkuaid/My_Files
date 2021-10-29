#define LOCAL
#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 100010;
const int MOD = 1e9 + 7;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int n, t, f[N][16], a[N], ans; char s[N], g[N];

inline int get(int x, int y, int z) {return g[x | (y << 1) | (z << 2)] - '0';}
inline int Madd(int x, int y) {return x + y >= MOD ? x + y - MOD : x + y;}

void MAIN() {
    scanf("%s%s", g, s + 1); n = strlen(s + 1);
    mset(f, 0); ans = 0; f[0][9] = 1;
    for (int i = 2; i < n; ++ i) 
      for (a[i - 1] = 0; a[i - 1] < 2; ++ a[i - 1])
        for (a[i] = 0; a[i] < 2; ++ a[i]) {
            if (s[i - 1] != '?' && s[i - 1] != a[i - 1] + '0') continue;
            if (s[i] != '?' && s[i] != a[i] + '0') continue;
            for (int S = 0; S < 16; ++ S) {
                if (!f[i - 2][S]) continue; int SS = 0;
                for (int p1 = 0; p1 < 2; ++ p1)
                  for (int p2 = 0; p2 < 2; ++ p2) {
                      int p = ((S & (1 << (get(a[i - 1], a[i], p1) << 1) + p2)) > 0);
                      if (get(0, a[i], p1) == p2) p |= ((S & (1 << (a[i - 1] << 1))) > 0);
                      if (get(1, a[i], p1) == p2) p |= ((S & (1 << (a[i - 1] << 1) + 1)) > 0);
                      if (p) SS |= (1 << (p1 << 1) + p2);
                  }
                f[i][SS] = Madd(f[i][SS], f[i - 2][S]);
            }
        }
    for (a[n] = 0; a[n] < 2; ++ a[n]) {
        if ((s[n] != '?') && (s[n] != a[n] + '0'))continue;
        for (int S = 0; S < 16; ++ S)
          if (S & (1 << (a[n] << 1) + 1))
            ans = Madd(ans, f[n - 1][S]);
    }
    printf("%d\n", ans);
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(t); while (t --) MAIN(); return 0;
}
