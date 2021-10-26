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

struct Edge {int u, v;} e[N];
struct List {int lst, nxt, id, col;} p[N];

int n, T, tal, frt = 1, ecnt; char s[N];

inline int get_col(char c) {return (c == 'R') ? 0 : ((c == 'G') ? 1 : 2);}

inline bool check(List x) {
    if (p[x.nxt].col == x.col || p[p[x.nxt].nxt].col == x.col
        || p[x.nxt].col == p[p[x.nxt].nxt].col) return false;
    return true;
}

inline void solve() {
    int now = frt;
    while (ecnt < n - 3) {
        while (check(p[now]) && ecnt < n - 3) {
            e[++ ecnt].u = p[now].id;
            e[ecnt].v = p[p[p[now].nxt].nxt].id;
            p[now].nxt = p[p[now].nxt].nxt;
        }
        now = p[now].lst;
    }
    for (int i = 1; i <= ecnt; ++ i)
      printf("%d %d\n", e[i].u, e[i].v);
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n); scanf("%s", s + 1);
    for (int i = 1; i <= n; ++ i)
      p[i].id = i, p[i].col = get_col(s[i]);
    for (int i = 1; i <= n; ++ i)
      p[i].lst = i - 1, p[i].nxt = i + 1;
    p[1].lst = n, p[n].nxt = 1;
    solve(); return 0;
}
