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

struct stg {
    int id, sum;
};
stg a[160];

char as[160][160];

inline bool cmp(const stg &x, const stg &y) {
    if (x.sum == y.sum) return x.id < y.id;
    else return x.sum > y.sum;
}

struct AC_automaton {
    int t[16000][30], fail[16000], tag[16000]; int cnt;

    inline AC_automaton() {cnt = 0;}

    inline void clear() {
        cnt = 0; mset(tag, 0);
        mset(t, 0); mset(fail, 0);
    }

    inline void insert(char *s, int id) {
        int now = 0, len = strlen(s);
        for (int i = 0; i < len; ++ i) {
            int k = s[i] - 'a';
            if (!t[now][k]) t[now][k] = ++ cnt;
            now = t[now][k];
        }
        tag[now] = id;
    }

    inline void build() {
        queue <int> q;
        for (int i = 0; i < 26; ++ i)
          if (t[0][i]) q.push(t[0][i]);
        while (q.size()) {
            int now = q.front(); q.pop();
            for (int i = 0; i < 26; ++ i)
              if (t[now][i]) {
                  fail[t[now][i]] = t[fail[now]][i];
                  q.push(t[now][i]);
              } else t[now][i] = t[fail[now]][i];
        }
    }

    inline void query(char *s) {
        int now = 0, len = strlen(s);
        for (int i = 0; i < len; ++ i) {
            now = t[now][s[i] - 'a'];
            for (int j = now; j; j = fail[j])
              a[tag[j]].sum ++;
        }
    }
};
AC_automaton ac;

int n;

inline void aclear() {
    for (int i = 0; i < 160; i ++) {
        a[i].id = a[i].sum = 0;
    }
}

int main() {
    while (scanf("%d", &n) != EOF) {
        if (!n) break; char t[N];
        aclear(); ac.clear();
        for (int i = 1; i <= n; ++ i) {
            scanf("%s", as[i]);
            a[i].id = i; ac.insert(as[i], i);
        }
        scanf("%s", t);
        ac.build();
        ac.query(t);
        sort(a + 1, a + n + 1, cmp);
        printf("%d\n",a[1].sum);
        int now = 1, minn = a[1].sum;
        while(a[now].sum == minn)
          printf("%s\n",as[a[now ++].id]);
    }
    return 0;
}