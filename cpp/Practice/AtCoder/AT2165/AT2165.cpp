#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 300010;
const int INF = 0x3fffffff;

int n, a[N];

inline bool up(int i, int j, int x) {return a[i] > x && a[j] > x;}
inline bool dn(int i, int j, int x) {return a[i] <= x && a[j] <= x;}

inline bool check(int x) {
    for (int i = 0; i < n - 1; ++ i) {
        if (up(n + i, n + i + 1, x) || up(n - i, n - i - 1, x)) return 0;
        if (dn(n + i, n + i + 1, x) || dn(n - i, n - i - 1, x)) return 1;
    }
    return dn(1, 1, x);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= (n << 1) - 1; ++ i)
      scanf("%d", &a[i]);
    int l = 1, r = (n << 1) - 1, ans;
    while (l <= r) {
        int mid = l + r >> 1;
        if (check(mid)) 
          r = mid - 1, ans = mid;
        else l = mid + 1;
    }
    printf("%d", ans);
    return 0;
}