#include <iostream>
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 1000010;
const int INF = 0x3fffffff;

struct Trie {
    int ch[30];
    int fail, tag, siz;
    inline Trie() {fail = tag = siz = 0;}
};

struct Edge {
    int u, v;
    int nxt;
};
Edge e[N];


int ecnt = 1, head[N], end[N];

struct AC_automaton {
    Trie t[N]; int cnt;

    inline AC_automaton() {cnt = 0;}

    inline void insert(char *s, int id) {
        int now = 0, len = strlen(s);
        for (int i = 0; i < len; ++ i) {
            int k = s[i] - 'a';
            if (!t[now].ch[k]) t[now].ch[k] = ++ cnt;
            now = t[now].ch[k];
        }
        ++ t[now].tag;
        end[id] = now;
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

    inline void query(char *s) {
        int now = 0, len = strlen(s);
        for (int i = 0; i < len; ++ i) {
            now = t[now].ch[s[i] - 'a'];
            t[now].siz ++;
        }
    }
};
AC_automaton ac;

inline void add(const int &u, const int &v) {
    e[ecnt].u = u, e[ecnt].v = v;
    e[ecnt].nxt = head[u], head[u] = ecnt ++;
}

inline void dp(int x) {
    for (int i = head[x]; i; i = e[i].nxt) {
        dp(e[i].v);
        ac.t[x].siz += ac.t[e[i].v].siz;
    }
}

int main() {
    int n; scanf("%d", &n);
    char s[N], t[N];
    for (int i = 1; i <= n; ++ i)
      scanf("%s", s), ac.insert(s, i);
    scanf("%s", t); ac.build();
    ac.query(t);
    for (int i = 1; i <= ac.cnt; i ++)
      add(ac.t[i].fail, i);
    dp(0);
    for (int i = 1; i <= n; ++ i)
      printf("%d\n", ac.t[end[i]].siz);
    return 0;
}