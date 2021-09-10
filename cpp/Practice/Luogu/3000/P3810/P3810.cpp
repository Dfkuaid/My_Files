#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 1000010;
const int INF = 0x3fffffff;

struct flo {
    int a, b, c, id, tot;
    
    inline bool operator < (const flo &t) const {
        if (a == t.a) {
            if (b == t.b) return c < t.c;
            else return b < t.b;
        } else return a < t.a;
    }

    inline bool operator != (const flo &t) const {
        return (a != t.a || b != t.b || c != t.c) ? true : false;
    }
};
flo p[N], v[N], q[N];

int n, k, cnt, ftot[N], ans[N], c[N << 8], res[N];

inline int lowbit(int x) {return (x & (-x));}

void insert(int i, int x) {
    while (i <= N){
        c[i] += x;
        i += lowbit(i);
    }
}

int query(int x) {
    int res = 0;
    while (x > 0) {
        res += c[x];
        x -= lowbit(x);
    }
    return res;
}

void cdq(flo *arr, int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    cdq(arr, l, mid); cdq(arr, mid + 1, r);
    for (int i = l; i <= r; i ++) q[i] = arr[i];
    int L = l, R = mid + 1, pos = l;
    while (R <= r && L <= mid) {
        if (q[L].b <= q[R].b) {
            insert(q[L].c, q[L].tot);
            arr[pos ++] = q[L ++];
        } else {
            ans[q[R].id] += query(q[R].c);
            arr[pos ++] = q[R ++];
        }
    }
    while (R <= r) ans[q[R].id] += query(q[R].c), ++ R;
    while (L <= mid) {insert(q[L].c, q[L].tot);arr[pos ++] = q[L ++]; }
    for (int i = l; i <= mid; i ++) insert(q[i].c, -q[i].tot);
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++ i)
      scanf("%d%d%d", &p[i].a, &p[i].b, &p[i].c);
    sort(p + 1, p + n + 1);
    v[++ cnt] = p[1]; v[cnt].id = v[cnt].tot = 1;
    for (int i = 2; i <= n; ++ i)
      if (p[i] != v[cnt]) {
          v[++ cnt] = p[i];
          v[cnt].id = cnt;
          v[cnt].tot ++;
      } else v[cnt].tot ++;
    cdq(v, 1, cnt);
    for (int i = 1; i <= cnt; ++ i)
      res[ans[v[i].id] + v[i].tot - 1] += v[i].tot;
    for (int i = 0; i < n; ++ i)
      printf("%d\n", res[i]);
    return 0;
}