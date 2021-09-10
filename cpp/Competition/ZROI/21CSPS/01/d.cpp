#include <bits/stdc++.h>
#define ll unsigned long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const ll N = 100010;
const ll INF = 0x3fffffff;
const ll MOD = 2148473647;

ll n;

inline ll fpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) (res *= a) %= MOD;
        (a *= a) %= MOD; b >>= 1;
    }
    return res;
}

int main() {
    scanf("%llu", &n);
    ll res1 = n * (n + 1) % MOD;
    ll res2 = fpow(2 * (2 * n - 1) % MOD, MOD - 2);
    printf("%llu", (res1 * res2 % MOD + MOD) % MOD);
    return 0;
}