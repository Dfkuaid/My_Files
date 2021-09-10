#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

int a, b;

int main() {
    scanf("%d%d", &a, &b);
    printf("%lf", (double)((a - b) / 3.0) + (double)b);
    return 0;
}