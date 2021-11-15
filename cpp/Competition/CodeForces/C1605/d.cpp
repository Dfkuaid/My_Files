#define LOCAL
#include <bits/stdc++.h>
#define ll long long
#define pbk push_back
using namespace std;

const int N = 500010;
const int INF = 0x3fffffff;

template<typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

struct Edge {int u, v, nxt;} e[N];

int head[N], ecnt(1);

inline void add_edge(int u, int v) {
    e[ecnt].u = u, e[ecnt].v = v;
    e[ecnt].nxt = head[u], head[u] = ecnt ++;
}

int t, n, result[N], c[N], lg2[N]; bool vis[N];

vector<int> S[2];

inline void dfs(int x, int fa, int col) {
    c[x] = col; S[col].pbk(x);
    for (int i = head[x]; i; i = e[i].nxt) 
      if (e[i].v != fa) dfs(e[i].v, x, col ^ 1);
}

inline void reset(){
    vector<int>().swap(S[0]); vector<int>().swap(S[1]);
    for (int i = 1; i <= n; ++ i)
      head[i] = vis[i] = c[i] = result[i] = 0;
    ecnt = 1;
}

void MAIN() {
    read(n); reset();
    for (int i = 1; i < n; ++ i) {
        int u, v; read(u); read(v);
        add_edge(u, v); add_edge(v, u);
    }
    dfs(1, 0, 0); int now = 0;
    if (S[0].size() < S[1].size()) now = 1;
    int k = 1; while ((k << 1) <= n) k <<= 1;
    int cnt = k, j;
    for (j = 0; j < S[now].size(); ++ j) {
        int x = S[now][j];
        result[x] = k; vis[k] = 1;
        ++ k; if (k == n + 1) break;
    }
    int rst = S[now].size() - j - 1; -- cnt;
    if(rst) {
        for (int k = lg2[cnt]; k >= 0; -- k) {
            if (rst < (1 << k)) continue;
            int l = (1 << k), r = (1 << (k + 1)) - 1;
            for (int o = l; o <= r; ++ o) {
                ++ j; int x = S[now][j];
                result[x] = o; -- rst; vis[o] = 1;
            }
        }
    }
    now ^= 1; j = 0;
    for (int i = 1; i <= n; ++ i) {
        if (vis[i]) continue;
        int x = S[now][j];
        result[x] = i; ++ j;
    }
    for (int i = 1; i <= n; ++ i)
      printf("%d ", result[i]);
    puts("");
}

int main(){
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    for (int i = 2; i <= 200000; ++ i) 
      lg2[i] = lg2[i >> 1] + 1;
    read(t); while(t--) MAIN(); return 0;
}
