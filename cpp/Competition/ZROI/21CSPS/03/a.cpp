#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

int rcnt, a[8], res, mx;

int main() {
    for (int i = 1; i <= 7; ++ i) {
        scanf("%d", &a[i]);
        res += a[i] * i;
        if (a[i]) mx = i;
    }
    res += a[1] * mx;
    printf("%d", res);
    return 0;
}