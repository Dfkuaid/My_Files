#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 500010;
const int INF = 0x3fffffff;

struct Edge {int u, v, nxt;} e[N];
struct Trie {int ch[26], fail, end, fa;};
struct Query {int idx, val;};

int n, ecnt = 1, head[N], m, dfn[N], ep[N];
int T, siz[N], rt = 1, sum[N], ans[N];

vector <Query> qes[N];

inline void add(int u, int v) {
    e[ecnt].u = u, e[ecnt].v = v;
    e[ecnt].nxt = head[u], head[u] = ecnt ++;
}

struct AC_automaton {
    Trie t[N], t_copy[N]; int cnt;

    inline AC_automaton() {cnt = 0, t[0].fail = -1;}
    inline void build() {
        queue <int> q;
        memcpy(t_copy, t, sizeof(t));
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
        for (int i = 1; i <= cnt; ++ i) add(t[i].fail, i);
    }
} ac;

inline void ub(int &x) {x += x & (-x);}
inline void db(int &x) {x -= x & (-x);}
inline void modify(int x, int t) {for(; x <= T; ub(x)) sum[x] += t;}
inline int query(int x) {
    int res = 0; for(; x > 0; db(x)) res += sum[x]; return res;
}

void dfs_fail(int x) {
    siz[x] = 1, dfn[x] = ++ T;
    for (int i = head[x]; i; i = e[i].nxt){
        dfs_fail(e[i].v);
        siz[x] += siz[e[i].v];
    }
}

void dfs_trie(int x) {
    modify(dfn[x], 1);
    if (ac.t[x].end) {
        int y = ac.t[x].end, vs = qes[y].size();
        for (int i = 0; i < vs; ++ i) {
            int id = qes[y][i].idx, vl = qes[y][i].val;
            ans[id] = query(dfn[ep[vl]] + siz[ep[vl]] - 1) - query(dfn[ep[vl]] - 1);
        }
    }
    for (int i = 0; i < 26; ++ i)
      if (ac.t_copy[x].ch[i]) dfs_trie(ac.t_copy[x].ch[i]);
    modify(dfn[x], -1);
}

int main() {
    char s[N]; scanf("%s", s);
    int n = strlen(s), p = 0, tot = 0;
    for (int i = 0; i < n; ++ i) {
        if (s[i] == 'B') p = ac.t[p].fa;
        else if (s[i] == 'P')
          ep[++ tot] = p, ac.t[p].end = tot;
        else {
            int k = s[i] - 'a';
            if (!ac.t[p].ch[k]) {
                ac.t[p].ch[k] = ++ ac.cnt;
                ac.t[ac.cnt].fa = p;
            }
            p = ac.t[p].ch[k];
        }
    }
    scanf("%d", &m); ac.build();
    for (int i = 1; i <= m; ++ i) {
        int x, y; scanf("%d%d", &x, &y);
        qes[y].push_back((Query){i, x});
    } ac.build_tree(); dfs_fail(0); dfs_trie(0);
    for (int i = 1; i <= m; ++ i) printf("%d\n", ans[i]);
    return 0;
}