#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 1000010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int n, k, cnt, p[N][2]; char s[N];

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(k); scanf("%s", s + 1);
    int lst = 1;
    for (int i = 1; i <= k; ++ i) {
        p[++ cnt][0] = lst; read(p[cnt][1]);
        lst = p[cnt][1] + 1;
    }
    if (k & 1) {
        for (int i = cnt; i >= 1; i -= 2)
          for (int j = p[i][1]; j >= p[i][0]; -- j)
            putchar(s[j]);
        for (int i = 2; i <= cnt; i += 2)
          for (int j = p[i][0]; j <= p[i][1]; ++ j)
            putchar(s[j]);
    } else {
        for (int i = cnt; i >= 1; i -= 2)
          for (int j = p[i][1]; j >= p[i][0]; -- j)
            putchar(s[j]);
        for (int i = 1; i <= cnt; i += 2)
          for (int j = p[i][0]; j <= p[i][1]; ++ j)
            putchar(s[j]);
    }
    for (int i = lst; i <= n; ++ i) putchar(s[i]);
    return 0;
}
