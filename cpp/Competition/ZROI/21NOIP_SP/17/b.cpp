#define LOCAL
#include <bits/stdc++.h>
#define ll long long
#define int long long 
using namespace std;

const int N = 100010;
const int M = 200010;

template <typename T> inline void read(T &x) {
    int f = 1; x = 0; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

struct node {int nxt, u, v;} e[M];

int head[N], cnt(1), n, m, T, a[N];
int ans, val, siz[N], f[N], bel[N];
bool locked[N];

int find(int x) {while (x != f[x]) x = f[x] = f[f[x]]; return x;}
int gcd(int x, int y) {return y ? gcd(y, x % y) : x;}

void add_edge(int u, int v) {
    e[cnt].u = u, e[cnt].v = v;
    e[cnt].nxt = head[u], head[u] = cnt ++;
}

void dfs(int u,int fa) {
    bel[u] ^= 1;
    for(int i = head[u]; i; i = e[i].nxt)
      if(e[i].v != fa) dfs(e[i].v, u);
}
signed main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(m);
    for (int i = 1; i <= n; ++ i) read(a[i]);
    for (int i = 1; i <= n; ++ i) f[i] = i;
    for (int i = 1; i <= n; ++ i) siz[i] = 1;
    while (m --) {
        int opt, x, y, c; read(opt);
        if (opt == 1) read(x), read(c), a[x] = c;
        else if (opt == 2) {
            read(x), read(y);
            if (x == y) continue;
            int fu = find(x), fv = find(y);
            if (siz[fu] > siz[fv])
              swap(x, y), swap(fu, fv);
            if (fu == fv) {
                if (bel[x] == bel[y])
                  locked[fv] = true;	
            } else {
                siz[fv] += siz[fu], f[fu] = fv;
                if (bel[x] == bel[y]) dfs(x, 0);
                add_edge(x, y), add_edge(y, x);
                if (locked[fu]) locked[fv] = true;
            }
        } else if (opt == 3) {
            read(x), read(y), read(c);
            int fu = find(x), fv = find(y);
            if (fu != fv) {puts("0"); continue;} 
            if (locked[fu]) {puts("0"); continue;}
            else {
                int fst = c * a[x], scd = a[y];
                int g = gcd(fst, scd); fst /= g, scd /= g;
                if (bel[x] != bel[y]) fst = -fst;
                printf("%lld/%lld\n", fst, scd); 
            }
        }
    }
    return 0;
}
