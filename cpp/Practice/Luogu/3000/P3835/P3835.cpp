#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 500010;
const int INF = 0x3fffffff;

struct Node {int ls, rs, val, tar, siz;} p[N << 6];

int n, cnt, rt[N];

inline int new_node(int x) {p[++ cnt] = (Node){0, 0, x, rand(), 1}; return cnt;}

inline void pushup(int k) {
    p[k].siz = p[p[k].ls].siz + p[p[k].rs].siz + 1;
}

void split(int k, int v, int &x, int &y) {
    if (!k) {x = y = 0; return;}
    int pos = ++ cnt; p[pos] = p[k];
    if (p[pos].val <= v) {
        x = pos; split(p[pos].rs, v, p[pos].rs, y);
    } else {
        y = pos; split(p[pos].ls, v, x, p[pos].ls);
    } pushup(pos);
}

int merge(int x, int y) {
    if (!x || !y) return x + y;
    if (p[x].tar < p[y].tar) {
        int pos = ++ cnt; p[pos] = p[x];
        p[pos].rs = merge(p[pos].rs, y);
        pushup(pos); return pos;
    } else {
        int pos = ++ cnt; p[pos] = p[y];
        p[pos].ls = merge(x, p[pos].ls);
        pushup(pos); return pos;
    }
}

inline void insert(int &root, int v) {
    int x = 0, y = 0; split(root, v, x, y);
    root = merge(merge(x, new_node(v)), y);
}

inline void del(int &root, int v) {
    int x = 0, y = 0, z = 0;
    split(root, v, x, z);
    split(x, v - 1, x, y);
    y = merge(p[y].ls, p[y].rs);
    root = merge(merge(x, y), z);
}

inline int pre(int &root, int v) {
    int x = 0, y = 0, pos; split(root, v - 1, x, y);
    if (!x) return -2147483647;
    pos = x; while (p[pos].rs) pos = p[pos].rs;
    root = merge(x, y); return p[pos].val;
}

inline int nxt(int &root, int v) {
    int x = 0, y = 0, pos; split(root, v, x, y);
    if (!y) return 2147483647;
    pos = y; while (p[pos].ls) pos = p[pos].ls;
    root = merge(x, y); return p[pos].val;
}

inline int kth(int k, int v) {
    while (true) {
        if (p[p[k].ls].siz >= v) k = p[k].ls;
        else if (p[p[k].ls].siz + 1 == v) return p[k].val;
        else v -= p[p[k].ls].siz + 1, k = p[k].rs;
    }
}

int rk(int &root, int v) {
    int x = 0, y = 0; split(root, v - 1, x, y);
    int res = p[x].siz + 1; root = merge(x, y);
    return res;
}

int main() {
    srand((unsigned)(time(NULL)));
    scanf("%d", &n); int v, op, x;
    for (int i = 1; i <= n; ++ i) {
        scanf("%d%d%d", &v, &op, &x);
        rt[i] = rt[v];
        if (op == 1) insert(rt[i], x);
        else if (op == 2) del(rt[i], x);
        else if (op == 3) printf("%d\n", rk(rt[i], x));
        else if (op == 4) printf("%d\n", kth(rt[i], x));
        else if (op == 5) printf("%d\n", pre(rt[i], x));
        else printf("%d\n", nxt(rt[i], x));
    }
    return 0;
}