#include <bits/stdc++.h>
#define ll long long
#define int long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 2000010;
const int INF = 0x3fffffff;

struct Trie {
    int ch[N][30], rt; ll cnt, res[30];

    inline void clear() {
        cnt = rt = 0;
        mset(ch, 0); mset(res, 0);
    }

    inline void insert(char *s) {
        int p = rt, len = strlen(s);
        for (int i = 0; i < len; ++ i) {
            int k = s[i] - 'a';
            if (!ch[p][k]) {
                ch[p][k] = ++ cnt;
                if (i > 0) ++ res[k];
            }
            p = ch[p][k];
        }
    }
} t[2];

int n, al[30]; ll ans;

inline void reset() {
    ans = 0; mset(al, 0);
    t[0].clear(); t[1].clear();
}

signed main() {
    while (scanf("%d", &n) != EOF) {
        reset(); char s[N];
        for (int i = 1; i <= n; ++ i) {
            scanf("%s", s);
            int len = strlen(s); t[0].insert(s);
            reverse(s, s + len); t[1].insert(s);
            if (len == 1) al[s[0] - 'a'] = 1;
        }
        ans = t[0].cnt * t[1].cnt;
        for (int i = 0; i < 26; ++ i) {
            if (al[i]) ++ ans;
            ans -= t[0].res[i] * t[1].res[i];
        }
        printf("%lld\n", ans);
    }
    return 0;
}