#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 200010;
const int INF = 0x3fffffff;


struct Node {int ls, rs, val, cnt, tar, vlz, clz, id;} p[N];

struct T_shart {
    int v, c;
    inline bool operator < (const T_shart b) {
        return v == b.v ? c < b.c : v > b.v;
    }
} t[N];

int cnt, rt, n, m, ans[N];

inline int new_node(int id, int x) {
    p[++ cnt] = (Node){0, 0, x, 0, rand(), 0, 0, id}; return cnt;
}

inline void red(int k, int v, int c) {
    p[k].val -= v, p[k].vlz += v;
    p[k].cnt += c, p[k].clz += c;
}

inline void pushdown(int k) {
    int ls = p[k].ls, rs = p[k].rs;
    if (ls) red(ls, p[k].vlz, p[k].clz);
    if (rs) red(rs, p[k].vlz, p[k].clz);
    p[k].clz = p[k].vlz = 0;
}

void split(int k, int v, int &x, int &y) {
    if (!k) {x = y = 0; return;} pushdown(k);
    if (p[k].val <= v) x = k, split(p[k].rs, v, p[k].rs, y);
    else y = k, split(p[k].ls, v, x, p[k].ls);
}

int merge(int x, int y) {
    if (!x || !y) return x + y; 
    pushdown(x), pushdown(y);
    if (p[x].tar < p[y].tar) {
        p[x].rs = merge(p[x].rs, y); return x;
    } else {
        p[y].ls = merge(x, p[y].ls); return y;
    }
}

inline void insert(int id, int v) {
    int x = 0, y = 0; split(rt, v, x, y);
    rt = merge(merge(x, new_node(id, v)), y);
}

void insmerge(int x, int &y, int c) {
    if (!x) return; pushdown(x);
    insmerge(p[x].ls, y, c); insmerge(p[x].rs, y, c);
    p[x].ls = p[x].rs = 0; p[x].val -= c; ++ p[x].cnt;
    int k1, k2; split(y, p[x].val, k1, k2);
    y = merge(merge(k1, x), k2);
}

void get_ans(int k) {
    if (!k) return; pushdown(k);
    ans[p[k].id] = p[k].cnt;
    get_ans(p[k].ls); get_ans(p[k].rs);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i)
      scanf("%d%d", &t[i].c, &t[i].v);
    sort(t + 1, t + n + 1);
    scanf("%d", &m);
    for (int i = 1; i <= m; ++ i) {
        int x; scanf("%d", &x); insert(i, x);
    }
    for (int i = 1; i <= n; ++ i) {
        int k1 = 0, k2 = 0, k3 = 0;
        split(rt, t[i].c - 1, k1, k2);
        split(k2, (t[i].c << 1) - 1, k2, k3);
        insmerge(k2, k1, t[i].c);
        red(k3, t[i].c, 1); rt = merge(k1, k3);
    }
    get_ans(rt);
    for (int i = 1; i <= m; ++ i)
      printf("%d ", ans[i]);
    return 0;
}