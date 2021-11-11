#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int t; ll a[6], b[6];

inline void pick(int x, int y) {
    ll z = min(a[x], b[y]);
    a[x] -= z, b[y] -= z, b[y - x] += z;
}

void MAIN() {
    for (int i = 1; i <= 5; ++ i) read(a[i]);
    for (int i = 1; i <= 5; ++ i) read(b[i]);
    a[0] = b[0] = 0;
    pick(5, 5); pick(4, 4); pick(4, 5);
    pick(3, 3); pick(3, 5); pick(3, 4);
    for (int i = 5; i >= 2; -- i) pick(2, i);
    for (int i = 5; i >= 1; -- i) pick(1, i);
    for (int i = 1; i <= 5; ++ i)
      if (a[i]) {puts("No"); return;}
    puts("Yes");
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(t); while (t --) MAIN(); return 0;
}
