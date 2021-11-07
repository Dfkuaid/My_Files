/*Haven't finished.*/
#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;
const int sd[5] = {1, 2, 4, 10, 20};

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int t, n, cnt[5], x[N];

inline bool cmp(int a, int b) {return a > b;}

void MAIN() {
    read(n);
    for (int i = 0; i < 5; ++ i) read(cnt[i]);
    for (int i = 1; i <= n; ++ i) read(x[i]);
    sort(x + 1, x + n + 1, cmp);
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(t); while (t --) {MAIN();} return 0;
}
