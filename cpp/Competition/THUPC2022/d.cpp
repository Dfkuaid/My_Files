#define LOCAL
#include <bits/stdc++.h>
#define ll long long
#define pbk(x) push_back(x)
using namespace std;

const int N = 1000010;
const int INF = 0x3f3f3f3f;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int n, a[N], cnt, vis[N], ans[N][2], acnt;

vector <int> r[N];

inline void add(int x, int y) {ans[++ acnt][0] = x, ans[acnt][1] = y;}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n);
    for (int i = 1; i <= n; ++ i) read(a[i]);
    for (int i = 1; i <= n; ++ i) if (!vis[i]) {
        if (a[i] == i) continue; int p = i; ++ cnt;
        while (!vis[p]) r[cnt].pbk(p), vis[p] = 1, p = a[p];
    }
    for (int i = 1; i <= cnt; ++ i) {
        for (auto v : r[i]) add(v, n + i);
        add(n + i, n + cnt + 1);
        add(n + cnt + 1, r[i][0]);
    }
    add(n + 1, n + cnt + 2);
    for (int i = 1; i < cnt; ++ i) add(n + i, n + i + 1);
    add(n + cnt, n + cnt + 2); add(n + cnt + 1, n + cnt + 2);
    printf("%d %d\n", cnt ? cnt + 2 : 0, acnt);
    for (int i = 1; i <= acnt; ++ i)
      printf("%d %d\n", ans[i][0], ans[i][1]);
    return (0 - 0);
}
