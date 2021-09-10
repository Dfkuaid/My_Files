#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 10010;
const int MOD = 1e4 + 7;
const int INF = 0x3fffffff;

struct Trie {int ch[30], fail, tag;};
struct AC {
    Trie t[N]; int cnt;

    inline AC() {cnt = 0;}
    inline void insert(char *s) {
        int p = 0, len = strlen(s);
        for (int i = 0; i < len; ++ i) {
            int k = s[i] - 'A';
            if (!t[p].ch[k]) t[p].ch[k] = ++ cnt;
            p = t[p].ch[k];
        }
        t[p].tag |= true;
    }

    inline void build() {
        queue <int> q;
        for (int i = 0; i < 26; ++ i)
          if (t[0].ch[i]) q.push(t[0].ch[i]);
        while (q.size()) {
            int now = q.front(); q.pop();
            for (int i = 0; i < 26; ++ i)
              if (t[now].ch[i]) {
                  t[t[now].ch[i]].fail = t[t[now].fail].ch[i];
                  t[t[now].ch[i]].tag |= t[t[t[now].fail].ch[i]].tag;
                  q.push(t[now].ch[i]);
              } else t[now].ch[i] = t[t[now].fail].ch[i];
        }
    }
} ac;

int n, m, f[N][N], ans;
char s[N];

inline int fpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) (res *= a) %= MOD;
        b >>= 1, (a *= a) %= MOD;
    }
    return res;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i)
      scanf("%s", s), ac.insert(s);
    ac.build(); f[0][0] = 1;
    for (int i = 1; i <= m; ++ i)
      for (int j = 0; j <= ac.cnt; ++ j)
        for (int k = 0; k < 26; ++ k)
          if (!ac.t[ac.t[j].ch[k]].tag)
            (f[i][ac.t[j].ch[k]] += f[i - 1][j]) %= MOD;
    for (int i = 0; i <= ac.cnt; ++ i)
      (ans += f[m][i]) %= MOD;
    printf("%d", (fpow(26, m) - ans + MOD) % MOD);
    return 0;
}