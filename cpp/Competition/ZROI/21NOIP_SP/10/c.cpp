#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 10000010;
const ll MOD = 2147483647;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

struct Node {int ls, rs, val;} p[N];

ll n, m, G, R, q, len[N], s[N], sp[N], lst, pcnt, f[N]; int rt;

void insert(int &k, int l, int r, int x, int c) {
    if (!k) k = ++ pcnt; p[k].val = c;
    if (l == r) return; int mid = l + r >> 1;
    if (x <= mid) insert(p[k].ls, l, mid, x, c);
    else insert(p[k].rs, mid + 1, r, x, c);
}

int query(int k, int l, int r, int x, int y) {
    if (!k) return n + 1; if (x <= l && r <= y) return p[k].val;
    int mid = l + r >> 1, res = INF;
    if (x <= mid) res = min(res, query(p[k].ls, l, mid, x, y));
    if (mid < y) res = min(res, query(p[k].rs, mid + 1, r, x, y));
    return res;
}

ll dist(int x, int y) {return y == n + 1 ? s[y] - s[x] : (s[y] - s[x] + m - 1) / m * m;}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(G), read(R); m = G + R;
    for (int i = 1; i <= n + 1; ++ i) read(len[i]);
    for (int i = 1; i <= n + 1; ++ i)
      s[i] = s[i - 1] + len[i], sp[i] = s[i] % m; 
    for (int i = n; i; -- i) {
        int l = (sp[i] + G) % m, r = (l + R - 1) % m, pos = 0;
        if (l > r) pos = min(query(rt, 0, m - 1, 0, r), query(rt, 0, m - 1, l, m - 1));
        else pos = query(rt, 0, m - 1, l, r);
        f[i] = dist(i, pos) + f[pos]; insert(rt, 0, m - 1, sp[i], i);
    }
    read(q);
    while (q --) {
        ll x; read(x); x ^= (lst % MOD); s[0] = -x; int pos = 0;
        int l = (0ll + m - x % m + G) % m, r = (l + R - 1) % m;
        if (l > r) pos = min(query(rt, 0, m - 1, 0, r), query(rt, 0, m - 1, l, m - 1));
        else pos = query(rt, 0, m - 1, l, r);
        printf("%lld\n", lst = dist(0, pos) + f[pos]);
    }
    return 0;
}
