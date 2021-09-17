#define DEBUG
#include <bits/stdc++.h>
#define ll long long
#define pii pair <int, int>
#define mkp(a, b) make_pair(a, b)
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 3000010;
const int BAS1 = 131;
const int BAS2 = 13331;
const int MOD1 = 998244353;
const int MOD2 = 1004535809;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int dfn[N], endp[N], ch[N][30], cnt = 1;
int hash_val1[N], hash_val2[N], T;

vector <pii > h[N];
vector <pair <pii, int> > v;

void insert(char *s) {
    int len = strlen(s), p = 1;
    hash_val1[len] = hash_val2[len] = 0;
    for (int i = len - 1; ~i; -- i)
      hash_val1[i] = (1ll * hash_val1[i + 1] * BAS1 % MOD1 + s[i] - 96) % MOD1,
      hash_val2[i] = (1ll * hash_val2[i + 1] * BAS2 % MOD2 + s[i] - 96) % MOD2;
    h[p].push_back(mkp(hash_val1[0], hash_val2[0]));
    for (int i = 0; i < len; ++ i) {
        int k = s[i] - 96;
        if (!ch[p][k]) {ch[p][k] = ++ cnt;} p = ch[p][k];
        h[p].push_back(mkp(hash_val1[i + 1], hash_val2[i + 1]));
    }
}

void dfs(int x) {
    dfn[x] = ++ T;
    for (auto i : h[x]) v.push_back(mkp(mkp(i.first, i.second), T));
    for (int i = 1; i <= 26; ++ i) if (ch[x][i]) dfs(ch[x][i]);
    endp[x] = T;
}

#define lb(x) lower_bound(v.begin(), v.end(), x)
#define ub(x) upper_bound(v.begin(), v.end(), x)

int n, m; char a[N];

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    read(n); read(m); 
    for (int i = 1; i <= n; ++ i)
      scanf("%s", a), insert(a);
    dfs(1); sort(v.begin(), v.end());
    while (m --) {
        scanf("%s", a); int l = strlen(a), p = 1, q = 0;
        while (q < l && a[q] != '*') p = ch[p][a[q] - 96], ++ q;
        int hv1 = 0, hv2 = 0;
        for (int i = l - 1; i > q; -- i)
          hv1 = (1ll * hv1 * BAS1 % MOD1 + a[i] - 96) % MOD1,
          hv2 = (1ll * hv2 * BAS2 % MOD2 + a[i] - 96) % MOD2;
        printf("%d\n", ub(mkp(mkp(hv1, hv2), endp[p])) - lb(mkp(mkp(hv1, hv2), dfn[p])));
    }
    return 0;
}