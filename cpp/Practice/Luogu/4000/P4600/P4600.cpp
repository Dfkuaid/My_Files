#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 1000010;
const int MOD = 1e9 + 7;
const int INF = 0x3fffffff;

struct Edge {int u, v, nxt;} e[N];
struct Trie {int ch[26], fail;};

int n, ecnt = 1, head[N], m; ll ans[N];
vector<int> ds[N];

inline void add(int u, int v) {
    e[ecnt].u = u, e[ecnt].v = v;
    e[ecnt].nxt = head[u], head[u] = ecnt ++;
}

struct AC_automaton {
    Trie t[N]; int cnt;

    inline AC_automaton() {cnt = 0, t[0].fail = -1;}
    inline void insert(char *s, int id) {
        int p = 0, len = strlen(s);
        ds[id].push_back(0);
        for (int i = 0; i < len; ++ i) {
            int k = s[i] - 'a';
            if (!t[p].ch[k]) {
                t[p].ch[k] = ++ cnt;
                ans[cnt + 1] = (ans[p + 1] * 26 % MOD + (ll)k) % MOD;
            }
            p = t[p].ch[k]; ds[id].push_back(p + 1);
        }
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
                  q.push(t[now].ch[i]);
              } else t[now].ch[i] = t[t[now].fail].ch[i];
        }
    }

    inline void build_tree() {
        for (int i = 1; i <= cnt; ++ i) add(t[i].fail + 1, i + 1);
    }
} ac;

int dfn[N], son[N], siz[N], top[N], T, f[N], d[N];

void dfs1(int x, int fa) {
    siz[x] = 1, f[x] = fa, d[x] = d[fa] + 1;
    for (int i = head[x]; i; i = e[i].nxt)
      if (e[i].v != fa) {
          dfs1(e[i].v, x);
          siz[x] += siz[e[i].v];
          if (siz[e[i].v] > siz[son[x]])
            son[x] = e[i].v;
      }
}

void dfs2(int x, int t) {
    dfn[x] = ++ T, top[x] = t;
    if (!son[x]) {return;} dfs2(son[x], t);
    for (int i = head[x]; i; i = e[i].nxt)
      if (e[i].v != f[x] && e[i].v != son[x])
        dfs2(e[i].v, e[i].v);
}

inline int LCA(int a, int b) {
    while (top[a] != top[b]) {
        if (d[top[a]] < d[top[b]]) swap(a, b);
        a = f[top[a]];
    }
    if (d[a] < d[b]) {swap(a, b);} return b;
}

int main() {
    scanf("%d", &n); char s[N];
    for (int i = 1; i <= n; ++ i) {
        scanf("%s", s);
        ac.insert(s, i);
    }
    ac.build(); ac.build_tree();
    dfs1(1, 0); dfs2(1, 1);
    scanf("%d", &m);
    while (m --) {
        int i, j, k, l;
        scanf("%d%d%d%d", &i, &j, &k, &l);
        int lca = LCA(ds[i][j], ds[k][l]);
        printf("%d\n", ans[lca]);
    }
    return 0;
}