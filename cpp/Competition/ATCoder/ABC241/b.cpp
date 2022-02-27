#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 100010;
const int INF = 0x3f3f3f3f;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int n, m, a[N], b[N];

map <int, int> mp;

int main() {
    read(n), read(m);
    for (int i = 1; i <= n; ++ i) read(a[i]), ++ mp[a[i]];
    for (int i = 1; i <= m; ++ i) {
        read(b[i]);
        if (mp[b[i]] > 0) -- mp[b[i]];
        else {puts("No"); return 0;}
    }
    puts("Yes"); return (0 - 0);
}
