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
    int fail, tag;
};

struct AC_automaton {
    Trie t[N]; int cnt;

    inline AC_automaton() {cnt = 0;}

    inline void insert(char *s) {
        int now = 0, len = strlen(s);
        for (int i = 0; i < len; ++ i) {
            int k = s[i] - 'a';
            if (!t[now].ch[k]) t[now].ch[k] = ++ cnt;
            now = t[now].ch[k];
        }
        ++ t[now].tag;
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

    inline int query(char *s) {
        int res = 0, now = 0, len = strlen(s);
        for (int i = 0; i < len; ++ i) {
            now = t[now].ch[s[i] - 'a'];
            for (int j = now; j && (~t[j].tag); j = t[j].fail)
              res += t[j].tag, t[j].tag = -1;
        }
        return res;
    }
};
AC_automaton ac;

int main() {
    int n; scanf("%d", &n);
    char s[N], t[N];
    for (int i = 1; i <= n; ++ i)
      scanf("%s", s), ac.insert(s);
    scanf("%s", t); ac.build();
    printf("%d", ac.query(t));
    return 0;
}