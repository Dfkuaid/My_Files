#define LOCAL
#include <bits/stdc++.h>
#define ll long long
#define pbk(x) push_back(x)
using namespace std;

const int N = 100010;
const ll MOD = 1e9 + 7;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

struct Node {
    int id; double val;
    
    inline Node() {}
    inline Node(int _id, double _val) {id = _id, val = _val;}
};
struct action {int op, pos; ll val;} p[N];

int k, n, m; ll a[N], ans = 1, cov[N];

vector <Node> add, mul, v[N];
vector <int> fnl;

inline double calc(int pos, double val) {
    return (1.0 * a[pos] + val) / (1.0 * a[pos]);
}

inline bool cmp(Node x, Node y) {return x.val > y.val;}

inline bool cmp2(int x, int y) {
    if (p[x].pos != p[y].pos) return p[x].pos < p[y].pos;
    else if (p[x].op != p[y].op) return p[x].op < p[y].op;
    else return p[x].val < p[y].val;
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(k), read(n), read(m);
    for (int i = 1; i <= k; ++ i) read(a[i]);
    for (int i = 1; i <= n; ++ i) {
        int op, pos; ll val;
        read(op), read(pos), read(val);
        p[i].op = op, p[i].pos = pos, p[i].val = val;
        if (op == 1) {
            if (!cov[pos]) cov[pos] = i;
            else if (p[cov[pos]].val < val)
              cov[pos] = i;
        }
        else if (op == 2) v[pos].pbk(Node(i, 1.0 * val));
        else mul.pbk(Node(i, 1.0 * val));
    }
    for (int i = 1; i <= k; ++ i) if (cov[i])
      v[i].pbk(Node(cov[i], 1.0 * (p[cov[i]].val - a[i])));
    for (int i = 1; i <= k; ++ i) sort(v[i].begin(), v[i].end(), cmp);
    for (int i = 1; i <= k; ++ i) {
        double sum = 1.0 * a[i];
        for (auto x : v[i]) {
            mul.pbk(Node(x.id, (sum + x.val) / sum));
            sum += x.val;
        }
    }
    sort(mul.begin(), mul.end(), cmp);
    for (int i = 0; i < m && i < mul.size(); ++ i) fnl.pbk(mul[i].id);
    sort(fnl.begin(), fnl.end(), cmp2);
    for (auto x : fnl) {
        if (p[x].op == 1) a[p[x].pos] = max(a[p[x].pos], p[x].val);
        else if (p[x].op == 2) (a[p[x].pos] += p[x].val) %= MOD;
        else (a[p[x].pos] *= p[x].val) %= MOD;
    }
    for (int i = 1; i <= k; ++ i) (ans *= a[i]) %= MOD;
    printf("%lld", ans); return 0;
}
