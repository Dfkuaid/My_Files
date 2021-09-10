#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

int t, n;

int main() {
    scanf("%d", &t);
    while (t --) {
        scanf("%d", &n);
        printf("%d %d\n", 2, n - 1);
    }
    return 0;
}