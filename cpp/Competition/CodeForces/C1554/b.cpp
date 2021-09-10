#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 300010;
const int INF = 0x3fffffff;

template <typename T>
inline T Max(const T a, const T b) {
    return a > b ? a : b;
}

int t, n, k, a[N];
ll ans;

int main() {
    scanf("%d", &t);
    while (t --) {
        scanf("%d%d", &n, &k); ans = -INF;
        for (int i = 1; i <= n; ++ i) scanf("%d", &a[i]);
        for (int i = Max(1, n - 1000); i < n; ++ i)
          for (int j = i + 1; j <= n; ++ j)
            ans = Max(ans, (ll)i * j - (ll)k * (ll)(a[i] | a[j]));
        printf("%lld\n", ans);
    }
    return 0;
}