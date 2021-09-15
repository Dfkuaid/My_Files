#define DEBUG
#include <bits/stdc++.h>
#define ll long long
#define pii pair <int, int>
#define mpr(a, b) make_pair(a, b)
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 1010;
const int M = 5000010;
const int INF = 0x3fffffff;

struct Node {int ls, rs, val;} p[M];

int n, m, mp[N][N], cnt, rt[N];
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

queue <pii> q;

inline int id(int x, int y) {return (x - 1) * 1000 + y;}

inline void pushup(int k) {
    p[k].val = max(p[p[k].ls].val, p[p[k].rs].val);
}

void modify(int k, int l, int r, int x, int c) {
    if (l == r) {p[k].val += c; return;}
    int mid = (l + r) >> 1;
    if (x <= mid) modify(p[k].ls, l, mid, x, c);
    else modify(p[k].rs, mid + 1, r, x, c);
    pushup(k);
}

void add(int &k, int l, int r, int x, int c) {
    if (!k) k = ++ cnt;
    if (l == r) {p[k].val = c; return;}
    int mid = (l + r) >> 1;
    if (x <= mid) add(p[k].ls, l, mid, x, c);
    else add(p[k].rs, mid + 1, r, x, c);
    pushup(k);
}

int tree_merge(int x, int y) {
    if (!x || !y) return x | y;
    p[x].ls = tree_merge(p[x].ls, p[y].ls);
    p[x].rs = tree_merge(p[x].rs, p[y].rs);
    pushup(x); return x;
}

struct DSU {
    int f[N * N], siz[N * N];
    
    inline void init(int x) {
        for (int i = 1; i <= x; ++ i)
          f[i] = i, siz[i] = 1;
    }
    
    inline int find(int x) {
        while (x != f[x]) x = f[x] = f[f[x]];
        return x;
    }

    inline void merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        if (siz[x] > siz[y]) swap(x, y);
        siz[y] += siz[x]; f[x] = y;
        rt[y] = tree_merge(rt[y], rt[x]);
    }
} dsu;

void del(int op, int x, int y) {
    q.push(mpr(x, y));
    while (q.size()) {
        pii now = q.front(); q.pop();
        int now_id = id(now.first, now.second);
        mp[now.first][now.second] = 0;
        dsu.f[now_id] = now_id; rt[now_id] = 0;
        for (int i = 0; i < 4; ++ i)
          if (mp[now.first + dir[i][0]][now.second + dir[i][1]] == op)
            q.push(mpr(now.first + dir[i][0], now.second + dir[i][1]));
    }
}

bool check_foul(int op, int x, int y) {
    if (mp[x][y]) return true; mp[x][y] = op + 1;
    if (mp[x + 1][y]) modify(rt[dsu.find(id(x + 1, y))], 1, 1e6, id(x + 1, y), -1);
    if (mp[x - 1][y]) modify(rt[dsu.find(id(x - 1, y))], 1, 1e6, id(x - 1, y), -1);
    if (mp[x][y + 1]) modify(rt[dsu.find(id(x, y + 1))], 1, 1e6, id(x, y + 1), -1);
    if (mp[x][y - 1]) modify(rt[dsu.find(id(x, y - 1))], 1, 1e6, id(x, y - 1), -1);
    for (int i = 0; i < 4; ++ i)
      if (mp[x + dir[i][0]][y + dir[i][1]] == (op ^ 1) + 1)
        if (p[rt[id(x + dir[i][0], y + dir[i][1])]].val == 0)
          del((op ^ 1) + 1, x + dir[i][0], y + dir[i][1]);
    int null_cnt = 0;
    for (int i = 0; i < 4; ++ i)
      if (!mp[x + dir[i][0]][y + dir[i][1]]) ++ null_cnt;
    add(rt[id(x, y)], 1, 1e6, id(x, y), null_cnt);
    for (int i = 0; i < 4; ++ i) {
        if (mp[x + dir[i][0]][y + dir[i][1]] == mp[x][y])
          dsu.merge(id(x, y), id(x + dir[i][0], y + dir[i][1]));
    }
    if (!p[rt[dsu.find(id(x, y))]].val) return true;
    return false;
}

bool check_win(int x, int y) {
    int i = x - 1, j = y, res = 0;
    while (i && mp[i][y] == mp[x][y]) -- i, ++ res;
    i = x + 1;
    while (i <= 1000 && mp[i][y] == mp[x][y]) ++ i, ++ res;
    if (++ res >= m) return true;
    j = y - 1, res = 0;
    while (j && mp[x][j] == mp[x][y]) -- j, ++ res;
    j = y + 1;
    while (j <= 1000 && mp[x][j] == mp[x][y]) ++ j, ++ res;
    if (++ res >= m) return true;
    i = x - 1, j = y - 1, res = 0;
    while (i && j && mp[i][j] == mp[x][y]) -- i, -- j, ++ res;
    i = x + 1, j = y + 1;
    while (i <= 1000 && j <= 1000 && mp[i][j] == mp[x][y]) ++ i, ++ j, ++ res;
    if (++ res >= m) return true;
    i = x - 1, j = y + 1, res = 0;
    while (i && j <= 1000 && mp[i][j] == mp[x][y]) -- i, ++ j, ++ res;
    i = x + 1, j = y - 1;
    while (i <= 1000 && j && mp[i][j] == mp[x][y]) ++ i, -- j, ++ res;
    if (++ res >= m) return true;
    return false;
}

int main() {
    #ifdef DEBUG
        freopen("ex_FIR2.in", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    scanf("%d%d", &n, &m); dsu.init(1e6);
    for (int i = 1; i <= n; ++ i) {
        int x, y; scanf("%d%d", &x, &y);
        if (check_foul(i & 1, x, y)) {
            printf("illegal"); return 0;
        }
        if (check_win(x, y)) {
            if (i & 1) {
                printf("Alice %d", i);
                return 0;
            } else {
                printf("Bob %d", i);
                return 0;
            }
        }
    }
    printf("draw");
    return 0;
}