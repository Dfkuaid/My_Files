#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 1000010;
const int INF = 0x3fffffff;

int t, n, ans;
char s1[N], s2[N];

int main() {
    scanf("%d", &t);
    while (t --) {
        scanf("%d%s%s", &n, s1 + 1, s2 + 1);
        for (int i = 1; i <= n; ++ i)
          if (s2[i] - '0' == 1) {
              if (s1[i] - '0' == 0) ++ ans;
              else {
                  if (i - 1 > 0 && s1[i - 1] - '0' == 1)
                    ++ ans, s1[i - 1] = '0';
                  else if (i + 1 <= n && s1[i + 1] - '0' == 1)
                    ++ ans, s1[i + 1] = '0';
              }
          }
        printf("%d\n", ans); ans = 0;
    }
    return 0;
}