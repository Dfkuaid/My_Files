#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

struct Point {
    int x, y;

    inline Point() {x = y = 0;}
    inline Point(int _x, int _y) {x = _x, y = _y;}

    inline bool operator < (const Point b) const {
        return x == b.x ? y < b.y : x < b.x;
    }
};

int a, b, c, d;
int dir[8][2] = {
    {1, 2}, {2, 1}, {-1, 2}, {1, -2},
    {-1, -2}, {-2, -1}, {2, -1}, {-2, 1}
};

priority_queue <Point> q;

int main() {
    read(a), read(b), read(c), read(d);
    for (int i = 0; i < 8; ++ i)
      q.push((Point){a + dir[i][0], b + dir[i][1]});
    for (int i = 0; i < 8; ++ i)
      q.push((Point){c + dir[i][0], d + dir[i][1]});
    Point lst = q.top(), now; q.pop();
    while (q.size()) {
        now = q.top(); q.pop();
        if (lst.x == now.x && lst.y == now.y) {
            puts("Yes"); return 0;
        }
        lst = now;
    }
    puts("No"); return 0;
}
