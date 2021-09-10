#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 1000010;
const int INF = 0x3fffffff;

template <typename T>
inline T Max(const T a, const T b) {return a > b ? a : b;}

template <typename T>
inline T Min(const T a, const T b) {return a < b ? a : b;}

struct Node {int ls, rs, s, lmx, rmn, lv, rv, lrv, v;} p[N];

int n, m, cnt, rt;
char S[N];

inline void pushup(int k) {
    p[k].s = p[p[k].ls].s + p[p[k].rs].s;
    p[k].lmx = Max(p[p[k].ls].lmx, p[p[k].rs].lmx + p[p[k].ls].s);
    p[k].rmn = Min(p[p[k].rs].rmn, p[p[k].ls].rmn + p[p[k].rs].s);
    p[k].lv = Max(Max(p[p[k].ls].lv, p[p[k].rs].lv - p[p[k].ls].s),
                  p[p[k].ls].lrv + p[p[k].rs].lmx);
    p[k].rv = Max(Max(p[p[k].rs].rv, p[p[k].ls].rv + p[p[k].rs].s),
                  p[p[k].rs].lrv - p[p[k].ls].rmn);
    p[k].lrv = Max(p[p[k].ls].lrv + p[p[k].rs].s, p[p[k].rs].lrv - p[p[k].ls].s);
    p[k].v = Max(Max(p[p[k].ls].v, p[p[k].rs].lv - p[p[k].ls].rmn), 
                 Max(p[p[k].rs].v, p[p[k].ls].rv + p[p[k].rs].lmx));
}

void build(int &k, int l, int r) {
    if (!k) k = ++ cnt;
    if (l == r) {
        p[k].s = (S[l] == '(' ? 1 : -1);
        p[k].lmx = Max(p[k].s, 0); p[k].rmn = Min(p[k].s, 0);
        p[k].lrv = p[k].lv = p[k].rv = p[k].v = 1;
        return;
    }
    int mid = l + r >> 1;
    build(p[k].ls, l, mid); build(p[k].rs, mid + 1, r);
    pushup(k);
}

void modify(int k, int l, int r, int x, int c) {
    if (l == r) {
        p[k].s = c, p[k].lmx = Max(p[k].s, 0);
        p[k].rmn = Min(p[k].s, 0); return;
    }
    int mid = l + r >> 1;
    if (x <= mid) modify(p[k].ls, l, mid, x, c);
    else modify(p[k].rs, mid + 1, r, x, c);
    pushup(k);
}

int main() {
    scanf("%d%d%s", &n, &m, S + 1);
    (n -= 1) <<= 1; build (rt, 1, n);
    printf("%d\n", p[rt].v);
    while (m --) {
        int a, b; scanf("%d%d", &a, &b);
        if (S[a] != S[b]) {
            swap(S[a], S[b]);
            modify(rt, 1, n, a, (S[a] == '(' ? 1 : -1));
            modify(rt, 1, n, b, (S[b] == '(' ? 1 : -1));
        }
        printf("%d\n", p[rt].v);
    }
    return 0;
}