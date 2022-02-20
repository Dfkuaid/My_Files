#define LOCAL
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#define ll long long
using namespace std;

const int N = 1010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T Max(T x, T y) {return x > y ? x : y;}

int n, w, f[N][50][2], v[N][2], ans;

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(w);
    for (int i = 1, x = 0; i <= n; ++ i)
      read(x), v[i][x - 1] = 1, v[i][!(x - 1)] = 0;
    for (int i = 1; i <= n; ++ i) {
        f[i][0][0] = f[i - 1][0][0] + v[i][0];
        f[i][0][1] = f[i - 1][0][1] + v[i][1];
        for (int j = 1; j <= w; ++ j) {
            f[i][j][0] = Max(f[i - 1][j][0], f[i - 1][j - 1][1]) + v[i][0];
            f[i][j][1] = Max(f[i - 1][j][1], f[i - 1][j - 1][0]) + v[i][1];
        }
    }
    for (int i = 1; i <= w; ++ i)
      ans = Max(ans, Max(f[n][i][0], f[n][i][1]));
    printf("%d", ans); return 0;
}
