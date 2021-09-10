#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 200010;
const ll INF = 0x7fffffff;

ll n, m, a[N], maxx = -INF, minn = INF, ans, xp, np;

template <typename T>
inline T Max(const T x, const T y) {
    return x > y ? x : y;
}

template <typename T>
inline T Min(const T x, const T y) {
    return x < y ? x : y;
}

int main() {
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; ++ i)
      scanf("%lld", &a[i]);
    for (int i = 1; i <= n; ++ i)
      if (a[i] > maxx) maxx = a[i], xp = i;
    for (int i = 1; i <= n; ++ i)
      if (i != xp && a[i] < minn) minn = a[i], np = i;
    for (int i = 1; i <= n; ++ i)
      if (i != xp && i != np) {
          ans += a[i];
          if (m >= maxx - a[i])
            ans += maxx - a[i], m -= (maxx - a[i]);
          else ans += m, m = 0;
        //   cout << i << " " << ans << endl;
      }
    if (m) {
        int t = m / (n - 1);
        ans += t * (n - 2), m %= (n - 1);
        if (m) ans += m - 1, m = 0;
    }
    printf("%lld", ans);
    return 0;
}