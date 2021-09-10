#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 10000010;
const int INF = 0x3fffffff;

int n, nprm[N], prm[N], pcnt;
ll phi[N], sphi[N], res;

void prework(int x) {
    phi[1] = 1;
    for (int i = 2; i <= x; i ++) {
        if (!nprm[i]) phi[i] = i - 1, prm[++ pcnt] = i;
        for (int j = 1; j <= pcnt; j ++) {
            if (prm[j] * i > x) break;
            nprm[prm[j] * i] = true;
            if (!(i % prm[j])) {
                phi[i * prm[j]] = phi[i] * prm[j];
                break;
            }
            phi[i * prm[j]] = phi[i] * (prm[j] - 1);
        }
    }
    for (int i = 2; i <= n; i ++)
      sphi[i] = sphi[i - 1] + phi[i];
}

int main() {
    scanf("%d", &n);
    prework(n);
    for (int i = 1; i <= pcnt; i ++)
      res += 2 * sphi[n / prm[i]];
    res += pcnt;
    printf("%lld", res);
    return 0;
}