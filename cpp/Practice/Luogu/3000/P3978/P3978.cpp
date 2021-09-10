#include <bits/stdc++.h>
#define ll long long
#define db double
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

db n;

int main() {
    scanf("%lf", &n);
    printf("%.12lf", n * (n + 1) / (2 * (2 * n - 1)));
    return 0;
}