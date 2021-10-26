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

int T; ll n, x, a, b, cnt, ans;

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(T);
    while (T --) {
        read(n), read(x), read(a), read(b);
        if (1ll * a * x <= b && 1ll * a * x <= n) puts("-1");
        else if (x > n) puts("0");
        else {
            if (a != 1) {
                ll c = 0;
                if (n >= 1ll * a * x) {
                    ll A = 1ll * a * x;
                    ll k = (1ll * a * x - b);
                    ll t = (n - A) / k + 1;
                    c += t * a; n -= t * k;
                }
                if (n >= x) c += n / x;
                printf("%lld\n", c);
			} else { 
                ll t = (n - x) / (x - b) + 1;
                printf("%lld\n", t);
			}
		}
    }
    return 0;
}   
