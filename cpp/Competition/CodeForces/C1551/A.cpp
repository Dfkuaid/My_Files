#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

int t, n, ans1, ans2;

int main() {
    scanf("%d", &t);
    while (t --) {
        scanf("%d", &n);
        ans1 = ans2 = n / 3;
        if (n % 3 == 1) ++ ans1;
        else if (n % 3 == 2) ++ ans2;
        printf("%d %d\n", ans1, ans2);
    }
    return 0;
}