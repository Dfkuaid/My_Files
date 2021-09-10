#include <iostream>
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define pii pair <int, int>
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 10;
const int INF = 0x3fffffff;
const int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int n, k, mp[10][10], ans;

void solve(int x, int y) {
    queue <pii > q;
    
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++ i)
      for (int j = 1; j <= n; ++ j) {
          char c; cin >> c;
          if (c == '#') mp[i][j] = 1;
      }
    for (int i = 1; i <= n; ++ i)
      for (int j = 1; j <= n; ++ j)
        if (mp[i][j]) continue;
        else solve(i, j);
    return 0;
}