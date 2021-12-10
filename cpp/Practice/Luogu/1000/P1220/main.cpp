#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 60;
const int INF = 0x3f3f3f3f;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T Min(T x, T y) {return x < y ? x : y;}
template <typename T> inline T Max(T x, T y) {return x > y ? x : y;}

int n, st, p[N]; ll w[N], f[N][N][2], s[N];

inline ll calc(int l, int r) {return s[n] - s[r] + s[l - 1];}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n); read(st); memset(f, 0x3f, sizeof f);
    for (int i = 1; i <= n; ++ i) read(p[i]), read(w[i]);
    for (int i = 1; i <= n; ++ i) s[i] = s[i - 1] + w[i];
    f[st][st][0] = f[st][st][1] = 0;
    for (int x = 2; x <= n; ++ x)
      for (int l = 1, r = l + x - 1; r <= n; ++ l, ++ r) {
          f[l][r][0] = Min(f[l][r][0], f[l + 1][r][0] + calc(l + 1, r) * (p[l + 1] - p[l]));
          f[l][r][0] = Min(f[l][r][0], f[l + 1][r][1] + calc(l + 1, r) * (p[r] - p[l]));
          f[l][r][1] = Min(f[l][r][1], f[l][r - 1][0] + calc(l, r - 1) * (p[r] - p[l]));
          f[l][r][1] = Min(f[l][r][1], f[l][r - 1][1] + calc(l, r - 1) * (p[r] - p[r - 1]));
      }
    printf("%lld", Min(f[1][n][0], f[1][n][1])); return 0;
}
