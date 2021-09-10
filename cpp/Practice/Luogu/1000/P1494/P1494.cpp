#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

int n, m, len, c[N];
ll ans[N][2], sum, cnt[N];

struct Query {
    int l, r, id;

    inline bool operator < (const Query &b) const {
        if (l / len != b.l / len) return l < b.l;
        if ((l / len) & 1) return r < b.r;
        return r > b.r;
    }
};
Query q[N];

inline void add(int i) {
    sum += cnt[i];
    cnt[i] ++;
}

inline void del(int i) {
    cnt[i] --;
    sum -= cnt[i];
}

inline ll gcd(ll x, ll y) {
    return y ? gcd(y, x % y) : x;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++)
      scanf("%d", &c[i]);
    for (int i = 1; i <= m; i ++) {
        scanf("%d%d", &q[i].l, &q[i].r);
        q[i].id = i;
    }
    len = sqrt(n);
    sort(q + 1, q + m + 1);
    for (int i = 1, l = 1, r = 0; i <= m; ++ i) {
        if (q[i].l == q[i].r) {
            ans[q[i].id][0] = 0, ans[q[i].id][1] = 1;
            continue;
        }
        while (l > q[i].l) add(c[-- l]);
        while (r < q[i].r) add(c[++ r]);
        while (l < q[i].l) del(c[l ++]);
        while (r > q[i].r) del(c[r --]);
        ans[q[i].id][0] = sum;
        ans[q[i].id][1] = (ll)(r - l + 1) * (r - l) / 2;
    }
    for (int i = 1; i <= m; ++ i) {
        if (ans[i][0]) {
            ll g = gcd(ans[i][0], ans[i][1]);
            printf("%lld/%lld\n", ans[i][0] / g, ans[i][1] / g);
        } else {
            ans[i][1] = 1;
            printf("%lld/%lld\n", ans[i][0], ans[i][1]);
        }
    }
    return 0;
}