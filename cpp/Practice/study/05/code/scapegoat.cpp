#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 500010;
const double alpha = 0.75;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T Max(T x, T y) {return x > y ? x : y;}

struct Node {int w, cnt, ls, rs, siz_single, siz_all, siz_without_del;};
struct ScapeGoat {
    Node p[N]; int rt, cnt, rub[N], rcnt, q[N], qcnt;
    
    inline int new_ind() {return rcnt ? rub[rcnt --] : ++ cnt;}
    inline void del_node(int k) {rub[++ rcnt] = k;}
    
    inline int new_node(int w) {
        int k = new_ind(); p[k].w = w, p[k].ls = p[k].rs = 0;
        p[k].cnt = p[k].siz_single = 1;
        p[k].siz_all = p[k].siz_without_del = 1; return k;
    }

    inline void pushup(int k) {
        int ls = p[k].ls, rs = p[k].rs;
        p[k].siz_single = p[ls].siz_single + p[rs].siz_single + 1;
        p[k].siz_all = p[ls].siz_all + p[rs].siz_all + p[k].cnt;
        p[k].siz_without_del = p[ls].siz_without_del + p[rs].siz_without_del + (p[k].cnt ? 1 : 0);
    }

    inline bool check(int k) {return p[k].w && (alpha * p[k].siz_single 
                                                  <= 1.0 * Max(p[p[k].ls].siz_single, p[p[k].rs].siz_single)
                                                || 1.0 * p[k].siz_without_del <= p[k].siz_single * alpha);}

    void unfold(int k) {
        if (!k) return;
        unfold(p[k].ls);
        if (p[k].cnt) q[++ qcnt] = k;
        else del_node(k);
        unfold(p[k].rs);
    }
    
    int build(int l, int r) {
        if (l > r) return 0; int mid = l + r >> 1;
        p[q[mid]].ls = build(l, mid - 1);
        p[q[mid]].rs = build(mid + 1, r);
        pushup(q[mid]); return q[mid];
    }

    void rebuild(int &k) {qcnt = 0; unfold(k); k = build(1, qcnt);}
    
    void insert(int &k, int x) {
        if (!k) {k = new_node(x); return;}
        if (p[k].w == x) ++ p[k].cnt;
        else if (p[k].w < x) insert(p[k].rs, x);
        else insert(p[k].ls, x);
        pushup(k); if (check(k)) rebuild(k);
    }

    void del(int &k, int x) {
        if (!k) return;
        if (p[k].w == x && p[k].cnt) -- p[k].cnt;
        else if (p[k].w < x) del(p[k].rs, x);
        else if (p[k].w > x) del(p[k].ls, x);
        pushup(k); if (check(k)) rebuild(k);
    }

    int upper_grade(int k, int x) {
        if (!k) return 1;
        if (p[k].w == x && p[k].cnt) return p[p[k].ls].siz_all + p[k].cnt + 1;
        if (p[k].w > x) return upper_grade(p[k].ls, x);
        else return p[p[k].ls].siz_all + p[k].cnt + upper_grade(p[k].rs, x);
    }

     int lower_grade(int k, int x) {
        if (!k) return 0;
        if (p[k].w == x && p[k].cnt) return p[p[k].ls].siz_all;
        if (p[k].w > x) return lower_grade(p[k].ls, x);
        else return p[p[k].ls].siz_all + p[k].cnt + lower_grade(p[k].rs, x);
     }

     int kth_value(int k, int x) {
        if (!k) return 0;
        if (p[p[k].ls].siz_all < x && x <= p[p[k].ls].siz_all + p[k].cnt) return p[k].w;
        if (p[p[k].ls].siz_all >= x) return kth_value(p[k].ls, x);
        else return kth_value(p[k].rs, x - p[k].cnt - p[p[k].ls].siz_all);
     }

     inline int pre_value(int x) {return kth_value(rt, lower_grade(rt, x));}
     inline int nxt_value(int x) {return kth_value(rt, upper_grade(rt, x));}
     inline int get_grade(int x) {return lower_grade(rt, x) + 1;}
} t;

int n;

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n);
    while (n --) {
        int opt = 0, x = 0; read(opt), read(x);
        if (opt == 1) t.insert(t.rt, x);
        else if (opt == 2) t.del(t.rt, x);
        else if (opt == 3) printf("%d\n", t.get_grade(x));
        else if (opt == 4) printf("%d\n", t.kth_value(t.rt, x));
        else if (opt == 5) printf("%d\n", t.pre_value(x));
        else printf("%d\n", t.nxt_value(x));
    }
    return 0;
}
