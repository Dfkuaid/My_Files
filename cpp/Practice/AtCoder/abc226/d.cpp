#define LOCAL
#include <bits/stdc++.h>
#define ll long long
#define mp(a, b) make_pair(a, b)
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T Abs(const T &x) {return x < 0 ? -x : x;}

struct Town {int x, y;} a[N];

int n, cnt;

map <pair <int, int>, bool> m;

int gcd(int x, int y) {return y ? gcd(y, x % y) : x;}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n);
    for (int i = 1; i <= n; ++ i)
      read(a[i].x), read(a[i].y);
    for (int i = 1; i <= n; ++ i)
      for (int j = 1; j <= n; ++ j) {
          if (i == j) continue;
          int dx = a[i].x - a[j].x;
          int dy = a[i].y - a[j].y;
          int g = gcd(Abs(dx), Abs(dy));
          if (!m[mp(dx / g, dy / g)])
            ++ cnt, m[mp(dx / g, dy / g)] = 1;
      }
    printf("%d", cnt); return 0;
}
