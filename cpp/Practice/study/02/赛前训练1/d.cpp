#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

struct Node {int ls, rs, len, val, lazy;};
struct SegmentTree {
    Node p[N]; int cnt, rt;
    
    inline SegmentTree() {cnt = rt = 0;}
    inline void pushup(int k) {
        p[k].val = p[p[k].ls].val + p[p[k].rs].val;
    }

    inline void pushdown(int k) {
        int ls = p[k].ls, rs = p[k].rs;
        if (p[k].lazy) {
            p[ls].lazy += p[k].lazy;
            p[ls].val += p[ls].len * p[k].lazy;
            p[rs].lazy += p[k].lazy;
            p[rs].val += p[rs].len * p[k].lazy;
            p[k].lazy = 0;
        }
    }

    void build(int &k, int l, int r) {
        if (!k) k = ++ cnt; int mid = l + r >> 1;
        p[k].val = p[k].lazy = 0, p[k].len = r - l + 1;
        build(p[k].ls, l, mid); build(p[k].rs, r, mid);
    }

    void modify(int k, int l, int r, int x, int y, int c) {
        if (x <= l && r <= y) {p[k].lazy += c; return;}
        int mid = l + r >> 1;
        if (x <= mid) modify(p[k].ls, l, mid, x, y, c);
        if (y > mid) modify(p[k].rs, mid + 1, r, x, y, c);
        pushup(k);
    }

    int query(int k, int l, int r, int x, int y) {
        if (x <= l && r <= y) return p[k].val;
        int mid = l + r >> 1, res = 0;
        if (x <= mid) res += query(p[k].ls, l, mid, x, y);
        if (y > mid) res += query(p[k].rs, mid + 1, r, x, y);
        return res;
    }
} t[40];

int t, n, m, nprm[N], prm[N], pcnt;

void pre_euler(int x) {
    for (int i = 2; i <= x; ++ i) {
        if (!nprm[i]) prm[++ pcnt] = i;
        for (int j = 1; j <= pcnt; ++ j) {
            if (prm[j] * i > x) break;
            nprm[prm[j] * i] = true;
            if (!(i % prm[j])) break;
        }
    }
}

inline void reset() {

}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(t); pre_euler(150);
    while (t --) {
        read(n); read(m);
        while (m --) {
            int op, l, r, x;
            read(op), read(l), read(r), read(x);
        }
    }
    return 0;
}
