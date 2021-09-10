#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 2000010;
const int INF = 0x3fffffff;

template <typename T>
inline T Max(const T a, const T b) {
    return a > b ? a : b;
}

struct Node {
    int link, len;
    int ch[30];
};

struct Edge {
    int u, v;
    int nxt;
};
Edge e[N];

int head[N], cnt = 1, f[N];

struct SAM {
    Node p[N]; int tot, last;

    inline SAM() {
        p[0].len = 0, p[0].link = -1;
        tot = 0, last = 0;
    }

    inline void insert(int c) {
        int cur = ++ tot; ++ f[cur];
        p[cur].len = p[last].len + 1;
        int now = last;
        while ((~now) && !p[now].ch[c])
          p[now].ch[c] = cur, now = p[now].link;
        if (!(~now)) p[cur].link = 0;
        else {
            int q = p[now].ch[c];
            if (p[q].len == p[now].len + 1)
              p[cur].link = q;
            else {
                int clone = ++ tot; p[clone] = p[q];
                p[clone].len = p[now].len + 1;
                p[cur].link = p[q].link = clone;
                while ((~now) && p[now].ch[c] == q)
                  p[now].ch[c] = clone, now = p[now].link;
            }
        }
        last = cur;
    }
};
SAM sam;

char s[N];
int n, ans;

inline void add(const int u, const int v) {
    e[cnt].u = u, e[cnt].v = v;
    e[cnt].nxt = head[u], head[u] = cnt ++;
}

void dp(int x) {
    for (int i = head[x]; i; i = e[i].nxt) {
        dp(e[i].v); f[x] += f[e[i].v];
    }
    if (f[x] > 1) ans = Max(f[x] * sam.p[x].len, ans);
}

int main() {
    scanf("%s", s); n = strlen(s);
    for (int i = 0; i < n; ++ i)
      sam.insert(s[i] - 'a');
    for (int i = 1; i <= sam.tot; ++ i)
      add(sam.p[i].link, i);
    dp(0);
    printf("%d", ans);
    return 0;
}