#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 500010;
const int M = 20000010;
const int INF = 0x3fffffff;

struct Node {int ch[2], siz, id;} t[M];

int cnt, rt[N], n, k;
ll ans, a[N];

inline int clone(int x) {t[++ cnt] = t[x]; return cnt;}

void insert(int lt, int &k, ll x, int b, int id) {
    k = clone(lt); ++ t[k].siz;
    if (b < 0) {t[k].id = id; return;}
    int c = (x >> b) & 1;
    insert(t[lt].ch[c], t[k].ch[c], x, b - 1, id);
}

int query(int u, int v, int b, ll x) {
    if (b == -1) return t[v].id;
    int d = (x >> b) & 1;
    if (t[t[v].ch[d ^ 1]].siz - t[t[u].ch[d ^ 1]].siz > 0)
      return query(t[u].ch[d ^ 1], t[v].ch[d ^ 1], b - 1, x);
    else return query(t[u].ch[d], t[v].ch[d], b - 1, x);
}

struct State {
    int l, r, x, id; ll val;
    
    inline State(int L, int R, int _x) {
        l = L, r = R, x = _x;
        id = query(rt[l - 1], rt[r], 31, a[x]);
        val = a[x] ^ a[id - 1];
    }

    inline bool operator < (const State &b) const {
        return val < b.val;
    }
};

priority_queue <State> q;

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++ i)
      scanf("%lld", &a[i]), a[i] ^= a[i - 1];
    for (int i = 1; i <= n; ++ i)
      insert(rt[i - 1], rt[i], a[i - 1], 31, i);
    for (int i = 1; i <= n; ++ i)
      q.push(State(1, i, i));
    while (k --) {
        State u = q.top(); q.pop(); ans += u.val;
        if (u.l < u.id) q.push(State(u.l, u.id - 1, u.x));
        if (u.id < u.r) q.push(State(u.id + 1, u.r, u.x));
    }
    printf("%lld\n", ans);
    return 0;
}