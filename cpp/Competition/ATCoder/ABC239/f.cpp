#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 400010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

struct Node {int lst, nxt, val;} p[N];
struct List {int head, tail, siz;} l[N];

int n, m, d[N], tot, f[N], q[N], cnt;

inline void clear(List &x) {x.head = x.tail = -1, x.siz = 0;}

inline int find(int x) {
    while (x != f[x])
      x = f[x] = f[f[x]];
    return x;
}

inline bool unify(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return false;
    f[y] = x; return true;
}

inline void check(int x) {
    if (!d[x]) {
        if (~p[x].lst) p[p[x].lst].nxt = p[x].nxt;
        if (~p[x].nxt) p[p[x].nxt].lst = p[x].lst;
        int fx = find(x);
        if (l[fx].head == x) l[fx].head = p[x].nxt;
        if (l[fx].tail == x) l[fx].tail = p[x].lst;
    }
}

inline bool connect(int x, int y) {
    int fx = find(x), fy = find(y);
    -- d[x], -- d[y], -- l[fx].siz, -- l[fy].siz;
    p[l[fx].tail].nxt = l[fy].head;
    p[l[fy].head].lst = l[fx].tail;
    l[fx].tail = l[fy].tail;
    l[fx].siz += l[fy].siz; clear(l[fy]);
    if (!unify(x, y) || !l[fx].siz) return false;
    check(x), check(y); return true;
}

inline bool cmp(int x, int y) {return l[x].siz > l[y].siz;}

inline void build(int x, int y) {
    -- d[l[x].head], -- d[l[y].head];
    printf("%d %d\n", l[x].head, l[y].head);
    p[l[x].tail].nxt = l[y].head;
    p[l[y].head].lst = l[x].tail;
    l[x].siz += l[y].siz - 2;
    l[x].tail = l[y].tail; clear(l[y]);
    check(x), check(y);
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(m);
    for (int i = 1; i <= n; ++ i) read(d[i]), tot += d[i];
    if (tot != 2 * n - 2) {puts("-1"); return (0 - 0);}
    for (int i = 1; i <= n; ++ i) f[i] = i;
    for (int i = 1; i <= n; ++ i) l[i].head = l[i].tail = i, l[i].siz = d[i];
    for (int i = 1; i <= n; ++ i) p[i].nxt = p[i].lst = -1, p[i].val = i;
    for (int i = 1, u, v; i <= m; ++ i) {
        read(u), read(v);
        if (!connect(u, v)) {puts("-1"); return (0 - 0);}
    }
    for (int i = 1; i <= n; ++ i) if (l[i].siz) q[++ cnt] = i;
    /*for (int i = 1; i <= n; ++ i, puts("")) {
        printf("%d (%d) : ", i, l[i].siz);
        for (int j = l[i].head; ~j; j = p[j].nxt)
          printf("%d ", p[j].val);
    }*/
    sort(q + 1, q + cnt + 1, cmp); int now = q[1];
    /*for (int i = 1; i <= cnt; ++ i, puts("")) {
        printf("#%d %d : ", i, q[i]);
        for (int j = l[q[i]].head; ~j; j = p[j].nxt)
          printf("%d ", p[j].val);
    }*/
    for (int i = 2; i <= cnt; ++ i) build(now, q[i]);
    return (0 - 0);
}
