#define LOCAL
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

char s[N]; int cnt[N], tot = 1, fac[N];

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    scanf("%s", s + 1); fac[0] = 1;
    for (int i = 1; i <= 3; ++ i) fac[i] = fac[i - 1] * i;
    for (int i = 1; i <= 3; ++ i) cnt[s[i] - 'a' + 1] ++;
    for (int i = 1; i <= 26; ++ i) tot *= fac[cnt[i]];
    printf("%d", fac[3] / tot); return 0;
}
