#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 500010;
const int INF = 0x3fffffff;

ll t, n, a[N], st[N][61], lg2[N], lgp = 1, b[N];

template <typename T>
inline T ABS(const T x) {return x >= 0 ? x : -x;}

ll Getgcd(ll x, ll y) {return y ? Getgcd(y, x % y) : x;}

inline void get_st() {
    for (int i = 1; i < n; ++ i) st[i][0] = a[i];
    for (int i = 1; i <= lg2[n]; ++ i)
      for (int j = 1; j + (1 << i) - 1 <= n; ++ j)
          st[j][i] = Getgcd(st[j][i - 1], st[j + (1 << (i - 1))][i - 1]);
}

inline ll query(ll l, ll r) {
    int k = lg2[r - l + 1];
    return Getgcd(st[l][k], st[r - (1 << k) + 1][k]);
}

int main() {
    scanf("%lld", &t); lg2[0] = -1;
    while (t --) {
        scanf("%lld", &n);
        while (lgp <= n) lg2[lgp] = lg2[lgp >> 1] + 1, ++ lgp;
        for (int i = 1; i <= n; ++ i) scanf("%lld", &b[i]);
        for (int i = 1; i < n; ++ i) a[i] = ABS(b[i + 1] - b[i]);
        int l = 1, r = 1, ans = 0; get_st();
        while (r < n) {
            while (l <= r && query(l, r) == 1)
              ans = max(ans, r - l + 1), ++ l;
            ++ r;
        }
        ans = max(ans, r - l + 1);
        printf("%d\n", ans);
    }
    return 0;
}