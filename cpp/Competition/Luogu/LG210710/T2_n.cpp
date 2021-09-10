#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 1000010;
const int INF = 0x3fffffff;

int t, n, a[N], ans, s[N];

template <typename T>
inline T ABS(const T x) {
    return x >= 0 ? x : -x;
}

template <typename T>
inline T Max(const T a, const T b) {
    return a > b ? a : b;
}

int main() {
    scanf ("%d", &t);
    while (t --) {
        scanf("%d", &n); ans = 0;
        for (int i = 1; i <= n; ++ i) {
            scanf("%d", &a[i]);
            int l = a[i], r = i;
            if (r < l) swap(l, r);
            s[l] = Max(s[l], r);
        }
        int L = 0, R = -1;
        for (int i = 1; i <= n; ++ i) {
            if (i > R) {
                if (L < R) ans += R - L + 1;
                L = i, R = s[i];
            } else R = Max(R , s[i]);
            s[i] = 0;
        }
        if (L < R) ans += R - L + 1;
        printf("%d\n", ans);
    }
    return 0;
}