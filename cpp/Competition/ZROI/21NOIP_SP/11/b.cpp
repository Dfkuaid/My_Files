#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int t, n, a[N];

inline void solve() {
    int mid = 1 + n >> 1, l = mid, r = mid + 1;
    for (int i = 1; i < n; ++ i) {
        printf("%d %d\n", a[l], a[r]);
        if (i & 1) -- l; else ++ r;
    }
}

inline void change() {
    for (int i = n + 1; i > 1; -- i) a[i] = a[i - 1];
    a[1] = a[n + 1];
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(t);
    for (int i = 1; i <= t; ++ i) {
        read(n); printf("Case #%d: %d\n", i, n / 2);
        for (int i = 1; i <= n; ++ i) a[i] = i;
        for (int k = 1; k <= n / 2; ++ k)
          solve(), change();
    }
    return 0;
}
