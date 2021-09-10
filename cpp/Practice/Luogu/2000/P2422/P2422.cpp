#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

ll a[N], q[N], sum[N], ans, f[N];
int n, lst[N], frt, tal = -1;

template <typename T>
inline T Max(const T a, const T b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++) {
        scanf("%lld", &a[i]);
        sum[i] = sum[i - 1] + a[i];
    }
    a[++ n] = 0;
    for (int i = 1; i <= n; i ++) {
        while (frt <= tal && a[q[tal]] >= a[i])
          f[q[tal]] += sum[i - 1] - sum[q[tal]], tal --;
        f[i] = sum[i] - sum[q[tal]];
        q[++ tal] = i;
    }
    for (int i = 1; i < n; i ++)
      ans = Max(ans, f[i] * a[i]);
    printf("%lld", ans);
    return 0;
}
