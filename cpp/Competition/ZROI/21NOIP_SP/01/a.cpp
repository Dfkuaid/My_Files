#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 100010;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

ll p, q, a, b, c, d, w;

ll fpow(ll x, ll y, ll c) {
    ll res = 1;
    while (y) {
        if (y & 1) (res *= x) %= c;
        y >>= 1, (x *= x) %= c;
    }
    return res;
}

int get_digit(ll x) {
    int res = 0; while (x) ++ res, x >>= 1; return res;
}

int main() {
#ifdef LOCAL
    freopen("my.in", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(p); read(q); w = get_digit(p);
    while (q --) {
        read(a); read(b); read(c); read(d);
        if ((a + b) % p != (c + d) % p) {puts("-1"); continue;}
        ll sum = (a + b) % p, inv = fpow(sum, p - 2, p);
        for (int i = 0; i <= w; ++ i) {
            ll now = ((1ll << i) * a % p - c + p) % p * inv % p;
            int now_cnt = get_digit(now);
            if (now_cnt <= i) {printf("%lld\n", i); break;}
        }
    }
    return 0;
}
