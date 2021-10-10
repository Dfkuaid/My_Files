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

int n; ll a[N], t[N], ans = INF;

bool check(ll x) {
    for (int i = 1; i <= n; ++ i) t[i] = a[i];
    for (int i = 2; i < n; ++ i) if (t[i] > x)
      t[i - 1] += t[i] - x, t[i + 1] += t[i] - x, t[i] = x;
    for (int i = 1; i <= n; ++ i)
      if (t[i] > x) return false;
    return true;
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n); ll l = INF, r = -INF; 
    for (int i = 1; i <= n; ++ i)
      read(a[i]), l = min(l, a[i]), r = max(r, a[i]);
    while (l <= r) {
        int mid = l + r >> 1;
        if (check(mid)) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    printf("%lld", ans); return 0;
}
