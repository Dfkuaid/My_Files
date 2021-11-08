#define LOCAL
#include <bits/stdc++.h>
#define ll long long
#define db double
using namespace std;

const int N = 200010;
const db eps = 1e-5;
const int LMT = 1e7;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T Max(T a, T b) {return a > b ? a : b;}

struct Bit {
    int val[N << 1], len;
    
    inline Bit() {len = 0;}
    inline void init(int x) {len = x;}
    inline void reset() {while (len) val[len --] = 0;}
    void insert(int x, int c) {while (x <= len) val[x] = Max(val[x], c), x += (x & -x);}
    inline int query(int x) {int res = 0; while (x) res = Max(res, val[x]), x -= (x & -x); return res;}
} t;

#define lb(l, len, x) lower_bound(l + 1, l + len + 1, x)

int n, K, s[N], f[N], pos[N]; db lt[N];

bool check(db x) {
    for (int i = 1; i <= n; ++ i) lt[i] = 1.0 * s[i] - i * x;
    lt[n + 1] = 0; sort(lt + 1, lt + n + 2); 
    int len = unique(lt + 1, lt + n + 2) - lt - 1;
    for (int i = 1; i <= n; ++ i) pos[i] = lb(lt, len, 1.0 * s[i] - i * x) - lt;
    t.reset(), t.init(len); t.insert(lb(lt, len, 0) - lt, 1);
    for (int i = 1; i <= n; ++ i) {
        f[i] = t.query(pos[i]); if (f[i]) t.insert(pos[i], f[i] + 1);
    }
    return f[n] >= K;
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(K);
    for (int i = 1; i <= n; ++ i) read(s[i]);
    for (int i = 2; i <= n; ++ i) s[i] += s[i - 1];
    db l = 0.0, r = 100, res = 0.0;
    while (r - l >= eps) {
        db mid = (l + r) / 2.0;
        if (check(mid)) res = mid, l = mid;
        else r = mid;
    }
    printf("%lf", res); return 0;
}
