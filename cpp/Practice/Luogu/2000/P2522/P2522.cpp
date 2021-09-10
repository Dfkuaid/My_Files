#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

int t, prm[N], nprm[N], pcnt, mu[N], smu[N];

template <typename T>
inline T Min(const T a, const T b) {
    return a < b ? a : b;
}

void prework(int x) {
    mu[1] = 1;
    for (int i = 2; i <= x; i ++) {
        if (!nprm[i]) mu[i] = -1, prm[++ pcnt] = i;
        for (int j = 1; j <= pcnt; j ++) {
            if (i * prm[j] > x) break;
            nprm[i * prm[j]] = true;
            if (i % prm[j]) mu[i * prm[j]] = -mu[i];
            else break;
        }
    }
    for (int i = 1; i <= x; i ++)
      smu[i] = smu[i - 1] + mu[i];
}

ll f(int n, int m, int k) {
    ll res = 0; n /= k, m /= k;
    ll lit = Min(n, m);
    for (ll l = 1, r; l <= lit; l = r + 1) {
        r = Min(n / (n / l), m / (m / l));
        res += (smu[r] - smu[l - 1]) * (n / l) * (m / l);
    }
    return res;
}

int main() {
    prework(50010);
    scanf("%d", &t);
    while (t --) {
        int a, b, c, d, k; ll res = 0;
        scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
        res = f(b, d, k) - f(b, c - 1, k) - f(a - 1, d, k) + f(a - 1, c - 1, k);
        printf("%lld\n", res);
    }
    return 0;
}