#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 500010;
const int INF = 0x3fffffff;

int n, m, a[N], b[N], ans = INF;

template <typename T>
inline T Abs(const T x) {
    return x >= 0 ? x : -x;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i)
      scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++ i)
      scanf("%d", &b[i]);
    sort(a + 1, a + n + 1);
    sort(b + 1, b + m + 1);
    int p1 = 1, p2 = 1;
    while (p1 <= n && p2 <= m) {
        while (p2 <= m && a[p1] >= b[p2])
          ans = min(ans,abs(a[p1] - b[p2])), ++ p2;
        if (p2 <= m) ans = min(ans, abs(a[p1] - b[p2]));
        ++ p1;
    }
    cout << ans;
    return 0;
}