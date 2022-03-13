#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 400010;
const int INF = 0x3f3f3f3f;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

struct Person {int x, y, dir;} p[N];

int n; char s[N];

inline bool cmp(Person a, Person b) {
    return a.y == b.y ? a.x < b.x : a.y < b.y;
}

int main() {
    read(n);
    for (int i = 1; i <= n; ++ i)
      read(p[i].x), read(p[i].y);
    scanf("%s", s + 1);
    for (int i = 1; i <= n; ++ i)
      if (s[i] == 'L') p[i].dir = 0;
      else p[i].dir = 1;
    sort(p + 1, p + n + 1, cmp);
    int now = 1, lst = -1, lt = 0, rt = 0;
    while (now <= n) {
        if (p[now].y != lst) lt = rt = 0, lst = p[now].y;
        if (p[now].dir) ++ rt;
        else if (rt) {puts("Yes"); return 0;}
        ++ now;
    }
    puts("No"); return (0 - 0);
}
