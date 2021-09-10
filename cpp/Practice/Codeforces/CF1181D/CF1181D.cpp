#define DEBUG
#include <bits/stdc++.h>
#define ll long long
#define int long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int M = 500010;
const int N = 2000010;
const int INF = 0x3fffffff;

struct City {
    int val, idx;
    inline bool operator < (const City b) const {
        return val < b.val;
    }
} a[N];

struct Query {
    ll val; int idx;
    inline bool operator < (const Query b) const {
        return val < b.val;
    }
} q[N];

int n, m, t, cnt, ans[M], sum[N], rt = 1, p = 1;
ll lmt[M], lim;

void insert(int k, int l, int r, int x) {
    if (l == r) {++ sum[k]; return;}
    int mid = l + r >> 1;
    if (x <= mid) insert(k << 1, l, mid, x);
    else insert(k << 1 | 1, mid + 1, r, x);
    sum[k] = sum[k << 1] + sum[k << 1 | 1];
}

int kth(int k, int l, int r, int x) {
    if (l == r) {return l;}
    int mid = l + r >> 1, lsum = sum[k << 1];
    if (x <= lsum) return kth(k << 1, l, mid, x);
    else return kth(k << 1 | 1, mid + 1, r, x - lsum);
}

signed main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    scanf("%d%d%d", &n, &m, &t);
    for (int i = 1; i <= n; ++ i) {
        int x; scanf("%d", &x); ++ a[x].val;
    }
    for (int i = 1; i <= m; ++ i) a[i].idx = i;
    for (int i = 1; i <= t; ++ i) {
        scanf("%lld", &q[i].val);
        q[i].val -= (ll)n, q[i].idx = i;
    }
    sort(a + 1, a + m + 1);  sort(q + 1, q + t + 1);
    lim = a[m].val * m - n;
    for (int i = 1; i <= m; ++ i)
      lmt[i] = lmt[i - 1] + ((i - 1) * (a[i].val - a[i - 1].val));
    insert(rt, 1, m, a[p ++].idx);
    for (int i = 1; i <= t; ++ i) {
        while (p <= m && q[i].val > lmt[p])
          insert(rt, 1, m, a[p ++].idx);
        int rk = q[i].val - lmt[p - 1];
        if (rk % (p - 1) == 0) rk = p - 1;
        else rk = rk % (p - 1);
        ans[q[i].idx] = kth(rt, 1, m, rk);
    }
    for (int i = 1; i <= t; ++ i) printf("%d\n", ans[i]);
    return 0;
}