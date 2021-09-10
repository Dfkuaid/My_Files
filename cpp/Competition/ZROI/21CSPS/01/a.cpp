#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

int n, t[N][2], cnt, len, tlen, lst;

int main() {
    scanf("%d", &n);
    t[len = 1][1] = 1;
    for (int i = 2; i <= n; ++ i) {
        tlen = 0, lst = 0, cnt = 0;
        for (int j = 1; j <= len; ++ j) {
            if (j != 1 && t[j][(i - 1) % 2] != lst) {
                t[++ tlen][i % 2] = cnt;
                t[++ tlen][i % 2] = lst; cnt = 0;
            }
            lst = t[j][(i - 1) % 2]; ++ cnt;
        }
        t[++ tlen][i % 2] = cnt;
        t[++ tlen][i % 2] = lst;
        len = tlen;
    }
    for (int i = 1; i <= len; ++ i)
      printf("%d", t[i][n % 2]);
    return 0;
}