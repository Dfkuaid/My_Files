#define DEBUG
#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 600010;
const int INF = 0x3fffffff;

template <typename T>
inline T Max(const T a, const T b) {return a > b ? a : b;}

struct Node {int ch[2], f, val, sum, siz, lc, rc, mc, rev, cvr;} p[N];

int n, m, rt, cnt, a[N], depot[N], dcnt;

inline int get(int k) {return p[p[k].f].ch[1] == k;}

inline int new_id() {return dcnt ? depot[dcnt --] : ++ cnt;}

inline int new_node(int k, int x, int fa) {
    p[k] = (Node){{0, 0}, fa, x, x, 1, max(x, 0), max(x, 0), x, 0, 0};
}

inline void del(int k) {
    p[k] = (Node){{0, 0}, 0, 0, 0, 0, 0, 0, -INF, 0, 0};
}

inline void pushdown(int k) {
    int ls = p[k].ch[0], rs = p[k].ch[1];
    if (p[k].cvr) {
        if (ls) {
            p[ls].val = p[k].val, p[ls].cvr = 1;
            p[ls].sum = p[k].val * p[ls].siz;
        }
        if (rs) {
            p[rs].val = p[k].val, p[rs].cvr = 1;
            p[rs].sum = p[k].val * p[rs].siz;
        }
        if (p[k].val > 0) {
            if (ls) p[ls].lc = p[ls].rc = p[ls].mc = p[ls].sum;
            if (rs) p[rs].lc = p[rs].rc = p[rs].mc = p[rs].sum;
        } else {
            if (ls) p[ls].lc = p[ls].rc = 0, p[ls].mc = p[ls].val;
            if (rs) p[rs].lc = p[rs].rc = 0, p[rs].mc = p[rs].val;
        }
        p[k].cvr = p[k].rev = 0;
    }
    if (p[k].rev) {
        p[p[k].ch[0]].rev ^= 1; p[p[k].ch[1]].rev ^= 1;
        swap(p[p[k].ch[0]].ch[0], p[p[k].ch[0]].ch[1]);
        swap(p[p[k].ch[1]].ch[0], p[p[k].ch[1]].ch[1]);
        swap(p[p[k].ch[0]].lc, p[p[k].ch[0]].rc);
        swap(p[p[k].ch[1]].lc, p[p[k].ch[1]].rc);
        p[k].rev = 0;
    }
    
}

inline void pushup(int k) {
    int ls = p[k].ch[0], rs = p[k].ch[1];
    p[k].siz = p[ls].siz + p[rs].siz + 1;
    p[k].sum = p[ls].sum + p[rs].sum + p[k].val;
    if (p[ls].sum == -INF) p[k].sum -= -INF;
    if (p[rs].sum == -INF) p[k].sum -= -INF;
    if (p[k].val == -INF) p[k].sum -= -INF;
    p[k].mc = Max(Max(p[ls].mc, p[rs].mc), p[ls].rc + p[k].val + p[rs].lc);
    p[k].lc = Max(p[ls].lc, p[ls].sum + p[k].val + p[rs].lc);
    p[k].rc = Max(p[rs].rc, p[rs].sum + p[k].val + p[ls].rc);   
}

inline void connect(int x, int y, int r) {
    if (x) {p[x].f = y;} if (y) {p[y].ch[r] = x;}
}

inline void rotate(int k)  {
    pushdown(p[k].f); pushdown(k);
    int f = p[k].f, ff = p[f].f, r = get(k), rf = get(f);
    connect(p[k].ch[r ^ 1], f, r); connect(f, k, r ^ 1);
    connect(k, ff, rf); pushup(f); pushup(k);
}

inline void splay(int k, int g) {
    for (int f = p[k].f; f = p[k].f, f != g; rotate(k))
      if (p[f].f != g) rotate(get(k) == get(f) ? f : k);
    if (!g) rt = k;
}

