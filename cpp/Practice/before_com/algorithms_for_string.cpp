#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

inline void build_sa(int m) {
    int i, p, w;
    for (i = 1; i <= n; ++ i) ++ cnt[rk[i] = s[i]];
    for (i = 1; i <= m; ++ i) cnt[i] += cnt[i - 1];
    for (i = n; i >= 1; -- i) sa[cnt[rk[i]] --] = i;
    for (w = 1; ; w <<= 1, m = p) {
        for (p = 0, i = n; i > n - w; -- i) id[++ p] = i;
        for (i = 1; i <= n; ++ i) if (sa[i] > w) id[++ p] = sa[i] - w;
        memset(cnt, 0, sizeof cnt);
        for (i = 1; i <= n; ++ i) ++ cnt[px[i] = rk[id[i]]];
        for (i = 1; i <= m; ++ i) cnt[i] += cnt[i - 1];
        for (i = n; i >= 1; -- i) sa[cnt[px[i]] --] = id[i];
        memcpy(oldrk, rk, sizeof rk);
        for (p = 0, i = 1; i <= n; ++ i)
          rk[i] = cmp(sa[i], sa[i - 1], w) ? p : ++ p;
        if (p == n) {for (i = 1; i <= n; ++ i) rk[sa[i]] = i; break;}
    }
}

inline void build_height() {
    for (int i = 1, k = 0; i <= n; ++ i) {
        if (k) -- k;
        while (s[sa[rk[i] - 1] + k] == s[i + k]) ++ k;
        ht[rk[i]] = k;
    }
}

inline void SA_and_height() {

}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    return 0;
}