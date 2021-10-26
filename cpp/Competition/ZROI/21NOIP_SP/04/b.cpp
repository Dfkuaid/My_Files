#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 1000005;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T Max(T a, T b) {return a > b ? a : b;}
template <typename T> inline T Min(T a, T b) {return a < b ? a : b;}

bool zx[N << 1], fx[N << 1];
ll even[N << 1], odd[N << 1], n, m, ans;

inline ll len(ll x) {return Min(x, 2 * n - x);}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(m); ans = n * n;
    for (int i = 1; i <= m; ++ i) {
        ll x, y; read(x), read(y); 
        zx[y - x + n] = 1, fx[2 * n - x - y + 1] = 1;
    }
    for (int i = 1; i < n << 1; ++ i)
      if (i & 1) odd[i] = odd[i - 1] + zx[i];
      else odd[i] = odd[i - 1];
    for (int i = 1; i < n << 1; ++ i)
      if (!(i & 1)) even[i] = even[i - 1] + zx[i];
      else even[i] = even[i - 1];
    for (int i = 1; i < n << 1; ++ i) ans -= zx[i] * len(i);
    for (int i = 1; i < n << 1; ++ i) ans -= fx[i] * len(i);
    for (int i = 1; i < n << 1; ++ i) {
        if (!fx[i]) continue;
        if (n & 1) {
            if (i & 1) ans += odd[n + len(i) - 1] - odd[n - len(i)];
            else ans += even[n + len(i) - 1] - even[n - len(i)];
        } else {
            if (!(i & 1)) ans += odd[n + len(i) - 1] - odd[n - len(i)];
            else ans += even[n + len(i) - 1] - even[n - len(i)];
        }
    }
    printf("%lld", ans); return 0;
}
