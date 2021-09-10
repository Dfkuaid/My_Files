#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 1000010;
const int INF = 0x3fffffff;

struct Node {
    int ls, rs;
    int l, r;
    ll sum;
};
Node p[N << 2];

int n, m, tot, bac[N], cnt, tcnt = 1, rt[N];

inline int NEW() {return tot ? bac[tot --] : ++ cnt;}

inline void del(int k) {
    bac[++ tot] = k, p[k].ls = p[k].rs = p[k].sum = 0;
}

void modify (int &k, int l, int r, int pos, int ts) {
    if (!k) k = NEW();
    p[k].sum += ts;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (pos <= mid) modify(p[k].ls, l, mid, pos, ts);
    else modify(p[k].rs, mid + 1, r, pos, ts);
}

ll query (int k, int l, int r, int x, int y) {
    if (x <= l && r <= y) return p[k].sum;
    ll res = 0, mid = (r + l) >> 1;
    if (x <= mid) res += query(p[k].ls, l, mid, x, y);
    if (mid < y) res += query(p[k].rs, mid + 1, r, x, y);
    return res;
}

int kth (int k, int l, int r, int x) {
    if (l == r) return l;
    int mid = (l + r) >> 1;
    if (p[p[k].ls].sum >= x) return kth(p[k].ls, l, mid, x);
    else return kth(p[k].rs, mid + 1, r, x - p[p[k].ls].sum);
}

int merge (int x, int y) {
    if (!x || !y) return x + y;
    p[x].sum += p[y].sum;
    p[x].ls = merge(p[x].ls, p[y].ls);
    p[x].rs = merge(p[x].rs, p[y].rs);
    del(y);
    return x;
}

void split (int x, int &y, ll k) {
    if (!x) return;
    y = NEW();
    ll v = p[p[x].ls].sum;
    if (k > v) split(p[x].rs, p[y].rs, k - v);
    else swap(p[x].rs, p[y].rs);
    if (k < v) split(p[x].ls, p[y].ls, k);
    p[y].sum = p[x].sum - k, p[x].sum = k;
}

int main () {
//    freopen("P5494_1.in", " r", stdin);
//    freopen("out.txt", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++) {
        int x; scanf("%d", &x);
        modify(rt[1], 1, n, i, x);
    }
    for (int i = 1; i <= m; i ++) {
        int opt, x, y, z; scanf("%d", &opt);
        if (opt == 0) {
            scanf("%d%d%d", &x, &y, &z);
            ll k1 = query(rt[x], 1, n, 1, z), k2 = query(rt[x], 1, n, y, z);
            int tmp = 0;
            split(rt[x], rt[++ tcnt], k1 - k2);
            split(rt[tcnt], tmp, k2);
            rt[x] = merge(rt[x], tmp);
        } else if (opt == 1) {
            scanf("%d%d", &x, &y);
            rt[x] = merge(rt[x], rt[y]);
        } else if (opt == 2) {
            scanf("%d%d%d", &x, &y, &z);
            modify(rt[x], 1, n, z, y);
        } else if (opt == 3) {
            scanf("%d%d%d", &x, &y, &z);
            printf("%lld\n", query(rt[x], 1, n, y, z));
        } else if (opt == 4) {
            scanf("%d%d", &x, &y);
            if (p[rt[x]].sum < y) {printf("-1\n"); continue;}
            printf("%d\n", kth(rt[x], 1, n, y));
        }
    }
    return 0;
}