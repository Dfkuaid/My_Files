#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

template <typename T> inline void read(T &x) {
    int f = 1; x = 0; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (f == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c -'0';
    x *= f;
}

int t, n, a[N], b[N], mx1, mx2;

inline void MAIN() {
    read(n); mx1 = mx2 = -1;
    for (int i = 1; i <= n; ++ i) read(a[i]);
    for (int i = 1; i <= n; ++ i) read(b[i]);
    for (int i = 1; i <= n; ++ i) if (a[i] > b[i]) swap(a[i], b[i]);
    for (int i = 1; i <= n; ++ i) mx1 = max(mx1, a[i]);
    for (int i = 1; i <= n; ++ i) mx2 = max(mx2, b[i]);
    printf("%d\n", mx1 * mx2);
}

int main() {
    read(t); while (t --) MAIN(); return 0;
}
