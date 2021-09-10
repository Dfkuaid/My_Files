#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

int t, n, k, x[N], y[N], id[N], vis[N], ans;

bool calc(int i, int j) {
    if ((x[i] < x[j] && y[i] > y[j]) || x[i] > y[j]) return false;
    if ((x[i] > x[j] && y[i] < y[j]) || x[j] > y[i]) return false;
    return true;
}

int main() {
    scanf("%d", &t);
    while (t --) {
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n << 1; ++ i) vis[i] = 0;
        for (int i = 1; i <= k; ++ i) {
            scanf("%d%d", &x[i], &y[i]);
            vis[x[i]] = vis[y[i]] = 1;
            if (x[i] > y[i]) swap(x[i], y[i]);
        }
        int cnt = 0; ans = 0;
        for (int i = 1; i <= n << 1; ++ i)
          if (!vis[i]) id[++ cnt] = i;
        for (int i = 1; i <= cnt >> 1; ++ i)
          ++ k, x[k] = id[i], y[k] = id[i + (cnt >> 1)];
        for (int i = 1; i <= n; ++ i)
          for (int j = i + 1; j <= n; ++ j)
            ans += calc(i, j);
        printf("%d\n", ans);
    }
    return 0;
}