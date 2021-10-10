#define LOCAL
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T abs(T &x) {return x < 0 ? -x : x;}
template <typename T> inline T Max(T &a, T &b) {return a > b ? a : b;}
template <typename T> inline T Min(T &a, T &b) {return a < b ? a : b;}

struct Point {int x, y;} p[N];
struct Status {int x, y, s, val, t[10][10];};

int n, ans = INF;

inline int calc(int a, int b) {
    return abs(p[a].x - p[b].x) + abs(p[a].y - p[b].y) + 1;
}

inline Status NEW(int x, int y, int s, int val) {return (Status){x, y, s, val};}
inline void update(Status s, int x, int y) {

}

inline int solve_1() {
    if (n <= 1) return 1; if (n == 2) return calc(1, 2);
    int mxx = -INF, mnx = INF, mxy = -INF, mny = INF;
    for (int i = 1; i <= n; ++ i) {
        mxx = Max(mxx, p[i].x);
        mnx = Min(mnx, p[i].x);
        mxy = Max(mxy, p[i].y);
        mny = Min(mny, p[i].y);
    }
    return mxx - mnx + mxy - mny + 1;
}

int m[10][10], vis[10][10][600];
const int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

inline void solve_2() {
    int upon_limit_x = -INF, down_limit_x = INF;
    int upon_limit_y = -INF, down_limit_y = INF;
    for (int i = 1; i <= n; ++ i) {
        upon_limit_x = Max(upon_limit_x, p[i].x);
        down_limit_x = Min(down_limit_x, p[i].x);
        upon_limit_y = Max(upon_limit_y, p[i].y);
        down_limit_y = Min(down_limit_y, p[i].y);
        m[p[i].x][p[i].y] = i;
    }
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n);
    for (int i = 1; i <= n; ++ i)
      read(p[i].x), read(p[i].y);
    if (n <= 4) printf("%d", solve_1());
    else solve_2(), printf("%d", ans);
    return 0;
}
