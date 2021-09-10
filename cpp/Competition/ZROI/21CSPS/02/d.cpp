#define DEBUG
#include <bits/stdc++.h>
#define ll long long
#define VI vector <int>
#define pii pair <ll, int>
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 2000100;
const int INF = 0x3fffffff;

template <typename T>
inline T Min(const T a, const T b) {return a < b ? a : b;}

template <typename T>
inline T Max(const T a, const T b) {return a > b ? a : b;}

struct Edge {int u, v, nxt;} e[N];

struct UFS {
    int fa[N]; int *d_;

    inline void init(int x, int *d) {
        for (int i = 0; i <= x; ++ i) fa[i] = i;
        this->d_ = d;
    }

    inline int find(int x) {
        while (x != fa[x]) x = fa[x] = fa[fa[x]];
        return x;
    }

    inline void merge(int x, int y) {
        x = find(x), y = find(y);
        if (x != y)  {
            if ((d_[x] > d_[y]) || (d_[x] == d_[y] && x > y))
              swap(y, x);
            fa[y] = x;
        }
    }
} ufs;

int n, m, d[N], head[N], ecnt(1), cbtot;
int frt, tal, q[N], pos[N], bin[N], max_k, cb_id[N];
int inq[N], kpc[N], kcnt; ll A, B, C;

vector <int> tk, pa;

inline void add_edge(int u, int v) {
    e[ecnt].u = u, e[ecnt].v = v; ++ d[u];
    e[ecnt].nxt = head[u], head[u] = ecnt ++;
}

inline void Get_Tags() {
    int max_d = 0, st = 0, now = 0;
    for (int i = 1; i <= n; ++ i)
      ++ bin[d[i]], max_d = Max(max_d, d[i]);
    for (int i = 0; i <= max_d; ++ i)
      now = bin[i], bin[i] = st, st += now;
    for (int i = 1; i <= n; ++ i)
      pos[i] = bin[d[i]] ++, q[pos[i]] = i;
    for (int i = max_d; i; -- i) bin[i] = bin[i - 1];
    bin[0] = 0, bin[max_d + 1] = n;
    for (int i = 0; i < n; ++ i) {
        int v = q[i];
        for (int j = head[v]; j; j = e[j].nxt) {
            int u = e[j].v;
            if (d[u] > d[v]) {
                int du = d[u], pu = pos[u];
                int pw = bin[du], w = q[pw];
                if (u != w) {
                    pos[u] = pw, q[pu] = w;
                    pos[w] = pu, q[pw] = u;
                } ++ bin[du], -- d[u];
            }
        }
    }
    for (int i = 1; i <= n; ++ i)
      max_k = Max(max_k, d[i]);
}

inline void Get_Connected_Blocks() {
    ufs.init(n, d); pa.push_back(0); tk.push_back(0);
    for (int k = max_k; k; -- k) {
        int l = bin[k], r = bin[k + 1] - 1; kcnt = 0;
        for (int i = l; i <= r; ++ i) {
            int v = q[i]; 
            for (int j = head[v]; j; j = e[j].nxt){
                int u = e[j].v;
                int fp = ufs.find(u);
                if (d[fp] > k) if (!inq[fp])
                  kpc[++ kcnt] = fp, inq[fp] = true;
                if (d[fp] >= k) ufs.merge(v, fp);
            }
        }
        for (int i = l; i <= r; ++ i) {
            int v = q[i], fp = ufs.find(v);
            if (!cb_id[fp]) {
                cb_id[fp] = ++ cbtot;
                pa.push_back(-1);
                tk.push_back(d[fp]);
            }
            cb_id[v] = cb_id[fp];
        }
        for (int i = 1; i <= kcnt; ++ i) {
            int v = kpc[i], fp = ufs.find(v);
            pa[cb_id[v]] = cb_id[fp], inq[v] = false;
        }
    }
}

void Compute_the_Answer() {
    VI vert(cbtot + 1, 0), edge(cbtot + 1, 0), boun(cbtot + 1, 0);
    for (int i = 1; i <= n; ++ i) {
        int ci = d[i], lt = 0, eq = 0, gt = 0;
        for (int j = head[i]; j; j = e[j].nxt) {
            int nbr = e[j].v, cnbr = d[nbr];
            if (cnbr < ci) ++ lt;
            else if (cnbr == ci) {
                if (i < nbr) ++ eq;
            } else ++ gt;
        }
        int ti = cb_id[i]; ++ vert[ti];
        edge[ti] += gt + eq; boun[ti] += lt - gt;
    }
    pii ans(1ll * (-1e18), -1);
    for (int i = 1; i <= cbtot; ++ i) {
        int f = pa[i];
        if (f != -1)
          vert[f] += vert[i], edge[f] += edge[i], boun[f] += boun[i];
        ll score = A * edge[i] - B * vert[i] + C * boun[i];
        if (tk[i] > 0) ans = max(ans, {score, tk[i]});
    }
    printf("%d %lld\n", ans.second, ans.first);
}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    scanf("%d%d%lld%lld%lld", &n, &m, &A, &B, &C);
    for (int i = 1; i <= m; ++ i) {
        int u, v; scanf("%d%d", &u, &v);
        add_edge(u, v); add_edge(v, u);
    }
    Get_Tags(); Get_Connected_Blocks();
    Compute_the_Answer(); return 0;
}