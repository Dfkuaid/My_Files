#define LOCAL
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#define ll long long
using namespace std;

const int N = 200010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T Max(T x, T y) {return x > y ? x : y;}

int n, w[N], f[N][2], max_odd, max_even;

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n);
    for (int i = 1; i <= n; ++ i) read(w[i]);
    for (int i = 1; i <= n; ++ i) {
        f[i][0] = max_odd - w[i];
        f[i][1] = max_even + w[i];
        max_odd = Max(max_odd, f[i][1]);
        max_even = Max(max_even, f[i][0]);
    }
    printf("%d", Max(max_odd, max_even)); return 0;
}
