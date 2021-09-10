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
    if (a > 0 && b == 0)
      printf("Gold");
    else if (a == 0 && b > 0)
      printf("Silver");
    else printf("Alloy");
    return 0;
}