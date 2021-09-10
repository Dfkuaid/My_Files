#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 4000010;
const int INF = 0x3fffffff;

struct Trie {
    int son[2];
    int val;
};
Trie t[N << 2];

int n, m, s[N], rt[N], cnt;

template <typename T>
inline T Max(const T a, const T b) {
    return a > b ? a : b;
}

void insert(int lt, int k, int x, int ind) {
    if (x < 0) {t[k].val = ind; return;}
    int c = (s[ind] >> x) & 1;
    if (lt) t[k].son[c ^ 1] = t[lt].son[c ^ 1];
    t[k].son[c] = ++ cnt;
    insert(t[lt].son[c], t[k].son[c], x - 1, ind);
    t[k].val = Max(t[t[k].son[0]].val, t[t[k].son[1]].val);
}

int query(int k, int x, int l, int len) {
    if (len < 0) return s[t[k].val] ^ x;
    int c = (x >> len) & 1;
    if (t[t[k].son[c ^ 1]].val >= l)
      return query(t[k].son[c ^ 1], x, l, len - 1);
    else return query(t[k].son[c], x, l, len - 1);
}

int main() {
    scanf("%d%d", &n, &m);
    t[0].val = -1, rt[0] = ++ cnt;
    insert(0, rt[0], 25, 0);
    for (int i = 1; i <= n; i ++){
        int x; scanf("%d", &x);
        s[i] = s[i - 1] ^ x, rt[i] = ++ cnt;
        insert(rt[i - 1], rt[i], 25, i);
    }
    for (int i = 1; i <= m; i ++) {
        char opt; cin >> opt;
        if (opt == 'A') {
            int x; scanf("%d", &x);
            rt[++ n] = ++ cnt, s[n] = s[n - 1] ^ x;
            insert(rt[n - 1], rt[n], 25, n);
        } else {
            int x, l, r; scanf("%d%d%d", &l, &r, &x);
            printf("%d\n", query(rt[r - 1], s[n] ^ x, l - 1, 25));
        }
    }
    return 0;
}