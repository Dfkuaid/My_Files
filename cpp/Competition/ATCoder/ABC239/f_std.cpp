#define LOCAL
#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pbk(x) push_back(x)
#define mp(a, b) make_pair(a, b)
using namespace std;

const int N = 300010;
const int INF = 0x3f3f3f3f;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

struct Node {
    int id, val;
    inline bool operator < (const Node &b) const {
        return val > b.val;
    }
};

int n, m, d[N], f[N], siz[N], tot, ecnt;
int q[N], frt, tal(-1), ad[N], cnt, t[N];

priority_queue <Node> h;
vector <pii > e;
vector <int> block[N];

inline int find(int x) {
    while (x != f[x])
      x = f[x] = f[f[x]];
    return x;
}

inline bool unify(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx == fy) return false;
    if (siz[fx] < siz[fy]) swap(fx, fy);
    f[fy] = fx, siz[fx] += siz[fy];
    ad[fx] += ad[fy], ad[fy] = 0;
    for (auto v : block[fy]) block[fx].pbk(v);
    if (!d[x]) return false; else -- d[x];
    if (!d[y]) return false; else -- d[y];
    if (!d[x] && !d[y]) return false;
    ad[fx] -= 2; return true;
}

inline int get_node(int x) {
    while (!d[block[x][t[x]]]) ++ t[x];
    -- d[block[x][t[x]]]; return block[x][t[x]];
}

inline void print() {
    for (auto v : e) printf("%d %d\n", get_node(v.first), get_node(v.second));
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(m);
    for (int i = 1; i <= n; ++ i) f[i] = i;
    for (int i = 1; i <= n; ++ i) siz[i] = 1;
    for (int i = 1; i <= n; ++ i) read(d[i]);
    for (int i = 1; i <= n; ++ i) tot += d[i];
    for (int i = 1; i <= n; ++ i) block[i].pbk(i);
    for (int i = 1; i <= n; ++ i) ad[i] = d[i];
    if (tot != 2 * (n - 1)) {puts("-1"); return 0;}
    for (int i = 1, x, y; i <= m; ++ i) {
        read(x), read(y);
        if (!unify(x, y)) {puts("-1"); return 0;}
    }
    // printf("Finished connecting.\n");
    for (int i = 1; i <= n; ++ i) 
      if (ad[i] == 1) q[++ tal] = i, ++ cnt;
      else if (ad[i] > 1) h.push((Node){i, ad[i]}), ++ cnt;
    // printf("The top of the heap: %d %d\n", h.top().id, h.top().val);
    // printf("Finished departing.\n");
    // printf("%d %d\n", tal - frt + 1, h.size());
    while (tal - frt >= 0 && h.size()) {
        int x = q[frt ++], y = h.top().id; h.pop();
        e.pbk(mp(x, y)); -- ad[x], -- ad[y], -- cnt;
        if (ad[y] == 1) q[++ tal] = y;
        else h.push((Node){y, ad[y]});
    }
    // printf("Finished building.\n");
    // printf("%d %d\n", tal - frt + 1, h.size());
    if (tal - frt != 1 || h.size()) {puts("-1"); return 0;}
    e.push_back(mp(q[frt], q[frt + 1])); print(); return (0 - 0);
}
