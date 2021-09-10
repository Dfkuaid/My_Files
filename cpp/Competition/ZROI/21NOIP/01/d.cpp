#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 200010;
const int INF = 0x3fffffff;

int a[N], s, n, T, l, r, p, tot;

inline bool check(int l, int r, int cnt) {
    while (l < r && a[l] == a[r]) ++ l, -- r;
    while (l < r && a[l] == a[l + 1]) l += 2;
    if (l < r) return 0; else return 1;
}

int main() {
    scanf("%d", &T);
    while (T --) {
        scanf("%d", &n); l = 1, r = n;
        p = 30, tot = 0, s = 0;
        for (int i = 1; i <= n; ++ i)
          scanf("%d", &a[i]), s ^= a[i];
        if (!s) {printf("Draw\n"); continue;}
        if (!(n & 1)) {printf("Alice\n"); continue;}
        while (p && !((s >> p) & 1)) -- p;
        for (int i = 1; i <= n; ++ i)
          a[i] = (a[i] >> p) & 1, tot += a[i];
        if (a[1] == 0 && a[n] == 0) {
            printf("Bob\n"); continue;
        }
        -- tot; if (tot % 4) {printf("Bob\n"); continue;}
        if ((a[1] && check(2, n, tot)) || (a[n] && check(1, n - 1, tot)))
          printf("Alice\n");
        else printf("Bob\n");
    }
    return 0;
}