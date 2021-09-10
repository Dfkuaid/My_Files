#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 2010;
const int INF = 0x3fffffff;

int mp[N][N], n, m, l[N][N][2], c[N][N][2], lcnt[N], ccnt[N];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i)
      for (int j = 1; j <= m; ++ j)
        scanf("%d", mp[i][j]);
    for (int i = 1; i <= n; ++ i)
      for (int j = 1; j <= m; ++ j)
        if (j == 1 || (!mp[i][j - 1] && mp[i][j]))
          l[i][++ lcnt[i]][0] = j, l[i][lcnt[i]][1] = j;
        else l[i][ccnt[i]][1] = j;
    
    return 0;
}