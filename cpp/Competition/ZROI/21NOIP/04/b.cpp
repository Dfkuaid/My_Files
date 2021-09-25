#define DEBUG
#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 4010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int n, cost[N][N];

bitset <N> f[N];

bool check(int x) {
    for (int i = 1; i <= n; ++ i) f[i].reset();
    for (int i = 1; i <= n; ++ i) f[i][i - 1] = 1;
    for (int l = n - 1; l; -- l)
      for (int r = l + 1; r <= n; r += 2)
        if (!f[l][r] && f[l + 1][r - 1] && cost[l][r] <= x)
          f[l][r] = 1, f[l] |= f[r + 1];
    return f[1][n];
}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    read(n);
    for (int i = 1; i < n; ++ i)
      for (int j = i + 1; j <= n; j += 2)
        read(cost[i][j]);
    int l = 1, r = n * n / 4, res = 0;
    while (l <= r) {
        int mid = l + r >> 1;
        if (check(mid)) r = mid - 1, res = mid;
        else l = mid + 1;
    }
    printf("%d", res);
    return 0;
}