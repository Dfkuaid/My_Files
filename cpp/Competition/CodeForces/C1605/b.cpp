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

int t, n, one_tot, pos[2][N], cnt; char s[N];

void MAIN() {
    one_tot = 0; cnt = 0;
    read(n); scanf("%s", s + 1);
    for (int i = 1; i <= n; ++ i)
      if (s[i] - '0') ++ one_tot;
    int l = 1, r = n;
    while (l <= r) {
        while (l <= n && !(s[l] - '0')) ++ l;
        while (r >= 1 && s[r] - '0') -- r;
        if (l < r) pos[0][++ cnt] = l, pos[1][cnt] = r;
        ++ l, -- r;
    }
    if (cnt) printf("1\n");
    printf("%d ", cnt * 2);
    for (int i = 1; i <= cnt; ++ i)
      printf("%d ", pos[0][i]);
    for (int i = cnt; i >= 1; -- i)
      printf("%d ", pos[1][i]);
    puts("");
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(t); while (t --) MAIN(); return 0;
}
