#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 1000010;
const int INF = 0x3fffffff;

int n, m, q, sum[N], ans, op, u, v;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++ i) {
        scanf("%d%d", &u, &v);
        if (u < v) ++ sum[u];
        else ++ sum[v];
    }
    for (int i = 1; i <= n; ++ i)
      if (!sum[i]) ++ ans;
    scanf("%d", &q);
    while (q --) {
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d%d", &u, &v);
            if (u < v) {
                if (!sum[u]) -- ans;
                ++ sum[u];
            } else {
                if (!sum[v]) -- ans;
                ++ sum[v];
            }
        } else if (op == 2) {
            scanf("%d%d", &u, &v);
            if (u < v) {
                if (!(-- sum[u])) ++ ans;
            } else {
                if (!(-- sum[v])) ++ ans;
            }
        } else printf("%d\n", ans);
    }
    return 0;
}