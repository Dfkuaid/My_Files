#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 500010;
const int M = 11000010;
const int INF = 0x3fffffff;

struct Node {int ls, rs, tot; ll sum;} p[M];

int cnt, rt[N], n, m, maxl = 1e6 + 5;

inline int clone(int k) {p[++ cnt] = p[k]; return cnt;}

inline void pushup(int k) {
    int ls = p[k].ls, rs = p[k].rs;
    p[k].sum = p[ls].sum + p[rs].sum;
    p[k].tot = p[ls].tot + p[rs].tot;
}

int insert(int k, int l, int r, int x) {
    k = clone(k); int mid = l + r >> 1;
    if (l == r) {p[k].sum = x, ++ p[k].tot; return k;}
    if (x <= mid) p[k].ls = insert(p[k].ls, l, mid, x);
    else p[k].rs = insert(p[k].rs, mid + 1, r, x);
    pushup(k); return k;
}

ll query(int k1, int k2, int l, int r, int x, int y, int st) {
    if (p[k2].tot - p[k1].tot == 0) return 0;
    ll siz = p[k2].tot - p[k1].tot;
    ll sum = p[k2].sum - p[k1].sum;
    if (l >= st + x - 1) return sum - ((st << 1) + x + y - 2) * siz / 2;
    if (r <= st + y - 1) return ((st << 1) + x + y - 2) * siz / 2 - sum;
    int mid = l + r >> 1, lsz = p[p[k2].ls].tot - p[p[k1].ls].tot;
    return query(p[k1].ls, p[k2].ls, l, mid, x, x + lsz - 1, st)
           + query(p[k1].rs, p[k2].rs, mid + 1, r, x + lsz, y, st);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i) {
        int x; scanf("%d", &x);
        rt[i] = insert(rt[i - 1], 1, maxl, x);
    }
    for (int i = 1; i <= m; ++ i) {
        int l, r, K; scanf("%d%d%d", &l, &r, &K);
        printf("%lld\n", query(rt[l - 1], rt[r], 1, maxl, 1, r - l + 1, K));
    }
    return 0;
}