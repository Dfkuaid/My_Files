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

ll x;

int main() {
    read(x);
    ll ans = x / 10;
    if (x < 0 && ans * 10 > x) -- ans;
    printf("%lld\n", ans);
    return 0;
}
