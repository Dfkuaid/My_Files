#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 20000010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1;
    char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

struct Node {int ls, rs, mx, tag;} p[N];

int cnt, n, m, a[N], rt;

inline void add(int k, int x) {
    p[k].tag += x; p[k].mx += x;
}

inline void pushdown(int k) {
    int ls = p[k].ls, rs = p[k].rs;
    if (ls) add(ls, p[k].tag);
    if (rs) add(rs, p[k].tag);
    p[k].tag = 0;
}

inline void pushup(int k) {
    p[k].mx = p[p[k].rs].mx;
}

void build(int &k, int l, int r) {
    if (!k) k = ++ cnt;
    int mid = l + r >> 1;
    if (l == r) {p[k].mx = a[l]; return;}
    build(p[k].ls, l, mid);
    build(p[k].rs, mid + 1, r); pushup(k);
}

void modify(int k, int l, int r, int x, int y, int c) {
    if (x <= l && r <= y) {add(k, c);
    return;}
    int mid = l + r >> 1; pushdown(k);
    if (x <= mid) modify(p[k].ls, l, mid, x, y, c);
    if (mid < y) modify(p[k].rs, mid + 1, r, x, y, c);
    pushup(k);
}

int get_pos(int k, int l, int r) {
    if (l == r) {return p[k].mx == l ? l : 0;}
    pushdown(k); int mid = l + r >> 1;
    int lval = p[p[k].ls].mx;
    if (lval > mid) return get_pos(p[k].ls, l, mid);
    if (lval < mid) return get_pos(p[k].rs, mid + 1, r);
    return mid;
}

int main() {
    read(m); read(n);
    for (int i = 1; i <= n; ++ i) read(a[i]);
    a[n + 1] = n + 1; build(rt, 0, n + 1); -- m;
    int pos1 = get_pos(rt, 0, n + 1);
    if (pos1 < 1 || pos1 > n) printf("NO\n");
    else printf("YES\n");
    while (m --) {
        int l, r, c; read(l); read(r); read(c);
        modify(rt, 0, n + 1, l, r, c);
        int pos = get_pos(rt, 0, n + 1);
        if (pos < 1 || pos > n) printf("NO\n");
        else printf("YES\n");
    }
    return 0;
}