#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 20000100;
const int INF = 0x3fffffff;

int lena, lenb, z[N], p[N];
ll ans1, ans2;
string a, b;

template <typename T>
inline T Max(const T a, const T b) {
    return a > b ? a : b;
}

template <typename T>
inline T Min(const T a, const T b) {
    return a < b ? a : b;
}

inline void z_func() {
    for (int i = 1, l = 0, r = 0; i < lenb; ++ i) {
        if (i <= r && z[i - l] < r - i + 1)
          z[i] = z[i - l];
        else {
            z[i] = Max(0, r - i + 1);
            while (i + z[i] < lenb && b[z[i]] == b[i + z[i]])
              ++ z[i];
        }
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
}

inline void p_func() {
    for (int i = 1, l = 0, r = 0; i < lena; ++ i) {
        if (i <= r && z[i - l] < r - i + 1)
          p[i] = z[i - l];
        else {
            p[i] = Max(0, r - i + 1);
            while (i + p[i] < lena && b[p[i]] == a[i + p[i]])
              ++ p[i];
        }
        if (i + p[i] - 1 > r) l = i, r = i + p[i] - 1;
    }
    while (p[0] < Min(lena, lenb) && b[p[0]] == a[p[0]]) p[0] ++;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> a >> b;
    lena = a.length();
    lenb = b.length();
    z_func(); z[0] = lenb;
    p_func();
    for (int i = 0; i < lenb; i ++)
      ans1 ^= ((ll)(i + 1) * (z[i] + 1));
    for (int i = 0; i < lena; i ++)
      ans2 ^= ((ll)(i + 1) * (p[i] + 1));
    printf("%lld\n%lld", ans1, ans2);
    return 0;
}