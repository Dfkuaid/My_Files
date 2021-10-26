#define LOCAL
#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 500010;
const int INF = 0x3f3f3f3f;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T Max(T a, T b) {return a > b ? a : b;}
template <typename T> inline T Min(T a, T b) {return a < b ? a : b;}

struct Status {int id, a, b, c, d;};
struct Block {int col[4], val[4], sum;} block[N];

int t, n, vis[5][5][5][5], f[N][40], ans, scnt[N]; char s[N];

Status status[2][40];

inline void reset() {
    mset(f, -INF); ans = -INF; mset(scnt, 0);
}

inline int get_col(char c) {
    return (c == 'B') ? 0 : ((c == 'G') ? 1 : ((c == 'R') ? 2 : 3));
}

inline int get_val(int col, int sum, int x) {
    if (col == 0) return sum - x;
    else if (col == 1) return sum + x;
    else if (col == 2) return sum * x;
    else if (x > 0) return sum / x;
    else return 0;
}

void get_status(int k, int icol[], int val) {
    if (val < -1e9) return;
    Status tmp; tmp.a = icol[0], tmp.b = icol[1], tmp.c = icol[2], tmp.d = icol[3];
    if (!vis[icol[0]][icol[1]][icol[2]][icol[3]]) tmp.id = ++ scnt[k];
    else tmp.id = vis[icol[0]][icol[1]][icol[2]][icol[3]];
    f[k][tmp.id] = Max(f[k][tmp.id], val);
    if (!vis[icol[0]][icol[1]][icol[2]][icol[3]]) {
        status[k & 1][scnt[k]] = tmp;
        vis[icol[0]][icol[1]][icol[2]][icol[3]] = tmp.id;
    }
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(t);
    while (t --) {
        read(n); reset();
        for (int i = 1; i <= n; ++ i) {
            scanf("%s", s + 1);
            block[i].col[0] = get_col(s[1]); block[i].val[0] = s[2] - '0';
            block[i].col[1] = get_col(s[5]); block[i].val[1] = s[6] - '0';
            block[i].col[2] = get_col(s[3]); block[i].val[2] = s[4] - '0';
            block[i].col[3] = get_col(s[7]); block[i].val[3] = s[8] - '0';
            block[i].sum = block[i].val[0] + block[i].val[1];
            block[i].sum += block[i].val[2] + block[i].val[3];
        }
        int col[4]; col[0] = 0, col[1] = 0, col[2] = 0, col[3] = 0;
        for (int i = 0; i < 4; ++ i) ++ col[block[1].col[i]];
        mset(vis, 0); get_status(1, col, 0);
        for (int i = 2; i <= n; ++ i) {
            mset(vis, 0);
            for (int j = 1; j <= scnt[i - 1]; ++ j) {
                Status k = status[(i - 1) & 1][j];
                col[0] = k.a, col[1] = k.b, col[2] = k.c, col[3] = k.d;
                get_status(i, col, f[i - 1][j] - block[i].sum);
                for (int l = 0; l < 4; ++ l) if (col[block[i].col[l]]) {
                    int val = get_val(block[i].col[l], block[i].sum, block[i].val[l]);
                    int tval = f[i - 1][j];
                    -- col[block[i].col[l]], ++ col[block[i].col[l ^ 1]];
                    get_status(i, col, val + tval);
                    ++ col[block[i].col[l]], -- col[block[i].col[l ^ 1]];
                }
            }
        }
        for (int i = 1; i <= scnt[n]; ++ i) ans = Max(ans, f[n][i]);
        printf("%d\n", ans);
    }
    return 0;
}
