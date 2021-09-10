#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 3000010;
const int INF = 0x3fffffff;

template <typename T>
inline T Max(const T a, const T b) {
    return a > b ? a : b;
}

template <typename T>
inline T Min(const T a, const T b) {
    return a < b ? a : b;
}

ll a[N], k, n, ans;
int qn[N], qx[N], frtn, taln = -1, frtx, talx = -1, l, r;

int main() {
    scanf("%lld%lld", &k, &n);
    for (int i = 1; i <= n; i ++)
      scanf("%lld", &a[i]);
    for (int l = r = 1; r <= n; ++ r) {
        while (frtx <= talx && a[qx[talx]] <= a[r]) talx --;
        while (frtn <= taln && a[qn[taln]] >= a[r]) taln --;
        qn[++ taln] = qx[++ talx] = r;
        while (a[qx[frtx]] - a[qn[frtn]] > k) {
            l = min(qx[frtx], qn[frtn]) + 1;
            while (frtx <= talx && qx[frtx] < l) frtx ++;
            while (frtn <= taln && qn[frtn] < l) frtn ++;
        }
        ans = Max(ans, (ll)(r - l + 1));
    }
    printf("%lld", ans);
    return 0;
}