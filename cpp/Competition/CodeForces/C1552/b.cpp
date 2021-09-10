#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

int t, n, a[5][N], res;

int main() {
    scanf("%d", &t);
    while (t --) {
        scanf("%d", &n); res = 1;
        for (int i = 1; i <= n; ++ i)
          for (int j = 0; j < 5; ++ j)
            scanf("%d", &a[j][i]);
        for (int i = 2; i <= n; ++ i) {
            int cnt = 0;
            for (int j = 0; j < 5; ++ j)
              if (a[j][i] < a[j][res]) ++ cnt;
            if (cnt > 2) res = i;
        }
        for(int i = 1; i <= n; i++) {
            int cnt = 0;
            if (i == res) continue;
            for (int j = 0; j < 5; ++ j)
              if (a[j][i] < a[j][res]) ++ cnt;
            if(cnt > 2) {res = -1; break;}
        }
        printf("%d\n", res);
    }
    return 0;
}