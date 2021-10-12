#define LOCAL
#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int T, n, k, a[N], ans = -1, s[N], LMT, st[N][3];

void dfs(int t, int tot, int lsum, int rsum) {
    if (~ans) return;
    if (t == LMT + 1) {if (lsum - rsum == T) ans = 1;return;}
    if (tot < k && !(~ans)) s[t] = 0, dfs(t + 1, tot + 1, lsum, rsum);
    if (!(~ans)) s[t] = 1, dfs(t + 1, tot, lsum + a[t], rsum);
    if (!(~ans)) s[t] = 2, dfs(t + 1, tot, lsum, rsum + a[t]);
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n); read(k); LMT = min(n, 25);
    int tot[3]; tot[0] = tot[1] = tot[2] = 0;
    for (int i = 1; i <= n; ++ i) read(a[i]);
    for (int i = 26; i <= n; ++ i){
        if (T > 0) T -= a[i], st[++ st[0][1]][1] = i;
        else T += a[i], st[++ st[0][2]][2] = i;
    }
    dfs(1, 0, 0, 0);
    if (!(~ans)) {puts("-1"); return 0;}
    for (int i = 1; i <= LMT; ++ i) ++ tot[s[i]];
    printf("%d ", tot[1] + st[0][1]);
    for (int i = 1; i <= st[0][1]; ++ i)
      printf("%d ", st[i][1]);
    for (int i = 1; i <= LMT; ++ i)
      if (s[i] == 1) printf("%d ", i);
    printf("\n%d ", tot[2] + st[0][2]);
    for (int i = 1; i <= st[0][2]; ++ i)
      printf("%d ", st[i][2]);
    for (int i = 1; i <= LMT; ++ i)
      if (s[i] == 2) printf("%d ", i);
    printf("\n"); return 0;
}
