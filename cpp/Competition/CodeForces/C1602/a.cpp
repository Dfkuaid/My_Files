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

char s[N]; int t, pos, n;

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(t);
    while (t --) {
        scanf("%s", s + 1); pos = 1; n = strlen(s + 1);
        for (int i = 2; i <= n; ++ i)
          if (s[pos] > s[i]) pos = i;
        putchar(s[pos]); putchar(' ');
        for (int i = 1; i <= n; ++ i)
          if (i != pos) putchar(s[i]);
        putchar('\n');
    }
    return 0;
}
