#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 1000010;
const int INF = 0x3fffffff;

struct Sub {
    int l, r;

    inline bool operator < (const Sub &b) const {
        return l == b.l ? r < b.r : l < b.l;
    }
};
Sub s[N];

int t, n, a[N], ans;

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
            s[i].l = a[i], s[i].r = i;
            if (s[i].r < s[i].l) swap(s[i].l, s[i].r);
        }
        sort(s + 1, s + n + 1);
        int L = 0, R = -1;
        for (int i = 1; i <= n; ++ i)
          if (s[i].l > R) {
              if (L < R) ans += R - L + 1;
              L = s[i].l, R = s[i].r;
          } else R = Max(R , s[i].r);
        if (L < R) ans += R - L + 1;
        printf("%d\n", ans);
    }
    return 0;
}