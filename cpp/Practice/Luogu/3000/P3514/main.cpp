#define LOCAL
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

int n, q, sum[N], a[N], mx[2], l[N], r[N]; char c[N];

inline void update(int x, int lp, int rp) {
    if (mx[x & 1] < x) mx[x & 1] = x, l[x] = lp, r[x] = rp;
}

inline void get_pos(int x) {
    if (a[l[x + 2]] == 1 && a[r[x + 2]] == 1)
      l[x] = l[x + 2] + 1, r[x] = r[x + 2] - 1;
    else if (a[l[x + 2]] == 2)
      l[x] = l[x + 2] + 1, r[x] = r[x + 2];
    else l[x] = l[x + 2], r[x] = r[x + 2] - 1;
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(q); scanf("%s", c + 1);
    for (int i = 1; i <= n; ++ i) a[i] = c[i] == 'T' ? 2 : 1;
    for (int i = 1; i <= n; ++ i) sum[i] = sum[i - 1] + a[i];
    for (int i = n; i >= 1; -- i) update(sum[i], 1, i);
    for (int i = 1; i <= n; ++ i) update(sum[n] - sum[i - 1], i, n);
    for (int i = mx[1] - 2; i > 0; i -= 2) get_pos(i);
    for (int i = mx[0] - 2; i > 0; i -= 2) get_pos(i);
    while (q --) {
        int x = 0; read(x);
        if (x > mx[x & 1]) printf("NIE\n");
        else printf("%d %d\n", l[x], r[x]);
    }
    return (0 - 0);
}
