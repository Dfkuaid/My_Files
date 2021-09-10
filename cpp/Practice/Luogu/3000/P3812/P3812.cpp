#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

ll n, a[N];

void insert(ll t) {
    for (int i = 51; i >= 0; i --) {
        if (!(t & (1ll << i))) continue;
        if (a[i]) t ^= a[i];
        else {
            for (int j = 0; j < i; j ++)
              if (t & (1ll << j)) t ^= a[j];
            for (int j = 51; j > i; j --)
              if (a[j] & (1ll << i)) a[j] ^= t;
            a[i] = t; break;
        }
    }
}

int main() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; i ++) {
        ll x; scanf("%lld", &x);
        insert(x);
    }
    ll res = 0;
    for (int i = 51; i >= 0; i --)
      res ^= a[i];
    printf("%lld", res);
    return 0;
}