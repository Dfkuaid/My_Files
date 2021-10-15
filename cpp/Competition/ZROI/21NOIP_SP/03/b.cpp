#define LOCAL
#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T Max(T a, T b) {return a > b ? a : b;}
template <typename T> inline T Min(T a, T b) {return a < b ? a : b;}

struct Query {int op, r, x, id;} q[N];

int n, m, a[N], mu[N], prm[N], pcnt, nprm[N], sum[N], ans[N];

vector <int> P[N];

void euler(int x) {
    mu[1] = 1;
    for (int i = 2; i <= x; ++ i) {
        if (!nprm[i]) prm[++ pcnt] = i, mu[i] = -1;
        for (int j = 1; j <= pcnt; ++ j) {
            if (prm[j] * i > x) break;
            nprm[prm[j] * i] = true;
            if (i % prm[j]) mu[i * prm[j]] = -mu[i];
            else break;
        }
    }
}

inline bool cmp(Query x, Query y) {return x.r < y.r;}

#define pbk(x) push_back(x)

inline void get_list(int x) {
    if (P[x].size()) return;
    for (int i = 1; i * i <= x; ++ i) if (!(x % i)) {
        P[x].pbk(i); if (i != x / i) P[x].pbk(x / i);
    }
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n); read(m); euler(N >> 1);
    for (int i = 1; i <= n; ++ i) read(a[i]);
    for (int i = 1; i <= m; ++ i) {
        int l, r, x; read(l), read(r), read(x);
        q[(i << 1) - 1] = (Query){-1, l - 1, x, i};
        q[(i << 1)] = (Query){1, r, x, i};
    }
    sort(q + 1, q + (m << 1) + 1, cmp);
    for (int i = 1, j = 1; i <= m << 1; ++ i) {
        for (; j <= n && j <= q[i].r; ++ j) {
            get_list(a[j]);
            for (auto k : P[a[j]]) ++ sum[k];
        }
        get_list(q[i].x);
        for (auto k : P[q[i].x])
          ans[q[i].id] += q[i].op * mu[k] * sum[k];
    }
    for (int i = 1; i <= m; ++ i) printf("%d\n", ans[i]);
    return 0;
}
