#include <bits/stdc++.h>
using namespace std;

const int N = 10010;

int n, a[N], ans[N], pos;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", &a[i]);
        if (a[i] == 1) pos = i;
    }
    int l = pos, r = pos;
    for (int i = 1; i <= n; ++ i) {
        while (l > 1 && a[l - 1] <= i) -- l;
        while (r < n && a[r + 1] <= i) ++ r;
        if (r - l + 1 >= i) ans[i] = 1;
        else ans[i] = 0;
    }
    for (int i = 1; i <= n; ++ i)
      printf("%d", ans[i]);
    return 0;
}
