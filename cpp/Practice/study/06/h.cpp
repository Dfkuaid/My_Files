#define LOCAL
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
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

int n, num[N], seq[N], lst[N], cnt;

vector <int> v;
vector <int>::iterator it;

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n);
    for (int i = 2; i <= n; ++ i) read(num[i]);
    for (int i = 1; i <= n; ++ i) v.push_back(i);
    for (int i = n; i > 1; -- i) {
        for (it = v.begin(), cnt = 1; it != v.end(); ++ it, ++ cnt)
          if (cnt == num[i] + 1) {
              seq[i] = (*it); v.erase(it); break;
          }
    }
    seq[1] = (*v.begin());
    for (int i = 1; i <= n; ++ i) printf("%d\n", seq[i]);
    return 0;
}
