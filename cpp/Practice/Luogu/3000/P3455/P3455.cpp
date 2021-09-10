#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

int t, n, m, d;
int prm[N], nprm[N], pcnt, mu[N], smu[N];

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

int main() {
    prework(50010);
    scanf("%d", &t);
    while (t --) {
        scanf("%d%d%d", &n, &m, &d);
        ll res = 0; n /= d, m /= d;
        ll lit = Min(n, m);
        for (ll l = 1, r; l <= lit; l = r + 1) {
            r = Min(n / (n / l), m / (m / l));
            res += (smu[r] - smu[l - 1]) * (n / l) * (m / l);
        }
        printf("%lld\n", res);
    }
    return 0;
}