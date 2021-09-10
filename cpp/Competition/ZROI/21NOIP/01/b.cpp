#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 1000010;
const ll MOD = 1e9 + 7;
const int INF = 0x3fffffff;

int n,  p, vis[N];
ll s = 1, ans = 1;

int main() {
    scanf("%d%d", &n, &p);
    for (int i = 1; i <= p; ++ i) {
        int x; scanf("%d", &x); vis[x] = 1;
    }
    for (int i = n; i >= 1; -- i) {
        (ans *= s) %= MOD;
        if (vis[i]) -- s; else ++ s;
    }
    printf("%lld", ans);
    return 0;
}