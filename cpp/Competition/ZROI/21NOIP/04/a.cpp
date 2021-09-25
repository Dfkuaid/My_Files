#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 5000010;
const int MOD = 998244353;
const int INF = 0x3fffffff;

char s[N]; int n, lstc, lsta, f[N], ans;

int main() {
    scanf("%s", s + 1); n = strlen(s + 1);
    for (int i = 1; i <= n; ++ i) {
        if (s[i] == 'B') f[i] = f[i - 1];
        else if (s[i] == 'A') f[i] = (f[lstc] + lstc) % MOD, lsta = i;
        else if (s[i] == 'C') f[i] = (f[lsta] + lsta) % MOD, lstc = i;
        (ans += f[i]) %= MOD;
    }
    printf("%d", ans); return 0;
}