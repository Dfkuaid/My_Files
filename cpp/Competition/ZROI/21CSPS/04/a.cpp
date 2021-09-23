#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 210;
const int INF = 0x3fffffff;

int n, m, a[N][N], ans;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i)
      for (int j = 1; j <= m; ++ j)
        scanf("%d", &a[i][j]);
    for (int i = n % 3 ? 1 : 2; i <= n; i += 3)
      for (int j = m % 3 ? 1 : 2; j <= m; j += 3)
        ans += a[i][j];
    printf("%d", ans);
    return 0;
}