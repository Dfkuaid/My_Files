#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

ll n;

ll phi(ll x) {
    ll res = x;
    for (ll i = 2; i * i <= x; i ++) {
        if (x % i == 0) res = res / i * (i - 1);
        while (x % i == 0) x /= i;
    }
    if (x > 1) res = res / x * (x - 1);
    return res;
}

ll f(ll x) {
    ll i = 1, res = 0;
    for (; i * i < x; i ++) if (x % i == 0)
      res += i * phi(x / i) + x / i * phi(i);
    if (i * i == x) res += i * phi(i);
    return res;
}

int main() {
    scanf("%lld", &n);
    printf("%lld", f(n));
    return 0;
}