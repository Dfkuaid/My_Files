#define DEBUG
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const ll INF = 1e18;
const int N = 1000010;
const int ULIMIT = 1e6 + 1;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for(; !isdigit(c); c = getchar()) if(c == '-') f = -f;
    for(; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T>
inline T Min(const T a, const T b) {return a < b ? a : b;}

int n; ll A, B;

struct Node {
    int ls, rs; ll mna, mnb, val, rec;
    inline Node() {ls = rs = 0, mna = mnb = val = rec = 0;}
};

struct SegmentTree {
    Node p[N << 1]; int rt, cnt;

    inline SegmentTree() {rt = cnt = 0;}
    inline void update_cov(int k, ll x) {
        p[k].mna = p[k].mnb = p[k].val = p[k].rec = x;
    }

    inline void pushdown(int k) {
        int ls = p[k].ls, rs = p[k].rs;
        if (p[k].rec) {
            if (ls) update_cov(ls, p[k].rec);
            if (rs) update_cov(rs, p[k].rec);
            p[k].rec = 0;
        }
    }

    inline void pushup(int k) {
        int ls = p[k].ls, rs = p[k].rs;
        p[k].val = Min(p[ls].val, p[rs].val);
        p[k].mna = Min(p[ls].mna, p[rs].mna);
        p[k].mnb = Min(p[ls].mnb, p[rs].mnb);
    }

    void recover(int k, int l, int r, int x, int y, ll c) {
        if (x <= l && r <= y) {update_cov(k, c); return;}
        int mid = l + r >> 1; pushdown(k);
        if (x <= mid) recover(p[k].ls, l, mid, x, y, c);
        if (mid < y) recover(p[k].rs, mid + 1, r, x, y, c);
        pushup(k);
    }

    void update_val(int k, int l, int r, ll x, ll c) {
        if (l == r) {
            p[k].mna = Min(p[k].mna, c + x * A);
            p[k].mnb = Min(p[k].mnb, c - x * B);
            p[k].val = Min(p[k].val, c); return;
        }
        int mid = l + r >> 1; pushdown(k);
        if (x <= mid) update_val(p[k].ls, l, mid, x, c);
        else update_val(p[k].rs, mid + 1, r, x, c);
        pushup(k);
    }

    ll get_val(int k, int l, int r, int x, int y, int op) {
        if (x <= l && r <= y) return op ? p[k].mnb : p[k].mna;
        int mid = l + r >> 1; ll res = INF; pushdown(k);
        if (x <= mid) res = Min(res, get_val(p[k].ls, l, mid, x, y, op));
        if (mid < y) res = Min(res, get_val(p[k].rs, mid + 1, r, x, y, op));
        return res;
    }

    void build(int &k, int l, int r) {
        if (!k) k = ++ cnt;
        if (l == r) {
            if (l == 0 || r == ULIMIT) {p[k].mna = p[k].mnb = p[k].val = INF; return;}
            p[k].val = 0; p[k].mna = l * A; p[k].mnb = -l * B; return;
        }
        int mid = (l + r) >> 1;
        build(p[k].ls, l, mid); build(p[k].rs, mid + 1, r); pushup(k);
    }

    inline ll get_ans() {return p[rt].val;}
} t;

int L[N], R[N], sec[N][2], scnt;

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    read(n); read(A); read(B); t.build(t.rt, 0, ULIMIT);
    for (int i = 1; i <= n; ++ i) {
        int k; read(k); scnt = 0;
        for (int j = 1; j <= k; ++ j) {
            int l, r; ll val = -1; read(l); read(r);
            L[++ scnt] = l, R[scnt] = r;
            val = t.get_val(t.rt, 0, ULIMIT, 0, l - 1, 1);
            t.update_val(t.rt, 0, ULIMIT, l, val + l * B);
            val = t.get_val(t.rt, 0, ULIMIT, l + 1, ULIMIT, 0);
            t.update_val(t.rt, 0, ULIMIT, l, val - l * A);
            val = t.get_val(t.rt, 0, ULIMIT, 0, r - 1, 1);
            t.update_val(t.rt, 0, ULIMIT, r, val + r * B);
            val = t.get_val(t.rt, 0, ULIMIT, r + 1, ULIMIT, 0);
            t.update_val(t.rt, 0, ULIMIT, r, val - r * A);
        }
        t.recover(t.rt, 0, ULIMIT, 0, L[1] - 1, INF);
        t.recover(t.rt, 0, ULIMIT, R[scnt] + 1, ULIMIT, INF);
        for (int i = 1; i <= scnt - 1; ++ i) {
            int l = R[i] + 1, r = L[i + 1] - 1;
            if (l > r) continue;
            t.recover(t.rt, 0, ULIMIT, l, r, INF);
        }
    }
    printf("%lld", t.get_ans()); return 0;
}