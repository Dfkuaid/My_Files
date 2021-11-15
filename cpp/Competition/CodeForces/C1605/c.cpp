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

int t, n; char s[N];

void MAIN() {
    read(n); scanf("%s", s + 1);
    for (int i = 1; i <= n - 1; ++ i)
      if (s[i] == 'a' && s[i + 1] == 'a') {
          puts("2"); return;
      }
    for (int i = 1; i <= n - 2; ++ i)
      if (s[i] == 'a' && s[i + 2] == 'a') {
          puts("3"); return;
      }
    for (int i = 1; i <= n - 3; ++ i)
      if (s[i] == 'a' && s[i + 3] == 'a' && s[i + 1] != s[i + 2]) {
          puts("4"); return;
    }
    for (int i = 1; i <= n - 6; ++ i)
      if (s[i] == 'a' && s[i + 3] == 'a' 
              && s[i + 6] == 'a' && s[i + 1] != s[i + 4]) {
          puts("7"); return;
    }
    puts("-1");
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(t); while (t --) MAIN(); return 0;
}
