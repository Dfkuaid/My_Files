#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

ll t, n, num[3];

int main() {
    scanf("%lld", &t);
    while (t --) {
        num[0] = num[1] = num[2] = 0;
        scanf("%lld", &n);
        if (n <= 6) {
            printf("%lld\n", (ll)15);
            continue;
        }
        num[0] = n / 6; n %= 6;
        if (n == 1 || n == 2)
          -- num[0], ++ num[1];
        else if (n == 3 || n == 4)
          -- num[0], ++ num[2];
        else if (n == 5) ++ num[0];
        printf("%lld\n", num[0] * 15 + num[1] * 20 + num[2] * 25);
    }
    return 0;
}