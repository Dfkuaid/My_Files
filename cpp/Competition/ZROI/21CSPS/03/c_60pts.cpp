#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

int n, m, a[N], b[N], res;

inline int bitcount(int x) {
    int cnt = 0;
    while (x) cnt += (x & 1), x >>= 1;
    return cnt;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i)
      scanf("%d", &a[i]);
    for (int i = 1; i <= m; ++ i)
      scanf("%d", &b[i]);
    for (int i = 1; i <= n; ++ i)
      for (int j = 1; j <= m; ++ j)
        if (bitcount(a[i] ^ b[j]) == 2) ++ res;
    printf("%d", res);
    return 0;
}