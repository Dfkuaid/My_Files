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

int a, b, c, d, nprm[N], prm[N], pcnt;

inline void euler(int LMT) {
    for (int i = 2; i <= LMT; ++ i) {
        if (!nprm[i]) prm[++ pcnt] = i;
        for (int j = 1; j <= pcnt; ++ j) {
            if (i * prm[j] > LMT) break;
            nprm[i * prm[j]] = 1;
            if (!(i % prm[j])) break;
        }
    }
}

inline bool check(int x) {
    for (int i = 1; i <= pcnt; ++ i)
      if (prm[i] - x >= c && prm[i] - x <= d)
        return false;
    return true;
}

int main() {
    read(a), read(b), read(c), read(d); euler(200);
    for (int i = a; i <= b; ++ i)
      if (check(i)) {printf("Takahashi"); return 0;}
    printf("Aoki"); return 0;
}
