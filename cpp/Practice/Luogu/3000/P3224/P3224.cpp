#define DEBUG
#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 1000010;
const int INF = 0x3fffffff;

struct Node {int sum, ls, rs;} p[N << 1];

int cnt, rt[N], n, m, q, id[N];

inline void pushup(int k) {
    p[k].sum = p[p[k].ls].sum + p[p[k].rs].sum;
}

void insert(int &k, int l, int r, int x) {
    if (!k) k = ++ cnt;
    ++ p[k].sum; if (l == r) return;
    int mid = (l + r) >> 1;
    if (x <= mid) insert(p[k].ls, l, mid, x);
    else insert(p[k].rs, mid + 1, r, x);
}

int tree_merge(int k1, int k2, int l, int r) {
    if (!k1 || !k2) return k1 + k2;
    if (l == r) {p[k1].sum += p[k2].sum; return k1;}
    int mid = (l + r) >> 1;
    p[k1].ls = tree_merge(p[k1].ls, p[k2].ls, l, mid);
    p[k1].rs = tree_merge(p[k1].rs, p[k2].rs, mid + 1, r);
    pushup(k1); return k1;
}

struct UFS {
    int fa[N], siz[N];

    inline void init(int x) {
        for (int i = 1; i <= x; ++ i)
          fa[i] = i, siz[i] = 1;
    }

    inline int find(int x) {
        while (x != fa[x]) x = fa[x] = fa[fa[x]];
        return x;
    }

    inline void merge(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx == fy) return;
        if (siz[fx] > siz[fy]) swap(fx, fy);
        siz[fy] += siz[fx]; fa[fx] = fy;
        rt[fy] = tree_merge(rt[fy], rt[fx], 1, n);
    }
} ufs;

int query(int k, int l, int r, int x) {
    if (l == r) return l;
    int mid = (l + r) >> 1, lsum = p[p[k].ls].sum;
    if (x <= lsum) return query(p[k].ls, l, mid, x);
    else return query(p[k].rs, mid + 1, r, x - lsum);
}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    scanf("%d%d", &n, &m); ufs.init(n);
    for (int i = 1; i <= n; ++ i) {
        int x; scanf("%d", &x);
        insert(rt[i], 1, n, x);
        id[x] = i;
    }
    for (int i = 1; i <= m; ++ i) {
        int u, v; scanf("%d%d", &u, &v);
        ufs.merge(u, v);
    } scanf("%d", &q);
    while (q --) {
        char op; int x, y; cin >> op >> x >> y;
        if (op == 'Q') {
            int fx = ufs.find(x);
            if (p[rt[fx]].sum >= y)
              printf("%d\n", id[query(rt[fx], 1, n, y)]);
            else printf("-1\n");
        } else ufs.merge(x, y);
    }
    return 0;
}