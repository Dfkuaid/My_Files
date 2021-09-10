#define DEBUG
#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 1000010;
const int INF = 0x3fffffff;

struct Task {int st, ed;};
struct Node {int ls, rs, tar, siz; Task t;};
struct Treap {
    Node p[N]; int rt, cnt;

    inline Treap() {rt = cnt = 0;}
    inline int new_node(Task t) {p[++ cnt] = (Node){0, 0, rand(), 1, t}; return cnt;}
    inline void pushup(int k) {p[k].siz = p[p[k].ls].siz + p[p[k].rs].siz + 1;}

    void split(int k, int v, int &x, int &y) {
        if (!k) {x = y = 0; return;}
        if (p[p[k].ls].siz >= v) {
            y = k; split(p[k].ls, v, x, p[k].ls);
        } else {
            x = k; split(p[k].rs, v - p[p[k].ls].siz - 1, p[k].rs, y);
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

    int find_pre(int k, Task t) {
        if (!k) return 0;
        if (p[k].t.ed >= t.st) return find_pre(p[k].ls, t);
        else return find_pre(p[k].rs, t) + p[p[k].ls].siz + 1; 
    }

    int find_nxt(int k, Task t) {
        if (!k) return 0;
        if (p[k].t.st > t.ed) return find_nxt(p[k].ls, t);
        else return find_nxt(p[k].rs, t) + p[p[k].ls].siz + 1;
    }

    inline int insert(Task t) {
        int l = find_pre(rt, t),  r = find_nxt(rt, t);
        int x = 0, y = 0, z = 0, res = 0;
        split(rt, r, x, z); split(x, l, x, y);
        int id = new_node(t);
        rt = merge(merge(x, id), z);
        res = p[y].siz; return res;
    }
} tp;

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    srand((unsigned)time(NULL));
    int n, l, r; char op; scanf("%d", &n);
    while (n --) {
        cin >> op;
        if (op == 'A') {
            scanf("%d%d", &l, &r);
            printf("%d\n", tp.insert((Task){l, r}));
        } else printf("%d\n", tp.p[tp.rt].siz);
    }
    return 0;
}