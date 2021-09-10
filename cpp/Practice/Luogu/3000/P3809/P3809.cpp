#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 1000010;
const int INF = 0x3fffffff;

char s[N];
int sa[N], t[N], t2[N], c[N], n;

template <typename T>
inline T Max(const T &a, const T &b) {
    return a > b ? a : b;
}

inline void build_sa(int m) {
    int i, *x = t, *y = t2;
    for (i = 0; i < m; ++ i) c[i] = 0;
    for (i = 0; i < n; ++ i) c[x[i] = s[i]] ++;
    for (i = 1; i < m; ++ i) c[i] += c[i - 1];
    for (i = n - 1; i >= 0; i --) sa[-- c[x[i]]] = i;
    for (int k = 1; k <= n; k <<= 1) {
        int p = 0;
        for (i = n - k; i < n; i ++) y[p ++] = i;
        for (i = 0; i < n; i ++) if (sa[i] >= k)
          y[p ++] = sa[i] - k;
        for (i = 0; i < m; ++ i) c[i] = 0;
        for (i = 0; i < n; ++ i) c[x[y[i]]] ++;
        for (i = 1; i < m; ++ i) c[i] += c[i - 1];
        for (i = n - 1; i >= 0; i --)
          sa[-- c[x[y[i]]]] = y[i];
        swap(x, y); p = 1; x[sa[0]] = 0;
        for (i = 1; i < n; ++ i)
          x[sa[i]] = y[sa[i-1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k] ? p - 1 : p ++;
        if (p >= n) break;
        m = p;
    }
}

int main() {
    scanf("%s", s);
    n = strlen(s);
    build_sa(128);
    for (int i = 0; i < n; i ++)
      cout << sa[i] + 1 << " ";
    return 0;
}