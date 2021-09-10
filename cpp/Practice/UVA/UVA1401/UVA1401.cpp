#define DEBUG

#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 500010;
const int MOD = 20071027;
const int INF = 0x3fffffff;

struct Trie {int ch[30], tag;} t[N];

int cnt, n, f[N], T;
char s[N];

inline void insert(char *S) {
    int p = 0, len = strlen(S);
    for (int i = 0; i < len; ++ i) {
        int k = S[i] - 'a';
        if (!t[p].ch[k]) t[p].ch[k] = ++ cnt;
        p = t[p].ch[k];
    }
    t[p].tag |= true;
}

inline void clear() {
    for (int i = 0; i <= cnt; ++ i) {
        for (int j = 0; j < 26; ++ j)
          t[i].ch[j] = 0;
        t[i].tag = 0;
    }
    mset(f, 0); cnt = 0;
}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    while (scanf("%s", s) != EOF) {
        clear(); scanf("%d", &n);
        for (int i = 1; i <= n; ++ i) {
            char S[N]; scanf("%s", S);
            insert(S);
        }
        int len = strlen(s); f[len] = 1;
        for (int i = len - 1; i >= 0; -- i) {
            int p = 0;
            for (int j = i; j < len; ++ j) {
                int k = s[j] - 'a';
                if (!t[p].ch[k]) break;
                else p = t[p].ch[k];
                if (t[p].tag) (f[i] += f[j + 1]) %= MOD;
            }
        }
        printf("Case %d: %d\n", ++ T, f[0]);
    }
    return 0;
}