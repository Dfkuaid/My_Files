#define LOCAL
#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 500010;
const int M = 3000010;
const int MOD = 2908361;
const ll std_block[8] = {
    276951438, 294753618, 438951276, 492357816,
    618753294, 672159834, 816357492, 834159672,
};

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

struct Status {ll val; int cnt;};
struct Hash {
    int head[M], nxt[N], cnt, val[N];

    inline void init() {cnt = 0; mset(head, 0);}
    inline void insert(ll x) {
        int H = x % MOD; val[++ cnt] = x;
        nxt[cnt] = head[H], head[H] = cnt;
    }

    inline int find(ll x) {
        int H = x % MOD;
        for (int i = head[H]; i; i = nxt[i])
          if (val[i] == x) return i;
        return -1;
    }
} hsh;

int t, T, vis[N]; ll p[11];

inline ll change(ll x, int op) {
    int p1 = 0, p2 = 0;
    if (op == 1) p1 = 1, p2 = 2; else if (op == 2) p1 = 2, p2 = 3;
    else if (op == 3) p1 = 1, p2 = 4; else if (op == 4) p1 = 2, p2 = 5;
    else if (op == 5) p1 = 3, p2 = 6; else if (op == 6) p1 = 4, p2 = 5;
    else if (op == 7) p1 = 5, p2 = 6; else if (op == 8) p1 = 4, p2 = 7;
    else if (op == 9) p1 = 5, p2 = 8; else if (op == 10) p1 = 6, p2 = 9;
    else if (op == 11) p1 = 7, p2 = 8; else if (op == 12) p1 = 8, p2 = 9;
    int n1 = x % p[p1] / p[p1 - 1], n2 = x % p[p2] / p[p2 - 1];
    x -= n1 * p[p1 - 1] + n2 * p[p2 - 1];
    x += n1 * p[p2 - 1] + n2 * p[p1 - 1];
    return x;
}

Status q[N]; int frt, tal, a[N];

inline void prework() {
    for (int i = 1; i <= 9; ++ i) a[i] = i;
    for (int i = 1; i <= 362880 - 1; ++ i) {
        ll val = 0;
        for (int j = 1; j <= 9; ++ j)
          val *= 10, val += a[j];
        hsh.insert(val);
        next_permutation(a + 1, a + 9 + 1);
    }
}

int bfs(ll st) {
    frt = 0, tal = -1; q[++ tal] = (Status){st, 0};
    while (frt <= tal) {
        ll now = q[frt].val; int sp = q[frt ++].cnt;
        if (vis[hsh.find(now)] == -1) return sp;
        for (int i = 1; i <= 12; ++ i) {
            ll ns = change(now, i), hns = hsh.find(ns);
            if (vis[hns] == -1) return sp + 1;
            if (vis[hns] != T) {
                q[++ tal] = (Status){ns, sp + 1};
                vis[hns] = T;
            }
        }
    }
    return -1;
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    hsh.init(); p[0] = 1; read(t); prework();
    for (int i = 1; i <= 10; ++ i)
      p[i] = p[i - 1] * 10;
    for (int i = 0; i <= 7; ++ i)
      vis[hsh.find(std_block[i])] = -1;
    for (T = 1; T <= t; ++ T) {
        ll x = 0, y = 0;
        for (int i = 0; i <= 8; ++ i)
          read(y), x = x * 10 + y;
        printf("%d\n", bfs(x));
    }
    return 0;
}
