#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 2000010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

ll n, s, a[N];

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(s);
    if (s == 0) {
        for (int i = 1; i <= n; ++ i)
          printf("%d\n", i);
        return 0;
    } else if (s == 1) {
        if (n < 2) printf("SPFA is dead!\n");
        else {
            printf("2\n1\n");
            for (int i = 3; i <= n; ++ i)
              printf("%d\n", i);
        }
        
    } else if (s == 2) {
        if (n < 3) printf("SPFA is dead!\n");
        else {
            printf("3\n1\n2\n");
            for (int i = 4; i <= n; ++ i)
              printf("%d\n", i);
        }
    } else {
        if (s > n * (n - 1) / 2) {puts("SPFA is dead!\n"); return 0;}
        ll rest = n * (n - 1) / 2 - s;
        for (int i = 1; i < n; ++ i) a[i] = i + 1; a[n] = 1;
        if (rest == 1) {
            if (n & 1) a[1] = 3, a[2] = 1, a[n] = 2;
            else swap(a[1], a[n]);
        } else {
            for (int i = n - 1; i; -- i) if (rest >= i)
              rest -= i, swap(a[i], a[i - 1]);
        }
        for (int i = 1; i <= n; ++ i) printf("%lld ", a[i]);
    }
    return 0;
}
