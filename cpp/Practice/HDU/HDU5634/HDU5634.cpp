#define DEBUG
#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 700010;
const int M = 10000010;
const int INF = 0x3fffffff;

struct Node {
    int ls, rs; ll sum, tag;

    inline Node() {ls = rs = sum = tag = 0;}
    inline void del() {ls = rs = sum = tag = 0;}
} p[N];

int T, n, m, cnt, phi[M], prm[N];
int rt, pcnt, nprm[M]; ll a[N]; 

void Get_Phi(int x) {
    phi[1] = 1;
    for (int i = 2; i <= x; ++ i) {
        if (!nprm[i]) prm[++ pcnt] = i, phi[i] = i - 1;
        for (int j = 1; j <= pcnt; ++ j) {
            if (prm[j] * i > x) {break;} nprm[prm[j] * i] = true;
            if (i % prm[j]) phi[prm[j] * i] = phi[i] * (prm[j] - 1);
            else {phi[prm[j] * i] = phi[i] * prm[j]; break;}
        }
    }
}

inline void clear() {
    for (int i = 1; i <= cnt; ++ i) p[i].del();
    cnt = 0;
}

inline void pushup(int k) {
    int ls = p[k].ls, rs = p[k].rs;
    p[k].sum = p[ls].sum + p[rs].sum;
    if (p[ls].tag && p[ls].tag == p[rs].tag)
      p[k].tag = p[ls].tag;
    else p[k].tag = 0;
}

inline void cover(int k, ll x, int l, int r) {
    p[k].tag = x, p[k].sum = 1ll * (r - l + 1) * x;
}

inline void pushdown(int k, int l, int r) {
    int ls = p[k].ls, rs = p[k].rs, mid = (l + r) >> 1;
    if (p[k].tag) {
        if (ls) cover(ls, p[k].tag, l, mid);
        if (rs) cover(rs, p[k].tag, mid + 1, r);
    }
}

void build(int &k, int l, int r) {
    if (!k) {k = ++ cnt;}
    if (l == r) {p[k].tag = p[k].sum = a[l]; return;}
    int mid = (l + r) >> 1;
    build(p[k].ls, l, mid); build(p[k].rs, mid + 1, r);
    pushup(k);
}

void recover(int k, int l, int r, int x, int y, ll c) {
    if (x <= l && r <= y) {cover(k, c, l, r); return;}
    int mid = l + r >> 1; pushdown(k, l, r);
    if (x <= mid) recover(p[k].ls, l, mid, x, y, c);
    if (mid < y) recover(p[k].rs, mid + 1, r, x, y, c);
    p[k].tag = 0; pushup(k);
}

void Change_to_Phi(int k, int l, int r, int x, int y) {
    if (x <= l && r <= y && p[k].tag) {
        cover(k, phi[p[k].tag], l, r); return;
    }
    int mid = (l + r) >> 1; pushdown(k, l, r);
    if (x <= mid) Change_to_Phi(p[k].ls, l, mid, x, y);
    if (mid < y) Change_to_Phi(p[k].rs, mid + 1, r, x, y);
    pushup(k);
}

ll query(int k, int l, int r, int x, int y) {
    if (x <= l && r <= y) return p[k].sum;
    int mid = (l + r) >> 1; ll res = 0; pushdown(k, l, r);
    if (x <= mid) res += query(p[k].ls, l, mid, x, y);
    if (mid < y) res += query(p[k].rs, mid + 1, r, x, y);
    return res;
}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    Get_Phi(1e7); scanf("%d", &T);
    while (T --) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++ i)
          scanf("%d", &a[i]);
        build(rt, 1, n); int id, l, r, x;
        while (m --) {
            scanf("%d%d%d", &id, &l, &r);
            if (id == 1) Change_to_Phi(rt, 1, n, l, r);
            else if (id == 2){
                scanf("%d", &x); recover(rt, 1, n, l, r, x);
            } else printf("%lld\n", query(rt, 1, n, l, r));
        }
    }
    return 0;
}