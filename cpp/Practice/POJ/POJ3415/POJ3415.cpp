#define LOCAL
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 500010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int k; char a[N], b[N], s[N]; ll ans;
int sa[N], rk[N], oldrk[N], px[N], id[N], cnt[N], n, ht[N];

inline void reset() {
    mset(sa, 0), mset(rk, 0), mset(oldrk, 0), mset(ht, 0);
    mset(px, 0), mset(id, 0), mset(cnt, 0); ans = 0;
    for (int i = 1; i <= n; ++ i) s[i] = '\0';
}

inline bool comp(int x, int y, int w) {
    return oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w];
}

inline void get_sa(int m) {
    int i, p, w;
    for (i = 1; i <= n; ++ i) ++ cnt[rk[i] = s[i]];
    for (i = 1; i <= m; ++ i) cnt[i] += cnt[i - 1];
    for (i = n; i >= 1; -- i) sa[cnt[rk[i]] --] = i;
    for (w = 1;; w <<= 1, m = p) {
        for (p = 0, i = n; i > n - w; --i) id[++ p] = i;
        for (i = 1; i <= n; ++ i) if (sa[i] > w) id[++ p] = sa[i] - w;
        memset(cnt, 0, sizeof(cnt));
        for (i = 1; i <= n; ++ i) ++ cnt[px[i] = rk[id[i]]];
        for (i = 1; i <= m; ++ i) cnt[i] += cnt[i - 1];
        for (i = n; i >= 1; -- i) sa[cnt[px[i]] --] = id[i];
        memcpy(oldrk, rk, sizeof(rk));
        for (p = 0, i = 1; i <= n; ++ i)
          rk[sa[i]] = comp(sa[i], sa[i - 1], w) ? p : ++ p;
        if (p == n) {for (int i = 1; i <= n; ++ i) sa[rk[i]] = i; break;}
    }
}

inline void get_height() {
    for (int i = 1, k = 0; i <= n; ++ i) {
        if (k) -- k;
        while (s[i + k] == s[sa[rk[i] - 1] + k]) ++ k;
        ht[rk[i]] = k;
    }
}

int stk[N], stp, lena, lenb; ll sum, tot[N];

void solve() {
    mset(tot, 0);
    for (int i = 1; i <= n; ++ i) {
        if (ht[i] < k) {stp = 0, sum = 0; continue;}
        while (stp && ht[stk[stp]] >= ht[i]) {
            sum -= 1ll * tot[stk[stp]] * (ht[stk[stp]] - k + 1);
            sum += 1ll * tot[stk[stp]] * (ht[i] - k + 1);
            tot[i] += tot[stk[stp]]; -- stp;
        }
        if (sa[i - 1] <= lena) sum += 1ll * (ht[i] - k + 1), ++ tot[i];
        stk[++ stp] = i; if (sa[i] > lena + 1) ans += sum;
    }
    mset(tot, 0);
    for (int i = 1; i <= n; ++ i) {
        if (ht[i] < k) {stp = 0, sum = 0; continue;}
        while (stp && ht[stk[stp]] >= ht[i]) {
            sum -= 1ll * tot[stk[stp]] * (ht[stk[stp]] - k + 1);
            sum += 1ll * tot[stk[stp]] * (ht[i] - k + 1);
            tot[i] += tot[stk[stp]]; -- stp;
        }
        if (sa[i - 1] > lena + 1) sum += 1ll * (ht[i] - k + 1), ++ tot[i];
        stk[++ stp] = i; if (sa[i] <= lena) ans += sum;
    }
}

void MAIN() {
    scanf("%s%s", a + 1, b + 1); reset();
    lena = strlen(a + 1), lenb = strlen(b + 1);
    for (int i = 1; i <= lena; ++ i) s[i] = a[i];
    n = lena + 1 + lenb; s[lena + 1] = '$';
    for (int i = 1; i <= lenb; ++ i) s[lena + 1 + i] = b[i];
    get_sa(256); get_height(); solve(); printf("%lld\n", ans);
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(k); while (k) {MAIN(); read(k);} return 0;
}
