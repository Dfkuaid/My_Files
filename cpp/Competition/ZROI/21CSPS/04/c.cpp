#define DEBUG
#include <bits/stdc++.h>
#define db double
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 1000010;
const db INF = 1e10;

template <typename T> inline T ABS(const T &x) {return x < 0 ? -x : x;}

double tana, ans_gap = INF;
int n; ll p, q, nx, ny;

struct Point {
    ll x, y;
    bool operator < (const Point & b) const {
        return -x * p + y * q < -b.x * p + b.y * q;
    }
} a[N];

ll gcd(ll x, ll y) {return y ? gcd(y, x % y) : x;}

db calc(Point x, Point y) {
    return x.x == y.x ? INF : (db)(x.y - y.y) / (db)(x.x - y.x); 
}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    scanf("%d%lld%lld", &n, &p, &q);
    tana = (db)p / (db)q;
    for (int i = 1; i <= n; ++ i)
      scanf("%lld%lld", &a[i].x, &a[i].y);
    sort(a + 1, a + n + 1);
    for (int i = 1; i < n; ++ i) {
        db now_gap = ABS(calc(a[i], a[i + 1]) - tana);
        if (now_gap < ans_gap) {
            ans_gap = now_gap;
            nx = ABS(a[i].x - a[i + 1].x);
            ny = ABS(a[i].y - a[i + 1].y);
        }
    }
    ll g = gcd(ny, nx);
    printf("%lld/%lld", ny / g, nx / g);
    return 0;
}