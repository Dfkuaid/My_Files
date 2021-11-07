#include <bits/stdc++.h>
#define int long long 
using namespace std;

const int N = 1e5 + 9;
const int M = 1e5 + 9;
const int MOD = 1e9 + 7;

int ans, val, a[N], n, Q, L[N], R[N], base[N];

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int get(int l, int r) {return a[r] - a[l - 1] * base[r - l + 1];}

bool check() {
    for (int i = 1; i <= Q; ++ i) {
        int val = get(L[i], R[i]);
        if (val % 9 != 0 ) return false;
    }
    return true;
}

void dfs(int step) {
    if (step == n + 1) {
        if (check()) ++ ans;
        (ans >= MOD) ? ans -= MOD : 0;
        return;
    }
    for (int i = 0; i <= 9; ++ i) {
        a[step] = a[step - 1] * 10 + i;
        dfs(step + 1); a[step] = 0;
    }
}

signed main() {
    read(n), read(Q); base[0] = 1;
    for (int i = 1; i <= Q; ++ i) read(L[i]), read(R[i]);
    for (int i = 1; i <= n; ++ i) base[i] = base[i - 1] * 10;
    dfs(1); printf("%lld\n", ans); return 0;
}
