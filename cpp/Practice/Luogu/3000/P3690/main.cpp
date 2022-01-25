#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 300010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

struct Node {int val, sum, rev_tag, ch[2], fa;};
struct LCT {
#define f(x) p[x].fa
#define ls(x) p[x].ch[0]
#define rs(x) p[x].ch[1]

    Node p[N];

    inline LCT() {}
    inline bool get_type(int x) {return x == p[f(x)].ch[1];}
    inline bool isroot(int x) {return ls(f(x)) != x && rs(f(x)) != x;}
    inline void pushup(int k) {p[k].sum = p[k].val ^ p[ls(k)].sum ^ p[rs(k)].sum;}
    inline void reverse(int x) {swap(p[x].ch[0], p[x].ch[1]); p[x].rev_tag ^= 1;}
    
    inline void pushdown(int x) {
        if (p[x].rev_tag) {
            if (ls(x)) reverse(ls(x));
            if (rs(x)) reverse(rs(x));
            p[x].rev_tag = 0;
        }
    }

    void update(int x) {if (!isroot(x)) update(f(x)); pushdown(x);}

    inline void rotate(int x) {
        int y = f(x), z = f(y), op = get_type(x);
        if (!isroot(y)) p[z].ch[get_type(y)] = x;
        p[y].ch[op] = p[x].ch[!op], p[p[x].ch[!op]].fa = y;
        p[x].ch[!op] = y, p[y].fa = x, p[x].fa = z;
        pushup(y), pushup(x);
    }

    inline void splay(int x) {
        update(x);
        for (int fa; fa = f(x), !isroot(x); rotate(x))
          if (!isroot(fa)) rotate(get_type(fa) == get_type(x) ? fa : x);
    }

    inline int Access(int x) {
        int t = 0;
        for (t = 0; x; t = x, x = f(x))
          splay(x), p[x].ch[1] = t, pushup(x);
        return t;
    }

    inline int find_root(int x) {
        Access(x), splay(x), pushdown(x);
        while (ls(x)) x = ls(x), pushdown(x);
        splay(x); return x;
    }

    inline void make_root(int x) {x = Access(x); reverse(x);}
    inline void link(int x, int y) {make_root(x); if (find_root(y) != x) splay(x), p[x].fa = y;}
    inline void split(int x, int y) {make_root(x); Access(y); splay(y);}
    
    inline void cut(int x, int y) {
        make_root(x);
        if (find_root(y) == x && f(y) == x && !ls(y))
          p[y].fa = p[x].ch[1] = 0, pushup(x);
    }
} lct;

int n, m;

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(m);
    for (int i = 1; i <= n; ++ i) read(lct.p[i].val);
    while (m --) {
        int op = 0, x = 0, y = 0;
        read(op), read(x), read(y);
        if (op == 0) lct.split(x, y), printf("%d\n", lct.p[y].sum);
        else if (op == 1) lct.link(x, y);
        else if (op == 2) lct.cut(x, y);
        else lct.splay(x), lct.p[x].val = y;
    }
    return 0;
}
