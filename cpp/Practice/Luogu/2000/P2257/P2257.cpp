#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 10000100;
const int INF = 0x3fffffff;

int mu[N], prm[N], pcnt, nprm[N], smu[N], ssmu[N];
int qs[N][2], T, lit;
ll ans[N];

template <typename T>
inline T Max(const T a, const T b) {
    return a > b ? a : b;
} 

template <typename T>
inline T Min(const T a, const T b) {
    return a < b ? a : b;
}

void prework(int x) {
    mu[1] = 1;
    for (int i = 2; i <= x; i ++) {
        if (!nprm[i]) {
            prm[++ pcnt] = i;
            mu[i] = -1;
        }
        for (int j = 1; j <= pcnt; j ++) {
            if (prm[j] * i > x) break;
            nprm[prm[j] * i] = true;
            if (i % prm[j]) mu[i * prm[j]] = -mu[i];
            else break;
        }
    }
    for (int i = 1; i <= pcnt; i ++)
      for (int j = 1; j * prm[i] <= x; j ++)
        smu[j * prm[i]] += mu[j];
    for (int i = 1; i <= x; i ++)
      ssmu[i] = ssmu[i - 1] + smu[i];
}

int main() {
    scanf("%d", &T);
    for (int i = 1; i <= T; i ++) {
        scanf("%d%d", &qs[i][0], &qs[i][1]);
        lit = Max(lit, Max(qs[i][0], qs[i][1]));
    }
    prework(lit + 10);
    for (int i = 1; i <= T; i ++) {
        int lt = Min(qs[i][0], qs[i][1]);
        int n = qs[i][0], m = qs[i][1];
        for (int l = 1, r; l <= lt; l = r + 1) {
            r = Min(n / (n / l), m / (m / l));
            ans[i] += (ll)(ssmu[r] - ssmu[l - 1]) * (ll)(n / l) * (ll)(m / l);
        }
    }
    for (int i = 1; i <= T; i ++)
      printf("%lld\n", ans[i]);
    return 0;
}