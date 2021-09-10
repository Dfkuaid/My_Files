#include <bits/stdc++.h>
#define ll long long
#define int long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 5000010;
const int INF = 0x3fffffff;

template <typename T>
inline T Min(const T a, const T b) {return a < b ? a : b;}

struct Node {int sum, ls, rs;} p[N];

int n, cnt, rt;
ll lsum, rsum, ans;

inline void pushup(int k) {
    p[k].sum = p[p[k].ls].sum + p[p[k].rs].sum;
}

void build(int &k, int l, int r, int x) {
    if (!k) k = ++ cnt;
    if (l == r) {p[k].sum += 1; return;}
    int mid = (l + r) >> 1;
    if (x <= mid) build(p[k].ls, l, mid, x);
    else build(p[k].rs, mid + 1, r, x);
    pushup(k);
}

int merge(int k1, int k2, int l, int r) {
    if (!k1 || !k2) return k1 + k2;
    if (l == r) {p[k1].sum += p[k2].sum; return k1;}
    lsum += (ll)(p[p[k1].rs].sum * p[p[k2].ls].sum);
    rsum += (ll)(p[p[k2].rs].sum * p[p[k1].ls].sum);
    int mid = (l + r) >> 1;
    p[k1].ls = merge(p[k1].ls, p[k2].ls, l, mid);
    p[k1].rs = merge(p[k1].rs, p[k2].rs, mid + 1, r);
    pushup(k1); return k1;
}

int dfs() {
    int p = 0, op; scanf("%lld", &op);
    if (!op) {
        int ls = dfs(), rs = dfs();
        lsum = rsum = 0;
        p = merge(ls, rs, 1, n);
        ans += Min(lsum, rsum);
    } else build(p, 1, n, op);
    return p;
}

signed main() {
    scanf("%lld", &n);
    rt = dfs();
    printf("%lld", ans);
    return 0;
}