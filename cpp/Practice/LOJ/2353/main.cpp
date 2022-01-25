#define LOCAL
#include <bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T Max(T x, T y) {return x > y ? x : y;}

struct Point {
    ld x, y;

    inline Point() {}
    inline Point(ld _x, ld _y) {x = _x, y = _y;}
    inline bool operator < (const Point b) const {return x == b.x ? y < b.y : x < b.x;}
    inline ld operator ^ (const Point b) const {return x * b.y - y * b.x;}
    inline Point operator - (const Point b) const {return Point(x - b.x, y - b.y);}
} p[N];

int n, s, tmp[N], q[N], slp[N], slp_cp[N]; ld f[N], slope[N], a[N], b[N], r[N];

inline long double Y(int x) {return f[x] / (r[x] * a[x] + b[x]);}
inline long double X(int x) {return Y(x) * r[x];}

inline bool cmp1(int x, int y) {return p[x].x == p[y].x ? p[x].y < p[y].y : p[x].x < p[y].x;}
inline bool cmp2(int x, int y) {return slope[x] > slope[y];}

inline long double get_slope(int x, int y) {return (p[x].y - p[y].y) / (p[x].x - p[y].x);}
inline long double calc(int x, int y) {return p[y].x * a[x] + p[y].y * b[x];}
inline bool illegal(int x1, int x2, int y) {return ((p[y] - p[x2]) ^ (p[x1] - p[x2])) >= 0;}

void cdq(int x, int y) {
    if (x == y) {f[x] = Max(f[x], f[x - 1]), p[x] = Point(X(x), Y(x)); return;}
    int mid = x + y >> 1, frt = 0, tal = -1; cdq(x, mid);
    for (int i = mid + 1; i <= y; ++ i) slp_cp[i] = slp[i];
    sort(tmp + x, tmp + mid + 1, cmp1);
    sort(slp_cp + mid + 1, slp_cp + y + 1, cmp2);
    for (int i = x; i <= mid; ++ i) {
        while (frt < tal && illegal(q[tal - 1], q[tal], tmp[i])) -- tal;
        q[++ tal] = tmp[i];
    }
    for (int i = mid + 1; i <= y; ++ i) {
        while (frt < tal && get_slope(q[frt], q[frt + 1]) > slope[slp_cp[i]]) ++ frt;
        f[slp_cp[i]] = Max(f[slp_cp[i]], calc(slp_cp[i], q[frt]));
    }
    cdq(mid + 1, y);
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(s); f[1] = s;
    for (int i = 1; i <= n; ++ i)
      scanf("%Lf%Lf%Lf", &a[i], &b[i], &r[i]);
    for (int i = 1; i <= n; ++ i) slope[i] = - a[i] / b[i];
    for (int i = 1; i <= n; ++ i) slp[i] = i, tmp[i] = i;
    cdq(1, n); printf("%.3Lf", f[n]); return 0;
}
