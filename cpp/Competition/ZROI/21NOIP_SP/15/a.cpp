#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 20010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int n, m, ans; char s[N];

bitset <64> X[N], Y[N];

int main() {
#ifdef LOCAL
    freopen("ex_a2.in", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(m);
    for (int i = 1; i <= m; ++ i) {
        scanf("%s", s + 1);
        for (int j = 1; j <= n; ++ j) {
            if (s[j] == '2' || s[j] == '3')
              X[j][i - 1] = 1;
            if (s[j] == '1' || s[j] == '3')
              Y[j][i - 1] = 1;
        }
    }
    for (int i = 2; i <= n; ++ i)
      for (int j = 1; j < i; ++ j)
        ans += (((X[i] & Y[j]) | (Y[i] & X[j])).count() & 1);
    printf("%d", ans); return 0;
}
