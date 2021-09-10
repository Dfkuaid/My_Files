#define DEBUG
#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 1100010;
const int INF = 0x3fffffff;

struct Node {int val, tar, siz, ls, rs;} p[N];

int n, m, cnt, rt, lst, ans;

inline void pushup(int k) {p[k].siz = p[p[k].ls].siz + p[p[k].rs].siz + 1;}
inline int new_node(int x) {p[++ cnt] = (Node){x, rand(), 1, 0, 0}; return cnt;}

void split(int k, int v, int &x, int &y) {
    if (!k) {x = y = 0; return;}
    if (p[k].val <= v) {
        x = k; split(p[k].rs, v, p[k].rs, y);
    } else {
        y = k; split(p[k].ls, v, x, p[k].ls);
    } pushup(k);
}

int merge(int x, int y) {
    if (!x || !y) return x + y;
    if (p[x].tar < p[y].tar) {
        p[x].rs = merge(p[x].rs, y);
        pushup(x); return x;
    } else {
        p[y].ls = merge(x, p[y].ls);
        pushup(y); return y;
    }
}

inline void insert(int v) {
    int x = 0, y = 0; split(rt, v, x, y);
    rt = merge(merge(x, new_node(v)), y);
}

inline void del(int v) {
    int x = 0, y = 0, z = 0;
    split(rt, v, x, z);
    split(x, v - 1, x, y);
    y = merge(p[y].ls, p[y].rs);
    rt = merge(merge(x, y), z);
}

void rk(int v) {
    int x = 0, y = 0; split(rt, v - 1, x, y);
    lst = (p[x].siz + 1); rt = merge(x, y);
}

inline int kth(int k, int v) {
    while (true) {
        if (p[p[k].ls].siz >= v) k = p[k].ls;
        else if (p[p[k].ls].siz + 1 == v) return p[k].val;
        else v -= p[p[k].ls].siz + 1, k = p[k].rs;
    }
}

inline int pre(int v) {
    int x = 0, y = 0, pos; split(rt, v - 1, x, y);
    pos = x; while (p[pos].rs) pos = p[pos].rs;
    merge(x, y); return p[pos].val;
}

inline int nxt(int v) {
    int x = 0, y = 0, pos; split(rt, v, x, y);
    pos = y; while (p[pos].ls) pos = p[pos].ls;
    merge(x, y); return p[pos].val;
}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    srand((unsigned)time(NULL));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i) {
        int x; scanf("%d", &x); insert(x);
    }
    while (m --) {
        int opt, x; scanf("%d%d", &opt, &x); x ^= lst;
        if (opt == 1) insert(x);
        else if (opt == 2) del(x);
        else if (opt == 3) rk(x);
        else if (opt == 4) lst = kth(rt, x);
        else if (opt == 5) lst = pre(x);
        else lst = nxt(x);
        if (opt >= 3) ans ^= lst;
    }
    printf("%d", ans);
    return 0;
}