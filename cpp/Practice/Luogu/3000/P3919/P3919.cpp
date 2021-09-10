#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 4000100;
const int INF = 0x3fffffff;

struct Node {
    int l, r;
    int ls, rs;
    int sum;
};
Node p[N << 2];

int n, a[N], cnt, rt[N], m;

void build(int k, int l, int r) {
    p[k].l = l, p[k].r = r;
    if (l == r) {p[k].sum = a[l]; return;}
    int mid = (l + r) >> 1;
    p[k].ls = ++ cnt;
    build(p[k].ls, l, mid);
    p[k].rs = ++ cnt;
    build(p[k].rs, mid + 1, r);
}

void modify(int t, int &k, int x, int c) {
    if (!k) k = ++ cnt;
    p[k].l = p[t].l, p[k].r = p[t].r;
    if (p[t].l == p[t].r) {p[k].sum = c; return;}
    int mid = (p[k].l + p[k].r) >> 1;
    if (x <= mid) {
        p[k].rs = p[t].rs;
        modify(p[t].ls, p[k].ls, x, c);
    } else {
        p[k].ls = p[t].ls;
        modify(p[t].rs, p[k].rs, x, c);
    }
}

int query(int k, int x) {
    if (p[k].l == p[k].r) return p[k].sum;
    int mid = (p[k].l + p[k].r) >> 1;
    if (x <= mid) return query(p[k].ls, x);
    else return query(p[k].rs, x);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++)
      scanf("%d", &a[i]);
    build(rt[0] = ++ cnt, 1, n);
    int v, op, pos, val;
    for (int i = 1; i <= m; i ++) {
        scanf("%d%d%d", &v, &op, &pos);
        if (op == 1) {
            scanf("%d", &val);
            modify(rt[v], rt[i], pos, val);
        } else {
            rt[i] = rt[v];
            printf("%d\n", query(rt[v], pos));
        }
    }
    return 0;
}
