#define DEBUG
#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 1010;
const int INF = 0x3fffffff;

int n, m, mp[N][N], vis[N][N], null_p;
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

void explore(int k, int x, int y) {
    vis[x][y] = 1;
    if (!(~mp[x][y])) {++ null_p; return;}
    if (mp[x][y] == k ^ 1) return;
    for (int i = 0; i < 4; ++ i)
      if (!vis[x + dir[i][0]][y + dir[i][1]])
        explore(k, x + dir[i][0], y + dir[i][1]);
}

void do_kill(int k, int x, int y) {
    mp[x][y] = -1, vis[x][y] = 0;
    for (int i = 0; i < 4; ++ i)
      if (mp[x + dir[i][0]][y + dir[i][1]] == k)
        do_kill(k, x + dir[i][0], y + dir[i][1]);
      else vis[x + dir[i][0]][y + dir[i][1]] = 0;
}

bool try_kill(int k, int x, int y) {
    null_p = 0; explore(k, x, y);
    if (!null_p) {do_kill(k, x, y); return true;}
    else {mset(vis, 0); return false;}
}

bool check_foul(int k, int x, int y) {
    if (~mp[x][y]) {return true;} mp[x][y] = k;
    for (int i = 0; i < 4; ++ i)
      if (mp[x + dir[i][0]][y + dir[i][1]] == (k ^ 1))
        try_kill(k ^ 1, x + dir[i][0], y + dir[i][1]);
    if (try_kill(k, x, y)) return true;
    else return false;
}

bool check_win(int x, int y) {
    int i = x - 1, j = y, res = 0;
    while (i && mp[i][y] == mp[x][y]) -- i, ++ res;
    i = x + 1;
    while (i <= 1000 && mp[i][y] == mp[x][y]) ++ i, ++ res;
    if (++ res >= m) return true; else j = y - 1, res = 0;
    while (j && mp[x][j] == mp[x][y]) -- j, ++ res;
    j = y + 1;
    while (j <= 1000 && mp[x][j] == mp[x][y]) ++ j, ++ res;
    if (++ res >= m) return true; else i = x - 1, j = y - 1, res = 0;
    while (i && j && mp[i][j] == mp[x][y]) -- i, -- j, ++ res;
    i = x + 1, j = y + 1;
    while (i <= 1000 && j <= 1000 && mp[i][j] == mp[x][y]) ++ i, ++ j, ++ res;
    if (++ res >= m) return true; else i = x - 1, j = y + 1, res = 0;
    while (i && j <= 1000 && mp[i][j] == mp[x][y]) -- i, ++ j, ++ res;
    i = x + 1, j = y - 1;
    while (i <= 1000 && j && mp[i][j] == mp[x][y]) ++ i, -- j, ++ res;
    if (++ res >= m) return true;
    return false;
}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    mset(mp, -1); scanf("%d%d", &n, &m); 
    for (int i = 1; i <= n; ++ i) {
        int x, y; scanf("%d%d", &x, &y);
        if (check_foul(i & 1, x, y)) {
            printf("illegal"); return 0;
        }
        if (check_win(x, y)) {
            if (i & 1) printf("Alice %d", i);
            else printf("Bob %d", i);
            return 0;
        }
    }
    printf("draw");
    return 0;
}