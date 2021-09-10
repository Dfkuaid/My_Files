#define DEBUG
#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 200010;
const int M = 4000010;
const int INF = 0x3fffffff;

struct Juice {int id; ll d, p, l;} a[N];
struct Node {int ls, rs; ll vsum, csum, prc;} p[M];

int n, m, cnt, rt[N];

inline bool cmp1(Juice a, Juice b) {return a.p < b.p;}
inline bool cmp2(Juice a, Juice b) {return a.d > b.d;}

inline void pushup(int k) {
    p[k].vsum = p[p[k].ls].vsum + p[p[k].rs].vsum;
    p[k].csum = p[p[k].ls].csum + p[p[k].rs].csum;
}

void build(int &k, int l, int r) {
    if (!k) {k = ++ cnt;} if (l == r) return;
    int mid = l + r >> 1; build(p[k].ls, l, mid);
    build(p[k].rs, mid + 1, r);
}

void insert(int t, int &k, int l, int r, int x, ll v, ll c) {
    if (!k) {k = ++ cnt;} int mid = l + r >> 1;
    if (l == r) {
        p[k].vsum = v, p[k].prc = c;
        p[k].csum = c * v; 
        // printf("%d: [%d, %d] %lld %lld\n", k, l, r, p[k].csum, p[k].vsum);
        return;
    }
    if (x <= mid) {
        p[k].rs = p[t].rs;
        insert(p[t].ls, p[k].ls, l, mid, x, v, c);
    } else {
        p[k].ls = p[t].ls;
        insert(p[t].rs, p[k].rs, mid + 1, r, x, v, c);
    } pushup(k);
    // printf("%d: [%d, %d] %lld %lld\n", k, l, r, p[k].csum, p[k].vsum);
}

ll query(int k, int l, int r, ll x) {
    // printf("QUERY: %d [%d, %d] %d\n", k, l, r, x);
    if (l == r) {return p[k].prc * x;}
    int mid = l + r >> 1; ll lsum = p[p[k].ls].vsum;
    if (lsum >= x) return query(p[k].ls, l, mid, x);
    else return p[p[k].ls].csum + query(p[k].rs, mid + 1, r, x - lsum);
}

inline bool check(int x, ll g, ll L) {
    if (p[rt[x]].vsum < L) return 0;
    ll res = query(rt[x], 1, n, L);
    // printf("check: %lld %lld %lld\n", a[x].d, g, res);
    return res <= g;
}

signed main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i)
      scanf("%lld%lld%lld", &a[i].d, &a[i].p, &a[i].l);
    sort(a + 1, a + n + 1, cmp1);
    // for (int i = 1; i <= n; ++ i)
    //   printf("%d %d %d\n", a[i].d, a[i].p, a[i].l);
    for (int i = 1; i <= n; ++ i) a[i].id = i;
    sort(a + 1, a + n + 1, cmp2);
    // for (int i = 1; i <= n; ++ i) printf("%d ", a[i].id);
    // printf("\n");
    build(rt[0], 1, n);
    for (int i = 1; i <= n; ++ i)
      insert(rt[i - 1], rt[i], 1, n, a[i].id, a[i].l, a[i].p);
    // for (int i = 1; i <= n; ++ i) printf("%d ", rt[i]);
    // printf("\n");
    while (m --) {
        ll g, L; scanf("%lld%lld", &g, &L);
        int l = 1, r = n, ans = -1;
        while (l <= r) {
            int mid = l + r >> 1;
            if (check(mid, g, L))
              ans = mid, r = mid - 1;
            else l = mid + 1;
        }
        if (!(~ans)) printf("-1\n");
        else printf("%lld\n", a[ans].d);
    }
    return 0;
}