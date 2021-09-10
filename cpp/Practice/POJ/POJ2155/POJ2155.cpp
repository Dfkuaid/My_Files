#include <iostream>
#include <cstdio>
#include <cstring>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 1010;
const int INF = 0x3fffffff;

int t, bit[N][N], n, q;

void add(int x, int y, int c) {
    int ty = y;
    while (x <= n) {
        y = ty;
        while (y <= n) bit[x][y] += c, y += y & -y;
        x += x & -x;
    }
}

inline void modify(int xa, int ya, int xb, int yb, int c) {
    add(xa, ya, c); add(xb + 1, yb + 1, c);
    add(xa, yb + 1, -c); add(xb + 1, ya, -c);
}

int query(int x, int y) {
    int res = 0, ty = y;
    while (x) {
        y = ty;
        while (y) res += bit[x][y], y -= y & -y;
        x -= x & -x;
    }
    return res;
}

int main() {
    scanf("%d", &t);
    while (t --) {
        mset(bit, 0); scanf("%d%d", &n, &q);
        while (q --) {
            char op; int xa, ya, xb, yb;
            cin >> op;
            if (op == 'C') {
                scanf("%d%d%d%d", &xa, &ya, &xb, &yb);
                modify(xa, ya, xb, yb, 1);
            } else {
                scanf("%d%d", &xa, &ya);
                printf("%d\n", query(xa, ya) & 1);
            }
        }
        printf("\n");
    }
    return 0;
}