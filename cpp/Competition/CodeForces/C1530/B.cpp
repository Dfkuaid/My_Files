#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

const int dir[8][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};

int t, n, m, mp[25][25];

inline bool check(int x, int y) {
    if (x <= 0 || x > n || y <= 0 || y > m) return 1;
    if (mp[x][y] == 1) return 0;
    return 1;
}

inline void change(int x, int y) {
    for (int i = 0; i < 8; i ++) {
        int dx = x + dir[i][0], dy = y + dir[i][1];
        if(!check(dx, dy)) return;
    } mp[x][y] = 1;
}

int main() {
    scanf("%d", &t);
    while (t --) {
        mset(mp, 0);
        scanf("%d%d", &n, &m);
        mp[1][1] = mp[1][m] = mp[n][1] = mp[n][m] = 1;
        for(int i = 2; i <= m - 1; i ++) change(1,i), change(n,i);
        for(int i = 2; i <= n - 1; i ++) change(i,1), change(i,m);
        for (int i = 1; i <= n; i ++) {
            for (int j = 1; j <= m; j ++)
              printf("%d", mp[i][j]);
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}