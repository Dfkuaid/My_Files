#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 2000010;
const int INF = 0x3f3f3f3f;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int n, stk[N], stp; ll x; char s[N];

int main() {
    read(n); read(x); scanf("%s", s + 1);
    for (int i = 1; i <= n; ++ i) {
        if (s[i] == 'U' && stp && stk[stp]) -- stp;
        else if (s[i] == 'U') stk[++ stp] = 0;
        else if (s[i] == 'L') stk[++ stp] = 1;
        else stk[++ stp] = 2;
    }
    for (int i = 1; i <= stp; ++ i) {
        if (!stk[i]) x >>= 1;
        else if (stk[i] == 1) x <<= 1;
        else x = x * 2 + 1;
    }
    printf("%lld", x); return (0 - 0);
}
