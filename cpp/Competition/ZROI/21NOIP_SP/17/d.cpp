#define LOCAL
#include <bits/stdc++.h>
#define ll long long
#define pii pair <int, int>
#define fir first
#define sec second
#define mp(a, b) make_pair(a, b)
#define pbk(x) push_back(x)
using namespace std;

const int N = 500010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

struct Node {int l, r, val;} e[N], ne[N];
struct Bit {
    ll val[2][N]; int lmt;
    
    inline void init(int x) {lmt = x;}
    inline void reset() {while (lmt) val[0][lmt] = val[1][lmt] = 0, lmt --;}
    
    inline void change(int x, ll y) {
        for (int i = x; i <= lmt; i += (i & -i))
          val[0][i] += y, val[1][i] += y * x;
    }

    inline ll ask(int x) {
        ll res = 0;
        for (int i = x; i; i -= (i & -i))
          res += 1ll * (x + 1) * val[0][i] - val[1][i];
        return res;
    }

    inline void modify(int x, int y, ll c) {change(x, c), change(y + 1, -c);}
    inline ll query(int x, int y) {return ask(y) - ask(x - 1);}
} t;

int T, n, q, a[N], cnt, tot; ll ans[N];

vector <pii > sq[N];

inline void reset() {
    for (int i = 1; i <= n; ++ i) sq[i].clear();
    t.reset(); cnt = 0;
}

inline bool check(int x) {int dv = sqrt(x); return (dv * dv) == x;}

void MAIN() {
    read(n), read(q); reset(); t.init(n);
    for (int i = 1; i <= n; ++ i) read(a[i]);
    for (int i = 1; i <= q; ++ i) {
        int l, r; read(l), read(r);
        sq[r].pbk(mp(l, i));
    }
    for (int i = 1; i <= n; ++ i) {
        tot = 0;
        e[++ cnt] = (Node){i, i, a[i]};
        for (int j = 1; j <= cnt; ++ j) {
            Node now = e[j]; now.val &= a[i];
            if (tot && ne[tot].val == now.val)
              ne[tot].r = now.r;
            else ne[++ tot] = now;
        }
        cnt = tot;
        for (int j = 1; j <= cnt; ++ j) e[j] = ne[j];
        for (int j = 1; j <= cnt; ++ j)
          if (check(e[j].val)) t.modify(e[j].l, e[j].r, 1);
        for (auto now : sq[i]) ans[now.sec] = t.query(now.fir, i);
    }
    for (int i = 1; i <= q; ++ i) printf("%lld\n", ans[i]);
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(T); while (T --) MAIN(); return 0;
}
