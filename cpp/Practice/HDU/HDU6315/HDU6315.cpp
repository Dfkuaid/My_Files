#define DEBUG
#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 500010;
const int INF = 0x3fffffff;

template <typename T>
inline T Min(const T a, const T b) {return a < b ? a : b;}

struct Node {
    int ls, rs, mn, lz, sum;
    inline Node() {ls = rs = mn = lz = sum = 0;}
    inline void del() {ls = rs = mn = lz = sum = 0;}
} p[N];

int n, q, cnt, rt, b[N];

inline void Reset() {
    for (int i = 1; i <= cnt; ++ i) p[i].del();
    cnt = rt = 0;
}

inline void pushup(int k) {
    if (!p[k].ls || !p[k].rs) return;
    p[k].mn = Min(p[p[k].ls].mn, p[p[k].rs].mn);
    p[k].sum = p[p[k].ls].sum + p[p[k].rs].sum;
}

inline void pushdown(int k) {
    int ls = p[k].ls, rs = p[k].rs;
    if (p[k].lz) {
        if (ls) p[ls].lz += p[k].lz, p[ls].mn -= p[k].lz;
        if (rs) p[rs].lz += p[k].lz, p[rs].mn -= p[k].lz;
        p[k].lz = 0;
    }
}

void update(int k, int l, int r) {
    if (l == r) {++ p[k].sum, p[k].mn = b[l]; return;}
    pushdown(k); int mid = (l + r) >> 1;
    if (!p[p[k].ls].mn) update(p[k].ls, l, mid);
    if (!p[p[k].rs].mn) update(p[k].rs, mid + 1, r);
    pushup(k);
}

inline void add(int k, int l, int r, int c) {
    p[k].lz += c, p[k].mn -= c;
    if (!p[k].mn) pushdown(k), update(k, l, r), pushup(k);
}

void build(int &k, int l, int r) {
    if (!k) k = ++ cnt;
    if (l == r) {p[k].mn = b[l]; return;}
    int mid = (l + r) >> 1; build(p[k].ls, l, mid);
    build(p[k].rs, mid + 1, r); pushup(k);
}

void modify(int k, int l, int r, int x, int y, int c) {
    if (x <= l && r <= y) {add(k, l, r, c); return;}
    int mid = (l + r) >> 1; pushdown(k);
    if (x <= mid) modify(p[k].ls, l, mid, x, y, c);
    if (mid < y) modify(p[k].rs, mid + 1, r, x, y, c);
    pushup(k);
}

int query(int k, int l, int r, int x, int y) {
    if (x <= l && r <= y) return p[k].sum;
    int mid = (l + r) >> 1, res = 0; pushdown(k);
    if (x <= mid) res += query(p[k].ls, l, mid, x, y);
    if (mid < y) res += query(p[k].rs, mid + 1, r, x, y);
    return res;
}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    while (~scanf("%d%d", &n, &q)) {
        for (int i = 1; i <= n; ++ i) scanf("%d", &b[i]);
        Reset(); build(rt, 1, n); char s[10]; int l, r;
        while (q --) {
            scanf("%s%d%d", s, &l, &r);
            if (s[0] == 'a') modify(rt, 1, n, l, r, 1);
            else printf("%d\n", query(rt, 1, n, l, r));
        }
    }
    return 0;
}