#define DEBUG
#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

struct DSU {
    int siz[N], f[N], tot;

    inline void init(int x) {
        tot = x;
        for (int i = 0; i <= x; ++ i)
          f[i] = i, siz[i] = 1;
    }

    inline int find(int x) {
        while (x != f[x]) x = f[x] = f[f[x]];
        return x;
    }

    inline void merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        if (siz[x] > siz[y]) swap(x, y);
        f[x] = y, siz[y] += siz[x], -- tot;
    }
} dsu;

int n, m, tcnt, ans; char c;

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m; dsu.init(n + m);
    for (int i = 1; i <= n; ++ i)
      for (int j = 1; j <= m; ++ j) {
        cin >> c; if (c == '1') dsu.merge(i, j + n), ++ tcnt;
      }
    ans = (dsu.tot - 1) * 4 + (n * m - tcnt - dsu.tot + 1) * 3;
    cout << ans; return 0;
}