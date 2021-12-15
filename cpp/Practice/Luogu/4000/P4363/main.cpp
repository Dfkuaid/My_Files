#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 10;
const int M = 1 << 20;
const int INIT = 0x3f3f3f3f;
const int INF = 1e9 + 7;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T Min(T x, T y) {return x < y ? x : y;}
template <typename T> inline T Max(T x, T y) {return x > y ? x : y;}

int n, m, a[N][N], b[N][N], f[M];

inline void print_digital(int x, int len = 16, char c = ' ') {
    for (int i = 0; i < len; ++ i) printf("%d", (x >> i) & 1); putchar(c);
}

int solve(int s, int who) {
    if (f[s] != INIT) return f[s]; else f[s] = who ? -INF : INF;
    for (int i = 0, x = n, y = 0; i < n + m - 1; ++ i) {
        if ((s >> i) & 1) -- x; else ++ y;
        if (((s >> i) & 3) != 1) continue;
        int nxt = s ^ (3 << i);
        if (who) f[s] = Max(f[s], solve(nxt, who ^ 1) + a[x][y]);
        else f[s] = Min(f[s], solve(nxt, who ^ 1) - b[x][y]);
    }
    return f[s];
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(m); memset(f, 0x3f, sizeof f);
    for (int i = 0; i < n; ++ i) for (int j = 0; j < m; ++ j) read(a[i][j]);
    for (int i = 0; i < n; ++ i) for (int j = 0; j < m; ++ j) read(b[i][j]);
    f[((1 << n) - 1) << m] = 0; printf("%d", solve((1 << n) - 1, 1)); return 0;
}
