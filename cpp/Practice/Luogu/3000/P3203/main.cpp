#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 200010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

struct Node {int siz, ch[2], fa;};

struct LCT {
#define ls(x) p[x].ch[0]
#define rs(x) p[x].ch[1]
#define f(x) p[x].fa

    Node p[N]; int siz;

    inline LCT() {siz = 0;}
    inline void init(int _siz) {siz = _siz; for (int i = 1; i <= siz; ++ i) p[i].siz = 1;}
    inline void pushup(int k) {p[k].siz = p[ls(k)].siz + p[rs(k)].siz + 1;}
    inline int get_type(int k) {return rs(f(k)) == k;}
    inline bool isroot(int k) {return ls(f(k)) != k && rs(f(k)) != k;}

    inline void rotate(int x) {
        int y = f(x), z = f(y), op = get_type(x);
        if (!isroot(y)) p[z].ch[get_type(y)] = x;
        p[y].ch[op] = p[x].ch[!op], p[p[x].ch[!op]].fa = y;
        p[x].ch[!op] = y, p[y].fa = x, p[x].fa = z;
        pushup(y), pushup(x);
    }

    inline void splay(int x) {
        for (int fa; fa = f(x), !isroot(x); rotate(x))
          if (!isroot(fa)) rotate(get_type(fa) == get_type(x) ? fa : x);
    }
    
    inline int Access(int x) {
        int t = 0;
        for (t = 0; x; t = x, x = f(x))
          splay(x), p[x].ch[1] = t, pushup(x);
        return t;
    }

    inline void link(int x, int y) {splay(x), p[x].fa = y;}
    
    inline void cut(int x, int y) {
        Access(x); splay(y); p[y].ch[1] = p[x].fa = 0; pushup(y);
    }

    inline int query(int x) {Access(x); splay(x); return p[x].siz;}
} lct;

int n, m, to[N];

inline void modify(int x, int y) {
    if (x + to[x] <= n) lct.cut(x, x + to[x]);
    if (x + y <= n) lct.link(x, x + (to[x] = y));
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n); lct.init(n);
    for (int i = 1; i <= n; ++ i) read(to[i]);
    for (int i = 1; i <= n; ++ i) 
      if (i + to[i] <= n) lct.link(i, i + to[i]);
    read(m);
    while (m --) {
        int op = 0, x = 0, y = 0; read(op), read(x); ++ x;
        if (op == 1) printf("%d\n", lct.query(x));
        else read(y), modify(x, y);
    }
    return 0;
}
