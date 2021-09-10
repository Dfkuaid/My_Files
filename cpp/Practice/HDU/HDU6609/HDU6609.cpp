#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 5000010;
const int INF = 0x3fffffff;

struct Node {int ls, rs, tot; ll sum;} p[N];

int t, n, cnt, rt; ll a[N], m;

inline void clear() {
    for (int i = 1; i <= cnt; ++ i)
      p[i].sum = p[i].tot = p[i].ls = p[i].rs = 0;
    cnt = rt = 0;
}

inline void pushup(int k) {
    p[k].sum = p[p[k].ls].sum + p[p[k].rs].sum;
    p[k].tot = p[p[k].ls].tot + p[p[k].rs].tot;
}

void update(int &k, int l, int r, ll x) {
    if (!k) k = ++ cnt;
    if (l == r) {p[k].sum += x, ++ p[k].tot; return;}
    int mid = (l + r) >> 1;
    if (x <= mid) update(p[k].ls, l, mid, x);
    else update(p[k].rs, mid + 1, r, x);
    pushup(k);
}

int query(int k, int l, int r, ll s) {
    if (!k) return 0;
    if (l == r) {
        if (l == 0) return 0;
        int res = s / l;
        if (res <= p[k].tot) return res;
        else return p[k].tot;
    }
    int mid = (l + r) >> 1; ll lsum = p[p[k].ls].sum;
    if (lsum >= s) return query(p[k].ls, l, mid, s);
    else return p[p[k].ls].tot + query(p[k].rs, mid + 1, r, s - lsum);
}

int main() {
    scanf("%d", &t);
    while (t --) {
        clear();
        scanf("%d%lld", &n, &m);
        for (int i = 1; i <= n; ++ i) scanf("%lld", &a[i]);
        for (int i = 1; i <= n; ++ i) {
            printf("%d ", i - 1 - query(rt, 0, m, m - a[i]));
            update(rt, 0, m, a[i]);
        }
        printf("\n");
    }
    return 0;
}