#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int t, a, b, c;

void MAIN() {
    read(a), read(b), read(c);
    if ((a + b + c) % 3) puts("1");
    else puts("0");
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(t); while (t --) MAIN(); return 0;
}
