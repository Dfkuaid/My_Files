#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 500010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int prm[N], nprm[N], ncnt;

inline void euler(int x) {
    for (int i = 2; i <= x; ++ i) {
        if (!nprm[i]) prm[++ ncnt] = i;
        for (int j = 1; j <= ncnt; ++ j) {
            if (prm[j] * i > x) break;
            nprm[i * prm[j]] = 1;
            if (!(i % prm[j])) break;
        }
    }
}

int t, n;

#define lb(l, len, x) lower_bound(l + 1, l + len + 1, x)

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    euler(5e5); read(t);
    while (t --) {
        read(n);
        int pos1 = lb(prm, ncnt, n + 1) - prm;
        int prm1 = prm[pos1];
        int pos2 = lb(prm, ncnt, prm1 + n) - prm;
        int prm2 = prm[pos2];
        printf("%lld\n", 1ll * prm1 * prm2);
    }
    return 0;
}
