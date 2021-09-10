#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

template <typename T>
inline T Max(const T a, const T b) {
    return a > b ? a : b;
}

ll t, n, a[N], ans;

int main() {
    scanf("%lld", &t);
    while (t --) {
        scanf("%lld", &n); ans = 0;
        for (int i = 1; i <= n; ++ i) {
            scanf("%lld", &a[i]);
            ans = Max(ans, a[i] * a[i - 1]);
        }
        printf("%lld\n", ans);
    }
    return 0;
}