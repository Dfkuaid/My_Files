#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 20000010;
const int MOD = 19260817;
const int INF = 0x3fffffff;

struct Hash {int val, tot, nxt;} h[N];

int n, m, a[N], b[N], head[N], cnt;
ll ans;

inline void insert(int x, int c) {
    int hx = x % MOD, p = head[hx];
    while (p && h[p].val != x) p = h[p].nxt;
    if (h[p].val == x) h[p].tot += c;
    else {
        h[++ cnt].val = x, h[cnt].tot = c;
        h[cnt].nxt = head[hx], head[hx] = cnt;
    }
}

inline int Count(int x) {
    int hx = x % MOD, p = head[hx];
    while (p && h[p].val != x) p = h[p].nxt;
    if (h[p].val == x) return h[p].tot;
    else return 0;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i)
      scanf("%d", &a[i]);
    for (int i= 1; i <= m; ++ i)
      scanf("%d", &b[i]);
    for (int i = 1; i <= 30; ++ i) {
        int k = 1 << (i - 1);
        for (int j = 1; j <= m; ++ j)
          ans += Count(b[j] ^ k);
        for (int j = 1; j <= n; ++ j)
          insert(a[j] ^ k, 1);
    }
    printf("%lld", ans);
    return 0;
}