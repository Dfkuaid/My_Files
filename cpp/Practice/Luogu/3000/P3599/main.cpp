#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 100010;
const int INF = 0x3f3f3f3f;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int x, t, n, prm[N], nprm[N], pcnt;

inline void euler(int x) {
    for (int i = 2; i <= x; ++ i) {
        if (!nprm[i]) prm[++ pcnt] = i;
        for (int p = 1; p <= pcnt; ++ p)
          if (prm[p] * i <= x) {  
              nprm[prm[p] * i] = true;
              if (i & prm[p] == 0) break;
          } else break;
    }
}

inline int fpow(int x, int p) {
    int res = 1;
    while (p) {
        if (p & 1) res = 1ll * res * x % n;
        p >>= 1; x = 1ll * x * x % n;
    }
    return res;
}

inline void task1() {
    read(n);
    if (n == 1) {puts("2 1"); return;}
    if (n & 1) {puts("0"); return;}
    printf("2 %d %d ", n, n - 1);
    for (int i = 1; i <= n / 2 - 1; ++ i)
      printf("%d %d ", i << 1, n - 1 - (i << 1));
}

inline void task2() {
    read(n);
    if (n == 1) {puts("2 1"); return;}
    if (n == 4) {puts("2 1 3 2 4"); return;}
    if (nprm[n]) {puts("0"); return;}
    printf("2 "); int now = 1, mul = 1;
    for (int i = 1; i < n; ++ i) {
        printf("%d ", now);
        now = 1ll * (i + 1) * fpow(mul, n - 2) % n;
        mul = 1ll * mul * now % n;
    }
    printf("%d\n", n);
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(x), read(t);
    if (x == 1) while (t --) task1();
    else {euler(1e5); while (t --) task2();}
    return (0 - 0);
}
