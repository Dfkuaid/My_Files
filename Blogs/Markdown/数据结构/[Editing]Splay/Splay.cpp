#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

struct Tree {int son[2], f, cnt, size, val;} t[N];

int rt, tot, n;

inline void clear(int k) {
    t[k].cnt = t[k].f = t[k].size = t[k].son[1] = t[k].son[0] = t[k].val = 0;
}

inline void pushup(int k) {
    t[k].size = t[t[k].son[0]].size + t[t[k].son[1]].size + t[k].cnt;
}

inline int get(int k) {return k == t[t[k].f].son[1];}

inline void connect(int x, int y, int op) {
    if (x) {t[x].f = y;} if (y) {t[y].son[op] = x;}
}

inline void rotate(int k) {
    int f = t[k].f, ff = t[f].f, r = get(k), rf = get(f);
    connect(t[k].son[r ^ 1], f, r); connect(f, k, r ^ 1);
    connect(k, ff, rf); pushup(f); pushup(k);
}

inline void splay(int k) {
    for (int f = t[k].f; f = t[k].f, f; rotate(k))
      if (t[f].f) rotate(get(k) == get(f) ? f : k);
    rt = k;
}

inline void insert(int k) {
    if (!rt){
        rt = ++ tot, t[rt].val = k;
        t[rt].cnt ++; pushup(rt); return;
    }
    int now = rt, f = 0;
    while (true) {
        if (t[now].val == k) {
            t[now].cnt ++; pushup(now);
            pushup(f); splay(now); break;
        }
        f = now; now = t[now].son[t[now].val < k];
        if (! now) {
            t[++ tot].val = k, t[tot].f = f;
            t[tot].cnt ++; t[f].son[t[f].val < k] = tot;
            pushup(tot); pushup(f); splay(tot); break;
        }
    }
}

inline int rk(int k) {
    int res = 0,now = rt;
    while (true) {
        if (k < t[now].val) now = t[now].son[0];
        else {
            res += t[t[now].son[0]].size;
            if (k == t[now].val) splay(now), return res + 1;
            res += t[now].cnt; now = t[now].son[1];
        }
    }
}

inline int kth(int k) {
    int now = rt;
    while (true) {
        if (k <= t[t[now].son[0]].size) now = t[now].son[0];
        else {
            k -= t[t[now].son[0]].size + t[now].cnt;
            if (k <= 0) splay(now), return t[now].val;
            now = t[now].son[1];
        }
    }
}

inline int pre() {
    int cur = t[rt].son[0];
    while (t[cur].son[1]) cur = t[cur].son[1];
    splay(cur); return cur;
}

inline int nxt() {
    int cur = t[rt].son[1];
    while (t[cur].son[0]) cur = t[cur].son[0];
    splay(cur); return cur;
}

inline void del(int k) {
    rk(k);
    if (t[rt].cnt > 1) {
        t[rt].cnt --; pushup(rt); return;
    } else if (!t[rt].son[0] && !t[rt].son[1]) {
        clear(rt); rt = 0; return;
    } else if (!t[rt].son[0]) {
        int tmp = rt; rt = t[tmp].son[1];
        t[rt].f = 0; clear(tmp); return;
    } else if (!t[rt].son[1]) {
        int tmp = rt; rt = t[tmp].son[0];
        t[rt].f = 0; clear(tmp); return;
    }
    int tmp = rt, l = pre(); splay(l);
    connect(t[tmp].son[1], rt, 1);
    clear(tmp); pushup(rt);
}

int main() {
    scanf("%d", &n); int opt,x;
    while (n --){
        scanf("%d%d", &opt, &x);
        if (opt == 1) insert(x);
        else if (opt == 2) del(x);
        else if (opt == 3) printf("%d\n", rk(x));
        else if (opt == 4) printf("%d\n", kth(x));
        else if (opt == 5)
          insert(x), printf("%d\n", t[pre()].val), del(x);
        else insert(x), printf("%d\n", t[nxt()].val), del(x);
    }
    return 0;
}