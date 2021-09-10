#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 4000100;
const int INF = 0x3fffffff;

int n, prm[N], pcnt, nprm[N];
ll phi[N], sphi[N], ssphi[N];

void prework(int x) {
    phi[1] = 1;
    for (int i = 2; i <= x; i ++) {
        if (!nprm[i]) phi[i] = i - 1, prm[++ pcnt] = i;
        for (int j = 1; j <= pcnt; j ++) {
            if (i * prm[j] > x) break;
            nprm[i * prm[j]] = true;
            if (i % prm[j] == 0) {
                phi[i * prm[j]] = phi[i] * prm[j];
                break;
            }
            else phi[i * prm[j]] = phi[i] * (prm[j] - 1);
        }
    }
    for (int i = 2; i <= x; i ++)
      sphi[i] = sphi[i - 1] + phi[i];
}

ll f(int x) {
    ll res = 0;
    for (ll l = 1, r; l <= x; l = r + 1) {
        r = x / (x / l);
        res += (l + r) * (r - l + 1) / 2 * sphi[x / l];
    }
    return res;
}

int main() {
    scanf("%d", &n);
    prework(n + 10);
    printf("%lld\n", f(n));
    return 0;
}