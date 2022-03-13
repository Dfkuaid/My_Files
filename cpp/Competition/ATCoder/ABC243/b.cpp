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

int n, a[N], b[N], ans1, ans2;

int main() {
   read(n);
   for (int i = 1; i <= n; ++ i) read(a[i]);
   for (int i = 1; i <= n; ++ i) read(b[i]);
   for (int i = 1; i <= n; ++ i) ans1 += (a[i] == b[i]);
   for (int i = 1; i <= n; ++ i)
     for (int j = 1; j <= n; ++ j) {
         if (i == j) continue;
         if (a[i] == b[j]) ++ ans2;
     }
   printf("%d\n%d\n", ans1, ans2);
   return (0 - 0);
}