inline int kth(int k) {
    int now = rt;
    while (true){
        pushdown(now);
        if (p[p[now].ch[0]].siz >= k)
          now = p[now].ch[0];
        else{
            k -= p[p[now].ch[0]].siz + 1;
            if (k <= 0) return now;
            now = p[now].ch[1];
        }
    }
}

void recycle(int k) {
    if (!k) {return;} 
    recycle(p[k].ch[0]);
    recycle(p[k].ch[1]);
    depot[++ dcnt] = k; del(k);
}

void build(int &k, int l, int r, int fa) {
    if (r < l) return; if (!k) k = new_id();
    if (l == r) {new_node(k, a[l], fa); return;}
    int mid = l + r >> 1; new_node(k, a[mid], fa);
    build(p[k].ch[0], l, mid - 1, k);
    build(p[k].ch[1], mid + 1, r, k);
    pushup(k);
}

inline void insert(int pos, int len) {
    int r = kth(pos + 2), l = kth(pos + 1);
    splay(l, 0); splay(r, l);
    int cur = 0; build(cur, 1, len, 0);
    connect(cur, p[rt].ch[1], 0);
    pushup(p[rt].ch[1]); pushup(rt);
}

inline void reverse(int pos, int len) {
    int l = pos - 1, r = pos + len;
    l = kth(l + 1); r = kth(r + 1);
    splay(l, 0); splay(r, l);
    p[p[p[rt].ch[1]].ch[0]].rev ^= 1;
    int rp = p[p[rt].ch[1]].ch[0];
    swap(p[rp].ch[0], p[rp].ch[1]);
    swap(p[rp].lc, p[rp].rc);
    pushup(p[rt].ch[1]); pushup(rt);
}

inline void clear(int pos, int len) {
    int l = kth(pos), r = kth(pos + len + 1);
    splay(l, 0); splay(r, l);
    recycle(p[p[rt].ch[1]].ch[0]);
    p[p[rt].ch[1]].ch[0] = 0;
    pushup(p[rt].ch[1]); pushup(rt);
}

inline void recover(int pos, int len, int c) {
    int l = pos - 1, r = pos + len;
    l = kth(l + 1); r = kth(r + 1);
    splay(l, 0); splay(r, l);
    int rp = p[p[rt].ch[1]].ch[0];
    p[rp].cvr = 1, p[rp].val = c;
    p[rp].sum = p[rp].val * p[rp].siz;
    if (c > 0) p[rp].lc = p[rp].rc = p[rp].mc = p[rp].sum;
    else p[rp].lc = p[rp].rc = 0, p[rp].mc = c;
    pushup(p[rt].ch[1]); pushup(rt);
}

inline int get_sum(int pos, int len) {
    int l = kth(pos), r = kth(pos + len + 1);
    splay(l, 0); splay(r, l);
    int rp = p[p[rt].ch[1]].ch[0];
    return p[rp].sum;
}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    scanf("%d%d", &n, &m); del(0);
    for (int i = 1; i <= n; ++ i)
      scanf("%d", &a[i + 1]);
    a[1] = a[n + 2] = -INF;
    build(rt, 1, n + 2, 0);
    while (m --) {
        string s; int len, x;
        cin >> s;
        if (s == "INSERT") {
            scanf("%d%d", &x, &len);
            for (int i = 1; i <= len; ++ i)
              scanf("%d", &a[i]);
            insert(x, len);
        } else if (s == "DELETE") {
            scanf("%d%d", &x, &len);
            clear(x, len);
        } else if (s == "MAKE-SAME") {
            int c; scanf("%d%d%d", &x, &len, &c);
            recover(x, len, c);
        } else if (s == "REVERSE") {
            scanf("%d%d", &x, &len);
            reverse(x, len);
        } else if (s == "GET-SUM") {
            scanf("%d%d", &x, &len);
            printf("%d\n", get_sum(x, len));
        } else printf("%d\n", p[rt].mc);
    }
    return 0;
}