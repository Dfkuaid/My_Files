#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int MOD = 998244353;
const int INF = 0x3fffffff;

ll n, k, l[N], r[N], cnt[N], res = 1;

int main() {
    scanf("%lld%lld", &n, &k);
    for (int i = 1; i <= k; ++ i) {
        char c; int x; cin >> c >> x;
        if (cnt[x]) {puts("0"); return 0;}
        if (c == 'L') ++ l[x], cnt[x] = 1;
        else ++ r[x], cnt[x] = 1;
    }
    for (int i = 1; i <= n; ++ i) (l[i] += l[i - 1]) %= MOD;
    for (int i = n; i >= 1; -- i) (r[i] += r[i + 1]) %= MOD;
    for (int i = 1; i <= n; ++ i) {
        if (cnt[i]) continue;
        cnt[i] = (l[i] + r[i]) % MOD;
    }
    for (int i = 1; i <= n; ++ i) (res *= cnt[i]) %= MOD;
    printf("%lld", res);
    return 0;
}