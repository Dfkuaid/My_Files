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

ll n, cnt, a[N], m1[N], m2[N], cnt1, cnt2;

#define lb(l, len, x) lower_bound(l + 1, l + len + 1, x)
#define ub(l, len, x) upper_bound(l + 1, l + len + 1, x)

void solve(ll total, ll x) {
    if (!x) return;
    if (x % 3 == 0) {
        ll res = 3; while (!(x % res)) res *= 3;
        res /= 3; solve(total * res, x / res);
    } else if (x % 3 == 1) {
        int pos = ub(m1, cnt1, x) - m1 - 1;
        a[++ cnt] = total * m1[pos];
        solve(total, x - m1[pos]);
    } else {
        int pos = ub(m2, cnt2, x) - m2 - 1;
        a[++ cnt] = total * m2[pos];
        solve(total, x - m2[pos]);
    }
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n);
    m1[++ cnt1] = 4, m2[++ cnt2] = 2;
    while (m1[cnt1] <= n) m1[cnt1 + 1] = m1[cnt1] << 2, ++ cnt1;
    while (m2[cnt2] <= n) m2[cnt2 + 1] = m2[cnt2] << 2, ++ cnt2;
    if (n & 1) {
        ll res = 3; while (res <= n) res *= 3;
        res /= 3; a[++ cnt] = res, n -= res;
    }
    solve(1, n); printf("%d\n", cnt);
    for (int i = 1; i <= cnt; ++ i) printf("%lld ", a[i]);
    return 0;
}
