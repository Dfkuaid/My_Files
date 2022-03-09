#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 100010;
const int INF = 0x3f3f3f3f;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int T, a[N], vis[N], tmp[N];

inline bool check_sum(int x) {
    memset(vis, 0, sizeof vis); tmp[0] = 0;
    for (int i = 1; i <= x; ++ i) {
        tmp[i] = tmp[i - 1] + a[i];
        if (vis[tmp[i] % x]) return false;
        vis[tmp[i] % x] = 1;
    }
    return true;
}

inline bool check_mul(int x) {
    memset(vis, 0, sizeof vis); tmp[0] = 1;
    for (int i = 1; i <= x; ++ i) {
        tmp[i] = tmp[i - 1] * a[i];
        if (vis[tmp[i] % x]) return false;
        vis[tmp[i] % x] = 1;
    }
    return true;
}

inline void solve(int x) {
    for (int i = 1; i <= x; ++ i) a[i] = i;
    printf("NOW: %d\n", x); int flag = 0;
    do {
        if (check_sum(x)) {
            printf("  SUM: YES\n    "); flag = 1;
            for (int i = 1; i <= x; ++ i) printf("%d ", a[i]); printf("\n    ");
            for (int i = 1; i <= x; ++ i) printf("%d ", tmp[i]); printf("\n    ");
            for (int i = 1; i <= x; ++ i) printf("%d ", tmp[i] % x); puts("");
        }
    } while (next_permutation(a + 1, a + x + 1));
    if (!flag) puts("  SUM: NO"); flag = 0;
    for (int i = 1; i <= x; ++ i) a[i] = i;
    do {
        if (check_mul(x)) {
            printf("  MUL: YES\n    "); flag = 1;
            for (int i = 1; i <= x; ++ i) printf("%d ", a[i]); printf("\n    ");
            for (int i = 1; i <= x; ++ i) printf("%d ", tmp[i]); printf("\n    ");
            for (int i = 1; i <= x; ++ i) printf("%d ", tmp[i] % x); puts("");
        }
    } while (next_permutation(a + 1, a + x + 1));
    if (!flag) puts("  MUL: NO");
    puts("--------------------------");
}

int main() {
#ifdef LOCAL
    freopen("brute.txt", "w", stdout);
#endif
    read(T); int i = 0; while (++ i <= T) solve(i); return (0 - 0);
}
