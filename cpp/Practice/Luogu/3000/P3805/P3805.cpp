#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 23000010;
const int INF = 0x3fffffff;

int len, ans= -1, p[N];
char s[N];

template <typename T>
inline T Min(const T a, const T b) {
    return a < b ? a : b;
}

template <typename T>
inline T Max(const T a, const T b) {
    return a > b ? a : b;
}

inline void input() {
    s[len ++] = '$', s[len ++] = '#';
    while (cin >> s[len]) s[++ len] = '#', ++ len;
    s[len ++] = '^', s[len] = '\0';
}

inline void Manacher() {
    int id = 0, mx = 0;
    for (int i = 0; i < len; i ++) {
        if (i < mx) p[i] = Min(p[2 * id - i], mx - i);
        else p[i] = 1;
        while (s[i - p[i]] == s[i + p[i]]) p[i] ++;
        if (mx < i + p[i]) id = i, mx = i + p[i];
        ans = Max(ans, p[i] - 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); input();
    Manacher(); cout << ans;
    return 0;
}