#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 1010;
const int INF = 0x3f3f3f3f;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int n, rst, cnt; char s[N][N];

int main() {
    read(n); rst = 6, cnt = 0;
    for (int i = 1; i <= n; ++ i) scanf("%s", s[i] + 1);
    for (int i = 1; i <= n; ++ i)
      for (int j = 1; j + 5 <= n; ++ j) {
          rst = 6, cnt = 0;
          for (int k = 0; k <= 5; ++ k) {
              if (s[i][j + k] == '.') {
                  if (cnt < 2) ++ cnt, -- rst;
                  else break;
              } else -- rst;
              if (!rst) {puts("Yes"); return 0;}
          }
      }
    for (int i = 1; i <= n; ++ i)
      for (int j = 1; j + 5 <= n; ++ j) {
          rst = 6, cnt = 0;
          for (int k = 0; k <= 5; ++ k) {
              if (s[j + k][i] == '.') {
                  if (cnt < 2) ++ cnt, -- rst;
                  else break;
              } else -- rst;
              if (!rst) {puts("Yes"); return 0;}
          }
      }
    for (int i = 1; i + 5 <= n; ++ i)
      for (int  j = 1; j + 5 <= n; ++ j) {
          rst = 6, cnt = 0;
          for (int k = 0; k <= 5; ++ k) {
              if (s[i + k][j + k] == '.') {
                  if (cnt < 2) ++ cnt, -- rst;
                  else break;
              } else -- rst;
              if (!rst) {puts("Yes"); return 0;}
          }
      }
    for (int i = n; i - 5 >= 1; -- i)
      for (int  j = 1; j + 5 <= n; ++ j) {
          rst = 6, cnt = 0;
          for (int k = 0; k <= 5; ++ k) {
              if (s[i - k][j + k] == '.') {
                  if (cnt < 2) ++ cnt, -- rst;
                  else break;
              } else -- rst;
              if (!rst) {puts("Yes"); return 0;}
          }
      }
    puts("No"); return (0 - 0);
}
