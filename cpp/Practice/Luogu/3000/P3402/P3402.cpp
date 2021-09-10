#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 200010;
const int INF = 0x3fffffff;

struct Node {
    int l, r;
    int ls, rs;
    int fa, dep;
};
Node p[N << 5];

int cnt, n, m, rt[N];

void build(int k, int l, int r) {
    p[k].l = l, p[k].r = r;
    if (l == r) { p[k].fa = l; return;}
    int mid = (l + r) >> 1;
    p[k].ls = ++ cnt;
    build(p[k].ls, l, mid);
    p[k].rs = ++ cnt;
    build(p[k].rs, mid + 1, r);
}

int get_index(int k, int x) {
    if (p[k].l == p[k].r) return k;
    int mid = (p[k].l + p[k].r) >> 1;
    if (x <= mid) return get_index(p[k].ls, x);
    else return get_index(p[k].rs, x);
}

inline int find(int r, int x) {
    int idx = get_index(r, x);
    while (p[idx].fa != x) {
        x = p[idx].fa;
        idx = get_index(r, x);
    }
    return idx;
}

void merge(int lt, int &k, int x, int y) {
    k = ++ cnt, p[k].l = p[lt].l, p[k].r = p[lt].r;
    if (p[k].l == p[k].r) {
        p[k].fa = y;
        p[k].dep = p[lt].dep;
        return;
    }
    int mid = (p[k].l + p[k].r) >> 1;
    if (x <= mid) {
        p[k].rs = p[lt].rs;
        merge(p[lt].ls, p[k].ls, x, y);
    } else {
        p[k].ls = p[lt].ls;
        merge(p[lt].rs, p[k].rs, x, y);
    }
}

void modify(int t, int &k, int x) {
    k = ++ cnt;
    p[k].l = p[t].l, p[k].r = p[t].r;
    if (p[k].l == p[k].r) {
        p[k].dep = p[t].dep + 1;
        p[k].fa = p[t].fa;
        return;
    }
    int mid = (p[k].l + p[k].r) >> 1;
    if (x <= mid) {
        p[k].rs = p[t].rs;
        modify(p[t].ls, p[k].ls, x);
    } else {
        p[k].ls = p[t].ls;
        modify(p[t].rs, p[k].rs, x);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    build(rt[0] = ++ cnt, 1, n);
    for (int i = 1; i <= m; i ++) {
        int op, a, b; scanf("%d", &op);
        if (op == 1) {
            scanf("%d%d", &a, &b);
            int posa = find(rt[i - 1], a);
            int posb = find(rt[i - 1], b);
            rt[i] = rt[i - 1];
            if (posa == posb) continue;
            if (p[posa].dep > p[posb].dep) swap(posa, posb);
            merge(rt[i - 1], rt[i], p[posa].fa, p[posb].fa);
            if (p[posa].dep == p[posb].dep)
              modify(rt[i], rt[i], p[posb].fa);
        } else if (op == 2) {
            scanf("%d", &a); rt[i] = rt[a];
        } else {
            scanf("%d%d", &a, &b); rt[i] = rt[i - 1];
            int af = find(rt[i], a), bf = find(rt[i], b);
            if (af == bf) printf("1\n");
            else printf("0\n");
        }
    }
    return 0;
}