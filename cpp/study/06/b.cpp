#define LOCAL
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <cassert>
#define ll long long
using namespace std;

const int N = 110;
const int M = 50010;
const int BASE = 131;
const int MOD = 998244353;
const int INF = 0x3f3f3f3f;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

char s[N], dar[M][N], dar_n[M][N];
int n, m, f[N], len[M], pre[N], ch[N];
int h[N], h_dar[M], pw[N];

inline int trans_char(char c) {
    if (c == 'i' || c == 'j') return 1;
    if (c == 'a' || c == 'b' || c == 'c') return 2;
    if (c == 'd' || c == 'e' || c == 'f') return 3;
    if (c == 'g' || c == 'h') return 4;
    if (c == 'k' || c == 'l') return 5;
    if (c == 'm' || c == 'n') return 6;
    if (c == 'p' || c == 'r' || c == 's') return 7;
    if (c == 't' || c == 'u' || c == 'v') return 8;
    if (c == 'w' || c == 'x' || c == 'y') return 9;
    return 0;
}

inline void trans(int x) {
    for (int i = 1; i <= len[x]; ++ i) dar_n[x][i] = trans_char(dar[x][i]) + '0';
}

inline int get_hash(int x, int L) {
    int l = x - L + 1, r = x;
    return (h[r] - ((1ll * pw[L] * h[l - 1]) % MOD) + MOD) % MOD;
}

void print(int x) {
    if (!x) return; print(pre[x]);
    assert(ch[x] >= 1 && ch[x] <= n);
    printf("%s", dar[ch[x]] + 1);
    if (x != m) putchar(' ');
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    scanf("%s", s + 1); m = strlen(s + 1); read(n);
    memset(f, 0x3f, sizeof f); pw[0] = 1; f[0] = 0;
    for (int i = 1; i <= n; ++ i)
      scanf("%s", dar[i] + 1), len[i] = strlen(dar[i] + 1), trans(i);
    for (int i = 1; i <= m; ++ i) pw[i] = (1ll * pw[i - 1] * BASE) % MOD;
    for (int i = 1; i <= m; ++ i)
      h[i] = (1ll * h[i - 1] * BASE + 1ll * (s[i] - '0' + 1)) % MOD;
    for (int i = 1; i <= n; ++ i) for (int j = 1; j <= len[i]; ++ j)
      h_dar[i] = (1ll * h_dar[i] * BASE + 1ll * (dar_n[i][j] - '0' + 1)) % MOD;
    for (int i = 1; i <= m; ++ i) for (int j = 1; j <= n; ++ j)
      if (len[j] <= i && get_hash(i, len[j]) == h_dar[j]) if (f[i - len[j]] + 1 < f[i])
        f[i] = f[i - len[j]] + 1, pre[i] = i - len[j], ch[i] = j;
    if (f[m] == INF) printf("No solution."); else print(m); return 0;
}
