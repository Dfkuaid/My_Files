#include <bits/stdc++.h>
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

int n, k, lg[N], mr[N], nxt[N], xtr[N][30], ans;

inline void clear() {
    ans = INF;
    mset(mr, 0); mset(nxt, 0); mset(xtr, 0);
}

int main() {
    for (int i = 2; i <= 2e6; ++ i) lg[i] = lg[i >> 1] + 1;
    while (scanf("%d%d", &n, &k) != EOF) {
        clear();
        for (int i = 1; i <= k; ++ i) {
            int l, r; scanf("%d%d", &l, &r);
            if (r < l) {r += n;} mr[l] = Max(mr[l], r);
        }
        int maxr = 0;
        for (int i = 1; i <= n << 1; ++ i) {
            if (mr[i]) {
                if (nxt[i - 1] != INF)
                  nxt[i] = Max(nxt[i - 1], mr[i]);
                else nxt[i] = mr[i];
                maxr = Max(maxr, mr[i]);
            } else if (maxr >= i) nxt[i] = nxt[i - 1];
            else nxt[i] = INF;
            xtr[i][0] = nxt[i] + 1;
        }
        for (int i = 1; i <= lg[n << 1]; ++ i) {
            for (int j = 1; j <= n << 1; ++ j) {
                if (xtr[j][i - 1] >= INF) xtr[j][i] = INF;
                else xtr[j][i] = xtr[xtr[j][i - 1]][i - 1];
            }
        }
        for (int i = 1; i <= n; ++ i) {
            int now = i, res = 0;
            for (int j = lg[n << 1]; j >= 0; -- j)
              if (xtr[now][j] < i + n)
                res += (1 << j), now = xtr[now][j];
            if (xtr[now][0] <= INF) ans = Min(ans, res);
        }
        if (ans != INF) printf("%d\n", ans + 1);
        else printf("impossible\n");
    }
    return 0;
}