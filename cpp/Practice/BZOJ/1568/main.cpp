#define LOCAL
#include <bits/stdc++.h>
#define ll long long
#define db double
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 200010;
const int LMT = 50010;
const int INF = 0x3fffffff;

template <typename T> void read(T &x) {
    int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T Max(T x, T y) {return x > y ? x : y;}
template <typename T> inline T Min(T x, T y) {return x < y ? x : y;}

struct Node {int ls, rs, val;};
struct Line {
    double k, b;
    inline Line() {k = b = 0;}
    inline Line(double _k, double _b) {k = _k, b = _b;}
    inline double val(int x) {return k * x + b;}
} s[N];

struct LCTree {
    Node p[N]; int cnt, rt;

    inline LCTree() {cnt = rt = 0;}

    void build(int &k, int l, int r) {
        if (!k) k = ++ cnt; if (l == r) return;
        int mid = l + r >> 1; p[k].val = 0;
        build(p[k].ls, l, mid); build(p[k].rs, mid + 1, r);
    }   

    void insert(int k, int l, int r, int id) {
        if (!p[k].val) {p[k].val = id; return;}
        int mid = l + r >> 1;
        db l2 = s[p[k].val].val(l), r2 = s[p[k].val].val(r);
        db l1 = s[id].val(l), r1 = s[id].val(r);
        if (l1 <= l2 && r1 <= r2) return;
        if (l1 > l2 && r1 > r2) {p[k].val = id; return;}
        db x = (s[id].b - s[p[k].val].b) / (s[p[k].val].k - s[id].k);
        if (l1 > l2) {
            if (x > mid) insert(p[k].rs, mid + 1, r, p[k].val), p[k].val = id;
            else insert(p[k].ls, l, mid, id);
        } else {
            if (x > mid) insert(p[k].rs, mid + 1, r, id);
            else insert(p[k].ls, l, mid, p[k].val), p[k].val = id;
        }
    } 
    
    double query(int k, int l, int r, int x) {
        // printf("QUERY: %d [%d, %d] %d (%d)\n", k, l, r, x, p[k].val);
        if (l == r) return s[p[k].val].val(x);
        int mid = l + r >> 1; double res = s[p[k].val].val(x);
        if (x <= mid) return Max(query(p[k].ls, l, mid, x), res);
        else return Max(query(p[k].rs, mid + 1, r, x), res);
    }
} t;

int n, lcnt, T; char op[N];

inline void Main() {
    scanf("%s", op);
    if (op[0] == 'P') {
        double k = 0, b = 0; scanf("%lf%lf", &b, &k);
        s[++ lcnt] = Line(k, b - k); t.insert(t.rt, 1, LMT, lcnt);
    } else {
        int x = 0; read(x);
        printf("%lld\n", (ll)(t.query(t.rt, 1, LMT, x) / 100.0));
    }
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    t.build(t.rt, 1, LMT); read(T); while (T --) Main(); return 0;
}
