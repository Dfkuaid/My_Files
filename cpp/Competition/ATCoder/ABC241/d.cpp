#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 20000010;
const ll LMT = 1e18;
const int INF = 0x3f3f3f3f;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

struct Node {int ls, rs, sum;};
struct SegmentTree {
#define ls(x) p[x].ls
#define rs(x) p[x].rs

    Node p[N]; int cnt, rt;

    inline SegmentTree() {cnt = rt = 0;}
    inline void pushup(int k) {p[k].sum = p[ls(k)].sum + p[rs(k)].sum;}

    void insert(int &k, ll l, ll r, ll x) {
        if (!k) k = ++ cnt;
        if (l == r) {++ p[k].sum; return;}
        ll mid = l + r >> 1;
        if (x <= mid) insert(p[k].ls, l, mid, x);
        else insert(p[k].rs, mid + 1, r, x);
        pushup(k);
    }

    int get_lower(int k, ll l, ll r, ll x, int tot) {
        if (!k) return tot + 0;
        if (l == r) return tot + p[k].sum;
        ll mid = l + r >> 1;
        if (x <= mid) return get_lower(p[k].ls, l, mid, x, tot);
        else return get_lower(p[k].rs, mid + 1, r, x, tot + p[ls(k)].sum);
    }

    int get_upper(int k, ll l, ll r, ll x, int tot) {
        if (!k) return tot + 0;
        if (l == r) return tot + p[k].sum;
        ll mid = l + r >> 1;
        if (x > mid) return get_upper(p[k].rs, mid + 1, r, x, tot);
        else return get_upper(p[k].ls, l, mid, x, tot + p[rs(k)].sum);
    }

    ll get_kth(int k, ll l, ll r, int x) {
        if (l == r) return l;
        ll mid = l + r >> 1; int lsiz = p[ls(k)].sum;
        if (x <= lsiz) return get_kth(p[k].ls, l, mid, x);
        else return get_kth(p[k].rs, mid + 1, r, x - lsiz);
    }
} t;

int q;

inline void Main() {
    ll op = 0, x = 0, k = 0;
    read(op), read(x);
    if (op == 1) t.insert(t.rt, 0, LMT, x);
    else if (op == 2) {
        read(k);
        int res = t.get_lower(t.rt, 0, LMT, x, 0);
        if (res < k) {puts("-1"); return;}
        printf("%lld\n", t.get_kth(t.rt, 0, LMT, res - k + 1));
    } else {
        read(k);
        int res = t.get_upper(t.rt, 0, LMT, x, 0);
        int tmp = t.get_lower(t.rt, 0, LMT, x - 1, 0);
        if (res < k) {puts("-1"); return;}
        printf("%lld\n", t.get_kth(t.rt, 0, LMT, tmp + k));
    }
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(q); while (q --) Main(); return (0 - 0);
}
