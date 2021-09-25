#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 1010;

struct Point {
    int x, y;

    inline Point operator - (const Point b) const {
        return (Point){x - b.x, y - b.y};
    }

    inline Point operator + (const Point b) const {
        return (Point){x + b.x, y + b.y};
    }
} p[N];

inline ll dot(Point a, Point b) {return a.x * b.x + a.y * b.y;}
inline ll cross(Point a, Point b) {return 1ll * a.x * b.y - 1ll * a.y * b.x;}
inline ll dis(Point a, Point b) {return dot(a - b, a - b);}


bool intersection(Point a, Point b, Point c, Point d) {
    // printf("%d,%d %d,%d %d,%d %d,%d\n", a.x, a.y, b.x, b.y, c.x, c.y, d.x, d.y);
    // printf(">> %d %d\n", max(a.x, b.x), min(c.x, d.x));
    if (max(c.x, d.x) <= min(a.x, b.x) || max(a.x, b.x) <= min(c.x, d.x) || max(c.y, d.y) <= min(a.y, b.y) || max(a.y, b.y) <= min(c.y, d.y)) return false;
    // printf("test one unpass.\n");
    ll res1 = cross(a - d, c - d), res2 = cross(b - d, c - d);
    ll res3 = cross(d - b, a - b), res4 = cross(c - b, a - b);
    if ((res1 <= 0 && res2 <= 0) || (res1 >= 0 && res2 >= 0)) return false;
    if ((res3 <= 0 && res4 <= 0) || (res3 >= 0 && res4 >= 0)) return false;
    return true;
}


int n, ans;

bool check(int a, int b) {
    // printf("now: %d %d\n", a, b);
    for (int i = 1; i <= n; ++ i)
      for (int j = i + 1; j <= n; ++ j) {
          if ((a == i && b == j) || (a == j && b == i)) continue;
          // printf("Test: %d %d\n", i, j);
          if (intersection(p[a], p[b], p[i], p[j])) return false;
      }
    return true;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i)
      scanf("%d%d", &p[i].x, &p[i].y);
    for (int i = 1; i <= n; ++ i)
      for (int j = i + 1; j <= n; ++ j)
        if (check(i, j)) {
            // printf("%d %d\n", i, j);
            ++ ans;
        } 
    printf("%d", ans);
    return 0;
}
