#define LOCAL
#include <bits/stdc++.h>
#define ll long long
#define pii pair <int, int>
#define plli pair <long long, int>
#define mp(a, b) make_pair(a, b)
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 500010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T Max(T a, T b) {return a > b ? a : b;}

struct Activity {
    int id, l, r; ll x;
    inline bool operator < (const Activity &b) const {return x > b.x;}
} a[N];

int T, n, d, k, q[N], siz, frt, tal, vis[N], st[N]; ll ans, sum;

priority_queue <plli > pq, cand;

vector <pii > qry[N];

inline bool cmp(Activity x, Activity y) {return x.l == y.l ? x.r < y.r : x.l < y.l;}

inline void reset() {
    frt = 0, tal = -1; ans = 0; mset(vis, 0);
    mset(st, 0); while (pq.size()) pq.pop();
    while (cand.size()) cand.pop(); siz = sum = 0;
    for (int i = 1; i <= d; ++ i) qry[i].clear();
}

void insert(int x) {
    if (siz < k) {
        pq.push(mp(-a[x].x, x)); ++ siz;
        sum += a[x].x; st[x] = 1;
    } else {
        plli tmp = pq.top();
        while (pq.size() && vis[tmp.second]) {pq.pop(); tmp = pq.top();}
        if (-tmp.first < a[x].x) {
            pq.pop(); cand.push(mp(-tmp.first, tmp.second));
            sum += a[x].x + tmp.first;
            pq.push(mp(-a[x].x, x));
            st[tmp.second] = 0, st[x] = 1;
        } else cand.push(mp(a[x].x, x)), st[x] = 0;
    }
}

void del(int x) {
    if (st[x] == 1) -- siz, sum -= a[x].x;
    vis[x] = 1, st[x] = 0;
    while (cand.size() && siz < k) {
        plli tmp = cand.top(); cand.pop();
        if (vis[tmp.second]) continue;
        ++ siz, sum += tmp.first; st[tmp.second] = 1;
        pq.push(mp(-tmp.first, tmp.second));
    }
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(T);
    for (int i = 1; i <= T; ++ i) {
        read(d); read(n); read(k); reset();
        for (int i = 1; i <= n; ++ i)
          read(a[i].x), read(a[i].l), read(a[i].r);
        sort(a + 1, a + n + 1, cmp);
        for (int i = 1; i <= n; ++ i) a[i].id = i;
        for (int i = 1; i <= n; ++ i) {
            qry[a[i].l].push_back(mp(1, i));
            qry[a[i].r + 1].push_back(mp(-1, i));
        }
        for (int i = 1; i <= d; ++ i) {
            for (auto k : qry[i])
              if (k.first == -1) del(k.second);
              else insert(k.second);
            ans = Max(sum, ans);
        }
        printf("Case #%d: %lld\n", i, ans);
    }
    return 0;
}
