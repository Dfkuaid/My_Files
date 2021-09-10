#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 500010;
const int INF = 0x3fffffff;

int n, a[N];

template <typename T>
inline T Min(const T a, const T b) {
    return a < b ? a : b;
}

inline int solve() {
    int k = 0, i = 0, j = 1;
    while (k < n && i < n && j < n) {
        // cout << i << " " << j << endl;
        if (a[(i + k) % n] == a[(j + k) % n]) k ++;
        else {
            if (a[(i + k) % n] < a[(j + k) % n])
              j = j + k + 1;
            else i = i + k + 1;
            k = 0; if (i == j) i ++;
        }
    }
    return Min(i, j);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i ++)
      scanf("%d", &a[i]);
    int st = solve();
    for (int i = 0; i < n; i ++)
      cout << a[(i + st) % n] << " ";
    return 0;
}