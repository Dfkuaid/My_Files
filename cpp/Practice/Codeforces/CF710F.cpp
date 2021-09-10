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
    int ch[26];
    int fail;
};

struct ACAM {
    Trie t[N]; int son[N][26], tot;
    int rt[N], last, siz[N], cnt[N], end[N];

    inline void build(int root) {
        queue <int> q;
        for (int i = 0; i < 26; ++ i)
          if (son[root][i]) {
              t[t[root].ch[i] = son[root][i]].fail = root;
              q.push(t[root].ch[i]);
          } else t[root].ch[i] = root;
        while (q.size()) {
            int now = q.front(); q.pop();
            for (int i = 0; i < 26; ++ i)
              if (son[now][i]) {
                  t[now].ch[i] = son[now][i];
                  t[t[now].ch[i]].fail = t[t[now].fail].ch[i];
                  q.push(t[now].ch[i]);
              } else t[now].ch[i] = t[t[now].fail].ch[i];
            cnt[now] = end[now] + cnt[t[now].fail];
        }
    }

    inline int merge(int a, int b) {
        if (!a || !b) return a + b;
        end[a] += end[b];
        for (int i = 0; i < 26; ++ i)
          son[a][i] = merge(son[a][i], son[b][i]);
        return a;
    }

    inline void insert(char *s) {
        int len = strlen(s); rt[++ last] = ++ tot;
        int now = rt[last]; siz[last] = 1;
        for (int i = 0; i < len; ++ i) {
            int k = s[i] - 'a';
            if (!son[now][k])
              son[now][k] = ++ tot;
            now = son[now][k];
        } end[now] = 1;
        while (siz[last] == siz[last - 1]) {
            rt[-- last] = merge(rt[last], rt[last + 1]);
            siz[last] += siz[last + 1];
        }
        build(rt[last]);
    }

    inline int query(char *s) {
        int res = 0, len = strlen(s);
        for (int i = 1; i <= last; i ++)
          for (int j = 0, now = rt[i]; j < len; j ++)
            now = t[now].ch[s[j] - 'a'], res += cnt[now];
        return res;
    }
};
ACAM ac1, ac2;

char s[N];

int main() {
    int m; scanf("%d", &m);
    for (int i = 1; i <= m; ++ i) {
        int op; scanf("%d", &op);
        scanf("%s", s);
        if (op == 1) ac1.insert(s);
        else if (op == 2) ac2.insert(s);
        else {
            printf("%d\n", ac1.query(s) - ac2.query(s));
            fflush(stdout);
        }
    }
    return 0;
}