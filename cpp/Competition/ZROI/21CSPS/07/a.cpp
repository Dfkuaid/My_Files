#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 10010;
const ll LIMIT = 1e15;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int n, m, T, sum; ll len[N];
char s[2][N];

inline void prework() {
    for (int i = 1; i <= 50; ++ i) {
        len[i] = 1ll << (i - 1);
        if (len[i] > LIMIT) len[i] = LIMIT + 1;
        if (LIMIT / sum < len[i]) len[i] = LIMIT + 1;
        else len[i] = len[i] * sum;
    }
    for (int i = 51; i <= 935; ++ i) len[i] = LIMIT + 1;;
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(m), read(T); sum = n + m;
    scanf("%s%s", s[0] + 1, s[1] + 1); prework();
    while (T --) {
        ll x; read(x); int op = 0, now = 935;
        while (now > 1) {
            if (x > len[now - 1])
              op ^= 1, x -= len[now - 1];
            now --;
        }
        if (op == 1) {if (x > m) x -= m, op ^= 1;}
        else {if (x > n) x -= n, op ^= 1;}
        putchar(s[op][x]); putchar('\n');
    }
    return 0;
} 
