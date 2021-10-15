#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 250010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

struct Block {int col[4], val[4];} blocks[N];

int t, n; ll f[N][4][4][4][4]; char s[N];

inline void get_col(char c) {
    return (c == 'B') ? 0 : ((c == 'G') ? 1 : ((c == 'R') ? 2 : 3));
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(t);
    while (t --) {
        read(n);
        for (int i = 1; i <= n; ++ i) {
            scanf("%s", s + 1);
            for (int j = 1; j <= 8; j += 2) {
                blocks[i].col[j / 2] = get_col(s[j]);
                blocks[i].val[j / 2] = s[j + 1] - '0';
            }
        }
    }
    return 0;
}
