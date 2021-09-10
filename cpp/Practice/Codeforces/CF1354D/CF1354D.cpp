#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 4000010;
const int INF = 0x3fffffff;

int n, q, cnt, rt = 1, p[N];

void add(int k, int l, int r, int x) {
     ++ p[k]; if (l == r) return;
    int mid = l + r >> 1;
    if (x <= mid) add(k << 1, l, mid, x);
    else add(k << 1 | 1, mid + 1, r, x);
}

int del(int k, int l, int r, int x) {
    -- p[k]; if (l == r) return l;
    int mid = l + r >> 1, lsum = p[k << 1];
    if (lsum >= x) return del(k << 1, l, mid, x);
    else return del(k << 1 | 1, mid + 1, r, x - lsum);
}

int main() {
    scanf("%d%d", &n, &q);
    int k;
    for (int i = 1; i <= n; ++ i)
      scanf("%d", &k), add(rt, 1, n, k);
    while (q --) {
        scanf("%d", &k);
        if (k >= 0) add(rt, 1, n, k);
        else if (p[rt] >= -k) del(rt, 1, n, -k);
    }
    if (p[rt] <= 0) printf("0");
    else printf("%d", del(rt, 1, n, 1));
    return 0;
}