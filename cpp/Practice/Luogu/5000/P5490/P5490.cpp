#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 300010;
const int INF = 0x3fffffff;

struct SLine {
    ll l, r, h, w;
    bool operator < (const SLine &b) const {
        return h < b.h;
    }
};
SLine line[N];

struct Node {
    int l, r;
    int ls, rs;
    ll len, sum;
};
Node p[N << 1];

int cnt, n;
ll X[N];

inline void pushup(int k) {
    if (p[k].sum) p[k].len = X[p[k].r + 1] - X[p[k].l];
    else p[k].len = p[p[k].ls].len + p[p[k].rs].len;
}

void build(int k, int l, int r) {
    p[k].l = l, p[k].r = r;
    p[k].len = p[k].sum = 0;
    if (l == r) return;
    int mid = (l + r) >> 1;
    p[k].ls = ++ cnt;
    build(p[k].ls, l, mid);
    p[k].rs = ++ cnt;
    build(p[k].rs, mid + 1, r);
}

void modify(int k, ll x, ll y, int c) {;
    if (y <= X[p[k].l] || x >= X[p[k].r + 1]) return;
    if (x <= X[p[k].l] && X[p[k].r + 1] <= y) {
        p[k].sum += c;
        pushup(k); return;
    }
    modify(p[k].ls, x, y, c);
    modify(p[k].rs, x, y, c);
    pushup(k);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) {
        ll a1, a2, b1, b2;
        scanf("%lld%lld%lld%lld", &a1, &b1, &a2, &b2);
        X[2 * i - 1] = a1, X[2 * i] = a2;
        line[2 * i - 1] = (SLine) {a1, a2, b1, 1};
        line[2 * i] = (SLine) {a1, a2, b2, -1};
    }
    n <<= 1;
    sort(line + 1, line + n + 1);
    sort(X + 1, X + n + 1);
    int tot = unique(X + 1, X + n + 1) - X - 1;
    build(++ cnt, 1, tot - 1);
    ll ans = 0;
    for (int i = 1; i < n; i ++) {
        modify(1, line[i].l, line[i].r, line[i].w);
        ans += (line[i + 1].h - line[i].h) * p[1].len;
    }
    printf("%lld", ans);
    return 0;
}