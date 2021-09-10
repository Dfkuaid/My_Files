/*Wrong Answer but haven't find the problem by 对拍*/
#define DEBUG
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 500010;
const int INF = 2147483647;

template <typename T>
inline T Max(const T a, const T b) {return a > b ? a : b;}

template <typename T>
inline T Min(const T a, const T b) {return a < b ? a : b;}

struct Edge {int u, v, nxt;} e[N << 1];

int n, q, lg[N], head[N], ecnt = 1, f[N][30], dep[N];
int mn[N][30], mx[N][30], dtu[N][30], utd[N][30], prc[N];

inline void add(int u, int v) {
    e[ecnt].u = u, e[ecnt].v = v;
    e[ecnt].nxt = head[u], head[u] = ecnt ++;
}

void get_father(int x, int fa) {
    f[x][0] = fa; dep[x] = dep[fa] + 1;
    mn[x][0] = Min(prc[x], prc[fa]);
    mx[x][0] = Max(prc[x], prc[fa]);
    dtu[x][0] = Max(0, prc[x] - prc[fa]);
    utd[x][0] = Max(0, prc[fa] - prc[x]);
    for (int i = head[x]; i; i = e[i].nxt)
      if (e[i].v != fa) get_father(e[i].v, x);
}

void get_val() {
    for (int i = 1; i <= lg[n]; ++ i)
      for (int x = 1; x <= n; ++ x) {
          int fa = f[x][i >> 1]; f[x][i] = f[fa][i >> 1];
          mn[x][i] = Min(mn[x][i >> 1], mn[fa][i >> 1]);
          mx[x][i] = Max(mx[x][i >> 1], mx[fa][i >> 1]);
          utd[x][i] = Max(Max(utd[x][i >> 1], utd[fa][i >> 1]), mx[fa][i >> 1] - mn[x][i >> 1]);
          dtu[x][i] = Max(Max(dtu[x][i >> 1], dtu[fa][i >> 1]), mx[x][i >> 1] - mn[fa][i >> 1]);
      }
}

int query(int x, int y) {
    int res = 0, nmn = INF, nmx = -INF;
    if (dep[x] > dep[y]) {
        for (int i = lg[n]; ~i; -- i)
          if (dep[f[x][i]] >= dep[y]){
              res = Max(Max(res, dtu[x][i]), nmx - mn[x][i]);
              nmx = Max(nmx, mx[x][i]); x = f[x][i];
          }
    } else if (dep[x] < dep[y]) {
        for (int i = lg[n]; ~i; -- i)
          if (dep[f[y][i]] >= dep[x]){
              res = Max(Max(res, utd[y][i]), mx[y][i] - nmn);
              nmn = Min(nmn, mn[y][i]); y = f[y][i];
          }
    }
    if (x == y) return res;
    for (int i = lg[n]; ~i; -- i)
      if (f[x][i] != f[y][i]) {
          res = Max(res, Max(dtu[x][i], utd[y][i]));
          res = Max(res, Max(nmx - mn[x][i], mx[y][i] - nmn));
          nmx = Max(nmx, mx[x][i]); nmn = Min(nmn, mn[y][i]);
          x = f[x][i], y = f[y][i];
      }
    res = Max(res, Max(dtu[x][0], utd[y][0]));
    res = Max(res, Max(nmx - mn[x][0], mx[y][0] - nmn));
    nmx = Max(nmx, mx[x][0]); nmn = Min(nmn, mn[y][0]);
    res = Max(res, nmx - nmn); return res;
}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    scanf("%d", &n);
    for (int i = 2; i <= n; ++ i) lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i <= n; ++ i) scanf("%d", &prc[i]);
    for (int i = 1; i < n; ++ i) {
        int u, v; scanf("%d%d", &u, &v);
        add(u, v); add(v, u);
    }
    get_father(1, 1); get_val();
    scanf("%d", &q);
    while (q --) {
        int u, v; scanf("%d%d", &u, &v);
        printf("%d\n", query(v, u));
    }
    return 0;
}